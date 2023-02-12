#include <QPainter>
#include <QPainterPath>
#include <math.h>
#include "headingmeter.h"
#include "ui_headingmeter.h"
#include "Log.h"

HeadingMeter::HeadingMeter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeadingMeter)
{
    m_pHeadPixmap = nullptr;
    m_fYaw = 0;
    ui->setupUi(this);
    setMask(QRegion(0,0,ui->pixmapLable->width(),ui->pixmapLable->height(),QRegion::Ellipse));
    LoadHeadPixmap();
    time(&m_lLasfRefreshTime);
}

HeadingMeter::~HeadingMeter()
{
    delete m_pHeadPixmap;
    delete ui;
}


int32_t HeadingMeter::LoadHeadPixmap()
{
    delete m_pHeadPixmap;
    m_pHeadPixmap = new QPixmap();
    if(!m_pHeadPixmap->load("/home/qufenglu/software/headingmeter.png"))
    {
        Error("[%p][HeadingMeter::LoadHeadPixmap] load pixmap fail", this);
        return -1;
    }

    ui->pixmapLable->setPixmap(*m_pHeadPixmap);

    return 0;
}

int32_t HeadingMeter::SetHead(float yaw)
{
    time_t now;
    time(&now);
    if(now - m_lLasfRefreshTime > 1)
    {
        m_lLasfRefreshTime = now;
    }
    else
    {
        return 0;
    }
    
    if(m_pHeadPixmap != nullptr)
    {
        if(fabs(yaw - m_fYaw) < 1)
        {
            return 0;
        }

        QMatrix matrix;
        matrix.rotate(360 - yaw);
        m_cTransformedPixmap = m_pHeadPixmap->transformed(matrix, Qt::SmoothTransformation);
        int x = (m_cTransformedPixmap.width() - m_pHeadPixmap->width()) / 2;
        int y = (m_cTransformedPixmap.height() - m_pHeadPixmap->height()) / 2;
        m_cTransformedPixmap = m_cTransformedPixmap.copy(x,y,m_pHeadPixmap->width(),m_pHeadPixmap->height());
        ui->pixmapLable->setPixmap(m_cTransformedPixmap);
        m_fYaw = yaw;
    }
    return 0;
}
