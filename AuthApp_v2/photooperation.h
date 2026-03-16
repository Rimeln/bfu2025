#pragma once
#include <QString>

class User; // forward

class PhotoOperation {
public:
    virtual ~PhotoOperation() = default;
    virtual void execute(User* user, const QString& photoPath = "") = 0;
};
