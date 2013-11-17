#include "session.h"
#include <QDebug>

Session::Session(QString token, QString card, QObject *parent) :
    _token(token),
    _card(card),
    QObject(parent)
{
    qDebug() << "Session started";
    return;
}

Session::~Session() {
    qDebug() << "Session closed";
    return;
}

void Session::setToken(QString token) {
    qDebug() << "Token changed";
    _token = token;
    return;
}
