#ifndef DOCKENVIROMENT_H
#define DOCKENVIROMENT_H

#include <QDockWidget>

namespace Ui {
class DockEnviroment;
}

class DockEnviroment : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockEnviroment(QWidget *parent = nullptr);
    ~DockEnviroment();

private:
    Ui::DockEnviroment *ui;
};

#endif // DOCKENVIROMENT_H
