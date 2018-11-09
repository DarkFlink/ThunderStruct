#ifndef ABOUTDATASTRUCTURE_H
#define ABOUTDATASTRUCTURE_H

#include <QDialog>

namespace Ui {
class AboutDataStructure;
}

class AboutDataStructure : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDataStructure(QWidget *parent = nullptr);
    ~AboutDataStructure();

    void SetMergeQueueDefinition();

private:
    Ui::AboutDataStructure *ui;
};

#endif // ABOUTDATASTRUCTURE_H
