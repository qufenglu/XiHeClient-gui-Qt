#include "mainform.h"
#include "ui_mainform.h"
#include "DigitalTransport/mavlink/mavlink_types.h"
#include "DigitalTransport/mavlink/ardupilotmega/mavlink.h"

#define Pi 3.1415926f

extern App g_App;
extern std::mutex g_AppLock;

MainForm::MainForm(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    connect(this,SIGNAL(SigRecvMsgFromeRemote(mavlink_message_t*)),this,SLOT(ProcessMsgFromeRemote(mavlink_message_t*)),Qt::BlockingQueuedConnection);
    connect(this,SIGNAL(SigRecvMsgFromeController(mavlink_message_t*)),this,SLOT(ProcessMsgFromeController(mavlink_message_t*)),Qt::BlockingQueuedConnection);
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::RenderVideoFrame(std::shared_ptr<VideoFrame>& video)
{
    m_pPlaywindow->RenderVideoFrame(video);
}

void MainForm::StartLoad()
{
    std::shared_ptr<XIheClient> pXIheClient = nullptr;
    {
        std::lock_guard<std::mutex> lock(g_AppLock);
        pXIheClient = g_App.GetClient();
    }
    if (pXIheClient != nullptr)
    {
        VideoDecoder::VideoFrameCallbaclk pVideoCallbaclk = std::bind(&MainForm::RenderVideoFrame, this, std::placeholders::_1);
        pXIheClient->SetVideoFrameCallback(pVideoCallbaclk);
        pXIheClient->PlayDevice("video0");
    }

    m_pPlaywindow = new PlayWindow(ui->PlayWin);
    m_pPlaywindow->Init();
}

void MainForm::Init()
{
    std::shared_ptr<XIheClient> pXIheClient = nullptr;
    {
        std::lock_guard<std::mutex> lock(g_AppLock);
        pXIheClient = g_App.GetClient();
    }
    if (pXIheClient != nullptr)
    {
        pXIheClient->OpenDigitalTransport();

        XIheClient::DigitalTransportMsgCallback callbaclk1 = std::bind(&MainForm::OnRecvMsgFromeController, this, std::placeholders::_1);
        pXIheClient->SetControllertMsgCallback(callbaclk1);
        XIheClient::DigitalTransportMsgCallback callbaclk2 = std::bind(&MainForm::OnRecvMsgFromeRemote, this, std::placeholders::_1);
        pXIheClient->SetRemoteMsgCallback(callbaclk2);

        UDPDataChannel::UDPDataChannelInitParam param;
        param.ip = pXIheClient->GetRemoteIp(); param.port = 8888; param.mode = UDPDataChannel::WorkMode::WORK_AS_CLIENT;
        pXIheClient->InitRemoteTransport("udp", &param);
        pXIheClient->StartTransport();
    }
}

uint16_t FilterChValue(uint16_t val,uint16_t max,uint16_t min)
{
    return val < min ? min :
           val > max ? max : val;
}

void MainForm::OnRecvMsgFromeRemote(mavlink_message_t* msg)
{
    emit SigRecvMsgFromeRemote(msg);
}

void MainForm::OnRecvMsgFromeController(mavlink_message_t* msg)
{
    emit SigRecvMsgFromeController(msg);
}

void MainForm::ProcessMsgFromeRemote(mavlink_message_t* msg)
{
    if (msg == nullptr)
    {
        return;
    }

    if(msg->msgid == MAVLINK_MSG_ID_ATTITUDE)
    {
        mavlink_attitude_t attitude;
        mavlink_msg_attitude_decode(msg, &attitude);

        float pitch = attitude.pitch * 180.0f / Pi;
        //pitch = pitch < 0 ? pitch + 360 : pitch;
        float roll = attitude.roll * 180.0f / Pi;
        //roll = roll < 0 ? roll + 360 : roll;
        float yaw = attitude.yaw * 180.0f / Pi;
        //yaw = yaw < 0 ? yaw + 360 : yaw;

        ui->head->SetHead(yaw);

        ui->pitchLb->setText(std::to_string(pitch).substr(0,6).c_str());
        ui->rollLb->setText(std::to_string(roll).substr(0,6).c_str());
        ui->yawLb->setText(std::to_string(yaw).substr(0,6).c_str());
    }
    else if(msg->msgid == MAVLINK_MSG_ID_GPS_RAW_INT)
    {
        mavlink_gps_raw_int_t gps;
        mavlink_msg_gps_raw_int_decode(msg, &gps);

        ui->lat->setText(std::to_string(0.0000001*gps.lat).substr(0,9).c_str());
        ui->lon->setText(std::to_string(0.0000001*gps.lon).substr(0,9).c_str());
        ui->alt->setText(std::to_string(0.001*gps.alt).substr(0,9).c_str());
        ui->vel->setText(std::to_string(0.01*gps.vel*3.6).substr(0,6).c_str());

    }
    else if(msg->msgid == MAVLINK_MSG_ID_SYS_STATUS)
    {
        mavlink_sys_status_t status;
        mavlink_msg_sys_status_decode(msg, &status);

        std::string vol = status.voltage_battery == UINT16_MAX ? "--.---" : (std::to_string(0.001*status.voltage_battery).substr(0,6).c_str());
        ui->vol->setText(vol.c_str());

        std::string cur = status.current_battery == -1 ? "--.---" : (std::to_string(0.01*status.current_battery).substr(0,6).c_str());
        ui->cur->setText(cur.c_str());

    }
    else if(msg->msgid == MAVLINK_MSG_ID_RC_CHANNELS)
    {
         mavlink_rc_channels_t channels;
         mavlink_msg_rc_channels_decode(msg, &channels);

         ui->roc1->SetChValues(FilterChValue(channels.chan4_raw,2000,1000),FilterChValue(channels.chan3_raw,2000,1000));
         ui->roc2->SetChValues(FilterChValue(channels.chan1_raw,2000,1000),FilterChValue(channels.chan2_raw,2000,1000));
         ui->ch5->setValue(FilterChValue(channels.chan5_raw,2000,1000));
         ui->ch6->setValue(FilterChValue(channels.chan6_raw,2000,1000));
         ui->ch7->setValue(FilterChValue(channels.chan7_raw,2000,1000));
         ui->ch8->setValue(FilterChValue(channels.chan8_raw,2000,1000));
         ui->ch9->setValue(FilterChValue(channels.chan9_raw,2000,1000));
         ui->ch10->setValue(FilterChValue(channels.chan10_raw,2000,1000));
    }
}

void MainForm::ProcessMsgFromeController(mavlink_message_t* msg)
{
    if (msg == nullptr)
    {
        return;
    }
}
