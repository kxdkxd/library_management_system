#include "registeruserwindow.h"
#include "ui_registeruserwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>
#include <QDateTime>

extern QSqlDatabase db;

RegisterUserWindow::RegisterUserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterUserWindow)
{
    ui->setupUi(this);
    ui->rdb_admin->click();
    QObject::connect(ui->btn_reg, SIGNAL(clicked()), this, SLOT(registerUserSlot()));
}

RegisterUserWindow::~RegisterUserWindow()
{
    delete ui;
}


void RegisterUserWindow::registerUserSlot(){
    if(ui->et_uid->text()==nullptr){
        QMessageBox::warning(this,"提示","请输入用户UID");
        return ;
    }
    if(ui->et_username->text()==nullptr){
        QMessageBox::warning(this,"提示","请输入用户名");
        return ;
    }
    if(ui->et_pwd->text()==nullptr || ui->et_pwd2->text()==nullptr){
        QMessageBox::warning(this,"提示","请输入密码");
        return ;
    }
    if(ui->et_pwd->text()!=ui->et_pwd2->text()){
        QMessageBox::warning(this,"提示","密码两次输入不一致！");
        return ;
    }
    int userPrivilege = 0;
    if(ui->rdb_normaluser->isChecked()){
        userPrivilege = 1;
    }
    QSqlQuery query(db);
    query.prepare("SELECT * FROM USERS WHERE USERID=:userid OR USERNAME=:username");
    query.bindValue(":userid", ui->et_uid->text());
    query.bindValue(":username", ui->et_username->text());
    query.exec();
    if(query.first()){
        QMessageBox::warning(this,"提示","用户UID或用户名已被注册！");
        return ;
    }
    query.prepare("INSERT INTO USERS(ID, USERNAME, PASSWORD, PRIVILEGE) VALUES (:userid, :username, :password, :privilege)");
    query.bindValue(":userid", ui->et_uid->text());
    query.bindValue(":username", ui->et_username->text());
    query.bindValue(":password", ui->et_pwd->text());
    query.bindValue(":privilege", userPrivilege);
    query.exec();
    QMessageBox::information(this,"提示","注册成功！");
}
