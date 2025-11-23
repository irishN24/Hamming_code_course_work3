#ifndef SECOND_WINDOW_H
#define SECOND_WINDOW_H

#include <QDialog>

namespace Ui {
class Second_window;
}

class Second_window : public QDialog
{
    Q_OBJECT

public:
    explicit Second_window(QWidget *parent = nullptr);
    ~Second_window();
private:
    Ui::Second_window *ui;
};

#endif // SECOND_WINDOW_H
