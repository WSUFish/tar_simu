#ifndef MULTIFILEDIRDIALOG_H
#define MULTIFILEDIRDIALOG_H

#include <QObject>
#include <QFileDialog>

class MultiFileDirDialog : public QFileDialog
{
    Q_OBJECT
public:
    explicit MultiFileDirDialog(QWidget *parent = nullptr);

public slots:
    void onChiose();

signals:

};

#endif // MULTIFILEDIRDIALOG_H
