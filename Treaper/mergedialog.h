#ifndef MERGEDIALOG_H
#define MERGEDIALOG_H

#include <QDialog>

namespace Ui {
class MergeDialog;
}

class MergeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MergeDialog(QWidget *parent = nullptr);
    ~MergeDialog();

    void AddStruct(const QString &name);
    void RemoveStruct(const QString& name);

    void setDefaultConfigs();
    bool isMergeEnabled();

    QString ChangedName();

private slots:
    void on_MergeButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::MergeDialog *ui;

    bool mMergeEnabled;
};

#endif // MERGEDIALOG_H
