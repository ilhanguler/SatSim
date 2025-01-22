#include "simguimanager.h"

SimGuiManager::SimGuiManager()
{
    
}

SimGuiManager::SimGuiManager(QTreeWidget *playerRoot, QTreeWidget *enviromentRoot, Qt3DCore::QEntity *rootEntity)
{
    this->playerRoot = playerRoot;
    this->enviromentRoot = enviromentRoot;
    this->rootEntity = rootEntity;

    strayParent = new QTreeWidgetItem(this->enviromentRoot);
    strayParent->setText(0, "Stray Entities");
    celestialParent = new QTreeWidgetItem(this->enviromentRoot);
    celestialParent->setText(0, "Celestial Bodies");
}

void SimGuiManager::initRoots(QTreeWidget *playerRoot, QTreeWidget *enviromentRoot, Qt3DCore::QEntity *rootEntity)
{
    this->playerRoot = playerRoot;
    this->enviromentRoot = enviromentRoot;
    this->rootEntity = rootEntity;
    
    strayParent = new QTreeWidgetItem(this->enviromentRoot);
    strayParent->setText(0, "Stray Entities");
    celestialParent = new QTreeWidgetItem(this->enviromentRoot);
    celestialParent->setText(0, "Celestial Bodies");
}

void SimGuiManager::addPlayerItem(size_t pId)
{
    playerItems.insert({pId, new PlayerItem(pId, playerRoot)});
}

void SimGuiManager::addPlayer3D(size_t pId)
{
    player3Ds.insert({pId, Player3D(pId, rootEntity)});
}

void SimGuiManager::addVehicleItem(size_t pId, size_t vId)
{
    auto pItr = playerItems.find(pId);
    if(pItr != playerItems.end()){
        pItr->second->addVehicleItem(vId);
    }
}

void SimGuiManager::addVehicle3D(size_t pId, size_t vId, const QVector3D &translation, QColor color)
{
    auto pItr = player3Ds.find(pId);
    if(pItr != player3Ds.end()){
        pItr->second.addVehicle3D(vId, translation, color);
    }
}

void SimGuiManager::addEventItem(size_t pId, size_t vId, size_t eId)
{
    auto pItr = playerItems.find(pId);
    if(pItr != playerItems.end()){
        pItr->second->addEventItem(vId, eId);
    }
}

void SimGuiManager::addEvent3D(size_t pId, size_t vId, size_t eId, const QVector3D &translation, QColor color)
{
    auto pItr = player3Ds.find(pId);
    if(pItr != player3Ds.end()){
        pItr->second.addEvent3D(vId, eId, translation, color);
    }
}

void SimGuiManager::addActionItem(size_t pId, size_t vId, size_t aId)
{
    auto pItr = playerItems.find(pId);
    if(pItr != playerItems.end()){
        pItr->second->addActionItem(vId, aId);
    }
}

void SimGuiManager::addAction3D(size_t pId, size_t vId, size_t aId, const QVector3D &translation, QColor color)
{
    auto pItr = player3Ds.find(pId);
    if(pItr != player3Ds.end()){
        pItr->second.addAction3D(vId, aId, translation, color);
    }
}

void SimGuiManager::addCelestialItem(size_t cId)
{
    celestialItems.insert({cId, new CelestialItem(cId, celestialParent)});
}

void SimGuiManager::addCelestial3D(size_t cId, const QVector3D &translation, QColor color, float radius)
{
    celestial3Ds.insert({cId, new Celestial3D(cId, rootEntity, translation, color, radius)});
}

void SimGuiManager::addStrayItem(size_t sId)
{
    strayItems.insert({sId, new StrayItem(sId, strayParent)});
}

void SimGuiManager::addStray3D(size_t sId, const QVector3D &translation, QColor color)
{
    stray3Ds.insert({sId, new Stray3D(sId, rootEntity, translation, color)});
}
