#ifndef DELBOOKWINDOW_H
#define DELBOOKWINDOW_H

#include <QMainWindow>

namespace Ui {
class DelBookWindow;
}

class DelBookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DelBookWindow(QWidget *parent = nullptr);
    ~DelBookWindow();

public slots:
    void delBookSlot();

private:
    Ui::DelBookWindow *ui;
};

#endif // DELBOOKWINDOW_H
