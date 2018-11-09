#include "thunderstruckabout.h"
#include "ui_thunderstruckabout.h"

ThunderstruckAbout::ThunderstruckAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThunderstruckAbout)
{
    ui->setupUi(this);
}

ThunderstruckAbout::~ThunderstruckAbout()
{
    delete ui;
}
