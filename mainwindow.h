#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "earth_view.h"

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

private slots:

    void on_simulateButton_clicked();
    void on_forwardButton_clicked();

private:

    Ui::MainWindow *ui;
    earth_view *earth_view;

};
#endif // MAINWINDOW_H
