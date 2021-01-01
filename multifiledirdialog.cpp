#include "multifiledirdialog.h"
#include <QListView>
#include <QTreeView>
#include <QDialogButtonBox>

MultiFileDirDialog::MultiFileDirDialog(QWidget *parent) : QFileDialog(parent)
{
    this->setOption(QFileDialog::DontUseNativeDialog,true);

        //支持多选
        QListView *pListView = this->findChild<QListView*>("listView");
        if (pListView)
            pListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        QTreeView *pTreeView = this->findChild<QTreeView*>();
        if (pTreeView)
            pTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        QDialogButtonBox *pButton = this->findChild<QDialogButtonBox *>("buttonBox");


        disconnect(pButton, SIGNAL(accepted()), this, SLOT(accept()));//使链接失效
        connect(pButton, SIGNAL(accepted()), this, SLOT(onChiose()));//改成自己的槽
}

void MultiFileDirDialog::onChiose()
{
    QDialog::accept();
}
