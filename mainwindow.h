#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <iostream>
#include "Archive.h"
#include "Compress.h"
#include "Decompress.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QString getStem(const QString &filePath);//从绝对路径中取出去一次后缀文件名

private slots:
    void on_okPushButton_clicked();

    void on_sourceToolButton_clicked();

    void on_uOkPushButton_clicked();

    void on_uSourceToolButton_clicked();

    void on_uTargetToolButton_clicked();

    void activateUnpack();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
