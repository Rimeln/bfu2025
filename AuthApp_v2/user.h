#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>

class User
{
public:

    QString username;
    QString passwordHash;
    QString avatarPath;

    QStringList photos;

    User(){}

    User(QString u, QString p, QString avatar = "")
        : username(u), passwordHash(p), avatarPath(avatar)
    {}
};

#endif
