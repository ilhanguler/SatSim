#include "earth_view.h"
#include "ui_earth_view.h"
#include <QVBoxLayout>

earth_view::earth_view(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::earth_view)
{
    ui->setupUi(this);

    view = new Qt3DExtras::Qt3DWindow();
    container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::StrongFocus);

    rootEntity = new Qt3DCore::QEntity();


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

    // Earth camera
    Qt3DRender::QCamera *earthCamera = view->camera();
    earthCamera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    earthCamera->setPosition(QVector3D(0, 0, 4.0f));
    earthCamera->setViewCenter(QVector3D(0, 0, 0));


    // METEOR
    // Meteor sphere
    Qt3DExtras::QSphereMesh *meteorSphere = new Qt3DExtras::QSphereMesh();
    meteorSphere->setRadius(0.1f);
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

// Function of meteor movement
void earth_view::moveMeteor() {

    static float angle = 0.0f;
    angle += 0.05f;
    float x = 1.0f * cos(angle);
    float z = 1.0f * sin(angle);

    meteorTransform->setTranslation(QVector3D(x, 0.0f, z));
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
