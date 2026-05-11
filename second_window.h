#ifndef SECOND_WINDOW_H
#define SECOND_WINDOW_H

#include <QDialog>
#include <QDebug>

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
    void setVerificationMatrix(const std::vector<std::vector<int>>& matrix)
    {
        H = matrix;
        qDebug() << "Second_window: verification matrix received, size:" << H.size() << "x" << (H.empty() ? 0 : H[0].size());
    }
private:
    Ui::Second_window *ui;
    int m_value = 0;  // параметр m (количество строк)
    int n_value = 0;  // длина кодового слова
    std::vector<std::vector<int>> H;
    std::vector<std::vector<int>> H_matrix;
private slots:
    void on_exit_Button_2_clicked();
    void on_back_Button_2_clicked();
    void on_decode_Button_2_clicked();
    void on_encode_Button_2_clicked();
};

#endif // SECOND_WINDOW_H
