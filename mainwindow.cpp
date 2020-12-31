#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->uSourceLineEdit, SIGNAL(textChanged(const QString &)),this, SLOT(activateUnpack()));
    connect(ui->uTargetLineEdit, SIGNAL(textChanged(const QString &)),this, SLOT(activateUnpack()));
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_okPushButton_clicked()
{

}

void MainWindow::on_sourceToolButton_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle=QString::fromLocal8Bit("选择多个文件");
    QString filter=QString::fromLocal8Bit("所有文件(*.*)");
    QStringList fileList=QFileDialog::getOpenFileNames(this,dlgTitle,curPath,filter);
//    QString allFile = "";
//    for (int i=0; i<fileList.count();i++){
//        allFile.append(fileList.at(i));
//    }

    ui->sourceLineEdit->setText(fileList.join(";"));
}

void MainWindow::on_uOkPushButton_clicked()
{
    Archive a;
    try {
        a.qExtract(ui->uTargetLineEdit->text(), ui->uSourceLineEdit->text());
        ui->uSourceLineEdit->clear();
        ui->uTargetLineEdit->clear();
        QMessageBox::information(this, QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("恢复成功"));
    }  catch (const std::runtime_error &e) {
        QString errorText =QString::fromLocal8Bit(e.what());
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"),errorText);
    }
}

void MainWindow::on_uSourceToolButton_clicked()
{
    QString curPath = QDir::rootPath();
    QString dlgTitle=QString::fromLocal8Bit("选择一个备份文件");
    QString filter=QString::fromLocal8Bit("备份文件(*.tar);;压缩文件(*.hfz)");
    QString filePath=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(filePath.length()!=0){
        ui->uSourceLineEdit->setText(filePath);
    }
}

void MainWindow::on_uTargetToolButton_clicked()
{
    QString curPath = QDir::rootPath();
    QString dlgTitle=QString::fromLocal8Bit("选择恢复位置");
    QString filePath= QFileDialog::getExistingDirectory(this, dlgTitle, curPath);
            //QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(filePath.length()!=0){
        ui->uTargetLineEdit->setText(filePath);
    }
}

void MainWindow::activateUnpack()
{
    if(ui->uSourceLineEdit->text()!="" && ui->uTargetLineEdit->text()!=""){
        ui->uOkPushButton->setDisabled(false);
    }else{
        ui->uOkPushButton->setDisabled(true);
    }
}
