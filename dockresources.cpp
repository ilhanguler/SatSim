#include "dockresources.h"
#include "ui_dockresources.h"

DockResources::DockResources(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::DockResources)
{
    ui->setupUi(this);
}

DockResources::~DockResources()
{
    delete ui;
}
