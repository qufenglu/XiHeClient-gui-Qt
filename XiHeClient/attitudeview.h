#ifndef ATTITUDEVIEW_H
#define ATTITUDEVIEW_H

#include <QWidget>

namespace Ui {
class AttitudeView;
}

class AttitudeView : public QWidget
{
    Q_OBJECT

public:
    explicit AttitudeView(QWidget *parent = nullptr);
    ~AttitudeView();

private:
    Ui::AttitudeView *ui;
};

#endif // ATTITUDEVIEW_H
