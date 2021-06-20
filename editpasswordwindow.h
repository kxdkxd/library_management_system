#ifndef EDITPASSWORDWINDOW_H
#define EDITPASSWORDWINDOW_H

#include <QMainWindow>

namespace Ui {
class EditPasswordWindow;
}

class EditPasswordWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditPasswordWindow(QWidget *parent = nullptr);
    ~EditPasswordWindow();

public slots:
    void editPwdSlot();

private:
    Ui::EditPasswordWindow *ui;
};

#endif // EDITPASSWORDWINDOW_H
