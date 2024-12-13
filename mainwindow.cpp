#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "earthview.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(800, 600);


    earth = new earthView();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    earth->show();
    earth->setFixedSize(650, 415);
}

