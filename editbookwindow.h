#ifndef EDITBOOKWINDOW_H
#define EDITBOOKWINDOW_H

#include <QMainWindow>

namespace Ui {
class EditBookWindow;
}

class EditBookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditBookWindow(QWidget *parent = nullptr);
    ~EditBookWindow();

public slots:
    void editBookSlot();

private:
    Ui::EditBookWindow *ui;
};

#endif // EDITBOOKWINDOW_H
