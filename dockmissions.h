#ifndef DOCKMISSIONS_H
#define DOCKMISSIONS_H

#include <QDockWidget>

namespace Ui {
class DockMissions;
}

class DockMissions : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockMissions(QWidget *parent = nullptr);
    ~DockMissions();

private:
    Ui::DockMissions *ui;
};

#endif // DOCKMISSIONS_H
