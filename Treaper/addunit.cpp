#include "addunit.h"
#include "ui_addunit.h"

AddUnit::AddUnit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUnit)
{
    ui->setupUi(this);

    mData = 0;
    mCreateEnabled = false;
    mErrors = false;
    setDefaultConfigs();
}

AddUnit::~AddUnit()
{
    delete ui;
}

void AddUnit::setDefaultConfigs()
{
    mCreateEnabled = false;
    mErrors = false;
}

bool AddUnit::isCreateEnabled()
{
    return mCreateEnabled;
}

int AddUnit::data()
{
    return mData;
}

bool AddUnit::isOK()
{
    return mErrors;
}

void AddUnit::on_buttonBox_accepted()
{
    bool ok;
    mData = ui->InputField->displayText().toInt(&ok);
    if(!ok)
        mErrors = true;

    mCreateEnabled = true;
    AddUnit::close();
}

void AddUnit::on_buttonBox_rejected()
{
    AddUnit::close();
}
