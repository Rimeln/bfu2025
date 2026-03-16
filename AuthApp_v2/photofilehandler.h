#pragma once
#include "filehandler.h"
#include <QStringList>
#include <QFile>
#include <QDir>
#include "logger.h"

class PhotoFileHandler : public FileHandler {
public:
    QString baseDir = "photos"; // папка для фото
    QStringList userPhotos;     // список фото текущего пользователя

    PhotoFileHandler() {
        QDir dir(baseDir);
        if(!dir.exists()) dir.mkpath(".");
    }

    bool load() override { return true; }
    bool save() override { return true; }

    bool addPhoto(const QString& filePath){
        if(userPhotos.size() >= 4){
            Logger::warning("Попытка загрузки более 4 фото");
            return false;
        }
        QFileInfo fi(filePath);
        QString dest = baseDir + "/" + fi.fileName();
        if(!QFile::copy(filePath, dest)) return false;
        userPhotos.append(dest);
        Logger::info("Фото загружено: ", dest.toStdString());
        return true;
    }

    bool deletePhoto(const QString& filePath){
        if(QFile::exists(filePath))
            QFile::remove(filePath);
        userPhotos.removeAll(filePath);
        Logger::info("Фото удалено: ", filePath.toStdString());
        return true;
    }

    QStringList getPhotos() const { return userPhotos; }
};
