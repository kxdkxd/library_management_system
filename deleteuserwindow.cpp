#include "deleteuserwindow.h"
#include "ui_deleteuserwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>
#include <QDateTime>

extern QSqlDatabase db;

DeleteUserWindow::DeleteUserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeleteUserWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btn_del, SIGNAL(clicked()), this, SLOT(delUserSlot()));
}

DeleteUserWindow::~DeleteUserWindow()
{
    delete ui;
}

void DeleteUserWindow::delUserSlot(){
    if(ui->et_username->text()==nullptr){
        QMessageBox::warning(this,"提示","请输入用户名");
        return ;
    }
    if(ui->et_pwd->text()==nullptr){
        QMessageBox::warning(this,"提示","请输入密码");
        return ;
    }
    QSqlQuery query(db);
    query.prepare("SELECT ID FROM USERS WHERE USERNAME=:username AND PASSWORD=:userpwd");
    query.bindValue(":username", ui->et_username->text());
    query.bindValue(":userpwd", ui->et_pwd->text());
    query.exec();
    if(!query.first()){
        QMessageBox::warning(this, "通知", "查无此用户");
        return;
    }
    int userid = query.value("id").toInt();
    query.prepare("SELECT BOOKID FROM USERBOOKS WHERE USERID=:userid");
    query.bindValue(":userid", userid);
    query.exec();
    if(query.first()){
        QMessageBox::warning(this, "通知", "用户存在未归还的图书，请检查！");
        return;
    }
    query.prepare("DELETE FROM USERS WHERE ID=:userid");
    query.bindValue(":userid", userid);
    query.exec();
    QMessageBox::information(this,"提示","用户已删除。");
}
