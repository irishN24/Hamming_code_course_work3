#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<std::vector<int>> getVerificationMatrix() const { return H; }
    int getM() const { return m_value; }
    int getN() const { return n_value; }
private slots:

    void on_calc_matrix_clicked(); //кнопка для расчёта матрицы
    void on_exit_Button_1_clicked();
    void on_encode_Button_1_clicked();
    void on_decode_Button_1_clicked();
    void verification_matrix(int m);

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<int>> H;  // проверочная матрица
    int m_value = 0;  // параметр m (количество строк)
    int n_value = 0;  // длина кодового слова
};
#endif // MAINWINDOW_H
