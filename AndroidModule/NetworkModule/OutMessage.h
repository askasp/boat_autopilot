
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


class OutMessage : public QObject
{
    Q_OBJECT
    public:
        explicit OutMessage(QObject *parent = nullptr):QObject(parent){
        }
        virtual ~OutMessage(){
        };
        std::mutex OutboxMutex;
        Q_INVOKABLE void updatePsi_D(int psi_D){
            OutboxMutex.lock();
            tmp = QString::number(psi_D);
            Psi_d = tmp.toUtf8().constData();
            OutboxMutex.unlock();
        }
        Q_INVOKABLE void updateSteering_d(int steeringAngle_d){
            OutboxMutex.lock();
            tmp = QString::number(steeringAngle_d);
            SteeringAngle_d = tmp.toUtf8().constData();
            OutboxMutex.unlock();
        }
        Q_INVOKABLE void updateState(QString state){
            OutboxMutex.lock();
            State = state.toUtf8().constData();
            OutboxMutex.unlock();
        }

        Q_INVOKABLE void updateType(QString type){
            OutboxMutex.lock();
            Type = type.toUtf8().constData();
            OutboxMutex.unlock();
        }

        Q_INVOKABLE void updateStepperRotation(QString type){
            OutboxMutex.lock();
            StepperRotation = type.toUtf8().constData();
            OutboxMutex.unlock();
        }

        Q_INVOKABLE void updateCoordinates(double longtitude, double latitude){
            OutboxMutex.lock();
            tmp = QString::number(latitude);
            Latitude = tmp.toUtf8().constData();
            tmp = QString::number(longtitude);
            Longtitude = tmp.toUtf8().constData();
            OutboxMutex.unlock();
        }

        std::string State = "OFF";
        std::string Type = "Manual";
        std::string StepperRotation = "Hold";
        std::string SteeringAngle_d = "0";
        std::string Psi_d = "0";
        std::string Latitude = "0";
        std::string Longtitude ="0";
        QString tmp;
};


#endif
