#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include<QSqlQuery>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showAllBooks();
    void showAllUsers();
    void initUserInfo(int uid);
    void freshUserInfoTable(QSqlQuery *query);
    void freshBookTable(QSqlQuery *query);
    QList<QTableWidgetItem*> getSelectedTableItems();

private:
    Ui::MainWindow *ui;
    int uid;
};

extern MainWindow *mainWindow;
extern QSqlDatabase db;
extern struct currentUserStruct{
    int privilege; // -1 not logged in, 0 su, 1 normal
    int uid;
    QString username;
} currentUser;

#endif // MAINWINDOW_H
