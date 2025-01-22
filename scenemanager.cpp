#include "scenemanager.h"

QJsonObject SceneManager::loadJson(const QString &filePath) {
    QFile file(filePath);

    if(!file.exists()) {
        qWarning() << "File does not exist:" << filePath;
        return{};
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open file:" << filePath;
        return {};
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        qWarning() << "Invalid JSON format in file:" << filePath;
        return {};
    }

    return doc.object();
}

bool SceneManager::saveJson(const QString &filePath, const QJsonObject &jsonObj) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Unable to open file for writing:" << filePath;
        return false;
    }

    QJsonDocument doc(jsonObj);
    file.write(doc.toJson());
    file.close();
    return true;
}

void SceneManager::saveScene(const QString &filePath, const SimDriver &sim){
    QJsonObject root;

    QJsonArray players;
    for(const auto  &p : sim.players){
        QJsonObject player;

        player["type"] = p.second.type;

        QJsonArray vehicles;
        for(auto &v : p.second.vehicles){
            QJsonObject vehicle;

            QJsonObject pos;
            pos["x"] = v.position.x.str().c_str();
            pos["y"] = v.position.y.str().c_str();
            pos["z"] = v.position.z.str().c_str();
            vehicle["pos"] = pos;

            vehicle["mass"] = v.mass.str().c_str();
            vehicle["radius"] = v.radius.str().c_str();
            vehicle["name"] = v.name;

            QJsonObject velocity;
            velocity["x"] = v.velocity.x.str().c_str();
            velocity["y"] = v.velocity.y.str().c_str();
            velocity["z"] = v.velocity.z.str().c_str();
            vehicle["velocity"] = velocity;

            vehicle["maxThrust"] = v.maxThrust.str().c_str();
            vehicle["fuelConsPerMSec"] = v.fuelConsPerMSec.str().c_str();
            vehicle["fuel"] = v.fuel.str().c_str();
            vehicle["antenna"] = v.antenna;
            vehicle["antennaGain"] = v.antennaGain.str().c_str();

            QJsonObject bearing;
            bearing["x"] = v.bearing.x.str().c_str();
            bearing["y"] = v.bearing.y.str().c_str();
            bearing["z"] = v.bearing.z.str().c_str();
            vehicle["bearing"] = bearing;

            vehicles.append(vehicle);
        }

        player["vehicles"] = vehicles;
        players.append(player);
    }

    QJsonArray strays;
    for(auto &s : sim.enviroment.strayEntities){
        QJsonObject stray;

        QJsonObject pos;
        pos["x"] = s.position.x.str().c_str();
        pos["y"] = s.position.y.str().c_str();
        pos["z"] = s.position.z.str().c_str();
        stray["pos"] = pos;

        stray["mass"] = s.mass.str().c_str();
        stray["radius"] = s.radius.str().c_str();
        stray["name"] = s.name;

        QJsonObject velocity;
        velocity["x"] = s.velocity.x.str().c_str();
        velocity["y"] = s.velocity.y.str().c_str();
        velocity["z"] = s.velocity.z.str().c_str();
        stray["velocity"] = velocity;

        strays.append(stray);
    }

    QJsonArray celestials;
    for(auto &cb : sim.enviroment.celestialBodies){
        QJsonObject celestial;

        QJsonObject pos;
        pos["x"] = cb.position.x.str().c_str();
        pos["y"] = cb.position.y.str().c_str();
        pos["z"] = cb.position.z.str().c_str();
        celestial["pos"] = pos;

        celestial["mass"] = cb.mass.str().c_str();
        celestial["radius"] = cb.radius.str().c_str();
        celestial["name"] = cb.name;

        QJsonObject velocity;
        velocity["x"] = cb.velocity.x.str().c_str();
        velocity["y"] = cb.velocity.y.str().c_str();
        velocity["z"] = cb.velocity.z.str().c_str();
        celestial["velocity"] = velocity;

        celestials.append(celestial);
    }

    root["players"] = players;
    root["strays"] = strays;
    root["celestials"] = celestials;

    saveJson(filePath, root);
}

void SceneManager::loadScene(const QString &filePath, SimDriver &sim){
    QJsonObject root = loadJson(filePath);

    if(root.empty()){
        return;
    }

    QJsonArray players = root["players"].toArray();

    PreciseVector3D pos;
    cpp_dec_float_100 mass;
    cpp_dec_float_100 radius;
    QString name;
    PreciseVector3D velocity;
    cpp_dec_float_100 maxThrust;
    cpp_dec_float_100 fuelConsPerMSec;
    cpp_dec_float_100 fuel;
    AntennaType antenna;
    cpp_dec_float_100 antennaGain;
    PreciseVector3D bearing;

    for (size_t i = 0; i < players.size(); ++i){
        QJsonObject player = players[i].toObject();
        sim.initialize(Player((PlayerType)player["type"].toInt()));

        QJsonArray vehicles = player["vehicles"].toArray();
        for (size_t k = 0; k < vehicles.size(); ++k){
            QJsonObject vehicle = vehicles[i].toObject();

            pos = PreciseVector3D(cpp_dec_float_100(vehicle["pos"].toObject()["x"].toString().toStdString()),
                                  cpp_dec_float_100(vehicle["pos"].toObject()["y"].toString().toStdString()),
                                  cpp_dec_float_100(vehicle["pos"].toObject()["z"].toString().toStdString())
                                  );
            mass.assign(vehicle["mass"].toString().toStdString());
            radius.assign(vehicle["radius"].toString().toStdString());
            name.assign(vehicle["name"].toString());
            velocity = PreciseVector3D(cpp_dec_float_100(vehicle["velocity"].toObject()["x"].toString().toStdString()),
                                       cpp_dec_float_100(vehicle["velocity"].toObject()["y"].toString().toStdString()),
                                       cpp_dec_float_100(vehicle["velocity"].toObject()["z"].toString().toStdString())
                                       );
             maxThrust.assign(vehicle["maxThrust"].toString().toStdString());
             fuelConsPerMSec.assign(vehicle["fuelConsPerMSec"].toString().toStdString());
             fuel.assign(vehicle["fuel"].toString().toStdString());
             antenna = (AntennaType)vehicle["antenna"].toInt();
             antennaGain.assign(vehicle["antennaGain"].toString().toStdString());
             bearing = PreciseVector3D(cpp_dec_float_100(vehicle["bearing"].toObject()["x"].toString().toStdString()),
                                    cpp_dec_float_100(vehicle["bearing"].toObject()["y"].toString().toStdString()),
                                    cpp_dec_float_100(vehicle["bearing"].toObject()["z"].toString().toStdString())
                                    );

            sim.initialize(i, VehicleEntity(pos, mass, radius, name, velocity, maxThrust, fuelConsPerMSec, fuel,
                                            antenna, antennaGain, bearing));
        }
    }

    QJsonArray strays = root.value("strays").toArray();

    for (size_t i = 0; i < strays.size(); ++i){
        QJsonObject stray = strays[i].toObject();

        pos = PreciseVector3D(cpp_dec_float_100(stray["pos"].toObject()["x"].toString().toStdString()),
                              cpp_dec_float_100(stray["pos"].toObject()["y"].toString().toStdString()),
                              cpp_dec_float_100(stray["pos"].toObject()["z"].toString().toStdString())
                              );
        mass.assign(stray["mass"].toString().toStdString());
        radius.assign(stray["radius"].toString().toStdString());
        name.assign(stray["name"].toString());
        velocity = PreciseVector3D(cpp_dec_float_100(stray["velocity"].toObject()["x"].toString().toStdString()),
                                   cpp_dec_float_100(stray["velocity"].toObject()["y"].toString().toStdString()),
                                   cpp_dec_float_100(stray["velocity"].toObject()["z"].toString().toStdString())
                                   );

        sim.initialize(StrayEntity(pos, mass, radius, name, velocity));
    }

    QJsonArray celestials = root.value("celestials").toArray();

    for (size_t i = 0; i < celestials.size(); ++i){
        QJsonObject celestial = celestials[i].toObject();

        pos = PreciseVector3D(cpp_dec_float_100(celestial["pos"].toObject()["x"].toString().toStdString()),
                              cpp_dec_float_100(celestial["pos"].toObject()["y"].toString().toStdString()),
                              cpp_dec_float_100(celestial["pos"].toObject()["z"].toString().toStdString())
                              );
        mass.assign(celestial["mass"].toString().toStdString());
        radius.assign(celestial["radius"].toString().toStdString());
        name.assign(celestial["name"].toString());
        velocity = PreciseVector3D(cpp_dec_float_100(celestial["velocity"].toObject()["x"].toString().toStdString()),
                                   cpp_dec_float_100(celestial["velocity"].toObject()["y"].toString().toStdString()),
                                   cpp_dec_float_100(celestial["velocity"].toObject()["z"].toString().toStdString())
                                   );

        sim.initialize(CelestialBody(pos, mass, radius, name, velocity));
    }
}
