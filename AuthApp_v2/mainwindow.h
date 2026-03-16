#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include "photofilehandler.h"

struct User {
    QString username;
    QString pathToAvatar;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent=nullptr);

private slots:
    void registerUser();
    void loginUser();
    void logoutUser();
    void goToRegister();
    void goToLogin();

private:
    QStackedWidget *stack;
    QWidget *loginPage;
    QWidget *registerPage;
    QWidget *profilePage;

    QLineEdit *loginUsername;
    QLineEdit *loginPassword;
    QLineEdit *regUsername;
    QLineEdit *regPassword;

    QLabel *profileLabel;
    QLabel *photoLabel;

    QMap<QString, QString> users;
    User* currentUser = nullptr;

    PhotoFileHandler* photoHandler;

    QString hashPassword(const QString &password);
    void loadUsers();
    void saveUsers();
};
