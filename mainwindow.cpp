#include "mainwindow.h"
#include "earth_view.h"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), earth_view(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(900, 650); //Main window size

    earth_view = new class earth_view(nullptr);



    // RESOURCES TAB
    // Adding spacecraft on tree widget (resources tab)
    QTreeWidgetItem *spacecraftRoot = new QTreeWidgetItem(ui->resourcesTreeWidget);
    spacecraftRoot->setText(0, "Spacecraft");
    QTreeWidgetItem *spacecraft1 = new QTreeWidgetItem(spacecraftRoot);
    spacecraft1->setText(0, "Spacecraft 1");
    QTreeWidgetItem *spacecraft2 = new QTreeWidgetItem(spacecraftRoot);
    spacecraft2->setText(0, "Spacecraft 2");

    // Adding meteor on tree widget (resources tab)
    QTreeWidgetItem *meteorRoot = new QTreeWidgetItem(ui->resourcesTreeWidget);
    meteorRoot->setText(0, "Meteor");
    QTreeWidgetItem *meteor1 = new QTreeWidgetItem(meteorRoot);
    meteor1->setText(0, "Meteor 1");
    QTreeWidgetItem *meteor2 = new QTreeWidgetItem(meteorRoot);
    meteor2->setText(0, "Meteor 2");

    // Adding satellite on tree widget (resources tab)
    QTreeWidgetItem *satelliteRoot = new QTreeWidgetItem(ui->resourcesTreeWidget);
    satelliteRoot->setText(0, "Satellite");
    QTreeWidgetItem *satellite1 = new QTreeWidgetItem(satelliteRoot);
    satellite1->setText(0, "Satellite 1");
    QTreeWidgetItem *satellite2 = new QTreeWidgetItem(satelliteRoot);
    satellite2->setText(0, "Satellite 2");


    ui->resourcesTreeWidget->expandAll();
    ui->tabWidget->setCurrentIndex(0);


    // MISSION TAB
    // Adding spacecraft on tree widget (mission tab)
    QTreeWidgetItem *spacecraftMissionRoot = new QTreeWidgetItem(ui->missionTreeWidget);
    spacecraftMissionRoot->setText(0, "Spacecraft");
    QTreeWidgetItem *spacecraftMission1 = new QTreeWidgetItem(spacecraftMissionRoot);
    spacecraftMission1->setText(0, "Spacecraft 1");
    QTreeWidgetItem *spacecraftMission2 = new QTreeWidgetItem(spacecraftMissionRoot);
    spacecraftMission2->setText(0, "Spacecraft 2");

    // Adding meteor on tree widget (mission tab)
    QTreeWidgetItem *meteorMissionRoot = new QTreeWidgetItem(ui->missionTreeWidget);
    meteorMissionRoot->setText(0, "Meteor");
    QTreeWidgetItem *meteorMission1 = new QTreeWidgetItem(meteorMissionRoot);
    meteorMission1->setText(0, "Meteor 1");
    QTreeWidgetItem *meteorMission2 = new QTreeWidgetItem(meteorMissionRoot);
    meteorMission2->setText(0, "Meteor 2");

    // Adding satellite on tree widget (mission tab)
    QTreeWidgetItem *satelliteMissionRoot = new QTreeWidgetItem(ui->missionTreeWidget);
    satelliteMissionRoot->setText(0, "Satellite");
    QTreeWidgetItem *satelliteMission1 = new QTreeWidgetItem(satelliteMissionRoot);
    satelliteMission1->setText(0, "Satellite 1");
    QTreeWidgetItem *satelliteMission2 = new QTreeWidgetItem(satelliteMissionRoot);
    satelliteMission2->setText(0, "Satellite 2");


    ui->missionTreeWidget->expandAll();
    ui->tabWidget->setCurrentIndex(1);

}

MainWindow::~MainWindow()
{
    delete ui;
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

