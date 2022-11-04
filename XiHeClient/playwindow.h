#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QWidget>
#include <QTimer>
#include <memory>
#include <mutex>
#include <SDL2/SDL.h>
#include "Common.h"

class PlayWindow : public QObject
{
    Q_OBJECT
public:
     PlayWindow(QWidget* parent);
    ~PlayWindow() Q_DECL_OVERRIDE;
     int32_t RenderVideoFrame(std::shared_ptr<VideoFrame>& video);
     int32_t Init();

private:
    int32_t ReleaseAll();
    void RenderProcess();

private:
    QWidget* m_pParentWidget;
    std::mutex m_pFrameLock;
    std::shared_ptr<VideoFrame> m_pVideoFrame;
    QTimer* m_pRenderTimer;
    SDL_Window* m_pSdlWindow;
    SDL_Renderer* m_pSdlRender;
    SDL_Texture * m_pSdlTexture;
    int32_t m_nTextureWidth;
    int32_t m_nTextureHeight;
    int32_t m_nRenderWidth;
    int32_t m_nRenderHeight;
    bool m_bStopUpdate;
};

#endif // PLAYWINDOW_H
