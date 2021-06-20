#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "querybookwindow.h"
#include "queryauthorwindow.h"
#include "queryuserwindow.h"
#include "addbookwindow.h"
#include "borrowbookwindow.h"
#include "delbookwindow.h"
#include "deleteuserwindow.h"
#include "editbookwindow.h"
#include "editpasswordwindow.h"
#include "registeruserwindow.h"
#include "returnbookwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include<QSqlQuery>


QSqlDatabase db;
struct currentUserStruct currentUser;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    currentUser.privilege = -1;
    db = QSqlDatabase::addDatabase("QMYSQL");             // DB Driver
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("librarymanagesystem");           // Database Name
    db.setUserName("root");                              // DB user (TODO: Change user to a non-root user)
    db.setPassword("kxdkxd");                            // DB pwd
    db.open();
    if(!db.open())    {
        qDebug()<< "connect to mysql error" <<db.lastError().text();
        return ;
    }
    qDebug() << "connect to mysql OK";

    ui->action_addbook->setEnabled(false);
    ui->action_delbook->setEnabled(false);
    ui->action_deluser->setEnabled(false);
    ui->action_editpwd->setEnabled(false);
    ui->action_reguser->setEnabled(false);
    ui->action_editbook->setEnabled(false);
    ui->action_querybook->setEnabled(false);
    ui->action_queryuser->setEnabled(false);
    ui->action_borrowbook->setEnabled(false);
    ui->action_returnbook->setEnabled(false);
    ui->action_cancellogin->setEnabled(false);
    ui->action_queryauthor->setEnabled(false);
    ui->action_showalluser->setEnabled(false);
    ui->action_showallbooks->setEnabled(false);

    connect(ui->action_login,&QAction::triggered,[=](){
        LoginWindow *w = new LoginWindow();
        w->show();});
    connect(ui->action_querybook,&QAction::triggered,[=](){
        QueryBookWindow *w = new QueryBookWindow();
        w->show();});
    connect(ui->action_queryauthor,&QAction::triggered,[=](){
        QueryAuthorWindow *w = new QueryAuthorWindow();
        w->show();});
    connect(ui->action_queryuser,&QAction::triggered,[=](){
        QueryUserWindow *w = new QueryUserWindow();
        w->show();});
    connect(ui->action_borrowbook,&QAction::triggered,[=](){
        BorrowBookWindow *w = new BorrowBookWindow();
        w->show();});
    connect(ui->action_addbook,&QAction::triggered,[=](){
        AddBookWindow *w = new AddBookWindow();
        w->show();});
    connect(ui->action_delbook,&QAction::triggered,[=](){
        DelBookWindow *w = new DelBookWindow();
        w->show();});
    connect(ui->action_deluser,&QAction::triggered,[=](){
        DeleteUserWindow *w = new DeleteUserWindow();
        w->show();});
    connect(ui->action_editbook,&QAction::triggered,[=](){
        EditBookWindow *w = new EditBookWindow();
        w->show();});
    connect(ui->action_editpwd,&QAction::triggered,[=](){
        EditPasswordWindow *w = new EditPasswordWindow();
        w->show();});
    connect(ui->action_reguser,&QAction::triggered,[=](){
        RegisterUserWindow *w = new RegisterUserWindow();
        w->show();});
    connect(ui->action_returnbook,&QAction::triggered,[=](){
        ReturnBookWindow *w = new ReturnBookWindow();
        w->show();});

    connect(ui->action_showallbooks,&QAction::triggered,[=](){
        this->showAllBooks();
    });
    connect(ui->action_showalluser,&QAction::triggered,[=](){
        this->showAllUsers();
    });

}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showAllUsers(){
    QSqlQuery query(db);
    QString sql = QString("SELECT ID, USERNAME, `PASSWORD`,  IF(PRIVILEGE=0, '超级用户', '普通用户') as PRIVILEGE, IFNULL(BOOKID, '') as BOOKID FROM (SELECT USERS.ID, USERNAME, `PASSWORD`, PRIVILEGE, USERBOOKS.BOOKID FROM USERS, USERBOOKS WHERE USERS.ID=USERBOOKS.USERID UNION SELECT ID, USERNAME, `PASSWORD`, PRIVILEGE, NULL FROM USERS WHERE USERNAME NOT IN (SELECT USERS.USERNAME FROM USERS, USERBOOKS WHERE USERS.ID=USERBOOKS.USERID)) AS T");
    query.exec(sql);
    this->freshUserInfoTable(&query);
}

void MainWindow::showAllBooks(){
    QSqlQuery query(db);
    QString sql = QString("SELECT ID, NAME, CATEGORY, AUTHOR, PUBLISHHOUSE, IF(INDOCK=1,'是','否') AS INDOCK, USERNAME  FROM ( SELECT BOOKS.ID, BOOKS.NAME, BOOKS.CATEGORY, BOOKS.AUTHOR, BOOKS.PUBLISHHOUSE, BOOKS.INDOCK, USERNAME  FROM USERS, USERBOOKS, BOOKS  WHERE USERS.ID=USERBOOKS.USERID AND BOOKS.ID=USERBOOKS.BOOKID AND RETURNTIME IS NULL UNION  SELECT ID, NAME, CATEGORY, AUTHOR, PUBLISHHOUSE, INDOCK, NULL  FROM BOOKS  WHERE INDOCK != 0)  AS T  ORDER BY ID ASC;");
    query.exec(sql);
    this->freshBookTable(&query);
}

void MainWindow::initUserInfo(int uid){
    qDebug() << "initUserInfo: uid=" + QString::number(uid);
    this->uid = uid;
    QSqlQuery query(db);
    query.prepare("SELECT USERNAME, PRIVILEGE FROM USERS WHERE ID=:userid");
    query.bindValue(":userid", uid);
    query.exec();
    query.first();
    currentUser.username = query.value("username").toString();
    currentUser.privilege = query.value("privilege").toInt();
    currentUser.uid = uid;
    if(currentUser.privilege != 0){
        ui->action_borrowbook->setVisible(false);
        ui->action_returnbook->setVisible(false);
        ui->action_showalluser->setVisible(false);
        ui->action_reguser->setVisible(false);
        ui->action_deluser->setVisible(false);
        ui->action_addbook->setVisible(false);
        ui->action_delbook->setVisible(false);
        ui->action_editbook->setVisible(false);
    }
    ui->action_addbook->setEnabled(true);
    ui->action_delbook->setEnabled(true);
    ui->action_deluser->setEnabled(true);
    ui->action_editpwd->setEnabled(true);
    ui->action_reguser->setEnabled(true);
    ui->action_editbook->setEnabled(true);
    ui->action_querybook->setEnabled(true);
    ui->action_queryuser->setEnabled(true);
    ui->action_borrowbook->setEnabled(true);
    ui->action_returnbook->setEnabled(true);
    ui->action_cancellogin->setEnabled(true);
    ui->action_queryauthor->setEnabled(true);
    ui->action_showalluser->setEnabled(true);
    ui->action_showallbooks->setEnabled(true);
    this->showAllBooks();
}

void MainWindow::freshUserInfoTable(QSqlQuery *query){
    ui->tableWidget->clear();
    QStringList strList;
    strList << "uid" << "username" << "password" << "privilege" << "BOOKID";
    ui->tableWidget->setColumnCount(strList.length());
    qDebug() << query->size();
    ui->tableWidget->setRowCount(query->size());
    ui->tableWidget->setHorizontalHeaderLabels(strList);
    for(int i=0; query->next(); i++){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(query->value("id").toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(query->value("username").toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(query->value("password").toString()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(query->value("privilege").toString()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(query->value("bookid").toString()));
    }
}

void MainWindow::freshBookTable(QSqlQuery *queryBook){
    ui->tableWidget->clear();
    QStringList strList;
    strList << "书号" << "书名" << "作者" << "类别" << "出版社" << "是否在馆" << "借阅者";
    ui->tableWidget->setColumnCount(strList.length());
    qDebug() << queryBook->size();
    ui->tableWidget->setRowCount(queryBook->size());
    ui->tableWidget->setHorizontalHeaderLabels(strList);
    for(int i=0; queryBook->next(); i++){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(queryBook->value("id").toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(queryBook->value("name").toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(queryBook->value("author").toString()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(queryBook->value("category").toString()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(queryBook->value("publishhouse").toString()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(queryBook->value("indock").toString()));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(queryBook->value("username").toString()));
    }
}

QList<QTableWidgetItem*> MainWindow::getSelectedTableItems(){
    return ui->tableWidget->selectedItems();
}

