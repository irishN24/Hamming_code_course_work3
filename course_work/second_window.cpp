#include "second_window.h"
#include "ui_second_window.h"

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
