#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "second_window.h"
#include "third_window.h"
#include <vector>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::verification_matrix(int m){
    if(m < 1 || m >= 10){
        QMessageBox::warning(this, "Ошибка", "m должно быть в диапазоне 1 <= m < 10");
        return;
    }
    m_value = m;
    int n = (1 << m) - 1;
    n_value = n;
    H.assign(m, vector<int>(n, 0));

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            H[m - 1 - i][j] = (j + 1 >> i) & 1;
        }
    }
    QString result;
    for (int i = 0; i < m; i++) {
        result += "| ";
        for (int j = 0; j < n; j++) {
            result += QString::number(H[i][j]) + " ";
        }
        result += "|\n";
    }
    ui->textEdit->setPlainText(result);
}

//кнопка "расчитать"
void MainWindow::on_calc_matrix_clicked(){
    int m = ui->SpinBox_M->value();

    verification_matrix(m);
}

// кнопка выхода
void MainWindow::on_exit_Button_1_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Внимание", "Вы уверены, что Вы хотите выйти?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
    else {
        qDebug() << "Нажата кнопка 'Нет'!";
    }
}
//кнопка перехода в окно 2
void MainWindow::on_encode_Button_1_clicked()
{
    int m = ui->SpinBox_M->value();
    if (m < 1 || m >= 10) {
        QMessageBox::warning(this, "Ошибка", "Введите корректное m (1..9)");
        return;
    }
    //hide();
    Second_window window;
    window.setM(m);
    window.setVerificationMatrix(H);
    window.setModal(true);
    window.exec();
}

//кнопка перехода в окно 3
void MainWindow::on_decode_Button_1_clicked()
{
    int m = ui->SpinBox_M->value();
    if (m < 1 || m >= 10) {
        QMessageBox::warning(this, "Ошибка", "Введите корректное m (1..9) для декодирования");
        return;
    }

    Third_window window;
    window.setM(m);
    window.setVerificationMatrix(H);
    window.setModal(true);
    window.exec();
}

