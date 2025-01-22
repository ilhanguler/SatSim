#include "earth_view.h"

earth_view::earth_view(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::earth_view)
{
    ui->setupUi(this);

    //setFixedSize(900, 650);

    view = new Qt3DExtras::Qt3DWindow();

    container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::StrongFocus);

    rootEntity = new Qt3DCore::QEntity();

    camera = view->camera();
    camera->setPosition(QVector3D(0, 0, 10));
    camera->setViewCenter(QVector3D(0, 0, 0));
    //camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);

    camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(camera);


    // EARTH
    // Earth sphere
    Qt3DExtras::QSphereMesh *earthSphere = new Qt3DExtras::QSphereMesh();
    earthSphere->setRadius(0.35f);
    Qt3DExtras::QPhongMaterial *earthMaterial = new Qt3DExtras::QPhongMaterial();
    earthMaterial->setDiffuse(QColor(QRgb(0x46A2FF)));

    // Earth entity
    Qt3DCore::QEntity *earthEntity = new Qt3DCore::QEntity(rootEntity);
    earthEntity->addComponent(earthSphere);
    earthEntity->addComponent(earthMaterial);


    // MOON
    // Moon sphere
    Qt3DExtras::QSphereMesh *moonSphere = new Qt3DExtras::QSphereMesh();
    moonSphere->setRadius(0.15f); // Dünya'dan daha küçük bir yarıçap

    // Moon material
    Qt3DExtras::QPhongMaterial *moonMaterial = new Qt3DExtras::QPhongMaterial();
    moonMaterial->setDiffuse(QColor(QRgb(0xC4C4C4))); // Gri renk

    // Moon entity
    Qt3DCore::QEntity *moonEntity = new Qt3DCore::QEntity(rootEntity);
    moonEntity->addComponent(moonSphere);
    moonEntity->addComponent(moonMaterial);

    // Moon transform
    Qt3DCore::QTransform *moonTransform = new Qt3DCore::QTransform();
    moonTransform->setTranslation(QVector3D(1.5f, 1.5f, -0.5f)); // Sağ üst köşe
    moonEntity->addComponent(moonTransform);





    // METEOR
    // Meteor sphere
    Qt3DExtras::QSphereMesh *meteorSphere = new Qt3DExtras::QSphereMesh();
    meteorSphere->setRadius(0.05f);
    Qt3DExtras::QPhongMaterial *meteorMaterial = new Qt3DExtras::QPhongMaterial();
    meteorMaterial->setDiffuse(QColor(QRgb(0xB1C62D)));

    // Meteor entity
    meteorEntity = new Qt3DCore::QEntity(rootEntity);
    meteorEntity->addComponent(meteorSphere);
    meteorEntity->addComponent(meteorMaterial);

    // Meteor transform
    meteorTransform = new Qt3DCore::QTransform();
    meteorTransform->setTranslation(QVector3D(1.0f, 0.0f, 0.0f));
    meteorEntity->addComponent(meteorTransform);

    // Meteor timer
    QTimer *meteorTimer = new QTimer(this);
    connect(meteorTimer, &QTimer::timeout, this, &earth_view::moveMeteor);
    meteorTimer->start(32);



    // Geometri oluştur
    Qt3DCore::QGeometry *geometry = new Qt3DCore::QGeometry();

    // Vertex buffer oluştur
    positionBuffer = new Qt3DCore::QBuffer(geometry); // VertexBuffer sabiti olmadan

    // Vertex verileri
    QByteArray vertexData;
    int numVertices = 100; // Örneğin
    vertexData.resize(3 * sizeof(float) * numVertices); // 3 boyutlu koordinatlar (x, y, z)
    float *rawVertexData = reinterpret_cast<float *>(vertexData.data());

    //qDebug() << "Creating vertex data for ellipse...";

    // Elips yörünge verileri oluştur
    float radiusX = 2.0f;
    float radiusY = 1.5f;
    for (int i = 0; i < numVertices; ++i) {
        float angle = static_cast<float>(i) / numVertices * 2.0f * M_PI;
        rawVertexData[3 * i] = radiusX * cos(angle);    // X
        rawVertexData[3 * i + 1] = radiusY * sin(angle); // Y
        rawVertexData[3 * i + 2] = 0.0f;               // Z (düzlemde)

       // qDebug() << "Vertex" << i << ":" << rawVertexData[3 * i] << rawVertexData[3 * i + 1] << rawVertexData[3 * i + 2];
    }

    // Veriyi buffer'a ekle
    positionBuffer->setData(vertexData);

    // Attribute tanımla
    Qt3DCore::QAttribute *positionAttribute = new Qt3DCore::QAttribute();
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(positionBuffer);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(numVertices);
    //qDebug() << "Position attribute count:" << positionAttribute->count();

    // Geometriye attribute ekle
    geometry->addAttribute(positionAttribute);



    // Geometry renderer oluştur
    Qt3DRender::QGeometryRenderer *geometryRenderer = new Qt3DRender::QGeometryRenderer();
    geometryRenderer->setGeometry(geometry);

    geometryRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::LineStrip); // Çizgiler için
    //qDebug() << "Geometry renderer type:" << geometryRenderer->primitiveType();

    Qt3DExtras::QPhongMaterial *lineMaterial = new Qt3DExtras::QPhongMaterial();
    lineMaterial->setDiffuse(QColor(0x00FF00)); // Yeşil renk


    // Entity oluştur ve sahneye ekle
    Qt3DCore::QEntity *orbitEntity = new Qt3DCore::QEntity(rootEntity);
    orbitEntity->addComponent(geometryRenderer);
    orbitEntity->addComponent(lineMaterial);




    // SPACECRAFT
    // Spacecraft cube
    Qt3DExtras::QCuboidMesh *spacecraftCube = new Qt3DExtras::QCuboidMesh();
    spacecraftCube->setXExtent(0.1f);
    spacecraftCube->setYExtent(0.1f);
    spacecraftCube->setZExtent(0.1f);
    Qt3DExtras::QPhongMaterial *spacecraftMaterial = new Qt3DExtras::QPhongMaterial();
    spacecraftMaterial->setDiffuse(QColor(QRgb(0xFF1414)));

    // Spacecraft entity
    spacecraftEntity = new Qt3DCore::QEntity(rootEntity);
    spacecraftEntity->addComponent(spacecraftCube);
    spacecraftEntity->addComponent(spacecraftMaterial);

    // Spacecraft transform
    spacecraftTransform = new Qt3DCore::QTransform();
    spacecraftTransform->setTranslation(QVector3D(-1.0f, 0.5f, 0.0f));
    spacecraftEntity->addComponent(spacecraftTransform);

    // Spacecraft timer
    QTimer *spacecraftTimer = new QTimer(this);
    connect(spacecraftTimer, &QTimer::timeout, this, &earth_view::moveSpacecraft);
    spacecraftTimer->start(48);


    view->setRootEntity(rootEntity);

    // Adding layout and place 3D window inside widget
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(container);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

}

void earth_view::moveMeteor() {
    static float angle = 0.0f;
    static int callCount = 0;
    //qDebug() << "moveMeteor called, count:" << ++callCount;

    // Hareket açısını güncelle
    angle += 0.02f;
    float x = cos(angle) * 1.0f;
    float y = sin(angle) * 0.5f;
    float z = 0.0f;

    QVector3D currentPosition(x, y, z);

    // Transform'u güncelle
    if (meteorTransform) {
        meteorTransform->setTranslation(currentPosition);
    } else {
      //  qWarning() << "meteorTransform is null.";
        return;
    }

    // Yeni konumu yörüngeye ekle
    orbitPoints.append(currentPosition);
    // qDebug() << "Orbit points size:" << orbitPoints.size(); // Listenin boyutunu kontrol edin

    // Yeterli nokta varsa yörüngeyi güncelle
    if (orbitPoints.size() >= 2) {
        updateOrbit();
    } else {
       // qDebug() << "Not enough points to render orbit.";
    }

    //qDebug() //<< "Current meteor position:" << currentPosition;
}



void earth_view::updateOrbit() {
    if (!positionBuffer) {
        //qWarning() << "Position buffer is not initialized.";
        return;
    }



    QByteArray positionData;
    positionData.resize(orbitPoints.size() * 3 * sizeof(float));
    float *data = reinterpret_cast<float *>(positionData.data());

    for (int i = 0; i < orbitPoints.size(); ++i) {
        data[3 * i] = orbitPoints[i].x();
        data[3 * i + 1] = orbitPoints[i].y();
        data[3 * i + 2] = orbitPoints[i].z();
    }

    //qDebug() << "Updating orbit with" << orbitPoints.size() << "points.";
    positionBuffer->setData(positionData);
}






// Function of spacecraft movement
void earth_view::moveSpacecraft() {

    static float angle = 0.0f;
    angle += 0.05f;
    float x = -1.5f + 0.5f * cos(angle);
    float y = -0.5f + 0.5f * sin(angle);

    spacecraftTransform->setTranslation(QVector3D(x, y, 0.0f));
}




earth_view::~earth_view()
{
    delete ui;
    delete rootEntity;
    delete view;
}
