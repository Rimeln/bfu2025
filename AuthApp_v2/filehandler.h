#pragma once
#include <QString>

class FileHandler {
public:
    virtual ~FileHandler() = default;
    virtual bool load() = 0;
    virtual bool save() = 0;
};
