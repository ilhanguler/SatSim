#include "earthview.h"
#include "ui_earthview.h"
#include <QVBoxLayout>

earthView::earthView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::earthView)
{
    ui->setupUi(this);

    view = new Qt3DExtras::Qt3DWindow();
    container = QWidget::createWindowContainer(view, this);
    container->setFixedSize(650, 415);
    container->setFocusPolicy(Qt::StrongFocus);

    rootEntity = new Qt3DCore::QEntity();

    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh();
    sphereMesh->setRadius(0.5f);

    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(QRgb(0x3399FF)));

    Qt3DCore::QEntity *sphereEntity = new Qt3DCore::QEntity(rootEntity);
    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(material);

    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    camera->setPosition(QVector3D(0, 0, 4.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setLinearSpeed(50.0f);
    camController->setLookSpeed(180.0f);
    camController->setCamera(camera);

    view->setRootEntity(rootEntity);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(container);
    setLayout(layout);



}

earthView::~earthView()
{
    delete ui;
    delete rootEntity;
    delete view;
}
