#ifndef HEADINGMETER_H
#define HEADINGMETER_H

#include <QWidget>

namespace Ui {
class HeadingMeter;
}

class HeadingMeter : public QWidget
{
    Q_OBJECT

public:
    explicit HeadingMeter(QWidget *parent = nullptr);
    ~HeadingMeter();

    int32_t SetHead(float yaw);
    int32_t LoadHeadPixmap();

private:
    Ui::HeadingMeter *ui;
    QPixmap* m_pHeadPixmap;
    QPixmap m_cTransformedPixmap;
    float m_fYaw;
};

#endif // HEADINGMETER_H
