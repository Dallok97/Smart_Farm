#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "chatServer.h"
#include "GPIO_PWM_API.h"
#include "I2C_API.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    ChatServer *server;
    GPIO_LED *LED12;
    I2C_PCA9685 *RGB_LED[3];
    I2C_PCA9685 *SERVO[2];
    I2C_SHT20 *SHT20;

private:
    Ui::Widget *ui;


private slots:
    void slot_clients(int users);
    void slot_message(QString msg);
};

#endif // WIDGET_H
