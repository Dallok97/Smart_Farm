#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include "loginwidget.h"
#include "testthread.h"
#include "I2C_API.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    I2C_PCA9685 *RGB_LED[3];
//    I2C_PCA9685 *SERVO[2];

private:
    Ui::Widget *ui;
    LoginWidget *loginWidget;

    QTcpSocket *socket;
    QString    ipAddr;
    QString    userName;

    TestThread *testthread;

private slots:
    void loginInfo(QString name);
    void sayButton_clicked();
    void connected();
    void readyRead();
    void button_sender();
    void sender_temp();
};

#endif // WIDGET_H
