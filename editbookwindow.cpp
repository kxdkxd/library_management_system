#include "editbookwindow.h"
#include "mainwindow.h"
#include "ui_editbookwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>
#include <QDateTime>
#include <QTableWidgetItem>

extern QSqlDatabase db;
extern MainWindow *mainWindow;

EditBookWindow::EditBookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditBookWindow)
{
    QList<QTableWidgetItem*> items = mainWindow->getSelectedTableItems();
    int count=items.count();
    for(int i=0; i<count; i++){
           QTableWidgetItem* item = items.at(i);
           QString name = item->text();
           qDebug() << "Edit Book vvv";
           qDebug() << name;
           qDebug() << "Edit Book ^^^";
    }
    ui->setupUi(this);
    QObject::connect(ui->btn_editbook, SIGNAL(clicked()), this, SLOT(editBookSlot()));
}

EditBookWindow::~EditBookWindow()
{
    delete ui;
}

void EditBookWindow::editBookSlot(){
    if(ui->et_bookid->text()==nullptr){
        QMessageBox::information(this,"提示","请输入书号");
        return ;
    }
    if(ui->et_category->text()==nullptr){
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

}

