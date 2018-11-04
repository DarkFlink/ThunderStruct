#include "adddatastructure.h"
#include "ui_adddatastructure.h"

AddDataStructure::
AddDataStructure(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AddDataStructure)
{
    ui->setupUi(this);

    ui->Structure->addItem("MergeQueue");

    mCreateEnabled = false;
}

AddDataStructure::~AddDataStructure()
{
    delete ui;
}

bool AddDataStructure::isCreateEnabled()
{
    return mCreateEnabled;
}

void AddDataStructure::setCreateEnabled(bool flag)
{
    mCreateEnabled = flag;
}

void AddDataStructure::setDefaultConfigs()
{
    mCreateEnabled = false;
    mStruct.setData("None", "Node");
}

MyQDataStructure AddDataStructure::structImpl()
{
    return mStruct;
}

void AddDataStructure::on_CancelButton_clicked()
{
    AddDataStructure::close();
}

void AddDataStructure::on_CreateButton_clicked()
{
    mCreateEnabled = true;
    mStruct.setData(ui->NameField->displayText(), ui->Structure->currentText());
    AddDataStructure::close();
}
