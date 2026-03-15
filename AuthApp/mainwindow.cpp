#include "mainwindow.h"
#include "Logger.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(400, 400);

    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    loadUsers();

    loginPage = new QWidget;
    QVBoxLayout *loginLayout = new QVBoxLayout;

    loginUsername = new QLineEdit;
    loginPassword = new QLineEdit;
    loginPassword->setEchoMode(QLineEdit::Password);

    QPushButton *loginBtn = new QPushButton("Войти");
    QPushButton *toRegisterBtn = new QPushButton("Регистрация");

    loginLayout->addWidget(new QLabel("Логин"));
    loginLayout->addWidget(loginUsername);
    loginLayout->addWidget(new QLabel("Пароль"));
    loginLayout->addWidget(loginPassword);
    loginLayout->addWidget(loginBtn);
    loginLayout->addWidget(toRegisterBtn);

    loginPage->setLayout(loginLayout);
    stack->addWidget(loginPage);

    registerPage = new QWidget;
    QVBoxLayout *regLayout = new QVBoxLayout;

    regUsername = new QLineEdit;
    regPassword = new QLineEdit;
    regPassword->setEchoMode(QLineEdit::Password);

    QPushButton *registerBtn = new QPushButton("Зарегистрироваться");
    QPushButton *backBtn = new QPushButton("Назад");

    regLayout->addWidget(new QLabel("Новый логин"));
    regLayout->addWidget(regUsername);
    regLayout->addWidget(new QLabel("Новый пароль"));
    regLayout->addWidget(regPassword);
    regLayout->addWidget(registerBtn);
    regLayout->addWidget(backBtn);

    registerPage->setLayout(regLayout);
    stack->addWidget(registerPage);

    profilePage = new QWidget;
    QVBoxLayout *profileLayout = new QVBoxLayout;

    photoLabel = new QLabel;
    QPixmap placeholder(100,100);
    placeholder.fill(Qt::gray);
    photoLabel->setPixmap(placeholder);
    photoLabel->setFixedSize(100,100);

    profileLabel = new QLabel("Добро пожаловать!");

    QPushButton *logoutBtn = new QPushButton("Выйти");

    profileLayout->addWidget(photoLabel, 0, Qt::AlignCenter);
    profileLayout->addWidget(profileLabel, 0, Qt::AlignCenter);
    profileLayout->addWidget(logoutBtn);

    profilePage->setLayout(profileLayout);
    stack->addWidget(profilePage);

    connect(loginBtn, &QPushButton::clicked, this, &MainWindow::loginUser);
    connect(toRegisterBtn, &QPushButton::clicked, this, &MainWindow::goToRegister);
    connect(registerBtn, &QPushButton::clicked, this, &MainWindow::registerUser);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::goToLogin);
    connect(logoutBtn, &QPushButton::clicked, this, &MainWindow::logoutUser);

    stack->setCurrentWidget(loginPage);
}

QString MainWindow::hashPassword(const QString &password)
{
    QByteArray hash = QCryptographicHash::hash(
        password.toUtf8(),
        QCryptographicHash::Sha256
        );
    return hash.toHex();
}

void MainWindow::loadUsers()
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(":");
        if (parts.size() == 2)
            users[parts[0]] = parts[1];
    }
    file.close();

    Logger::info("Пользователи загружены");
}

void MainWindow::saveUsers()
{
    QFile file("users.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (auto it = users.begin(); it != users.end(); ++it)
        out << it.key() << ":" << it.value() << "\n";

    file.close();
}

void MainWindow::registerUser()
{
    Logger::info("Нажата кнопка: Зарегистрироваться");

    QString username = regUsername->text();
    QString password = regPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поля не должны быть пустыми");
        Logger::warning("Попытка регистрации с пустыми полями");
        return;
    }

    if (users.contains(username)) {
        QMessageBox::warning(this, "Ошибка", "Пользователь уже существует");
        Logger::warning("Регистрация существующего пользователя: ", username.toStdString());
        return;
    }

    users[username] = hashPassword(password);
    saveUsers();

    Logger::info("Новый пользователь зарегистрирован: ", username.toStdString());

    QMessageBox::information(this, "Успех", "Регистрация успешна");
    stack->setCurrentWidget(loginPage);
}

void MainWindow::loginUser()
{
    Logger::info("Нажата кнопка: Войти");

    QString username = loginUsername->text();
    QString password = loginPassword->text();

    if (!users.contains(username)) {
        QMessageBox::warning(this, "Ошибка", "Пользователь не существует");
        Logger::error("Попытка входа несуществующего пользователя: ", username.toStdString());
        return;
    }

    if (users[username] != hashPassword(password)) {
        QMessageBox::warning(this, "Ошибка", "Неверный пароль");
        Logger::error("Неверный пароль для пользователя: ", username.toStdString());
        return;
    }

    profileLabel->setText("Добро пожаловать, " + username + "!");
    stack->setCurrentWidget(profilePage);

    Logger::info("Пользователь вошел: ", username.toStdString());
}

void MainWindow::logoutUser()
{
    Logger::info("Нажата кнопка: Выйти");

    stack->setCurrentWidget(loginPage);
    Logger::info("Пользователь вышел из системы");
}

void MainWindow::goToRegister()
{
    Logger::info("Нажата кнопка: Перейти к регистрации");
    stack->setCurrentWidget(registerPage);
}

void MainWindow::goToLogin()
{
    Logger::info("Нажата кнопка: Назад к авторизации");
    stack->setCurrentWidget(loginPage);
}
