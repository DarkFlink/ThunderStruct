#ifndef ADDUNIT_H
#define ADDUNIT_H

#include <QDialog>

namespace Ui {
class AddUnit;
}

class AddUnit : public QDialog
{
    Q_OBJECT

public:
    explicit AddUnit(QWidget *parent = nullptr);
    ~AddUnit();

    void setDefaultConfigs();
    bool isCreateEnabled();
    int data();

    bool isOK();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddUnit *ui;

    int mData;
    bool mCreateEnabled;
    bool mErrors;
};

#endif // ADDUNIT_H
