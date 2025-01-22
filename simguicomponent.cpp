#include "simguicomponent.h"

// EventItem

EventItem::EventItem(size_t id, QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{
    this->id = id;
    this->setText(0, "Event: " + QString::number(id));
}

// ActionItem

ActionItem::ActionItem(size_t id, QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{
    this->id = id;
    this->setText(0, "Action: " + QString::number(id));
}

// VehicleItem

VehicleItem::VehicleItem(size_t id, QTreeWidgetItem *parent)  : QTreeWidgetItem(parent)
{
    this->id = id;
    this->setText(0, "Vehicle " + QString::number(id));

    eventParent = new QTreeWidgetItem(this);
    actionParent = new QTreeWidgetItem(this);
}

void VehicleItem::addEventItem(size_t eId)
{
    eventItems.insert({eId, new EventItem(eId, this)});
}

void VehicleItem::addActionItem(size_t aId)
{
    actionsItems.insert({aId, new ActionItem(aId, this)});
}

// PlayerItem

PlayerItem::PlayerItem(size_t id, QTreeWidget *root) : QTreeWidgetItem(root)
{
    this->id = id;
    this->setText(0, "Player: " + QString::number(id));
}

void PlayerItem::addVehicleItem(size_t vId)
{
    vehicleItems.insert({vId, new VehicleItem(vId, this)});
}

void PlayerItem::addEventItem(size_t vId, size_t eId)
{
    auto vItr = vehicleItems.find(vId);
    if(vItr != vehicleItems.end()){
        vItr->second->addEventItem(eId);
    }
}

void PlayerItem::addActionItem(size_t vId, size_t aId)
{
    auto vItr = vehicleItems.find(vId);
    if(vItr != vehicleItems.end()){
        vItr->second->addActionItem(aId);
    }
}

// StrayItem

StrayItem::StrayItem(size_t id, QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{
    this->id = id;
    this->setText(0, "Stray: " + QString::number(id));
}

// CelestialItem

CelestialItem::CelestialItem(size_t id, QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{
    this->id = id;
    this->setText(0, "Celestial: " + QString::number(id));
}


