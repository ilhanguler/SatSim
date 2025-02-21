#ifndef DOCKRESOURCES_H
#define DOCKRESOURCES_H

#include <QDockWidget>

namespace Ui {
class DockResources;
}

class DockResources : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockResources(QWidget *parent = nullptr);
    ~DockResources();

private:
    Ui::DockResources *ui;
};

#endif // DOCKRESOURCES_H
