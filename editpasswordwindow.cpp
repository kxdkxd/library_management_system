#include "editpasswordwindow.h"
#include "ui_editpasswordwindow.h"
#include "mainwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>
#include <QDateTime>

extern QSqlDatabase db;


EditPasswordWindow::EditPasswordWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditPasswordWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btn_editpwd, SIGNAL(clicked()), this, SLOT(editPwdSlot()));
}

EditPasswordWindow::~EditPasswordWindow()
{
    delete ui;
}

void EditPasswordWindow::editPwdSlot(){
    if(ui->et_originpwd->text()==nullptr){
        QMessageBox::warning(this,"提示","请输入用户名");
        return ;
    }
    if(ui->et_newpwd->text()==nullptr || ui->et_newpwd_2->text()==nullptr){
        QMessageBox::warning(this,"提示","请输入密码");
        return ;
    }
    if(ui->et_newpwd->text() != ui->et_newpwd_2->text()){
        QMessageBox::warning(this,"提示","两次密码输入不一致");
        return ;
    }
    QSqlQuery query(db);
    query.prepare("SELECT ID FROM USERS WHERE ID=:userid AND PASSWORD=:oripwd");
    query.bindValue(":userid", currentUser.uid);
    query.bindValue(":oripwd", ui->et_originpwd->text());
    query.exec();
    if(!query.first()){
        QMessageBox::warning(this, "通知", "原始密码与数据库不对应！");
        return;
    }
    query.prepare("UPDATE USERS SET PASSWORD=:newpwd WHERE ID=:userid");
    query.bindValue(":userid", currentUser.uid);
    query.bindValue(":newpwd", ui->et_newpwd->text());
    query.exec();
    QMessageBox::information(this, "通知", "修改成功");
}
