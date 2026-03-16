#pragma once
#include "photooperation.h"
#include "photofilehandler.h"
#include <QFile>

class DeletePhoto : public PhotoOperation {
public:
    PhotoFileHandler* handler;
    DeletePhoto(PhotoFileHandler* h): handler(h){}
    void execute(User* user, const QString& photoPath = "") override {
        if(QFile::exists(photoPath))
            QFile::remove(photoPath);
        handler->userPhotos.removeAll(photoPath);
        Logger::info("Фото удалено: ", photoPath.toStdString());
    }
};
