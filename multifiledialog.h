#ifndef MULTIFILEDIALOG_H
#define MULTIFILEDIALOG_H

#include <QDialog>

namespace Ui {
class MultiFileDialog;
}

class MultiFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MultiFileDialog(QWidget *parent = nullptr);
    ~MultiFileDialog();

private:
    Ui::MultiFileDialog *ui;
};

#endif // MULTIFILEDIALOG_H
