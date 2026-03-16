#include "photofilehandler.h"

#include <QDir>
#include <QFile>
#include <QMimeDatabase>
#include <QFileInfo>

PhotoFileHandler::PhotoFileHandler(QString dir)
{
    path = dir;
    QDir().mkdir(dir);
}

bool PhotoFileHandler::load()
{
    return true;
}

bool PhotoFileHandler::save()
{
    return true;
}

bool PhotoFileHandler::copyPhoto(const QString& src, QString& dest)
{
    QMimeDatabase db;

    auto mime = db.mimeTypeForFile(src);

    if(!mime.name().startsWith("image"))
        return false;

    QFileInfo info(src);

    dest = path + "/" + info.fileName();

    return QFile::copy(src, dest);
}

bool PhotoFileHandler::deletePhoto(const QString& file)
{
    return QFile::remove(file);
}
