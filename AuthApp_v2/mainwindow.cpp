#include "mainwindow.h"
#include "logger.h"
#include "uploadphoto.h"
#include "deletephoto.h"
#include "setavatarphoto.h"
#include "choosephoto.h"

#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QCryptographicHash>
#include <QPixmap>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    resize(400, 500);
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    loadUsers();
    photoHandler = new PhotoFileHandler;

    // --- Login Page ---
    loginPage = new QWidget;
    QVBoxLayout* loginLayout = new QVBoxLayout;
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

    // --- Register Page ---
    registerPage = new QWidget;
    QVBoxLayout* regLayout = new QVBoxLayout;
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

    // --- Profile Page ---
    profilePage = new QWidget;
    QVBoxLayout* profileLayout = new QVBoxLayout;
    photoLabel = new QLabel;
    QPixmap placeholder(100,100); placeholder.fill(Qt::gray);
    photoLabel->setPixmap(placeholder); photoLabel->setFixedSize(100,100);
    profileLabel = new QLabel("Добро пожаловать!");
    QPushButton *logoutBtn = new QPushButton("Выйти");
    QPushButton *uploadBtn = new QPushButton("Загрузить фото");
    QPushButton *chooseBtn = new QPushButton("Выбрать фото");
    QPushButton *deleteBtn = new QPushButton("Удалить фото");
    QPushButton *setAvatarBtn = new QPushButton("Установить аватар");

    profileLayout->addWidget(photoLabel, 0, Qt::AlignCenter);
    profileLayout->addWidget(profileLabel, 0, Qt::AlignCenter);
    profileLayout->addWidget(uploadBtn);
    profileLayout->addWidget(chooseBtn);
    profileLayout->addWidget(deleteBtn);
    profileLayout->addWidget(setAvatarBtn);
    profileLayout->addWidget(logoutBtn);
    profilePage->setLayout(profileLayout);
    stack->addWidget(profilePage);

    // --- Connect slots ---
    connect(loginBtn, &QPushButton::clicked, this, &MainWindow::loginUser);
    connect(toRegisterBtn, &QPushButton::clicked, this, &MainWindow::goToRegister);
    connect(registerBtn, &QPushButton::clicked, this, &MainWindow::registerUser);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::goToLogin);
    connect(logoutBtn, &QPushButton::clicked, this, &MainWindow::logoutUser);

    UploadPhoto* uploadOp = new UploadPhoto(photoHandler);
    ChoosePhoto* chooseOp = new ChoosePhoto(photoHandler);
    DeletePhoto* deleteOp = new DeletePhoto(photoHandler);
    SetAvatarPhoto* setAvatarOp = new SetAvatarPhoto;

    connect(uploadBtn, &QPushButton::clicked, [=](){
        QString filePath = QFileDialog::getOpenFileName(this,"Выбрать фото");
        if(!filePath.isEmpty() && currentUser) uploadOp->execute(currentUser,filePath);
    });

    connect(chooseBtn, &QPushButton::clicked, [=](){
        if(currentUser) chooseOp->execute(currentUser);
        QPixmap pix(currentUser->pathToAvatar);
        if(!pix.isNull()) photoLabel->setPixmap(pix.scaled(100,100));
    });

    connect(deleteBtn, &QPushButton::clicked, [=](){
        if(currentUser) deleteOp->execute(currentUser,currentUser->pathToAvatar);
        QPixmap placeholder(100,100); placeholder.fill(Qt::gray);
        photoLabel->setPixmap(placeholder);
    });

    connect(setAvatarBtn, &QPushButton::clicked, [=](){
        if(currentUser) setAvatarOp->execute(currentUser,currentUser->pathToAvatar);
        QPixmap pix(currentUser->pathToAvatar);
        if(!pix.isNull()) photoLabel->setPixmap(pix.scaled(100,100));
    });

    stack->setCurrentWidget(loginPage);
}

QString MainWindow::hashPassword(const QString &password){
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex();
}

void MainWindow::loadUsers(){
    QFile file("users.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList parts = line.split(":");
        if(parts.size()==2) users[parts[0]] = parts[1];
    }
    file.close();
}

void MainWindow::saveUsers(){
    QFile file("users.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    for(auto it = users.begin(); it != users.end(); ++it)
        out << it.key() << ":" << it.value() << "\n";
    file.close();
}

void MainWindow::registerUser(){
    QString username = regUsername->text();
    QString password = regPassword->text();
    if(username.isEmpty() || password.isEmpty()){ QMessageBox::warning(this,"Ошибка","Поля пустые"); return;}
    if(users.contains(username)){ QMessageBox::warning(this,"Ошибка","Пользователь уже существует"); return;}
    users[username] = hashPassword(password);
    saveUsers();
    QMessageBox::information(this,"Успех","Регистрация успешна");
    stack->setCurrentWidget(loginPage);
}

void MainWindow::loginUser(){
    QString username = loginUsername->text();
    QString password = loginPassword->text();
    if(!users.contains(username)){ QMessageBox::warning(this,"Ошибка","Пользователь не найден"); return;}
    if(users[username]!=hashPassword(password)){ QMessageBox::warning(this,"Ошибка","Неверный пароль"); return;}
    currentUser = new User{username,""};
    profileLabel->setText("Добро пожаловать, "+username+"!");
    QPixmap placeholder(100,100); placeholder.fill(Qt::gray);
    photoLabel->setPixmap(placeholder);
    stack->setCurrentWidget(profilePage);
}

void MainWindow::logoutUser(){
    stack->setCurrentWidget(loginPage);
    delete currentUser;
    currentUser=nullptr;
}

void MainWindow::goToRegister(){ stack->setCurrentWidget(registerPage); }
void MainWindow::goToLogin(){ stack->setCurrentWidget(loginPage); }
