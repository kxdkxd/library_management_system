#include "borrowbookwindow.h"
#include "ui_borrowbookwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>
#include <QDateTime>

extern QSqlDatabase db;

BorrowBookWindow::BorrowBookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BorrowBookWindow)
{
    ui->setupUi(this);
    ui->rdb_bookid->click();
    ui->et_bookname->setEnabled(false);
    connect(ui->rdb_bookid,&QRadioButton::clicked,[=](){
        ui->et_bookid->setEnabled(true);
        ui->et_bookid->setFocus();
        ui->et_bookname->clear();
        ui->et_bookname->setEnabled(false);
    });
    connect(ui->rdb_bookname,&QRadioButton::clicked,[=](){
        ui->et_bookname->setEnabled(true);
        ui->et_bookname->setFocus();
        ui->et_bookid->clear();
        ui->et_bookid->setEnabled(false);
    });
    QObject::connect(ui->btn_borrow, SIGNAL(clicked()), this, SLOT(borrowBookSlot()));
}

BorrowBookWindow::~BorrowBookWindow()
{
    delete ui;
}



void BorrowBookWindow::borrowBookSlot(){
    if(ui->rdb_bookid->isChecked()&&ui->et_bookid->text()==nullptr){
        QMessageBox::information(this,"提示","请输入书号");
        return ;
    }
    if(ui->rdb_bookname->isChecked()&&ui->et_bookname->text()==nullptr){
        QMessageBox::information(this,"提示","请输入书名");
        return ;
    }
    if(ui->et_userid->text()==nullptr){
        QMessageBox::information(this,"提示","请输入书借书人账户");
        return ;
    }
    QSqlQuery query(db);
    query.prepare("SELECT ID FROM USERS WHERE ID=:userid");
    query.bindValue(":userid", ui->et_userid->text());
    query.exec();
    if(!query.first()){
        QMessageBox::warning(this, "通知", "查无此用户");
        return;
    }
    if(ui->rdb_bookid->isChecked()){
        query.prepare("SELECT INDOCK FROM BOOKS WHERE ID=:bookid");
        query.bindValue(":bookid", ui->et_bookid->text());
        query.exec();
        if(!query.first()){
            QMessageBox::warning(this, "通知", "查无此书");
            return;
        }
        if(query.value("indock").toInt() == 0){
            QMessageBox::warning(this, "通知", "此书不在馆");
            return;
        }
        query.prepare("UPDATE BOOKS SET INDOCK=0 WHERE ID=:bookid");
        query.bindValue(":bookid", ui->et_bookid->text());
        query.exec();
        query.prepare("INSERT INTO USERBOOKS(USERID, BOOKID, LENDTIME) VALUES (:userid, :bookid, :lendtime)");
        query.bindValue(":userid", ui->et_userid->text());
        query.bindValue(":bookid", ui->et_bookid->text());
        query.bindValue(":lendtime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        query.exec();
        QMessageBox::information(this, "提示", "借书成功。书号为"+ui->et_bookid->text()+"\n借书人"+ui->et_userid->text());
    }
    else if (ui->rdb_bookname->isChecked()){
        query.prepare("SELECT ID, INDOCK FROM BOOKS WHERE NAME=:bookname");
        query.bindValue(":bookname", ui->et_bookname->text());
        query.exec();
        if(!query.first()){
            QMessageBox::warning(this, "通知", "查无此书");
            return;
        }
        if(query.value("indock").toInt() == 0){
            QMessageBox::warning(this, "通知", "此书不在馆");
            return;
        }
        int bookid = query.value("id").toInt();
        query.prepare("UPDATE BOOKS SET INDOCK=0 WHERE ID=:bookid");
        query.bindValue(":bookid", bookid);
        query.exec();
        query.prepare("INSERT INTO USERBOOKS(USERID, BOOKID, LENDTIME) VALUES (:userid, :bookid, :lendtime)");
        query.bindValue(":userid", ui->et_userid->text());
        query.bindValue(":bookid", bookid);
        query.bindValue(":lendtime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        query.exec();
    }
}

