#ifndef EARTH_VIEW_H
#define EARTH_VIEW_H

#include <QVBoxLayout>
#include <QDebug>
#include <QWidget>
#include <QTimer>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DCore/QBuffer>
#include <Qt3DCore/QAttribute>
#include <Qt3DExtras/QOrbitCameraController>

#include "ui_earth_view.h"

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
    Qt3DCore::QEntity *orbitEntity;        // Yörünge çizen varlık
    Qt3DCore::QGeometry *orbitGeometry;    // Yörünge geometrisi
    Qt3DCore::QAttribute *positionAttribute;
    Qt3DCore::QBuffer *positionBuffer;     // Konum verilerini tutan tampon
    QVector<QVector3D> orbitPoints;        // Yörünge noktaları

    // Camera controller
    Qt3DRender::QCamera *camera;
    Qt3DExtras::QOrbitCameraController *camController;

    void updateOrbit(); // Yörüngeyi güncelleyen fonksiyon

private slots:

    void moveMeteor();
    void moveSpacecraft();

};

#endif // EARTH_VIEW_H
