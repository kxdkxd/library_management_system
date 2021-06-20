#ifndef REGISTERUSERWINDOW_H
#define REGISTERUSERWINDOW_H

#include <QMainWindow>

namespace Ui {
class RegisterUserWindow;
}

class RegisterUserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterUserWindow(QWidget *parent = nullptr);
    ~RegisterUserWindow();

public slots:
    void registerUserSlot();

private:
    Ui::RegisterUserWindow *ui;
};

#endif // REGISTERUSERWINDOW_H
