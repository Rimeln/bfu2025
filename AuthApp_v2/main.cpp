#include "mainwindow.h"
#include "logger.h"
#include <QApplication>

int main(int argc, char* argv[]){
    QApplication a(argc, argv);
    a.setStyle("Fusion");

    Logger::init(true,"logger.txt");
    Logger::info("Приложение запущено");

    MainWindow w;
    w.show();
    return a.exec();
}
