#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPushButton>
#include <wiringPi.h>
#include <softPwm.h>

const int RGBLedPin[] = {0,1,2};
const int servoPin[2] ={3,4};

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);

    loginWidget = new LoginWidget();
    connect(loginWidget, SIGNAL(loginInfo(QString)),
            this,        SLOT(loginInfo(QString)));
    connect(ui->sayButton, &QPushButton::pressed,
            this,           &Widget::sayButton_clicked);
    /*
    connect(ui->pushButton_LED, &QPushButton::pressed,
            this,           &Widget::button_sender);
            */
    connect(ui->pushButton_LIG, &QPushButton::clicked,
            this,           &Widget::button_sender);
    connect(ui->pushButton_WIN, &QPushButton::clicked,
            this,           &Widget::button_sender);
    connect(ui->pushButton_WAT, &QPushButton::clicked,
            this,           &Widget::button_sender);



    loginWidget->show();

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()),
            this,   SLOT(readyRead()));
    connect(socket, SIGNAL(connected()),
            this,   SLOT(connected()));

    testthread = new TestThread(this);
    connect(testthread, SIGNAL(ThreadEnd()), this, SLOT(sender_temp()));


}
void Widget::loginInfo(QString name)
{
    qDebug() << Q_FUNC_INFO << name;
    ipAddr = "192.168.0.17";
    //ipAddr = addr;
    userName = name;
    socket->connectToHost(ipAddr, 35000);
    testthread->start();
}

void Widget::sayButton_clicked()
{
    QString message = ui->sayLineEdit->text().trimmed();

    if(!message.isEmpty())
    {
        socket->write(QString(message + "\n").toUtf8());
    }
    ui->sayLineEdit->clear();
    ui->sayLineEdit->setFocus();
}

void Widget::button_sender()
{
    if(sender()==ui->pushButton_LIG)
    {
        QPushButton *pushbuttonBox_RGB = {ui->pushButton_LIG};
        bool ButtonCheck=ui->pushButton_LIG->isChecked();


        if(ButtonCheck==true)
        {
        ui->pushButton_LIG->setIcon(QIcon(":/image/Checkbox_On.png"));
        socket->write(QString("SUNLIGHT_ON\n").toUtf8());
        }
        else if(ButtonCheck==false)
        {
        ui->pushButton_LIG->setIcon(QIcon(":/image/Checkbox_Off.png"));
        socket->write(QString("SUNLIGHT_OFF\n").toUtf8());
        }
     }
    if(sender()==ui->pushButton_WAT)
    {
        QPushButton *pushbuttonBox_RGB = {ui->pushButton_WAT};
        bool ButtonCheck=ui->pushButton_WAT->isChecked();


        if(ButtonCheck==true)
        {
        ui->pushButton_WAT->setIcon(QIcon(":/image/Checkbox_On.png"));
        socket->write(QString("WATER_ON\n").toUtf8());
        }
        else if(ButtonCheck==false)
        {
        ui->pushButton_WAT->setIcon(QIcon(":/image/Checkbox_Off.png"));
        socket->write(QString("WATER_OFF\n").toUtf8());
        }

    }
    if(sender()==ui->pushButton_WIN)
    {
        QPushButton *pushbuttonBox_RGB = {ui->pushButton_WIN};
        bool ButtonCheck=ui->pushButton_WIN->isChecked();


        if(ButtonCheck==true)
        {
        ui->pushButton_WIN->setIcon(QIcon(":/image/Checkbox_On.png"));
        socket->write(QString("OPEN_DOOR\n").toUtf8());
        }
        else if(ButtonCheck==false)
        {
        ui->pushButton_WIN->setIcon(QIcon(":/image/Checkbox_Off.png"));
        socket->write(QString("CLOSE_DOOR\n").toUtf8());
        }

    }
}
void Widget::connected()
{
    loginWidget->hide();
    this->window()->show();

    socket->write(QString("/me:" + userName + "\n").toUtf8());
}

void Widget::readyRead()
{
    while(socket->canReadLine())
    {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();
        QRegExp messageRegex("^([^:]+):(.*)$");

        if(messageRegex.indexIn(line) != -1)
        {
            QString user = messageRegex.cap(1);
            QString message = messageRegex.cap(2);
            if(message.contains("temp"))
            {
                QString value = message.remove(0,5);
                ui->lcdNumber_Temp_1->display(value);
            }
            if(message.contains("humi"))
            {
                QString value = message.remove(0,5);
                ui->lcdNumber_Humi_1->display(value);
            }
            ui->roomTextEdit->append("<b>"+user+"</b>: "+message);
        }
    }
}

Widget::~Widget()
{
    testthread->stop();
    delete ui;
}
void Widget::sender_temp(void)
{
    socket->write(QString("temp\n").toUtf8());
    socket->write(QString("humi\n").toUtf8());
}
