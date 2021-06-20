#ifndef DELETEUSERWINDOW_H
#define DELETEUSERWINDOW_H

#include <QMainWindow>

namespace Ui {
class DeleteUserWindow;
}

class DeleteUserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeleteUserWindow(QWidget *parent = nullptr);
    ~DeleteUserWindow();

public slots:
    void delUserSlot();

private:
    Ui::DeleteUserWindow *ui;
};

#endif // DELETEUSERWINDOW_H
