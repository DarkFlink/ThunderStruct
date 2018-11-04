#include "splitqueues.h"
#include "ui_splitqueues.h"

SplitQueues::SplitQueues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplitQueues)
{
    ui->setupUi(this);
    setDefaultConfigs();
}

SplitQueues::~SplitQueues()
{
    delete ui;
}

void SplitQueues::setDefaultConfigs()
{
    mSplitEnabled = false;
    mName1 = "";
    mName2 = "";
}

bool SplitQueues::isSplitEnabled()
{
    return mSplitEnabled;
}

size_t SplitQueues::data()
{
    return mData;
}

QString &SplitQueues::Name1()
{
    return mName1;
}

QString &SplitQueues::Name2()
{
    return mName2;
}

void SplitQueues::on_buttonBox_accepted()
{
    mSplitEnabled = true;
    mData = ui->IndexField->displayText().toULong();
    mName1 = ui->LeftNameField->displayText();
    mName2 = ui->RightNameField->displayText();
    SplitQueues::close();
}

void SplitQueues::on_buttonBox_rejected()
{
    SplitQueues::close();
}
