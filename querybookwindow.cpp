#include "querybookwindow.h"
#include "ui_querybookwindow.h"
#include "mainwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>

extern QSqlDatabase db;

QueryBookWindow::QueryBookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QueryBookWindow)
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
    QObject::connect(ui->btn_querybook, SIGNAL(clicked()), this, SLOT(queryBookSlot()));
}


QueryBookWindow::~QueryBookWindow()
{
    delete ui;
}


void QueryBookWindow::queryBookSlot(){
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
        query.prepare("SELECT * FROM ( SELECT BOOKS.ID, BOOKS.NAME, BOOKS.CATEGORY, BOOKS.AUTHOR, BOOKS.PUBLISHHOUSE, IF(BOOKS.INDOCK=1,'是','否'), USERNAME  FROM USERS, USERBOOKS, BOOKS  WHERE USERS.ID=USERBOOKS.USERID AND BOOKS.ID=USERBOOKS.BOOKID  UNION  SELECT ID, NAME, CATEGORY, AUTHOR, PUBLISHHOUSE, INDOCK, NULL  FROM BOOKS  WHERE INDOCK != 0)  AS T WHERE ID=:bookid ORDER BY ID ASC");
        query.bindValue(":bookid", ui->et_bookid->text());
    }
    else if (ui->rdb_bookname->isChecked()){
        query.prepare("SELECT * FROM ( SELECT BOOKS.ID, BOOKS.NAME, BOOKS.CATEGORY, BOOKS.AUTHOR, BOOKS.PUBLISHHOUSE, IF(BOOKS.INDOCK=1,'是','否'), USERNAME  FROM USERS, USERBOOKS, BOOKS  WHERE USERS.ID=USERBOOKS.USERID AND BOOKS.ID=USERBOOKS.BOOKID  UNION  SELECT ID, NAME, CATEGORY, AUTHOR, PUBLISHHOUSE, INDOCK, NULL  FROM BOOKS  WHERE INDOCK != 0)  AS T WHERE NAME=:bookname ORDER BY ID ASC");
        query.bindValue(":bookname", ui->et_bookname->text());
    }
    query.exec();
    if(query.first()){
        QMessageBox::information(this,
                                 "查询结果",
                                 "图书编号："+query.value("id").toString()
                                  +"\n图书类型："+query.value("category").toString()
                                  +"\n图书名称："+query.value("name").toString()
                                  +"\n作者："+query.value("author").toString()
                                  +"\n出版社："+query.value("publishhouse").toString()
                                  +"\n是否在馆："+query.value("indock").toString()
                                  +"\n借阅人："+query.value("username").toString());
    }
    else{
        QMessageBox::critical(this, "错误", "未找到对应书籍名称。");
    }
}

