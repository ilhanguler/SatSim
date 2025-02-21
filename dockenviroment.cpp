#include "dockenviroment.h"
#include "ui_dockenviroment.h"

DockEnviroment::DockEnviroment(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::DockEnviroment)
{
    ui->setupUi(this);
}

DockEnviroment::~DockEnviroment()
{
    delete ui;
}
