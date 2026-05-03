#ifndef THIRD_WINDOW_H
#define THIRD_WINDOW_H

#include <QDialog>

namespace Ui {
class Third_window;
}

class Third_window : public QDialog
{
    Q_OBJECT

public:
    explicit Third_window(QWidget *parent = nullptr);
    ~Third_window();

private:
    Ui::Third_window *ui;

private slots:
    void on_exit_Button_2_clicked();
    void on_back_Button_3_clicked();
    void on_decode_Button_3_clicked();
};

#endif // THIRD_WINDOW_H
