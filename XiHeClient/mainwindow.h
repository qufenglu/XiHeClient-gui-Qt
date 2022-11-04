#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    int ShowIndexWidget();
    int ShowMainWidget();

private:
    Ui::MainWindow* ui;
    QStackedLayout* m_pStackedLayout;
    QWidget* m_pIndexWidget;
    QWidget* m_pMainWidget;
};

#endif // MAINWINDOW_H
