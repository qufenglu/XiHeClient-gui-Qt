#ifndef ROCKER_H
#define ROCKER_H

#include <QWidget>

namespace Ui {
class Rocker;
}

class Rocker : public QWidget
{
    Q_OBJECT

public:
    explicit Rocker(QWidget *parent = nullptr);
    ~Rocker();
    void SetCh1Value(int value);
    void SetCh2Value(int value);
    void SetChValues(int value1,int value2);

private:
    void MoveRocker();

private:
    Ui::Rocker *ui;
    int m_nCh1Value;
    int m_nCh1ValueMin;
    int m_nCh1ValueMax;
    int m_nCh2Value;
    int m_nCh2ValueMin;
    int m_nCh2ValueMax;
};

#endif // ROCKER_H
