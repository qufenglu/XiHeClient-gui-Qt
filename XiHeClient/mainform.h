#ifndef MAINFORM_H
#define MAINFORM_H

#include  <QWidget>
#include "playwindow.h"
#include "App.h"

namespace Ui {
    class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

signals:
    void SigRecvMsgFromeRemote(mavlink_message_t* msg);
    void SigRecvMsgFromeController(mavlink_message_t* msg);

public slots:
    void ProcessMsgFromeRemote(mavlink_message_t* msg);
    void ProcessMsgFromeController(mavlink_message_t* msg);

public:
    explicit MainForm(QWidget* parent = nullptr);
    ~MainForm();
    void RenderVideoFrame(std::shared_ptr<VideoFrame>& video);
    void StartLoad();
    void Init();

private:
     void OnRecvMsgFromeRemote(mavlink_message_t* msg);
     void OnRecvMsgFromeController(mavlink_message_t* msg);

private:
    Ui::MainForm* ui;
    PlayWindow* m_pPlaywindow;
};

#endif // MAINFORM_H
