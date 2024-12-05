#include "ElaDxgiManagerPrivate.h"
#ifdef Q_OS_WIN
#if USE_ELA_SCREEN
ElaDxgiManagerPrivate::ElaDxgiManagerPrivate(QObject* parent)
    : QObject{parent}
{
}

ElaDxgiManagerPrivate::~ElaDxgiManagerPrivate()
{
}

ElaDxgiScreenPrivate::ElaDxgiScreenPrivate(QObject* parent)
    : QObject{parent}
{
}

ElaDxgiScreenPrivate::~ElaDxgiScreenPrivate()
{
}
#endif // USE_ELA_SCREEN
#endif // Q_OS_WIN
