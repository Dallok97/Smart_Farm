#include <QtWidgets>
#include <QRegExp>
#include "chatServer.h"
#include <QDebug>

//const int ledPin12[] = {23,24};
const int RGBLedPin[] = {0,1,2};
const int servoPin[2] ={3,4};

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{
    //LED12 = new GPIO_LED(ledPin12[0]);
    for(int i=0;i<3; i++)
        RGB_LED[i] = new I2C_PCA9685(PCA9685_I2C_ADDR, RGBLedPin[i]);
    for(int i=0;i<2; i++)
        SERVO[i] = new I2C_PCA9685(PCA9685_I2C_ADDR, servoPin[i]);
    SHT20 = new I2C_SHT20(SHT20_I2C_ADDR);
}

void ChatServer::incomingConnection(int socketfd)
{
    qDebug() << Q_FUNC_INFO;

    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    emit clients_signal(clients.count());

    QString str;
    str = QString("새로운 접속자: %1")
            .arg(client->peerAddress().toString());

    emit message_signal(str);

    connect(client, SIGNAL(readyRead()), this,
                    SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this,
                    SLOT(disconnected()));
}

void ChatServer::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();       
        QString str;
        str = QString("Read line: %1").arg(line);
        emit message_signal(str);

        QRegExp meRegex("^/me:(.*)$");
        if(meRegex.indexIn(line) != -1)
        {
            QString user = meRegex.cap(1);
            users[client] = user;
            foreach(QTcpSocket *client, clients)
            {
                client->write(QString("서버: %1 접속")
                              .arg(user).toUtf8());
            }

            sendUserList();
        }
        else if(users.contains(client))
        {
            QString message = line;
            QString user = users[client];
            if(message=="temp")
            {
                int m_temp;
                m_temp = SHT20->measureTemp();
                message.append(":");
                message.append(QString ::number(m_temp));
            }
            else if(message=="humi")
            {
                int m_humi;
                m_humi = SHT20->measureHumi();
                message.append(":");
                message.append(QString ::number(m_humi));
            }
            else if(line=="SUNLIGHT_ON")
            {
                RGB_LED[0]->setPwm(4096);
                /*for(int i=0;i<3; i++)
                {
                    switch (i)
                    {
                    case 0:
                        RGB_LED[0]->setPwm(4096);
                        break;
                    case 1:
                        RGB_LED[1]->setPwm(0);
                        break;
                    case 2:
                        RGB_LED[2]->setPwm(1);
                        break;

                    }
                }
                */
            }
            else if(line=="SUNLIGHT_OFF")
            {
                for(int i=0;i<3; i++)
                {
                    RGB_LED[i]->setPwm(0);
                }
            }
            else if(line=="WATER_ON")
            {
                SERVO[0]->setPwm(512);
            }
            else if(line=="WATER_OFF")
            {
                SERVO[0]->setPwm(102);
            }
            else if(line=="OPEN_DOOR")
            {
                SERVO[1]->setPwm(512);
            }
            else if(line=="CLOSE_DOOR")
            {
                SERVO[1]->setPwm(100);
            }

            QString str;
            str = QString("유저명: %1, 메시지: %2")
                    .arg(user).arg(message);
            emit message_signal(str);

            foreach(QTcpSocket *otherClient, clients)
                otherClient->write(QString(user+":"+message+"\n")
                                        .toUtf8());
        }
    }
}

void ChatServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();

    QString str;
    str = QString("접속자 연결 종료 :: %1")
            .arg(client->peerAddress().toString());

    emit message_signal(str);

    clients.remove(client);

    emit clients_signal(clients.count());

    QString user = users[client];
    users.remove(client);

    sendUserList();
    foreach(QTcpSocket *client, clients)
        client->write(QString("서버: %1 접속종료").arg(user).toUtf8());
}

void ChatServer::sendUserList()
{
    QStringList userList;
    foreach(QString user, users.values())
        userList << user;

    foreach(QTcpSocket *client, clients)
        client->write(QString("/유저:" + userList.join(",") + "\n")
                       .toUtf8());
}
