#pragma once
#include "photooperation.h"
#include "photofilehandler.h"
#include <QMimeDatabase>
#include <QFileInfo>

class UploadPhoto : public PhotoOperation {
public:
    PhotoFileHandler* handler;
    UploadPhoto(PhotoFileHandler* h): handler(h){}

    void execute(User* user, const QString& photoPath = "") override {
        if(handler->userPhotos.size() >= 4){
            Logger::warning("Нельзя загрузить более 4 фото");
            return;
        }

        QMimeDatabase db;
        QString mime = db.mimeTypeForFile(photoPath).name();
        if(!mime.startsWith("image/")){
            Logger::error("Недопустимый формат файла: ", photoPath.toStdString());
            return;
        }

        QFileInfo fi(photoPath);
        QString dest = handler->baseDir + "/" + user->username + "_" + fi.fileName();
        QFile::copy(photoPath, dest);
        handler->userPhotos.append(dest);
        Logger::info("Фото загружено: ", dest.toStdString());
    }
};
