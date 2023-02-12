#include "mainwindow.h"
#include <QApplication>
#include <bcm_host.h>
#include <SDL2/SDL.h>
#include "App.h"
#include "Log/Log.h"

const std::string g_strAppVersion = "1.0.0.0";

extern App g_App;
extern std::mutex g_AppLock;

int main(int argc, char* argv[])
{
    InitLog("/home/qufenglu/XiheClient.txt");
    SetLogLevel(TRACE);
    Debug("App start version:%s",g_strAppVersion.c_str());
    
    bcm_host_init();
    SDL_Init(SDL_INIT_VIDEO);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int ret = a.exec();

    {
        std::lock_guard<std::mutex> lock(g_AppLock);
        g_App.ReleaseClient();
    }

    return ret;
}
