#include "widget.h"
#include "ui_widget.h"
#include "chatServer.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new ChatServer();
    connect(server, SIGNAL(clients_signal(int)), this,
                    SLOT(slot_clients(int)));
    connect(server, SIGNAL(message_signal(QString)), this,
                    SLOT(slot_message(QString)));

    server->listen(QHostAddress::Any, 35000);
}

void Widget::slot_clients(int users)
{
    QString str = QString("접속자수 : %1").arg(users);
    ui->label->setText(str);
}

void Widget::slot_message(QString msg)
{
    ui->textEdit->append(msg);
}

Widget::~Widget()
{
    delete ui;
}
