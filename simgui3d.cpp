#include "simgui3d.h"

// Trajectory3D

Trajectory3D::Trajectory3D(QEntity *root) : Qt3DCore::QEntity(root)
{

}

void Trajectory3D::setTrajectory(const QVector<QVector3D> &trajectory, const QVector<unsigned int> &indices, const QColor &color)
{
    geometry = new Qt3DCore::QGeometry(root);

    // Trajectory positions
    QByteArray bufferBytes;
    bufferBytes.resize(3 * trajectory.size() * sizeof(float));
    auto positions = reinterpret_cast<float*>(bufferBytes.data());
    for (int n = trajectory.size(), i = 0; i < n; ++i)
    {
        *positions++ = trajectory[i].x();
        *positions++ = trajectory[i].y();
        *positions++ = trajectory[i].z();
    }

    positionBuffer = new Qt3DCore::QBuffer(geometry);
    positionBuffer->setData(bufferBytes);

    positionAttribute = new Qt3DCore::QAttribute(geometry);
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(positionBuffer);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(trajectory.size());
    geometry->addAttribute(positionAttribute);

    // Connectivity of points
    QByteArray indexBytes;
    indexBytes.resize(indices.size() * sizeof(unsigned int));
    memcpy(indexBytes.data(), indices.data(), indices.size() * sizeof(unsigned int));

    indexBuffer = new Qt3DCore::QBuffer(geometry);
    indexBuffer->setData(indexBytes);

    indexAttribute = new Qt3DCore::QAttribute(geometry);
    indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedInt);
    indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
    indexAttribute->setVertexSize(1);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setByteStride(1 * sizeof(unsigned int));
    indexAttribute->setCount(indices.size());
    geometry->addAttribute(indexAttribute);

    renderer = new Qt3DRender::QGeometryRenderer(root);
    renderer->setGeometry(geometry);
    renderer->setRestartIndexValue(-1);
    renderer->setPrimitiveRestartEnabled(true);
    renderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::LineStrip);
    material = new Qt3DExtras::QPhongMaterial(root);
    material->setAmbient(color);

    this->addComponent(renderer);
    this->addComponent(material);
}

void Trajectory3D::clearTrajectory(){
    delete renderer;
    delete geometry;
    delete indexAttribute;
    delete positionAttribute;
    delete positionBuffer;
    delete indexBuffer;
    delete material;
}

// Event3D

Event3D::Event3D(size_t id, QEntity *root, const QVector3D &translation, QColor color)
{
    shape = new Qt3DExtras::QCuboidMesh();
    material = new Qt3DExtras::QPhongMaterial();
    transform = new Qt3DCore::QTransform();

    shape->setXExtent(0.10f);
    shape->setYExtent(0.10f);
    shape->setZExtent(0.10f);
    material->setDiffuse(color);
    transform->setTranslation(translation);

    this->id = id;
    this->addComponent(shape);
    this->addComponent(material);
    this->addComponent(transform);
}

// Action3D

Action3D::Action3D(size_t id, QEntity *root, const QVector3D &translation, QColor color)
{
    shape = new Qt3DExtras::QCuboidMesh();
    material = new Qt3DExtras::QPhongMaterial();
    transform = new Qt3DCore::QTransform();

    shape->setXExtent(0.10f);
    shape->setYExtent(0.10f);
    shape->setZExtent(0.10f);
    material->setDiffuse(color);
    transform->setTranslation(translation);

    this->id = id;
    this->addComponent(shape);
    this->addComponent(material);
    this->addComponent(transform);
}

// Vehicle3D

Vehicle3D::Vehicle3D(size_t id, Qt3DCore::QEntity *root, const QVector3D &translation, QColor color) : Qt3DCore::QEntity(root)
{
    shape = new Qt3DExtras::QCylinderMesh();
    material = new Qt3DExtras::QPhongMaterial();
    transform = new Qt3DCore::QTransform();

    shape->setLength(0.10f);
    shape->setRadius(0.10f);
    material->setDiffuse(color);
    transform->setTranslation(translation);

    this->id = id;
    this->addComponent(shape);
    this->addComponent(material);
    this->addComponent(transform);
}

void Vehicle3D::addEvent3D(size_t eId, const QVector3D &translation, QColor color)
{
    event3Ds.insert({eId, new Event3D(eId, this->parentEntity(), translation, color)});
}

void Vehicle3D::addAction3D(size_t aId, const QVector3D &translation, QColor color)
{
    action3Ds.insert({aId, new Action3D(aId, this->parentEntity(), translation, color)});
}

// Player3D

Player3D::Player3D(size_t id, Qt3DCore::QEntity *root) : id(id), root(root)
{

}

void Player3D::addVehicle3D(size_t vId, const QVector3D &translation, QColor color)
{
    vehicle3Ds.insert({vId, new Vehicle3D(vId, root, translation, color)});
}

void Player3D::addEvent3D(size_t vId, size_t eId, const QVector3D &translation, QColor color)
{
    auto vItr = vehicle3Ds.find(vId);
    if(vItr != vehicle3Ds.end()){
        vItr->second->addEvent3D(eId, translation, color);
    }
}

void Player3D::addAction3D(size_t vId, size_t aId, const QVector3D &translation, QColor color)
{
    auto vItr = vehicle3Ds.find(vId);
    if(vItr != vehicle3Ds.end()){
        vItr->second->addAction3D(aId, translation, color);
    }
}

// Stray3D

Stray3D::Stray3D(size_t id, Qt3DCore::QEntity *root, const QVector3D &translation, QColor color) : Qt3DCore::QEntity(root)
{
    shape = new Qt3DExtras::QSphereMesh();
    material = new Qt3DExtras::QPhongMaterial();
    transform = new Qt3DCore::QTransform();

    shape->setRadius(0.10f);
    material->setDiffuse(color);
    transform->setTranslation(translation);

    this->id = id;
    this->addComponent(shape);
    this->addComponent(material);
    this->addComponent(transform);
}

// Celestial3D

Celestial3D::Celestial3D(size_t id, Qt3DCore::QEntity *root, const QVector3D &translation, QColor color, float radius) : Qt3DCore::QEntity(root)
{
    shape = new Qt3DExtras::QSphereMesh();
    material = new Qt3DExtras::QPhongMaterial();
    transform = new Qt3DCore::QTransform();

    shape->setRadius(radius);
    material->setDiffuse(color);
    transform->setTranslation(translation);

    this->id = id;
    this->addComponent(shape);
    this->addComponent(material);
    this->addComponent(transform);
}
