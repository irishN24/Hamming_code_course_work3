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

    // 1. Получаем информационное слово
    QString infoStr = ui->textEdit->toPlainText().trimmed();
    if (infoStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите информационное слово.");
        return;
    }

    // Проверяем, что слово не длиннее infoBitsCount
    if (infoStr.length() > infoBitsCount) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Информационное слово слишком длинное. Максимум %1 бит.").arg(infoBitsCount));
        return;
    }

    // Дополняем нулями слева до нужной длины (можно и справа — по желанию)
    while (infoStr.length() < infoBitsCount) {
        infoStr = "0" + infoStr;
    }

    // 2. Построение проверочной матрицы H (размер k x n)
    vector<vector<int>> H(k, vector<int>(n, 0));
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < k; i++) {
            H[k - 1 - i][j] = ((j + 1) >> i) & 1;
        }
    }

    // 3. Определим, какие позиции — проверочные (степени двойки: 1,2,4,8,...)
    vector<bool> isParity(n, false);
    for (int i = 0; i < k; i++) {
        int pos = (1 << i) - 1;  // 0-индексация: позиции 0,1,3,7,...
        if (pos < n) isParity[pos] = true;
    }

    // 4. Заполняем кодовое слово (пока нулями)
    vector<int> codeWord(n, 0);
    int infoIdx = 0; // индекс в информационной строке

    // Расставляем информационные биты
    for (int i = 0; i < n; i++) {
        if (!isParity[i]) {
            codeWord[i] = infoStr[infoIdx].digitValue();
            infoIdx++;
        }
    }

    // 5. Решаем систему H * codeWord^T = 0 (mod 2) для проверочных битов
    // Каждый проверочный бит p_j связан с определённым уравнением:
    // строка H_j * codeWord = 0 (j = 0..k-1)
    // Проверочный бит p_j стоит на позиции (2^j - 1)
    // Уравнение: p_j + сумма по информационным битам (H[j][i] * codeWord[i]) = 0 mod 2
    // => p_j = сумма по тем информационным битам, где H[j][i] == 1

    for (int j = 0; j < k; j++) {
        int parityPos = (1 << j) - 1;
        if (parityPos >= n) continue;

        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (i != parityPos && H[j][i] == 1) {
                sum ^= codeWord[i];  // XOR = сложение по модулю 2
            }
        }
        codeWord[parityPos] = sum;
    }

    // 6. Вывод результата
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

    ui->textEdit_2->setPlainText(result);
}

//кнопка перехода к окну 3
void Second_window::on_decode_Button_2_clicked()
{
    hide();
    Third_window window;
    window.setModal(true);
    window.exec();
}



