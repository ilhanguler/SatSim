#include "dockmissions.h"
#include "ui_dockmissions.h"

DockMissions::DockMissions(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::DockMissions)
{
    ui->setupUi(this);
}

DockMissions::~DockMissions()
{
    delete ui;
}
