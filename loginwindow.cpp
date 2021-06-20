#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include<QSqlQuery>
#include<QShortcut>
#include <QMessageBox>


extern QSqlDatabase db;
extern MainWindow *mainWindow;


LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    QShortcut *key=new QShortcut(QKeySequence(Qt::Key_Return),this);//创建一个快捷键"Key_Return"键
    connect(key,SIGNAL(activated()),this,SLOT(LoginSlot()));//连接到指定槽函数

    QObject::connect(ui->btn_exit,&QPushButton::clicked,[=](){
        this->close();
    });
    QObject::connect(ui->btn_login, SIGNAL(clicked()), this,
                     SLOT(LoginSlot()));
}


LoginWindow::~LoginWindow()
{
    delete ui;
}


QVariant getUserIdVarient(QString username, QString password){
    QSqlQuery query(db);
    query.prepare("SELECT ID FROM USERS WHERE USERNAME=:username AND PASSWORD=:password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();
    query.first();
    qDebug() << query.value("id");
    return query.value("id");
}

void LoginWindow::LoginSlot(){
    if(ui->et_account->text()==nullptr){
        QMessageBox::warning(this, "提示","请填写用户名");
        ui->et_account->setFocus();
        return ;
    }
    else if(ui->et_password->text()==nullptr){
        QMessageBox::warning(this, "提示","请填写密码");
        ui->et_password->setFocus();
        return ;
    }

    QString account = ui->et_account->text();
    QString pwd = ui->et_password->text();

    QVariant uidVarient = getUserIdVarient(account, pwd);
    if(uidVarient != QVariant::Invalid){
        QMessageBox::information(this, "欢迎", "欢迎您，"+account+"。");
        mainWindow->initUserInfo(uidVarient.toInt());
        this->close();
    }
    else{
        QMessageBox::critical(this, "错误", "账号或密码错误！");
        ui->et_password->clear();
    }
}
