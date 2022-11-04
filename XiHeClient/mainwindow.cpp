#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "indexform.h"
#include "mainform.h"
#include "Log.h"
#include "RTSPClient.h"
#include "App.h"

App g_App;
std::mutex g_AppLock;

const int nIndexWidgetIdx = 0;
const int nMainWidgetIdx = 1;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);

    m_pStackedLayout = new QStackedLayout(ui->SubWidget);
    m_pIndexWidget = new IndexForm(ui->SubWidget, this);
    m_pMainWidget = new MainForm(ui->SubWidget);
    m_pStackedLayout->insertWidget(nIndexWidgetIdx, m_pIndexWidget);
    m_pStackedLayout->insertWidget(nMainWidgetIdx, m_pMainWidget);
    m_pStackedLayout->setCurrentIndex(nIndexWidgetIdx);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::ShowIndexWidget()
{
    if (m_pStackedLayout == nullptr)
    {
        Error("[%p]MainWindow::ShowIndexWidget m_pStackedLayout is null", this);
        return -1;
    }

    m_pStackedLayout->setCurrentIndex(nIndexWidgetIdx);
    return 0;
}

int MainWindow::ShowMainWidget()
{
    if (m_pStackedLayout == nullptr)
    {
        Error("[%p]MainWindow::ShowMainWidget m_pStackedLayout is null", this);
        return -1;
    }

    m_pStackedLayout->setCurrentIndex(nMainWidgetIdx);
    ((MainForm*)m_pMainWidget)->Init();
    ((MainForm*)m_pMainWidget)->StartLoad();
    return 0;
}
