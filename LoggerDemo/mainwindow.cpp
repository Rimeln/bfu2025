
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Logger.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QScrollBar>
#include <QFileDialog>
#include <QFont>
#include <QPalette>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->workingButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    padding: 15px;"
        "    font-weight: bold;"
        "    border-radius: 8px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #3d8b40;"
        "}"
        );

    ui->brokenButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #F44336 ;"
        "    color: white;"
        "    border: none;"
        "    padding: 15px;"
        "    font-weight: bold;"
        "    border-radius: 8px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #D32F2F;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #B71C1C;"
        "}"
        );

    ui->clearButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0b7dda;"
        "}"
        );

    setWindowTitle("Лаба 3 Логирование");

    Logger::init(true, "application.log");

    Logger::info("Приложение запущено");
    Logger::info("Главное окно создано");

    setupConnections();

    logTimer = new QTimer(this);
    connect(logTimer, &QTimer::timeout, this, &MainWindow::updateLogDisplay);
    logTimer->start(500); // Обновляем каждые 500 мс

    ui->logTextEdit->setFont(QFont("Courier New", 10));

    Logger::info("=======================================");
    Logger::info("==== =  =  ====  =     =     ====  ====");
    Logger::info("==== =  =  =     =     =     =  =  ====");
    Logger::info("==== ====  ====  =     =     =  =  ====");
    Logger::info("==== =  =  =     =     =     =  =  ====");
    Logger::info("==== =  =  ====  ====  ====  ====  ====");
    Logger::info("=======================================");
    Logger::info("Добро пожаловать в демонстрацию Logger!");
    Logger::info("Нажимайте кнопки для генерации логов");
}

MainWindow::~MainWindow()
{
    Logger::info("Приложение закрывается");
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->workingButton, &QPushButton::clicked,
            this, &MainWindow::onWorkingButtonClicked);

    connect(ui->brokenButton, &QPushButton::clicked,
            this, &MainWindow::onBrokenButtonClicked);

    connect(ui->clearButton, &QPushButton::clicked,
            this, &MainWindow::onClearButtonClicked);
}

void MainWindow::onWorkingButtonClicked()
{
    Logger::info("--- Нажата ПРАВИЛЬНАЯ кнопка ---");

    try {
        executeCorrectCode();

        QMessageBox::information(this, "Успех",
                                 "Правильный код выполнен успешно!\n"
                                 "Все операции отработали корректно.\n"
                                 "Проверьте вывод в логах.");

        Logger::info("Правильная кнопка: выполнение завершено успешно");

    } catch (const std::exception& e) {
        Logger::error("Неожиданная ошибка в правильном коде: ", e.what());
        QMessageBox::critical(this, "Ошибка",
                              QString("Неожиданная ошибка: %1").arg(e.what()));
    }
}

void MainWindow::onBrokenButtonClicked()
{
    Logger::warning("=== Нажата СЛОМАННАЯ кнопка ===");
    Logger::warning("Выполняется код с ошибками...");

    try {
        executeBrokenCode();

        QMessageBox::warning(this, "Ошибка",
                             "Сломанный код выполнен.\n"
                             "Были сгенерированы ошибки в логах.\n");

        Logger::warning("Сломанная кнопка: выполнение завершено с ошибками");

    } catch (...) {
        Logger::fatal("Критическая ошибка в сломанном коде!");
    }
}

void MainWindow::executeCorrectCode()
{
    Logger::debug("Начало выполнения правильного кода");

    Logger::info("Математические операции");
    int a = 10;
    int b = 20;
    int sum = a + b;
    int product = a * b;
    Logger::info("Сумма: ", a, " + ", b, " = ", sum);
    Logger::info("Произведение: ", a, " * ", b, " = ", product);

    Logger::info("Работа с вектором");
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    int total = 0;
    for (size_t i = 0; i < numbers.size(); i++) {
        total += numbers[i];
        Logger::debug("Добавляем элемент [", i, "]: ", numbers[i]);
    }
    Logger::info("Общая сумма элементов вектора: ", total);

    Logger::info("Преобразование типов");
    std::string numberStr = "123";
    try {
        int number = std::stoi(numberStr);
        Logger::info("Успешно преобразовано в число: ", number);
    } catch (const std::exception& e) {
        Logger::error("Ошибка преобразования: ", e.what());
        throw;
    }

    Logger::info("Работа с динамической памятью");
    int* array = new int[5]{10, 20, 30, 40, 50};
    Logger::debug("Выделена память для массива из 5 элементов");

    int arraySum = 0;
    for (int i = 0; i < 5; i++) {
        arraySum += array[i];
    }
    Logger::info("Сумма элементов массива: ", arraySum);

    delete[] array;
    Logger::debug("Память успешно освобождена");

    Logger::debug("Правильный код выполнен полностью");
}

void MainWindow::executeBrokenCode()
{
    Logger::debug("Начало выполнения сломанного кода");

    Logger::info("Попытка деления на ноль");
    try {
        int x = 100;
        int y = 0;
        if (y == 0) {
            throw std::runtime_error("Деление на ноль запрещено");
        }
        int result = x / y;
        Logger::info("Результат деления: ", result);
    } catch (const std::exception& e) {
        Logger::error("Ошибка деления: ", e.what());
    }

    Logger::info("Выход за границы массива");
    try {
        std::vector<int> vec(3);
        for (size_t i = 0; i <= vec.size(); i++) { // Ошибка: <= вместо <
            if (i == vec.size()) {
                throw std::out_of_range("Выход за границы массива");
            }
            vec[i] = i * 10;
        }
        Logger::info("Массив заполнен");
    } catch (const std::exception& e) {
        Logger::error("Ошибка границ массива: ", e.what());
    }

    Logger::info("Некорректное преобразование типа");
    try {
        std::string invalid = "abc123xyz";
        int number = std::stoi(invalid);
        Logger::info("Преобразованное число: ", number);
    } catch (const std::exception& e) {
        Logger::error("Ошибка преобразования типа: ", e.what());
    }

    Logger::info("Работа с нулевым указателем");
    try {
        int* ptr = nullptr;
        if (ptr == nullptr) {
            throw std::runtime_error("Попытка работы с нулевым указателем");
        }
        *ptr = 42;
        Logger::info("Значение записано");
    } catch (const std::exception& e) {
        Logger::error("Ошибка указателя: ", e.what());
    }

    Logger::warning("Сломанный код выполнен (с ошибками)");
}

void MainWindow::onClearButtonClicked()
{
    clearLogFile();
    updateLogDisplay();
    QMessageBox::information(this, "Информация", "Лог-файл очищен");
    Logger::info("Пользователь очистил лог-файл");
}

void MainWindow::updateLogDisplay()
{
    QString logContent = getLogFileContent();

    QScrollBar* scrollBar = ui->logTextEdit->verticalScrollBar();
    bool atBottom = (scrollBar->value() == scrollBar->maximum());

    ui->logTextEdit->setPlainText(logContent);

    if (atBottom && scrollBar->maximum() > 0) {
        scrollBar->setValue(scrollBar->maximum());
    }
}

QString MainWindow::getLogFileContent()
{
    QFile file("application.log");
    if (!file.exists()) {
        return "Лог-файл не найден или пуст\n";
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QString content = stream.readAll();
        file.close();
        return content;
    }

    return "Не удалось открыть лог-файл\n";
}

void MainWindow::clearLogFile()
{
    QFile file("application.log");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "";
        file.close();
    }
}
