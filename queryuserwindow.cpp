#include "queryuserwindow.h"
#include "ui_queryuserwindow.h"
#include "mainwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>


void QueryUserWindow::queryUser(QString username){
    QSqlQuery query(db);
    query.prepare("SELECT ID, USERNAME, `PASSWORD`, IF(PRIVILEGE=0, '超级用户', '普通用户') as PRIVILEGE, IFNULL(BOOKID, '') as BOOKID FROM (SELECT USERS.ID, USERNAME, `PASSWORD`, PRIVILEGE, USERBOOKS.BOOKID FROM USERS, USERBOOKS WHERE USERS.ID=USERBOOKS.USERID UNION SELECT ID, USERNAME, `PASSWORD`, PRIVILEGE, NULL FROM USERS WHERE USERNAME NOT IN (SELECT USERS.USERNAME FROM USERS, USERBOOKS WHERE USERS.ID=USERBOOKS.USERID)) AS T WHERE USERNAME=:username");
    query.bindValue(":username", username);
    query.exec();
    if(query.first()){
        QString bookIdInfo("\n" + query.value("BOOKID").toString() + "\n");
        QString temp("编号："+query.value("id").toString()+
                     "\n用户名："+query.value("username").toString()+
                     "\n用户类型："+query.value("privilege").toString());
        for(int i=0; query.next(); i++){
            bookIdInfo.append(query.value("BOOKID").toString() + "\n");
        }
        QMessageBox::information(this,"用户信息", temp + "\n借阅信息："+bookIdInfo);
    }
    else{
        QMessageBox::critical(this,"错误", "没有此用户");
    }
}

QueryUserWindow::QueryUserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QueryUserWindow)
{
    if(currentUser.privilege != 0){
        QSqlQuery query(db);
        query.prepare("SELECT USERNAME FROM USERS WHERE ID=:userid");
        query.bindValue(":userid", currentUser.username);
        query.exec();
        queryUser(currentUser.username);
        this->close();
        return;
    }
    ui->setupUi(this);
    QObject::connect(ui->btn_queryuser, SIGNAL(clicked()), this, SLOT(queryUserSlot()));
}

QueryUserWindow::~QueryUserWindow()
{
    delete ui;
}

void QueryUserWindow::queryUserSlot(){
    if(ui->et_username->text()==nullptr){
        QMessageBox::information(this,"提示","请输入用户名");
        return ;
    }
    this->queryUser(ui->et_username->text());
}
