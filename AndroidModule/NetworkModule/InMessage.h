
#ifndef INBOX_H
#define INBOX_H
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


class  InMessage: public QObject
{
Q_OBJECT
   Q_PROPERTY(int getPsi READ getPsi WRITE dummywrite NOTIFY messageChanged)
    public:
    explicit InMessage(QObject *parent = nullptr):QObject(parent){
    }
        virtual ~InMessage(){
        };
        std::mutex InboxMutex;
        int Psi;
        int SteeringAngle;
        int someting;

        void dummywrite(int k){
        }

        int getPsi(){
            return Psi;
        }
        Q_INVOKABLE int getSteeringAngle(){
            return SteeringAngle;
        }

        Q_INVOKABLE void notifyQML(){
            emit messageChanged();
        }


signals:
      void messageChanged();
    };




#endif
