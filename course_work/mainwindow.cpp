#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "second_window.h"
#include <vector>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <QString>

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
    int n = (1 << m) - 1;
    vector<vector<int>> H(m, vector<int>(n, 0));
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
    ui->textEdit_2->setPlainText(result);
}

void MainWindow::on_pushButton_4_clicked(){
    int m = ui->SpinBox_M->value();

    verification_matrix(m);
}

void MainWindow::on_pushButton_3_clicked()
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
void MainWindow::on_pushButton_clicked()
{
    hide();
    Second_window window;
    window.setModal(true);
    window.exec();
}

