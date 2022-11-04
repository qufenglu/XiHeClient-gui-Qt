#ifndef INDEXFORM_H
#define INDEXFORM_H

#include <QWidget>
#include "mainwindow.h"
#include "XiheClient.h"

namespace Ui {
    class IndexForm;
}

class IndexForm : public QWidget
{
    Q_OBJECT

public:
    explicit IndexForm(QWidget* parent = nullptr, MainWindow* win = nullptr);
    ~IndexForm();

private slots:
    void on_qConectButton_clicked();

private:
    Ui::IndexForm* ui;
    MainWindow* m_pMainWindow;
};

#endif // INDEXFORM_H
