#ifndef SIMGUICOMPONENT_H
#define SIMGUICOMPONENT_H

#include <QTreeWidgetItem>

// This file defines GUI components of corresponding entities.

class EventItem : public QTreeWidgetItem
{
public:
    EventItem(size_t id, QTreeWidgetItem *parent);

    size_t id;
};

class ActionItem : public QTreeWidgetItem
{
public:
    ActionItem(size_t id, QTreeWidgetItem *parent);

    size_t id;
};

class VehicleItem : public QTreeWidgetItem
{
public:
    VehicleItem(size_t id, QTreeWidgetItem *parent);

    void addEventItem(size_t eId);

    void addActionItem(size_t aId);

    // Id of vehicle
    size_t id;

    QTreeWidgetItem *eventParent;
    std::map<size_t, EventItem *> eventItems;

    QTreeWidgetItem *actionParent;
    std::map<size_t, ActionItem *> actionsItems;

};

class PlayerItem : public QTreeWidgetItem
{
public:
    PlayerItem(size_t id, QTreeWidget *root);

    void addVehicleItem(size_t vId);

    void addEventItem(size_t vId, size_t eId);

    void addActionItem(size_t vId, size_t aId);

    // Id of owner
    size_t id;

    std::map<size_t, VehicleItem *> vehicleItems;

};

class CelestialItem : public QTreeWidgetItem
{
public:
    CelestialItem(size_t id, QTreeWidgetItem *parent);

    size_t id;
};

class StrayItem : public QTreeWidgetItem
{
public:
    StrayItem(size_t id, QTreeWidgetItem *parent);

    size_t id;
};

// Manager class for GUI components that related to corresponding entities.


#endif // SIMGUICOMPONENT_H
