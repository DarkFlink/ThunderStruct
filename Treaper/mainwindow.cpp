#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mAddDataStructureWidget = new AddDataStructure(nullptr);
    mAddUnitWidget = new AddUnit(nullptr);
    mSplitQueuesWidget = new SplitQueues(nullptr);

    setDefaultActionsConfigs();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mAddDataStructureWidget;
    delete mAddUnitWidget;
    delete mSplitQueuesWidget;
}

void MainWindow::setDefaultActionsConfigs()
{
    ui->actionAddUnit->setDisabled(true);
    ui->actionMergeTreaps->setDisabled(true);
    ui->actionRemoveStruct->setDisabled(true);
    ui->actionRemoveUnit->setDisabled(true);
    ui->actionSplitTreap->setDisabled(true);
    ui->StructInfoBar->setDisabled(true);
}

void MainWindow::setUnitActionConfigs(bool flag)
{
    ui->actionAddUnit->setEnabled(flag);
    ui->actionRemoveUnit->setEnabled(flag);
}

void MainWindow::setStructActionConfigs(bool flag)
{
    ui->actionRemoveStruct->setEnabled(flag);
    ui->actionMergeTreaps->setEnabled(flag);
    ui->actionSplitTreap->setEnabled(flag);
    ui->StructInfoBar->setEnabled(flag);
}

//_________SLOTS_________//

void MainWindow::on_actionAddStruct_triggered()
{
    QPoint mPoint;
    mPoint.setX(MainWindow::width()/3);
    mPoint.setY(MainWindow::height()/3);
    mAddDataStructureWidget->move(MainWindow::mapToGlobal(mPoint));
    mAddDataStructureWidget->exec();

    if(mAddDataStructureWidget->isCreateEnabled())
    {
        QString name = mAddDataStructureWidget->structImpl().UniqueName();
        if(!name.length())
        {
            msgboxOutput("Empty name field.\n Try again", "Error", "ERR");
            return;
        }
        if(isDublicate(name))
        {
                msgboxOutput("Struct with that name is\nalready created. Try again", "Error", "ERR");
                return;
        }
        if(!mMergeQueues.size())
        {
            setUnitActionConfigs(true);
            setStructActionConfigs(true);
        }

        if(mAddDataStructureWidget->structImpl().StructName() == "MergeQueue")
        {
            mMergeQueues.push_front(MyQMergeQueue<int>(mAddDataStructureWidget->structImpl().UniqueName()));
        }
        ui->StructsList->addItem(name);
        on_StructsList_activated(name);
    }
    mAddDataStructureWidget->setDefaultConfigs();
}

void MainWindow::msgboxOutput(QString mMessage, QString mTitle, QString msgType)
{
    QMessageBox* msgBox = new QMessageBox;
    msgBox->setWindowTitle(mTitle);
    msgBox->setText(mMessage);

    if(msgType == "ERR")
        msgBox->setIcon(QMessageBox::Critical);

    QPoint mPoint;
    mPoint.setX(MainWindow::width()/3);
    mPoint.setY(MainWindow::height()/3);
    msgBox->move(MainWindow::mapToGlobal(mPoint));

    msgBox->exec();
    delete msgBox;
}

void MainWindow::updateMainWindow(QString name)
{
    for(std::list<MyQMergeQueue<int>>::iterator i = mMergeQueues.begin(); i != mMergeQueues.end() ; i++)
    {
        if(i->UniqueName() == name)
        {
            mIterator = i;
            //InfoBox
            QString mText;
            mText.setNum(i->mQueue.Size());
            ui->StructSizeField_2->setText(mText);
            mText.clear();
            ui->DataTypeField_2->setText(mText.append(i->StructName()));
            try {
                mText.clear();
                mText = QString("%1").arg(i->mQueue.Top());
                ui->TopElDataField_2->setText(mText);
            } catch (std::out_of_range &err) {
                ui->TopElDataField_2->setText("<NODATA>");
            }

            // Scheme
            mText.clear();
            std::string mScheme;
            i->mQueue.DisplayTreap(mScheme);
            ui->StructScheme->setText(mText.append(mScheme.c_str()));

            // Data print
            mScheme.clear();
            mText.clear();
            i->mQueue.PrintData(mScheme);
            ui->StructElemList->setText(mText.append(mScheme.c_str()));

            break;
        }
    }
}

void MainWindow::removeDataStruct()
{
    mMergeQueues.erase(mIterator);
    ui->StructsList->removeItem(ui->StructsList->currentIndex());
    if(mMergeQueues.size() != 0)
    {
        mIterator = mMergeQueues.begin();
        updateMainWindow(mMergeQueues.begin()->UniqueName());
    }
    else
        setDefaultActionsConfigs();
}

bool MainWindow::isDublicate(QString name)
{
    for(auto i = mMergeQueues.begin(); i != mMergeQueues.end() ; i++)
        if(i->UniqueName() == name)
            return true;
    return false;
}

void MainWindow::on_StructsList_activated(const QString &arg1)
{
    updateMainWindow(arg1);
}

void MainWindow::on_actionAddUnit_triggered()
{
    QPoint mPoint;
    mPoint.setX(MainWindow::width()/3);
    mPoint.setY(MainWindow::height()/3);
    mAddUnitWidget->move(MainWindow::mapToGlobal(mPoint));
    mAddUnitWidget->exec();

    int data = mAddUnitWidget->data();
    mIterator->mQueue.Push(&data);
    updateMainWindow(mIterator->UniqueName());
}

void MainWindow::on_actionRemoveUnit_triggered()
{
    try {
        mIterator->mQueue.Pop();
    } catch (std::out_of_range &err) {
        msgboxOutput(err.what(), "Error", "ERR");
        return;
    }
    updateMainWindow(mIterator->UniqueName());
}

void MainWindow::on_actionRemoveStruct_triggered()
{
    removeDataStruct();
}

void MainWindow::on_actionSplitTreap_triggered()
{
    QPoint mPoint;
    mPoint.setX(MainWindow::width()/3);
    mPoint.setY(MainWindow::height()/3);
    mSplitQueuesWidget->move(MainWindow::mapToGlobal(mPoint));
    mSplitQueuesWidget->exec();

    if(isDublicate(mSplitQueuesWidget->Name1()) || isDublicate(mSplitQueuesWidget->Name2()) || mSplitQueuesWidget->Name2() == mSplitQueuesWidget->Name1())
    {
        msgboxOutput("Duplicating data sturcture names.\n Try again", "Error", "ERR");
        return;
    }

    if(mSplitQueuesWidget->isSplitEnabled()) {
        try {
            mMergeQueues.push_back(MyQMergeQueue<int>(mSplitQueuesWidget->Name1()));
            auto it1 = mMergeQueues.end(); it1--;
            mMergeQueues.push_back(MyQMergeQueue<int>(mSplitQueuesWidget->Name2()));
            auto it2 = it1; it2++;
            mIterator->mQueue.Split(it1->mQueue, it2->mQueue, mSplitQueuesWidget->data());

            ui->StructsList->addItem(mSplitQueuesWidget->Name1());
            ui->StructsList->addItem(mSplitQueuesWidget->Name2());
            removeDataStruct();

        } catch (std::out_of_range &err) {
            msgboxOutput(err.what(), "Error", "ERR");
            return;
        }
    }
//    updateMainWindow(mMergeQueues[current_struct].UniqueName());
}

void MainWindow::on_actionMergeTreaps_triggered()
{

}
