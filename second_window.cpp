#include "second_window.h"
#include "third_window.h"
#include "ui_second_window.h"
#include <QMessageBox>
#include <QDebug>
#include <vector>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <QString>

using namespace std;

Second_window::Second_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Second_window)
{
    ui->setupUi(this);
}

Second_window::~Second_window()
{
    delete ui;
}
//кнопка выхода
void Second_window::on_exit_Button_2_clicked()
{
    QApplication::quit();
}
//кнопка назад
void Second_window::on_back_Button_2_clicked()
{
    this->close();
}
//кнопка кодировать
void Second_window::on_encode_Button_2_clicked()
{
    if (m_value < 1 || m_value >= 10) {
        QMessageBox::warning(this, "Ошибка", "Параметр m не задан или некорректен. Сначала вернитесь в главное окно и рассчитайте матрицу.");
        return;
    }

    int k = m_value;              // количество проверочных битов
    int n = (1 << k) - 1;         // длина кодового слова
    int infoBitsCount = n - k;    // количество информационных битов


    QString infoStr = ui->textEdit->toPlainText().trimmed();
    if (infoStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите информационное слово.");
        return;
    }
    for (QChar ch : infoStr) {
        if (ch != '0' && ch != '1') {
            QMessageBox::warning(this, "Ошибка", "Кодовое слово должно содержать только 0 и 1");
            return;
        }
    }

    if (infoStr.length() > infoBitsCount) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Информационное слово слишком длинное. Максимум %1 бит.").arg(infoBitsCount));
        return;
    }


    while (infoStr.length() < infoBitsCount) {
        infoStr = "0" + infoStr;
    }


    vector<vector<int>> H(k, vector<int>(n, 0));
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < k; i++) {
            H[k - 1 - i][j] = ((j + 1) >> i) & 1;
        }
    }


    vector<bool> isParity(n, false);
    vector<int> parityPositions;
    for (int i = 0; i < k; i++) {
        int pos = (1 << i) - 1;  // позиции: 0,1,3,7,...
        if (pos < n) {
            isParity[pos] = true;
            parityPositions.push_back(pos);
        }
    }


    vector<int> codeWord(n, 0);
    int infoIdx = 0;

    for (int i = 0; i < n; i++) {
        if (!isParity[i]) {
            codeWord[i] = infoStr[infoIdx].digitValue();
            infoIdx++;
        }
    }

    for (int parityPos : parityPositions) {
        int sum = 0;
        // Номер проверочного бита (i) - это индекс строки в H
        // Проверочный бит на позиции 2^i-1 соответствует строке i (считая снизу)
        // Определяем номер строки: у позиции (2^i-1) двоичное представление имеет 1 на i-м месте
        int rowIndex = -1;
        for (int i = 0; i < k; i++) {
            if (parityPos == (1 << i) - 1) {
                rowIndex = k - 1 - i;  // строка в H (так как H построена с инверсией)
                break;
            }
        }

        if (rowIndex == -1) continue;

        // Суммируем все биты, где в H[rowIndex][j] = 1, исключая сам проверочный бит
        for (int j = 0; j < n; j++) {
            if (j != parityPos && H[rowIndex][j] == 1) {
                sum ^= codeWord[j];
            }
        }
        codeWord[parityPos] = sum;
    }

    QString result;
    result += "Информационное слово (" + QString::number(infoBitsCount) + " бит): " + infoStr + "\n";
    result += "Кодовое слово (" + QString::number(n) + " бит): ";
              for (int bit : codeWord) {
        result += QString::number(bit);
    }
    result += "\n\nПроверочные биты на позициях: ";
    for (int j = 0; j < k; j++) {
        int pos = (1 << j) - 1;
        if (pos < n) {
            result += "x" + QString::number(pos + 1) + "=" + QString::number(codeWord[pos]) + " ";
        }
    }
    H_matrix = H;
    ui->textEdit_2->setPlainText(result);
}

//кнопка перехода к окну 3
void Second_window::on_decode_Button_2_clicked()
{
    hide();
    Third_window window;
    window.setM(m_value);
    window.setVerificationMatrix(H);
    window.setModal(true);
    window.exec();
}



