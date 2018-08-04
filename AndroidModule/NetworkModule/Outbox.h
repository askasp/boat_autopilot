
#ifndef OUTBOX_H
#define OUTBOX_H
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <signal.h>
#include <thread>
#include <QDebug>
#include <mutex>
#include <QString>
#include <string>


class Outbox : public QObject
{
    Q_OBJECT
    public:
        explicit Outbox(QObject *parent = nullptr):QObject(parent){
        }
        virtual ~Outbox(){
        };
        std::mutex OutboxMutex;
        Q_INVOKABLE void updatePsi_D(int psi_D){
            OutboxMutex.lock();
            tmp = QString::number(psi_D);
            Psi_d = tmp.toUtf8().constData();
            OutboxMutex.unlock();
        }
        Q_INVOKABLE void updateState(QString state){
            OutboxMutex.lock();
            State = state.toUtf8().constData();
            OutboxMutex.unlock();
        }

        std::string State = "OFF";
        std::string Psi_d = "0";
        QString tmp;
};


#endif
