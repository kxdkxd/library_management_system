#ifndef BORROWBOOKWINDOW_H
#define BORROWBOOKWINDOW_H

#include <QMainWindow>

namespace Ui {
class BorrowBookWindow;
}

class BorrowBookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BorrowBookWindow(QWidget *parent = nullptr);
    ~BorrowBookWindow();

public slots:
    void borrowBookSlot();

private:
    Ui::BorrowBookWindow *ui;
};

#endif // BORROWBOOKWINDOW_H
