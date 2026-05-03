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
    void setM(int m)
    {
        m_value = m;
    }
private:
    Ui::Second_window *ui;
    int m_value = 0;  // параметр m (количество строк)
    int n_value = 0;  // длина кодового слова
private slots:
    void on_exit_Button_2_clicked();
    void on_back_Button_2_clicked();
    void on_decode_Button_2_clicked();
    void on_encode_Button_2_clicked();
};

#endif // SECOND_WINDOW_H
