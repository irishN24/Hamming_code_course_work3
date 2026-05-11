#include "third_window.h"
#include "ui_third_window.h"
#include "second_window.h"
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

void Third_window::setM(int m)
{
    m_value = m;
    qDebug() << "Third_window: m_value set to" << m_value;
}

void Third_window::setVerificationMatrix(const std::vector<std::vector<int>>& matrix)
{
    H = matrix;
    qDebug() << "Third_window: verification matrix received, size:" << H.size() << "x" << (H.empty() ? 0 : H[0].size());
}

void Third_window::on_exit_Button_2_clicked()
{
    QApplication::quit();
}

void Third_window::on_back_Button_3_clicked()
{
    this->close();
    Second_window *secondWin = new Second_window();
    secondWin->setM(m_value);
    secondWin->setAttribute(Qt::WA_DeleteOnClose);
    secondWin->show();
}

void Third_window::on_decode_Button_3_clicked()
{
    if (m_value < 1 || m_value >= 10) {
        QMessageBox::warning(this, "Ошибка", "Параметр m не задан. Сначала вернитесь в главное окно и введите m.");
        return;
    }

    QString codeWordStr = ui->textEdit->toPlainText().trimmed();

    if (codeWordStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите кодовое слово для декодирования");
        return;
    }

    int k = m_value;              // количество проверочных битов
    int n = (1 << k) - 1;         // длина кодового слова
    int infoBitsCount = n - k;    // количество информационных битов

    if (codeWordStr.length() != n) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Кодовое слово должно иметь длину %1 бит (при m=%2)").arg(n).arg(m_value));
        return;
    }

    for (QChar ch : codeWordStr) {
        if (ch != '0' && ch != '1') {
            QMessageBox::warning(this, "Ошибка", "Кодовое слово должно содержать только 0 и 1");
            return;
        }
    }

    vector<int> receivedWord(n);
    for (int i = 0; i < n; i++) {
        receivedWord[i] = codeWordStr[i].digitValue();
    }

    // Проверочная матрица (как в кодировании)
    if (H.empty() || H.size() != k || H[0].size() != n) {
        H.assign(k, vector<int>(n, 0));
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < k; i++) {
                H[k - 1 - i][j] = ((j + 1) >> i) & 1;
            }
        }
        qDebug() << "Third_window: Matrix recalculated, size:" << H.size() << "x" << H[0].size();
    }

    // Вычисление синдрома (прямой порядок, без инверсии)
    vector<int> syndrome(k, 0);
    for (int i = 0; i < k; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum ^= (H[i][j] & receivedWord[j]);
        }
        syndrome[i] = sum;
    }

    // Определение позиции ошибки (прямой порядок битов)
    int errorPos = 0;
    for (int i = 0; i < k; i++) {
        errorPos |= (syndrome[i] << (k - 1 - i));
    }

    QString result;
    result += "Полученное кодовое слово (" + QString::number(n) + " бит): " + codeWordStr + "\n";

    QString syndromeStr;
    for (int bit : syndrome) {
        syndromeStr += QString::number(bit);
    }
    result += "Синдром: " + syndromeStr + "\n";

    vector<int> correctedWord = receivedWord;
    if (errorPos != 0) {
        result += "Обнаружена ошибка в позиции: " + QString::number(errorPos) + "\n";
        if (errorPos - 1 < n) {
            correctedWord[errorPos - 1] ^= 1;
            result += "Ошибка исправлена.\n";
        }
    } else {
        result += "Ошибок не обнаружено.\n";
    }

    QString correctedStr;
    for (int bit : correctedWord) {
        correctedStr += QString::number(bit);
    }
    result += "Исправленное кодовое слово: " + correctedStr + "\n";

    // Определение позиций проверочных битов
    vector<bool> isParity(n, false);
    for (int i = 0; i < k; i++) {
        int pos = (1 << i) - 1;
        if (pos < n) isParity[pos] = true;
    }

    // Извлечение информационных битов (пропуская проверочные)
    QString infoBits;
    for (int i = 0; i < n; i++) {
        if (!isParity[i]) {
            infoBits += QString::number(correctedWord[i]);
        }
    }

    // Удаляем ведущие нули для удобства (не обязательно)
    infoBits = infoBits.trimmed(); // или оставить как есть

    result += "\nДекодированное информационное слово (" + QString::number(infoBitsCount) + " бит): " + infoBits;

    ui->textEdit_2->setPlainText(result);
}
