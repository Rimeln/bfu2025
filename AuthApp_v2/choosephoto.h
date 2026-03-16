#pragma once
#include "photooperation.h"
#include "photofilehandler.h"
#include <QInputDialog>

class ChoosePhoto : public PhotoOperation {
public:
    PhotoFileHandler* handler;
    ChoosePhoto(PhotoFileHandler* h): handler(h){}
    void execute(User* user, const QString& photoPath = "") override {
        if(handler->userPhotos.isEmpty()){
            Logger::warning("Нет доступных фото для выбора");
            return;
        }

        bool ok;
        QString chosen = QInputDialog::getItem(nullptr, "Выбрать фото",
                                               "Фото", handler->userPhotos, 0, false, &ok);
        if(ok && !chosen.isEmpty()){
            user->pathToAvatar = chosen;
            Logger::info("Выбрано фото: ", chosen.toStdString());
        }
    }
};
