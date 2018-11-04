#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QToolBar>
#include <list>

#include "adddatastructure.h"
#include "addunit.h"
#include "splitqueues.h"
#include "mergedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDefaultConfigs();
    void setDefaultActionsConfigs();
    void setUnitActionConfigs(bool flag);
    void setStructActionConfigs(bool flag);

    void msgboxOutput(QString, QString, QString);
    void updateMainWindow(QString);

    void removeDataStruct();
    bool isDublicate(QString);

    void execDialogForm(QDialog *mDialog);

    std::list<MyQMergeQueue<int>>::iterator findQueue(const QString&arg);

private slots:
    void on_actionAddStruct_triggered();

    void on_StructsList_activated(const QString &arg1);

    void on_actionAddUnit_triggered();

    void on_actionRemoveUnit_triggered();

    void on_actionRemoveStruct_triggered();

    void on_actionSplitTreap_triggered();

    void on_actionMergeTreaps_triggered();

    void on_actionAddRandUnit_triggered();

private:
    Ui::MainWindow *ui;

    AddDataStructure* mAddDataStructureWidget;
    AddUnit* mAddUnitWidget;
    SplitQueues* mSplitQueuesWidget;
    MergeDialog* mMergeQueueWidget;

    std::list<MyQMergeQueue<int>>::iterator mIterator;
    std::list<MyQMergeQueue<int>> mMergeQueues;

};

#endif // MAINWINDOW_H
