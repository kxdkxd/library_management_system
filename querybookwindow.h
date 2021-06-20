#ifndef QUERYBOOKWINDOW_H
#define QUERYBOOKWINDOW_H

#include <QMainWindow>

namespace Ui {
class QueryBookWindow;
}

class QueryBookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QueryBookWindow(QWidget *parent = nullptr);
    ~QueryBookWindow();

public slots:
    void queryBookSlot();

private:
    Ui::QueryBookWindow *ui;
};

#endif // QUERYBOOKWINDOW_H
