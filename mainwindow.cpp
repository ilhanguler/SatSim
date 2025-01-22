#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), earth_view(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setFixedSize(850, 650); //Main window size

    simGui.initRoots(ui->playersTreeWidget, ui->environmentTreeWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete earth_view;
}

void MainWindow::populateTree()
{
    for(const auto &p : sim.players){
        simGui.addPlayerItem(p.second.id);
        for(const auto &v : p.second.vehicles){
            simGui.addVehicleItem(p.second.id, v.id);
        }
    }

    for(const auto &cb : sim.enviroment.celestialBodies){
        simGui.addCelestialItem(cb.id);
    }

    for(const auto &s : sim.enviroment.strayEntities){
        simGui.addStrayItem(s.id);
    }
}

void MainWindow::on_loadButton_clicked()
{
    sceneManager.loadScene(":/scenes/scene1.json", sim);
    populateTree();
}

void MainWindow::on_loadButton_2_clicked()
{
    sceneManager.loadScene(":/scenes/scene2.json", sim);
    populateTree();
}

void MainWindow::on_simulateButton_clicked()
{
    earth_view->show();
    //earth_view->setFixedSize(620, 400); //Earth window size
    earth_view->raise();
}

void MainWindow::on_forwardButton_clicked()
{
    earth_view->show();
    //earth_view->setFixedSize(620, 400); //Earth window size
    earth_view->raise();
}

void MainWindow::on_thrustButton_clicked()
{

}

void MainWindow::on_trainButton_clicked()
{

}


void MainWindow::on_analysisButton_clicked()
{

}

