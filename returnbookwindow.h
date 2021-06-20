#ifndef RETURNBOOKWINDOW_H
#define RETURNBOOKWINDOW_H

#include <QMainWindow>

namespace Ui {
class ReturnBookWindow;
}

class ReturnBookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReturnBookWindow(QWidget *parent = nullptr);
    ~ReturnBookWindow();

public slots:
    void returnBookSlot();

private:
    Ui::ReturnBookWindow *ui;
};

#endif // RETURNBOOKWINDOW_H
