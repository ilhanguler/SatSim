#ifndef EARTHVIEW_H
#define EARTHVIEW_H

#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QOrbitCameraController>

namespace Ui {
class earthView;
}

class earthView : public QWidget
{
    Q_OBJECT

public:
    explicit earthView(QWidget *parent = nullptr);
    ~earthView();

private:

    Ui::earthView *ui;

    Qt3DExtras::Qt3DWindow *view;
    QWidget *container;
    Qt3DCore::QEntity *rootEntity;
};

#endif // EARTHVIEW_H
