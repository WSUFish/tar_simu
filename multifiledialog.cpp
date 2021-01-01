#include "multifiledialog.h"
#include "ui_multifiledialog.h"

MultiFileDialog::MultiFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultiFileDialog)
{
    ui->setupUi(this);
}

MultiFileDialog::~MultiFileDialog()
{
    delete ui;
}
