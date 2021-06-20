#include "delbookwindow.h"
#include "ui_delbookwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>
#include <QDateTime>

extern QSqlDatabase db;

DelBookWindow::DelBookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DelBookWindow)
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
    QObject::connect(ui->btn_delbook, SIGNAL(clicked()), this, SLOT(delBookSlot()));
}

DelBookWindow::~DelBookWindow()
{
    delete ui;
}


void DelBookWindow::delBookSlot(){
    if(ui->rdb_bookid->isChecked()&&ui->et_bookid->text()==nullptr){
        QMessageBox::information(this,"提示","请输入书号");
        return ;
    }
    if(ui->rdb_bookname->isChecked()&&ui->et_bookname->text()==nullptr){
        QMessageBox::information(this,"提示","请输入书名");
        return ;
    }
    if(ui->rdb_bookid->isChecked()){
        QSqlQuery query(db);
        query.prepare("SELECT INDOCK FROM BOOKS WHERE ID=:bookid");
        query.bindValue(":bookid", ui->et_bookid->text());
        query.exec();
        if(!query.first()){
            QMessageBox::warning(this, "通知", "查无此书");
            return;
        }
        if(query.value("indock").toInt() == 0){
            QMessageBox::warning(this, "通知", "此书不在馆！无法删除。");
            return;
        }
        query.prepare("DELETE FROM BOOKS WHERE ID=:bookid");
        query.bindValue(":bookid", ui->et_bookid->text());
        query.exec();
    }
    else{
        QSqlQuery query(db);
        query.prepare("SELECT ID, INDOCK FROM BOOKS WHERE NAME=:bookname");
        query.bindValue(":bookname", ui->et_bookname->text());
        query.exec();
        if(!query.first()){
            QMessageBox::warning(this, "通知", "查无此书");
            return;
        }
        if(query.value("indock").toInt() == 0){
            QMessageBox::warning(this, "通知", "此书不在馆！无法删除。");
            return;
        }
        int bookid = query.value("id").toInt();
        query.prepare("DELETE FROM BOOKS WHERE ID=:bookid");
        query.bindValue(":bookid", bookid);
        query.exec();
    }
    QMessageBox::information(this, "通知", "已删除该图书！");
}
