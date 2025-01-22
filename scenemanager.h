#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "simdriver.h"

class SceneManager {
public:
    // Load JSON file and return a QJsonObject
    static QJsonObject loadJson(const QString &filePath);

    // Save QJsonObject to JSON file
    static bool saveJson(const QString &filePath, const QJsonObject &jsonObj);

    // Saves scene to JSON file
    static void saveScene(const QString &filePath, const SimDriver &sim);

    // Loads scene from JSON file
    static void loadScene(const QString &filePath, SimDriver &sim);

};


#endif // SCENEMANAGER_H
