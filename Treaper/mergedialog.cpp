#include "mergedialog.h"
#include "ui_mergedialog.h"

MergeDialog::MergeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MergeDialog)
{
    ui->setupUi(this);

    setDefaultConfigs();
}

MergeDialog::~MergeDialog()
{
    delete ui;
}

void MergeDialog::RemoveStruct(const QString &name)
{
    for(int it=0; it < ui->ListStructs->count(); it++)
        if(name == ui->ListStructs->item(it)->text())
            delete ui->ListStructs->item(it);
}

void MergeDialog::setDefaultConfigs()
{
    mMergeEnabled = false;
}

bool MergeDialog::isMergeEnabled()
{
    return mMergeEnabled;
}

QString MergeDialog::ChangedName()
{
    return ui->ListStructs->currentItem()->text();
}

void MergeDialog::AddStruct(const QString& name)
{
    ui->ListStructs->addItem(name);
}

void MergeDialog::on_MergeButton_clicked()
{
    mMergeEnabled = true;
    MergeDialog::close();
}

void MergeDialog::on_CancelButton_clicked()
{
    MergeDialog::close();
}
