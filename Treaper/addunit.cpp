#include "addunit.h"
#include "ui_addunit.h"

AddUnit::AddUnit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUnit)
{
    ui->setupUi(this);

    mData = 0;
    mCreateEnabled = false;
    setDefaultConfigs();
}

AddUnit::~AddUnit()
{
    delete ui;
}

void AddUnit::setDefaultConfigs()
{
    ui->RadioDataTypeInt->setChecked(true);
}

bool AddUnit::isCreateEnabled()
{
    return mCreateEnabled;
}

int AddUnit::data()
{
    return mData;
}

void AddUnit::on_buttonBox_accepted()
{
    mCreateEnabled = true;
    mData = ui->InputField->displayText().toInt();
    AddUnit::close();
}

void AddUnit::on_buttonBox_rejected()
{
    AddUnit::close();
}
