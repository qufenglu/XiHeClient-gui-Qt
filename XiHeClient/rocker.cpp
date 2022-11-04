#include "rocker.h"
#include "ui_rocker.h"

Rocker::Rocker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rocker)
{
    m_nCh1Value = 1500;
    m_nCh1ValueMin = 1000;
    m_nCh1ValueMax = 2000;
    m_nCh2Value = 1500;
    m_nCh2ValueMin = 1000;
    m_nCh2ValueMax = 2000;
    ui->setupUi(this);
}

Rocker::~Rocker()
{
    delete ui;
}

void Rocker::SetCh1Value(int value)
{
    value = value < m_nCh1ValueMin ? m_nCh1ValueMin :
            value > m_nCh1ValueMax ? m_nCh1ValueMax : value;

    if(m_nCh1Value != value)
    {
        m_nCh1Value = value;
        MoveRocker();
    }
}

void Rocker::SetCh2Value(int value)
{
    value = value < m_nCh2ValueMin ? m_nCh2ValueMin :
            value > m_nCh2ValueMax ? m_nCh2ValueMax : value;

    if(m_nCh2Value != value)
    {
        m_nCh2Value = value;
        MoveRocker();
    }
}

void Rocker::SetChValues(int value1,int value2)
{
    value1 = value1 < m_nCh1ValueMin ? m_nCh1ValueMin :
             value1 > m_nCh1ValueMax ? m_nCh1ValueMax : value1;

    value2 = value2 < m_nCh2ValueMin ? m_nCh2ValueMin :
             value2 > m_nCh2ValueMax ? m_nCh2ValueMax : value2;

    if(m_nCh1Value != value1 || m_nCh2Value != value2)
    {
        m_nCh1Value = value1;
        m_nCh2Value = value2;
        MoveRocker();
    }
}

void Rocker::MoveRocker()
{
    int width1 = ui->widget->width();
    int width2 = ui->point->width();
    int height1 = ui->widget->height();
    int height2 = ui->point->height();

    int nMargeX = (width1 - width2)*(m_nCh1Value - m_nCh1ValueMin)/(m_nCh1ValueMax - m_nCh1ValueMin);
    int nMargeY = (height1 - height2)*(m_nCh2Value - m_nCh2ValueMin)/(m_nCh2ValueMax - m_nCh2ValueMin);
    nMargeY = (height1 - height2) - nMargeY;


    ui->point->setGeometry(nMargeX,nMargeY,width2,height2);
}
