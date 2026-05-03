#include "third_window.h"
#include "ui_third_window.h"
#include <QMessageBox>
#include <QDebug>
#include <vector>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <QString>

using namespace std;

Third_window::Third_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Third_window)
{
    ui->setupUi(this);
}

Third_window::~Third_window()
{
    delete ui;
}

void Third_window::on_exit_Button_2_clicked()
{
    QApplication::quit();
}
void Third_window::on_back_Button_3_clicked()
{
    this->close();
}
void Third_window::on_decode_Button_3_clicked()
{
    QString codeWord = ui->textEdit->toPlainText().trimmed();

    if (codeWord.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите кодовое слово для декодирования");
        return;
    }

    QString result = "Получено кодовое слово: " + codeWord + "\n";
    result += "Функция декодирования будет реализована позже.";

    ui->textEdit_2->setPlainText(result);
}
