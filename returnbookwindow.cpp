#include "returnbookwindow.h"
#include "ui_returnbookwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>
#include <QDateTime>

extern int currentPrivilege;
extern QSqlDatabase db;

ReturnBookWindow::ReturnBookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReturnBookWindow)
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
    QObject::connect(ui->btn_return, SIGNAL(clicked()), this, SLOT(returnBookSlot()));
}

ReturnBookWindow::~ReturnBookWindow()
{
    delete ui;
}


void ReturnBookWindow::returnBookSlot(){
    if(ui->rdb_bookid->isChecked()&&ui->et_bookid->text()==nullptr){
        QMessageBox::information(this,"提示","请输入书号");
        return ;
    }
    if(ui->rdb_bookname->isChecked()&&ui->et_bookname->text()==nullptr){
        QMessageBox::information(this,"提示","请输入书名");
        return ;
    }
    QSqlQuery query(db);
    if(ui->rdb_bookid->isChecked()){
        query.prepare("SELECT INDOCK FROM BOOKS WHERE ID=:bookid");
        query.bindValue(":bookid", ui->et_bookid->text());
        query.exec();
        if(!query.first()){
            QMessageBox::warning(this, "通知", "查无此书");
            return;
        }
        if(query.value("INDOCK").toInt() == 1){
            QMessageBox::warning(this, "通知", "此书已在馆");
            return;
        }
        query.prepare("SELECT RECID FROM USERBOOKS WHERE BOOKID=:bookid AND RETURNTIME IS NULL");
        query.bindValue(":bookid", ui->et_bookid->text());
        query.exec();
        if(!query.first()){
            QMessageBox::warning(this, "通知", "无借书记录");
            return;
        }
        int recid = query.value("RECID").toInt();
        query.prepare("UPDATE BOOKS SET INDOCK=1 WHERE ID=:bookid");
        query.bindValue(":bookid", ui->et_bookid->text());
        query.exec();
        query.prepare("UPDATE USERBOOKS SET RETURNTIME=:returntime WHERE RECID=:recid");
        query.bindValue(":recid", recid);
        query.bindValue(":returntime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        query.exec();
        QMessageBox::information(this, "提示", "还书成功。书号为"+ui->et_bookid->text());
    }
    else if (ui->rdb_bookname->isChecked()){
        query.prepare("SELECT ID, INDOCK FROM BOOKS WHERE NAME=:bookname");
        query.bindValue(":bookname", ui->et_bookname->text());
        query.exec();
        if(!query.first()){
            QMessageBox::warning(this, "通知", "查无此书");
            return;
        }
        if(query.value("INDOCK").toInt() == 1){
            QMessageBox::warning(this, "通知", "此书已在馆");
            return;
        }
        int bookid = query.value("ID").toInt();
        query.prepare("SELECT RECID FROM USERBOOKS WHERE BOOKID=:bookid AND RETURNTIME IS NULL");
        query.bindValue(":bookid", ui->et_bookid->text());
        query.exec();
        if(!query.first()){
            QMessageBox::warning(this, "通知", "无借书记录");
            return;
        }
        int recid = query.value("recid").toInt();
        query.prepare("UPDATE BOOKS SET INDOCK=1 WHERE ID=:bookid");
        query.bindValue(":bookid", bookid);
        query.exec();
        query.prepare("UPDATE USERBOOKS SET RETURNTIME=:returntime WHERE RECID=:recid");
        query.bindValue(":recid", recid);
        query.bindValue(":returntime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        query.exec();
    }
}

