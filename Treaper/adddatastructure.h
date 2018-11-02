#ifndef ADDDATASTRUCTURE_H
#define ADDDATASTRUCTURE_H

#include <QDialog>

#include <myqdatastructure.h>

namespace Ui {
class AddDataStructure;
}

class AddDataStructure : public QDialog
{
    Q_OBJECT

public:
    explicit AddDataStructure(QDialog *parent = nullptr);
    ~AddDataStructure();

    bool isCreateEnabled();
    void setCreateEnabled(bool flag);
    void setDefaultConfigs();

    MyQDataStructure structImpl();

private slots:
    void on_CancelButton_clicked();
    void on_CreateButton_clicked();

private:
    Ui::AddDataStructure *ui;

    bool mCreateEnabled;
    MyQDataStructure mStruct;
};

#endif // ADDDATASTRUCTURE_H
