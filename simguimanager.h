#ifndef SIMGUIMANAGER_H
#define SIMGUIMANAGER_H

#include "simgui3d.h"
#include "simguicomponent.h"

class SimGuiManager
{
public:
    SimGuiManager();
    SimGuiManager(QTreeWidget *playerRoot, QTreeWidget *enviromentRoot, Qt3DCore::QEntity *rootEntity);

    // If default constructor is called, then you have to call this function.
    // Otherwise, it will crash.
    void initRoots(QTreeWidget *playerRoot, QTreeWidget *enviromentRoot, Qt3DCore::QEntity *rootEntity);

    void addPlayerItem(size_t pId);
    void addPlayer3D(size_t pId);
    
    void addVehicleItem(size_t pId, size_t vId);
    void addVehicle3D(size_t pId, size_t vId, const QVector3D &translation, QColor color);
    
    void addEventItem(size_t pId, size_t vId, size_t eId);
    void addEvent3D(size_t pId, size_t vId, size_t eId, const QVector3D &translation, QColor color);
    
    void addActionItem(size_t pId, size_t vId, size_t aId);
    void addAction3D(size_t pId, size_t vId, size_t aId, const QVector3D &translation, QColor color);
    
    void addCelestialItem(size_t cId);
    void addCelestial3D(size_t cId, const QVector3D &translation, QColor color, float radius);
    
    void addStrayItem(size_t sId);
    void addStray3D(size_t sId, const QVector3D &translation, QColor color);

    // ----Collection of 3D Entities----

    // Root entity for 3D objects
    Qt3DCore::QEntity *rootEntity;

    std::map<size_t, Player3D> player3Ds;
    std::map<size_t, Stray3D *> stray3Ds;
    std::map<size_t, Celestial3D *> celestial3Ds;

    // ----Collection of TreeWidgets----
    
    // Tree widget for PlayerItem (s)
    QTreeWidget *playerRoot;
    
    // Tree widget for celestialParent and strayParent
    QTreeWidget *enviromentRoot;
    
    std::map<size_t, PlayerItem *> playerItems;
    
    QTreeWidgetItem *celestialParent;
    std::map<size_t, CelestialItem *> celestialItems;
    
    QTreeWidgetItem *strayParent;
    std::map<size_t, StrayItem *> strayItems;
    
};

#endif // SIMGUIMANAGER_H
