#ifndef QUERYUSERWINDOW_H
#define QUERYUSERWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class QueryUserWindow;
}

class QueryUserWindow : public QMainWindow
{
    Q_OBJECT

public:
    void queryUser(QString username);
    explicit QueryUserWindow(QWidget *parent = nullptr);
    ~QueryUserWindow();

public slots:
    void queryUserSlot();

private:
    Ui::QueryUserWindow *ui;
};

#endif // QUERYUSERWINDOW_H
