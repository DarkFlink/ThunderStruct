#ifndef SPLITQUEUES_H
#define SPLITQUEUES_H

#include <QDialog>

namespace Ui {
class SplitQueues;
}

class SplitQueues : public QDialog
{
    Q_OBJECT

public:
    explicit SplitQueues(QWidget *parent = nullptr);
    ~SplitQueues();

    void setDefaultConfigs();

    bool isSplitEnabled();
    size_t data();

    QString& Name1();
    QString& Name2();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SplitQueues *ui;

    bool mSplitEnabled;
    size_t mData;

    QString mName1;
    QString mName2;
};

#endif // SPLITQUEUES_H
