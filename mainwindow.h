#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "earth_view.h"
#include "scenemanager.h"
#include "simdriver.h"
#include "simguimanager.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void populateTree();

    SceneManager sceneManager;
    SimDriver sim;
    SimGuiManager simGui;

private slots:

    void on_loadButton_clicked();

    void on_loadButton_2_clicked();

    void on_simulateButton_clicked();

    void on_forwardButton_clicked();

    void on_thrustButton_clicked();

    void on_trainButton_clicked();

    void on_analysisButton_clicked();

private:

    Ui::MainWindow *ui;
    earth_view *earth_view;

};
#endif // MAINWINDOW_H
