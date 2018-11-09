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
    mMergeQueueWidget = new MergeDialog(nullptr);
    mAboutWidget = new ThunderstruckAbout(nullptr);

    setDefaultConfigs();
    createFileMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mAddDataStructureWidget;
    delete mAddUnitWidget;
    delete mSplitQueuesWidget;
    delete mMergeQueueWidget;
    delete mAboutWidget;

    delete mMenuFile;
}

void MainWindow::setDefaultConfigs()
{
    setDefaultActionsConfigs();
    ui->StructScheme->clear();
    ui->StructElemList->clear();
    ui->StructSizeField_2->clear();
    ui->TopElDataField_2->clear();
    ui->DataTypeField_2->clear();
}

void MainWindow::setDefaultActionsConfigs()
{
    ui->actionAddUnit->setDisabled(true);
    ui->actionMergeTreaps->setDisabled(true);
    ui->actionStructAbout->setDisabled(true);
    ui->actionRemoveStruct->setDisabled(true);
    ui->actionRemoveUnit->setDisabled(true);
    ui->actionSplitTreap->setDisabled(true);
    ui->StructInfoBar->setDisabled(true);
    ui->actionAddRandUnit->setDisabled(true);
    ui->actionAddTenRandUnits->setDisabled(true);
}

void MainWindow::setUnitActionConfigs(bool flag)
{
    ui->actionAddUnit->setEnabled(flag);
    ui->actionAddRandUnit->setEnabled(flag);
    ui->actionAddTenRandUnits->setEnabled(flag);
    ui->actionRemoveUnit->setEnabled(flag);
}

void MainWindow::setStructActionConfigs(bool flag)
{
    ui->actionRemoveStruct->setEnabled(flag);
    ui->actionMergeTreaps->setEnabled(flag);
    ui->actionSplitTreap->setEnabled(flag);
    ui->actionStructAbout->setEnabled(flag);
    ui->StructInfoBar->setEnabled(flag);
}

void MainWindow::createFileMenu()
{
    mMenuFile = new QMenu;
    mMenuFile->addAction(ui->actionExit);
}

//_________SLOTS_________//

void MainWindow::on_actionAddStruct_triggered()
{
    execDialogForm(mAddDataStructureWidget);
    if(mAddDataStructureWidget->isCreateEnabled())
    {
        QString name = mAddDataStructureWidget->structImpl().UniqueName();
        if(!name.length())
            msgboxOutput("Empty name field.\n Try again", "Error", "ERR");

        else if(isDublicate(name))
            msgboxOutput("Struct with that name is\nalready created. Try again", "Error", "ERR");

        else if(mAddDataStructureWidget->structImpl().StructName() == "MergeQueue")
        {
            mMergeQueues.push_front(MyQMergeQueue<int>(name));
            ui->StructsList->addItem(name);
            mMergeQueueWidget->AddStruct(name);
            if(mMergeQueues.size() == 1)
            {
                setUnitActionConfigs(true);
                setStructActionConfigs(true);
                on_StructsList_activated(name);
            }
        }
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

    execDialogForm(msgBox);
    delete msgBox;
}

void MainWindow::updateMainWindow(QString name)
{
    for(auto i = mMergeQueues.begin(); i != mMergeQueues.end() ; i++)
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
    mMergeQueueWidget->RemoveStruct(ui->StructsList->currentText());
    ui->StructsList->removeItem(ui->StructsList->currentIndex());
    mMergeQueues.erase(mIterator);
    if(mMergeQueues.size() != 0)
    {
        mIterator = mMergeQueues.begin();
        updateMainWindow(mMergeQueues.begin()->UniqueName());
    }
    else
        setDefaultConfigs();
}

bool MainWindow::isDublicate(QString name)
{
    for(auto i = mMergeQueues.begin(); i != mMergeQueues.end() ; i++)
        if(i->UniqueName() == name)
            return true;
    return false;
}

void MainWindow::execDialogForm(QDialog * mDialog)
{
    QPoint mPoint;
    mPoint.setX(MainWindow::width()/3);
    mPoint.setY(MainWindow::height()/3);
    mDialog->move(MainWindow::mapToGlobal(mPoint));
    mDialog->exec();
}

std::list<MyQMergeQueue<int>>::iterator MainWindow::findQueue(const QString &arg)
{
    for(auto it = mMergeQueues.begin(); it != mMergeQueues.end() ;it++)
        if(it->UniqueName() == arg)
            return it;
    return mIterator;
}

void MainWindow::on_StructsList_activated(const QString &arg1)
{
    updateMainWindow(arg1);
}

void MainWindow::on_actionAddUnit_triggered()
{
    execDialogForm(mAddUnitWidget);
    if(mAddUnitWidget->isCreateEnabled())
    {
        if(mAddUnitWidget->isOK())
            msgboxOutput("Invalid input.\n Try again", "Error", "ERR");

        else
        {
            int data = mAddUnitWidget->data();
            mIterator->mQueue.Push(&data);
            updateMainWindow(mIterator->UniqueName());
        }
    }
    mAddUnitWidget->setDefaultConfigs();
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
    execDialogForm(mSplitQueuesWidget);
    if(mSplitQueuesWidget->isSplitEnabled())
    {
        if(isDublicate(mSplitQueuesWidget->Name1()) || isDublicate(mSplitQueuesWidget->Name2()) || mSplitQueuesWidget->Name2() == mSplitQueuesWidget->Name1())
            msgboxOutput("Duplicating data sturcture names.\n Try again", "Error", "ERR");

        else if(mSplitQueuesWidget->data() >= mIterator->mQueue.Size())
            msgboxOutput("Invalid splitter index.\n Try again", "Error", "ERR");

        else if (!mSplitQueuesWidget->Name1().size() || !mSplitQueuesWidget->Name2().size())
            msgboxOutput("Empty name field[s].\n Try again", "Error", "ERR");

        else
        {
            // Add Queues in array
            mMergeQueues.push_back(MyQMergeQueue<int>(mSplitQueuesWidget->Name1()));
            auto it1 = mMergeQueues.end(); it1--;
            mMergeQueues.push_back(MyQMergeQueue<int>(mSplitQueuesWidget->Name2()));
            auto it2 = it1; it2++;

            mIterator->mQueue.Split(it1->mQueue, it2->mQueue, mSplitQueuesWidget->data());

            // Add queues in interface
            ui->StructsList->addItem(mSplitQueuesWidget->Name1());
            mMergeQueueWidget->AddStruct(mSplitQueuesWidget->Name1());
            ui->StructsList->addItem(mSplitQueuesWidget->Name2());
            mMergeQueueWidget->AddStruct(mSplitQueuesWidget->Name2());
            removeDataStruct();
        }
        mSplitQueuesWidget->setDefaultConfigs();
    }
}

void MainWindow::on_actionMergeTreaps_triggered()
{
    execDialogForm(mMergeQueueWidget);
    if(mMergeQueueWidget->isMergeEnabled())
    {
        if(mMergeQueueWidget->ChangedName() == mIterator->UniqueName())
            msgboxOutput("Cannot merge queue by itself.\n Change another queue", "Warning", "WARN");
        else
        {
            auto mFirst = findQueue(mMergeQueueWidget->ChangedName());
            mIterator->mQueue.Merge(mFirst->mQueue);
            updateMainWindow(mIterator->UniqueName());
        }
    }
    mMergeQueueWidget->setDefaultConfigs();
    ui->statusBar->showMessage("fwe");
}

void MainWindow::on_actionAddRandUnit_triggered()
{
    int data = std::rand() % 1000;
    mIterator->mQueue.Push(&data);
    updateMainWindow(mIterator->UniqueName());
}

void MainWindow::on_actionAddTenRandUnits_triggered()
{
    for(int i=0; i<10; i++)
        on_actionAddRandUnit_triggered();
}

void MainWindow::on_actionFile_triggered()
{
    QPoint mo;
    mo.setX(ui->ToolbarMenu->pos().x()+4);
    mo.setY(ui->ToolbarMenu->pos().y()+46);
    mMenuFile->move(ui->ToolbarMenu->mapToGlobal(mo));

    if(!ui->actionFile->isCheckable())
        ui->actionFile->setCheckable(true);

    ui->actionFile->setChecked(true);
    mMenuFile->exec();
    ui->actionFile->setChecked(false);
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox msgBox;
    msgBox.setPalette(MainWindow::palette());
    QPoint mPoint;
    mPoint.setX(MainWindow::width()/3);
    mPoint.setY(MainWindow::height()/3);
    msgBox.move(MainWindow::mapToGlobal(mPoint));
    msgBox.setWindowTitle("Exit");
    msgBox.setText("Are you sure want\n          to exit?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    int res = msgBox.exec();
    if(res == QMessageBox::Ok)
        MainWindow::close();
    else
        msgBox.close();
}

void MainWindow::on_actionAbout_triggered()
{
    QPoint mPoint;
    mPoint.setX(MainWindow::width()/3);
    mPoint.setY(MainWindow::height()/3);
    mAboutWidget->move(MainWindow::mapToGlobal(mPoint));
    mAboutWidget->show();
}

void MainWindow::on_actionStructAbout_triggered()
{
    AboutDataStructure mDialog;
    mDialog.SetMergeQueueDefinition();
    execDialogForm(&mDialog);
}
