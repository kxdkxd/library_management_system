#include "addbookwindow.h"
#include "ui_addbookwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>
#include <QDateTime>

extern QSqlDatabase db;

AddBookWindow::AddBookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddBookWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btn_addbook, SIGNAL(clicked()), this, SLOT(addBookSlot()));
}


void AddBookWindow::addBookSlot(){
    if(ui->et_bookid->text()==nullptr){
        QMessageBox::information(this,"提示","请输入书号");
        return ;
    }
    if(ui->et_bookcategory->text()==nullptr){
        QMessageBox::information(this,"提示","请输入图书类型");
        return ;
    }
    if(ui->et_bookname->text()==nullptr){
        QMessageBox::information(this,"提示","请输入图书名称");
        return ;
    }
    if(ui->et_author->text()==nullptr){
        QMessageBox::information(this,"提示","请输入图书作者");
        return ;
    }
    if(ui->et_publishhouse->text()==nullptr){
        QMessageBox::information(this,"提示","请输入图书出版社");
        return ;
    }
    QSqlQuery query(db);
    query.prepare("SELECT ID FROM BOOKS WHERE ID=:bookid OR NAME=:bookname");
    query.bindValue(":bookid", ui->et_bookid->text());
    query.bindValue(":bookname", ui->et_bookname->text());
    query.exec();
    if(query.first()){
        QMessageBox::warning(this, "通知", "已存在相同的书号或者书名");
        return;
    }
    query.prepare("INSERT INTO BOOKS(ID, NAME, AUTHOR, CATEGORY, PUBLISHHOUSE, INDOCK) VALUES (:bookid, :bookname, :author, :category, :publishhouse, 1)");
    query.bindValue(":bookid", ui->et_bookid->text());
    query.bindValue(":bookname", ui->et_bookname->text());
    query.bindValue(":author", ui->et_author->text());
    query.bindValue(":category", ui->et_bookcategory->text());
    query.bindValue(":publishhouse", ui->et_publishhouse->text());
    query.exec();
    QMessageBox::information(this, "通知", "添加成功");
}

AddBookWindow::~AddBookWindow()
{
    delete ui;
}
