
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


class  Inbox: public QObject
{
Q_OBJECT
   Q_PROPERTY(int getPsi READ getPsi WRITE dummywrite NOTIFY inboxUpdated)
    public:
    explicit Inbox(QObject *parent = nullptr):QObject(parent){
    }
        virtual ~Inbox(){
        };
        std::mutex InboxMutex;
        int Psi;
        int SteeringAngle;
        bool isConnected;

        void dummywrite(int k){
        }

        int getPsi(){
            return Psi;
        }
        Q_INVOKABLE int getSteeringAngle(){
            return SteeringAngle;
        }
        Q_INVOKABLE bool IsConnected(){
            return isConnected;
        }

        Q_INVOKABLE void notifyQML(){
            emit inboxUpdated();
        }


signals:
      void inboxUpdated();
    };




#endif
