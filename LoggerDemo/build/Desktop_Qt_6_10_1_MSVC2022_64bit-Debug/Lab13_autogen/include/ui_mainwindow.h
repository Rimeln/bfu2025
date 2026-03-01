/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *workingButton;
    QPushButton *brokenButton;
    QPushButton *clearButton;
    QTextEdit *logTextEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        workingButton = new QPushButton(centralwidget);
        workingButton->setObjectName("workingButton");
        workingButton->setGeometry(QRect(100, 110, 201, 61));
        workingButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4CAF50;  /* \320\227\320\265\320\273\320\265\320\275\321\213\320\271 */\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"}"));
        brokenButton = new QPushButton(centralwidget);
        brokenButton->setObjectName("brokenButton");
        brokenButton->setGeometry(QRect(510, 110, 201, 61));
        brokenButton->setStyleSheet(QString::fromUtf8(""));
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName("clearButton");
        clearButton->setGeometry(QRect(310, 220, 191, 29));
        logTextEdit = new QTextEdit(centralwidget);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setGeometry(QRect(30, 300, 741, 271));
        logTextEdit->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        workingButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\260\320\262\320\270\320\273\321\214\320\275\320\260\321\217 \320\272\320\275\320\276\320\277\320\272\320\260", nullptr));
        brokenButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\276\320\274\320\260\320\275\320\275\320\260\321\217 \320\272\320\275\320\276\320\277\320\272\320\260", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\273\320\276\320\263\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
