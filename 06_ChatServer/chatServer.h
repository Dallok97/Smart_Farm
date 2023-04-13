#ifndef CHATSERVER_H
#define CHATSERVER_H

//#include "GPIO_PWM_API.h"
#include "I2C_API.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer(QObject *parent=0);

private slots:
    void readyRead();
    void disconnected();
    void sendUserList();

signals:
    void clients_signal(int users);
    void message_signal(QString msg);

protected:
    void incomingConnection(int socketfd);

private:
    QSet<QTcpSocket*> clients;
    QMap<QTcpSocket*,QString> users;
    //GPIO_LED *LED12;
    I2C_PCA9685 *RGB_LED[3];
    I2C_PCA9685 *SERVO[2];
    I2C_SHT20 *SHT20;
};

#endif // CHATSERVER_H
