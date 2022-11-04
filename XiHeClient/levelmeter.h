#ifndef LEVELMETER_H
#define LEVELMETER_H

#include <QWidget>

namespace Ui {
class LevelMeter;
}

class LevelMeter : public QWidget
{
    Q_OBJECT

public:
    explicit LevelMeter(QWidget *parent = nullptr);
    ~LevelMeter();

private:
    Ui::LevelMeter *ui;
    QWidget* m_pTopWidget;
    QWidget* m_pBottomWidget;
};

#endif // LEVELMETER_H
