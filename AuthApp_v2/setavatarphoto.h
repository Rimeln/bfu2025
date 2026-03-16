#pragma once
#include "photooperation.h"
#include "mainwindow.h"

class SetAvatarPhoto : public PhotoOperation {
public:
    void execute(User* user, const QString& photoPath = "") override {
        user->pathToAvatar = photoPath;
        Logger::info("Аватар обновлён: ", photoPath.toStdString());
    }
};
