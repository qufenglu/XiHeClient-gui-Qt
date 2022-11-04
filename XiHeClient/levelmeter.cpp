#include "levelmeter.h"
#include "ui_levelmeter.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>


LevelMeter::LevelMeter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelMeter)
{
    ui->setupUi(this);
    setMask(QRegion(0,0,this->width(),this->height(),QRegion::Ellipse));

}

LevelMeter::~LevelMeter()
{
    delete ui;
}
