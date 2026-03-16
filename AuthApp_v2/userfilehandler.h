#pragma once
#include "filehandler.h"
#include <QMap>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "logger.h"

class UserFileHandler : public FileHandler {
public:
    QString filePath;
    QMap<QString, QString> users; // username -> hashedPassword

    UserFileHandler(const QString& path) : filePath(path) {}

    bool load() override {
        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            QStringList parts = line.split(":");
            if(parts.size() == 2)
                users[parts[0]] = parts[1];
        }
        file.close();
        Logger::info("Пользователи загружены");
        return true;
    }

    bool save() override {
        QFile file(filePath);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream out(&file);
        for(auto it = users.begin(); it != users.end(); ++it)
            out << it.key() << ":" << it.value() << "\n";
        file.close();
        return true;
    }
};
