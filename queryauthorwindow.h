#ifndef QUERYAUTHORWINDOW_H
#define QUERYAUTHORWINDOW_H

#include <QMainWindow>

namespace Ui {
class QueryAuthorWindow;
}

class QueryAuthorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QueryAuthorWindow(QWidget *parent = nullptr);
    ~QueryAuthorWindow();

public slots:
    void queryAuthorSlot();

private:
    Ui::QueryAuthorWindow *ui;
};

#endif // QUERYAUTHORWINDOW_H
