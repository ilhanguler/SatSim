#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "earthview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    earthView *earth;

};
#endif // MAINWINDOW_H
