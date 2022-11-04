#include "attitudeview.h"
#include "ui_attitudeview.h"
//#include <QEntity>
//#include <Qt3DRender>
//#include <Qt3DExtras>


AttitudeView::AttitudeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttitudeView)
{
    ui->setupUi(this);
    /*setMask(QRegion(0,0,this->width(),this->height(),QRegion::Ellipse));

    setAttribute(Qt::WA_PaintOnScreen,true);
    setAttribute(Qt::WA_PaintUnclipped);

    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);
    Qt3DCore::QEntity *chestEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QMesh *chestMesh = new Qt3DRender::QMesh(rootEntity);
    chestMesh->setSource(QUrl::fromLocalFile("/home/qufenglu/software/plane.obj"));
    chestEntity->addComponent(chestMesh);
    chestEntity->addComponent(material);

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(25, 25, 25));
    camera->setViewCenter(QVector3D(-25, -25, -25));

    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setLinearSpeed( 10.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);

    Qt3DCore::QTransform *sphereTransform1 = new Qt3DCore::QTransform();
    sphereTransform1->setScale(0.003f);
    sphereTransform1->setRotation(QQuaternion::fromEulerAngles(0,180,0));
    sphereTransform1->setTranslation(QVector3D(5.0f, 4.0f, 0.0f));
    chestEntity->addComponent(sphereTransform1);

    view->setRootEntity(rootEntity);
    view->show();*/
}

AttitudeView::~AttitudeView()
{
    delete ui;
}
