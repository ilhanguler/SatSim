#ifndef EARTH_VIEW_H
#define EARTH_VIEW_H

#include <QWidget>
#include <QTimer>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>


namespace Ui {
class earth_view;
}

class earth_view : public QWidget
{
    Q_OBJECT

public:
    explicit earth_view(QWidget *parent = nullptr);
    ~earth_view();

private:

    Ui::earth_view *ui;
    QWidget *container;
    Qt3DExtras::Qt3DWindow *view;
    Qt3DCore::QEntity *rootEntity;
    Qt3DCore::QEntity *meteorEntity;
    Qt3DCore::QTransform *meteorTransform;
    Qt3DCore::QEntity *spacecraftEntity;
    Qt3DCore::QTransform *spacecraftTransform;


private slots:

    void moveMeteor();
    void moveSpacecraft();

};

#endif // EARTH_VIEW_H
