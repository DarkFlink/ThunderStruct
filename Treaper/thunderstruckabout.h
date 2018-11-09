#ifndef THUNDERSTRUCKABOUT_H
#define THUNDERSTRUCKABOUT_H

#include <QWidget>

namespace Ui {
class ThunderstruckAbout;
}

class ThunderstruckAbout : public QWidget
{
    Q_OBJECT

public:
    explicit ThunderstruckAbout(QWidget *parent = nullptr);
    ~ThunderstruckAbout();

private:
    Ui::ThunderstruckAbout *ui;
};

#endif // THUNDERSTRUCKABOUT_H
