#include "userfilehandler.h"

#include <QFile>
#include <QTextStream>

UserFileHandler::UserFileHandler(QString p)
{
    path = p;
}

bool UserFileHandler::load()
{
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if(parts.size() >= 3)
        {
            User u(parts[0], parts[1], parts[2]);
            users[parts[0]] = u;
        }
    }

    file.close();
    return true;
}

bool UserFileHandler::save()
{
    QFile file(path);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    for(auto &u : users)
    {
        out << u.username << ","
            << u.passwordHash << ","
            << u.avatarPath << "\n";
    }

    file.close();
    return true;
}
