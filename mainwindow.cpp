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



    // ACTOR 1 TAB
    // Adding spacecrafts on tree widget (ACTOR 1 TAB)
    QTreeWidgetItem *spacecraftsRootTab1 = new QTreeWidgetItem(ui->actor1TreeWidget);
    spacecraftsRootTab1->setText(0, "SPACECRAFTS");
    QTreeWidgetItem *satelliteTab1 = new QTreeWidgetItem(spacecraftsRootTab1);
    satelliteTab1->setText(0, "Satellite");
    QTreeWidgetItem *spaceCapsuleTab1 = new QTreeWidgetItem(spacecraftsRootTab1);
    spaceCapsuleTab1->setText(0, "Space Capsule");

    // Adding actions on tree widget (ACTOR 1 TAB)
    QTreeWidgetItem *actionsRootTab1 = new QTreeWidgetItem(ui->actor1TreeWidget);
    actionsRootTab1->setText(0, "ACTIONS");
    QTreeWidgetItem *action1Tab1 = new QTreeWidgetItem(actionsRootTab1);
    action1Tab1->setText(0, "Action 1");
    QTreeWidgetItem *action2Tab1 = new QTreeWidgetItem(actionsRootTab1);
    action2Tab1->setText(0, "Action 2");

    // Adding events on tree widget (ACTOR 1 TAB)
    QTreeWidgetItem *eventsRootTab1 = new QTreeWidgetItem(ui->actor1TreeWidget);
    eventsRootTab1->setText(0, "EVENTS");
    QTreeWidgetItem *event1Tab1 = new QTreeWidgetItem(eventsRootTab1);
    event1Tab1->setText(0, "Event 1");
    QTreeWidgetItem *event2Tab1 = new QTreeWidgetItem(eventsRootTab1);
    event2Tab1->setText(0, "Event 2");


    ui->actor1TreeWidget->expandAll();
    ui->tabWidget->setCurrentIndex(0);



    // ACTOR 2 TAB
    // Adding spacecrafts on tree widget (ACTOR 2 TAB)
    QTreeWidgetItem *spacecraftsRootTab2 = new QTreeWidgetItem(ui->actor2TreeWidget);
    spacecraftsRootTab2->setText(0, "SPACECRAFTS");
    QTreeWidgetItem *satelliteTab2 = new QTreeWidgetItem(spacecraftsRootTab2);
    satelliteTab2->setText(0, "Satellite");
    QTreeWidgetItem *spaceCapsuleTab2 = new QTreeWidgetItem(spacecraftsRootTab2);
    spaceCapsuleTab2->setText(0, "Space Capsule");

    // Adding actions on tree widget (ACTOR 2 TAB)
    QTreeWidgetItem *actionsRootTab2 = new QTreeWidgetItem(ui->actor2TreeWidget);
    actionsRootTab2->setText(0, "ACTIONS");
    QTreeWidgetItem *action1Tab2 = new QTreeWidgetItem(actionsRootTab2);
    action1Tab2->setText(0, "Action 1");
    QTreeWidgetItem *action2Tab2 = new QTreeWidgetItem(actionsRootTab2);
    action2Tab2->setText(0, "Action 2");

    // Adding events on tree widget (ACTOR 2 TAB)
    QTreeWidgetItem *eventsRootTab2 = new QTreeWidgetItem(ui->actor2TreeWidget);
    eventsRootTab2->setText(0, "EVENTS");
    QTreeWidgetItem *event1Tab2 = new QTreeWidgetItem(eventsRootTab2);
    event1Tab2->setText(0, "Event 1");
    QTreeWidgetItem *event2Tab2 = new QTreeWidgetItem(eventsRootTab2);
    event2Tab2->setText(0, "Event 2");


    ui->actor2TreeWidget->expandAll();
    ui->tabWidget->setCurrentIndex(1);


    // ENVIRONMENT TAB
    // Adding Planets on tree widget (ENVIRONMENT TAB)
    QTreeWidgetItem *planetsRoot = new QTreeWidgetItem(ui->environmentTreeWidget);
    planetsRoot->setText(0, "PLANETS");
    QTreeWidgetItem *earthTreeView = new QTreeWidgetItem(planetsRoot);
    earthTreeView->setText(0, "Earth");
    QTreeWidgetItem *marsTreeView = new QTreeWidgetItem(planetsRoot);
    marsTreeView->setText(0, "Mars");

    // Adding Moon on tree widget (ENVIRONMENT TAB)
    QTreeWidgetItem *moonRoot = new QTreeWidgetItem(ui->environmentTreeWidget);
    moonRoot->setText(0, "MOON");

    // Adding Meteors on tree widget (ENVIRONMENT TAB)
    QTreeWidgetItem *meteorsRoot = new QTreeWidgetItem(ui->environmentTreeWidget);
    meteorsRoot->setText(0, "METEORS");
    QTreeWidgetItem *meteor1TreeView = new QTreeWidgetItem(meteorsRoot);
    meteor1TreeView->setText(0, "Meteor 1");
    QTreeWidgetItem *meteor2TreeView = new QTreeWidgetItem(meteorsRoot);
    meteor2TreeView->setText(0, "Meteor 2");


    ui->environmentTreeWidget->expandAll();
    ui->tabWidget->setCurrentIndex(2);



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

