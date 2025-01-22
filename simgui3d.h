#ifndef SIMGUI3D_H
#define SIMGUI3D_H

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DCore/QBuffer>
#include <Qt3DCore/QAttribute>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QGeometry>
#include <QRandomGenerator>
#include <qfiledevice.h>

class Trajectory3D : public Qt3DCore::QEntity
{
public:
    Trajectory3D(Qt3DCore::QEntity* root);

    void setTrajectory(const QVector<QVector3D> &trajectory, const QVector<unsigned int> &indices, const QColor &color);

    void clearTrajectory();

    Qt3DCore::QEntity *root;
    Qt3DRender::QGeometryRenderer *renderer;
    Qt3DCore::QGeometry *geometry;
    Qt3DCore::QAttribute *indexAttribute;
    Qt3DCore::QAttribute *positionAttribute;
    Qt3DCore::QBuffer *positionBuffer;
    Qt3DCore::QBuffer *indexBuffer;
    Qt3DExtras::QPhongMaterial *material;
};

class Event3D : public Qt3DCore::QEntity
{
public:
    Event3D(size_t id, QEntity *root, const QVector3D &translation, QColor color);

    size_t id;

    Qt3DExtras::QCuboidMesh *shape;
    Qt3DExtras::QPhongMaterial *material;
    Qt3DCore::QTransform *transform;
};

class Action3D : public Qt3DCore::QEntity
{
public:
    Action3D(size_t id, QEntity *root, const QVector3D &translation, QColor color);

    size_t id;

    Qt3DExtras::QCuboidMesh *shape;
    Qt3DExtras::QPhongMaterial *material;
    Qt3DCore::QTransform *transform;
};


class Vehicle3D : public Qt3DCore::QEntity
{
public:
    Vehicle3D(size_t id, QEntity *root, const QVector3D &translation, QColor color);

    void addEvent3D(size_t eId, const QVector3D &translation, QColor color);

    void addAction3D(size_t aId, const QVector3D &translation, QColor color);

    size_t id;

    Qt3DExtras::QCylinderMesh *shape;
    Qt3DExtras::QPhongMaterial *material;
    Qt3DCore::QTransform *transform;

    Trajectory3D *trajectoryEntity;

    std::map<size_t, Event3D *> event3Ds;
    std::map<size_t, Action3D *> action3Ds;
};

// This class DOES NOT represent a 3D object.
class Player3D
{
public:
    Player3D(size_t id, Qt3DCore::QEntity *root);

    void addVehicle3D(size_t vId, const QVector3D &translation, QColor color);

    void addEvent3D(size_t vId, size_t eId, const QVector3D &translation, QColor color);

    void addAction3D(size_t vId, size_t aId, const QVector3D &translation, QColor color);

    size_t id;

    Qt3DCore::QEntity *root;
    std::map<size_t, Vehicle3D *> vehicle3Ds;
};

class Stray3D : public Qt3DCore::QEntity
{
public:
    Stray3D(size_t id, QEntity *root, const QVector3D &translation, QColor color);

    size_t id;

    Qt3DExtras::QSphereMesh *shape;
    Qt3DExtras::QPhongMaterial *material;
    Qt3DCore::QTransform *transform;

    Trajectory3D *trajectoryEntity;
};

class Celestial3D : public Qt3DCore::QEntity
{
public:
    Celestial3D(size_t id, QEntity *root, const QVector3D &translation, QColor color, float radius);

    size_t id;

    Qt3DExtras::QSphereMesh *shape;
    Qt3DExtras::QPhongMaterial *material;
    Qt3DCore::QTransform *transform;

    Trajectory3D *trajectoryEntity;
};

#endif // SIMGUI3D_H
