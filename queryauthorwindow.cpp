#include "queryauthorwindow.h"
#include "ui_queryauthorwindow.h"
#include "mainwindow.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QDebug>

extern MainWindow *mainWindow;

QueryAuthorWindow::QueryAuthorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QueryAuthorWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btn_queryauthor, SIGNAL(clicked()), this, SLOT(queryAuthorSlot()));
}

QueryAuthorWindow::~QueryAuthorWindow()
{
    delete ui;
}

void QueryAuthorWindow::queryAuthorSlot(){
    if(ui->et_author->text()==nullptr){
        QMessageBox::information(this,"提示","请输入作者姓名");
        return ;
    }
    QSqlQuery query(db);
    query.prepare("SELECT * FROM ( SELECT BOOKS.ID, BOOKS.NAME, BOOKS.CATEGORY, BOOKS.AUTHOR, BOOKS.PUBLISHHOUSE, BOOKS.INDOCK, USERNAME  FROM USERS, USERBOOKS, BOOKS  WHERE USERS.ID=USERBOOKS.USERID AND BOOKS.ID=USERBOOKS.BOOKID  UNION  SELECT ID, NAME, CATEGORY, AUTHOR, PUBLISHHOUSE, INDOCK, NULL  FROM BOOKS  WHERE INDOCK != 0)  AS T WHERE AUTHOR=:author ORDER BY ID ASC");
    query.bindValue(":author", ui->et_author->text());
    query.exec();
    mainWindow->freshBookTable(&query);
}
