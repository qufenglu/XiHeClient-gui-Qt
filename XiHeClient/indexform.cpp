#include "indexform.h"
#include "ui_indexform.h"
#include "mainwindow.h"
#include "Log.h"
#include "App.h"

extern App g_App;
extern std::mutex g_AppLock;

IndexForm::IndexForm(QWidget* parent, MainWindow* win) :
    QWidget(parent),
    ui(new Ui::IndexForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    m_pMainWindow = win;
}

IndexForm::~IndexForm()
{
    delete ui;
}

void IndexForm::on_qConectButton_clicked()
{
    {
        std::lock_guard<std::mutex> lock(g_AppLock);
        std::shared_ptr<XIheClient> pXIheClient = std::make_shared<XIheClient>("192.168.5.53", 7777);
        g_App.SetClient(pXIheClient);
    }

    if (m_pMainWindow == nullptr)
    {
        Error("[%p]IndexForm::on_qConectButton_clicked m_pMainWindow is null", this);
        return;
    }
    int ret = m_pMainWindow->ShowMainWidget();
    if (ret != 0)
    {
        Error("[%p]IndexForm::on_qConectButton_clicked ShowMainWidget fail,return:%d", this, ret);
        return;
    }
}
