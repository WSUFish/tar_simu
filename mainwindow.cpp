#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sourceLineEdit, SIGNAL(textChanged(const QString &)),this, SLOT(activatePack()));
    connect(ui->targetLineEdit, SIGNAL(textChanged(const QString &)),this, SLOT(activatePack()));
    connect(ui->uSourceLineEdit, SIGNAL(textChanged(const QString &)),this, SLOT(activateUnpack()));
    connect(ui->uTargetLineEdit, SIGNAL(textChanged(const QString &)),this, SLOT(activateUnpack()));
}

MainWindow::~MainWindow()
{
    delete packSourceDialog;
    delete ui;
}

QString MainWindow::getStem(const QString &filePath)
{
    QString fileName = filePath.section('/', -1, -1);
    return fileName.section('.', 0, -2);
}

QString MainWindow::getCommParent(QStringList &allPath)
{
    QString prefix = allPath.at(0);
    if(allPath.count()==1){
        return prefix.section('/', 0, -2);
    }

    for(int i=1;i<allPath.count();i++){

    }
    return prefix;
}



std::string MainWindow::getCommParent(std::vector<std::string> &vs)
{
    std::string prefix = vs.at(0);
    if(vs.size()==1){
        QString q = GbkToQ(prefix);
        return QToGbk(q.section("/", 0, -2));
    }
    for(auto &s:vs){
        auto p =std::mismatch(prefix.begin(), prefix.end(), s.begin());
        if(p.first!=prefix.end()){
            prefix.substr(p.first - prefix.begin());
        }
    }
    return prefix;
}




void MainWindow::on_okPushButton_clicked()
{
    QDir workPath = packSourceDialog->directory();
    Archive a(QToGbk(workPath.absolutePath()));
    QStringList allPath = ui->sourceLineEdit->text().split(';');
    std::vector<std::string> vs;
    std::string targetName = QToGbk(ui->targetLineEdit->text());
    for(int i=0;i<allPath.count();i++){
        vs.emplace_back(QToGbk(workPath.relativeFilePath(allPath.at(i))));
    }
//    std::string workpath = getCommParent(vs);
//    std::cout<<"common path is:"<<workpath<<std::endl;
    try {
        targetName += ".tar";
        a.create(targetName, vs);
        if(ui->compressCheckBox->isChecked()){
            Compress c(targetName);
            c.genCompressed(targetName+".hfz");
            QFile::remove(GbkToQ(targetName));
        }

        ui->sourceLineEdit->clear();
        ui->targetLineEdit->clear();
        QMessageBox::information(this, QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("备份成功"));
    }  catch (const std::runtime_error &e) {

        QString errorText =QString::fromLocal8Bit(e.what());
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"),errorText);
    }
}

void MainWindow::on_sourceToolButton_clicked()
{

    //QString filter=QString::fromLocal8Bit("所有文件(*.*)");

    if(packSourceDialog == nullptr){
        QString curPath = QDir::rootPath();
        QString dlgTitle=QString::fromLocal8Bit("选择需要备份的文件/文件夹");
        QString lookLabel=QString::fromLocal8Bit("当前目录");
        QString fnLabel=QString::fromLocal8Bit("文件名");
        QString ftLabel=QString::fromLocal8Bit("文件类型");
        packSourceDialog = new MultiFileDirDialog(this);
        packSourceDialog->setWindowTitle(dlgTitle);
        packSourceDialog->setDirectory(curPath);
        packSourceDialog->findChild<QLabel *>("lookInLabel")->setText(lookLabel);
        packSourceDialog->findChild<QLabel *>("fileNameLabel")->setText(fnLabel);
        packSourceDialog->findChild<QLabel *>("fileTypeLabel")->setText(ftLabel);

    }
//    auto wl =packSourceDialog->findChildren<QWidget *>();
//    for(auto &w:wl){
//        std::cout<<QToGbk(w->objectName())<<" : "
//            <<QToGbk(w->metaObject()->className())
//            <<std::endl;
//    }
    packSourceDialog->exec();
    if(packSourceDialog->result()==QDialog::Rejected){
        return;
    }
    QStringList fileList=packSourceDialog->selectedFiles();
    //QStringList fileList2=QFileDialog::getOpenFileNames(this,dlgTitle,curPath,filter);
    QString allFile = "";
    for (int i=0; i<fileList.count();i++){
        allFile.append(fileList.at(i));
    }

    ui->sourceLineEdit->setText(fileList.join(";"));
}

void MainWindow::on_uOkPushButton_clicked()
{
    Archive a;
    QString targetPath = ui->uTargetLineEdit->text();
    QString packageName = ui->uSourceLineEdit->text();
    std::string sPackage = QToGbk(packageName);
    try {
        if(packageName.endsWith(".tar.hfz")){
            Decompress d(sPackage);
            d.decompress(sPackage+".temp");
            a.extract(QToGbk(targetPath) , sPackage+".temp");
            QFile::remove(GbkToQ(sPackage+".temp"));
        }else if(packageName.endsWith(".hfz")){
            Decompress d(sPackage);
            d.decompress(QToGbk(targetPath + "/" +getStem(packageName)));
        }
        else{
            a.qExtract(targetPath, packageName);
        }
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
    QString filter=QString::fromLocal8Bit("备份文件(*.tar *.hfz)");
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

void MainWindow::activatePack()
{
    if(ui->sourceLineEdit->text()!="" && ui->targetLineEdit->text()!=""){
        ui->okPushButton->setDisabled(false);
    }else{
        ui->okPushButton->setDisabled(true);
    }
}

void MainWindow::on_targetToolButton_clicked()
{
    QString curPath;
    if(packSourceDialog!=nullptr){
        QDir workPath = packSourceDialog->directory();
        curPath = workPath.absolutePath()+"/"+workPath.dirName()+ ".tar";
    }else{
        curPath = QDir::rootPath();
        curPath += "/package.tar";
    }
    QString dlgTitle=QString::fromLocal8Bit("选择备份位置");
    QString filter=QString::fromLocal8Bit("备份文件(*.tar *.hfz)");
    QString filePath= QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
            //QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(filePath.length()!=0){
        ui->targetLineEdit->setText(filePath.section('.', 0, -2));
    }
}
