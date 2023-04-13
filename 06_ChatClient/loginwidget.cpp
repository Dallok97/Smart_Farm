#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::pressed,
            this, &LoginWidget::loginBtnClicked);
}

void LoginWidget::loginBtnClicked()
{
    //QString serverIp = ui->ipLineEdit->text().trimmed();
    QString serverIp = "192.168.0.17";
    //ui->ipLineEdit->text().remove();
    QString name = ui->nameLineEdit->text().trimmed();
    emit loginInfo(name);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
