#include <QTimer>
#include "playwindow.h"
#include "Log.h"

#define VERTEXIN 0
#define TEXTUREIN 1

PlayWindow::PlayWindow(QWidget* parent)
{
    m_pParentWidget = parent;
    m_pVideoFrame = nullptr;
    m_pRenderTimer = nullptr;
    m_pSdlWindow = nullptr;
    m_pSdlRender = nullptr;
    m_pSdlTexture = nullptr;
    m_nTextureWidth = 0;
    m_nTextureHeight = 0;
    m_nRenderWidth = 0;
    m_nRenderHeight = 0;
    m_bStopUpdate = false;
}

PlayWindow::~PlayWindow()
{
    m_pParentWidget->setUpdatesEnabled(true);
    ReleaseAll();
}

int32_t PlayWindow::ReleaseAll()
{
    if (m_pRenderTimer != nullptr)
    {
        m_pRenderTimer->stop();
        delete m_pRenderTimer;
        m_pRenderTimer = nullptr;
    }

    {
        std::lock_guard<std::mutex> lock(m_pFrameLock);
        m_pVideoFrame = nullptr;
    }

    if (m_pSdlWindow != nullptr)
    {
        SDL_DestroyWindow(m_pSdlWindow);
        m_pSdlWindow = nullptr;
    }
    if (m_pSdlRender != nullptr)
    {
        SDL_DestroyRenderer(m_pSdlRender);
        m_pSdlRender = nullptr;
    }
    if (m_pSdlTexture != nullptr)
    {
        SDL_DestroyTexture(m_pSdlTexture);
        m_pSdlTexture = nullptr;
        m_nTextureWidth = 0;
        m_nTextureHeight = 0;
    }

    return 0;
}

int32_t PlayWindow::RenderVideoFrame(std::shared_ptr<VideoFrame>& video)
{
    if(!m_bStopUpdate)
    {
        m_pParentWidget->setUpdatesEnabled(false);
        m_bStopUpdate = true;
    }

    if (m_pFrameLock.try_lock())
    {
        m_pVideoFrame = video;
        m_pFrameLock.unlock();
    }
    return 0;
}

int32_t PlayWindow::Init()
{
    ReleaseAll();
    m_pSdlWindow = SDL_CreateWindowFrom((void*)m_pParentWidget->winId());
    if (m_pSdlWindow == nullptr)
    {
        Error("[%p][PlayWindow::Init] SDL_CreateWindowFrom fail.return:%s", this, SDL_GetError());
        ReleaseAll();
        return  -1;
    }
    m_nRenderWidth = m_pParentWidget->width();
    m_nRenderHeight = m_pParentWidget->height();
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    m_pSdlRender = SDL_CreateRenderer(m_pSdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_pSdlWindow == nullptr)
    {
        Error("[%p][PlayWindow::Init] SDL_CreateRenderer fail.return:%s", this, SDL_GetError());
        ReleaseAll();
        return  -2;
    }
    SDL_ShowWindow(m_pSdlWindow);
    SDL_SetRenderDrawColor(m_pSdlRender,255,255,255,102);
    SDL_RenderClear(m_pSdlRender);


    m_pRenderTimer = new QTimer(this);
    connect(m_pRenderTimer, &QTimer::timeout, [=] {
        RenderProcess();
        });
    m_pRenderTimer->start(40);

    return 0;
}

void PlayWindow::RenderProcess()
{
    int ret = 0;
    {
        std::lock_guard<std::mutex> lock(m_pFrameLock);
        if (m_pVideoFrame == nullptr)
        {
            return;
        }

        if (m_pSdlTexture != nullptr)
        {
            if (m_nTextureWidth != m_pVideoFrame->m_nWidth || m_nTextureHeight != m_pVideoFrame->m_nHeight)
            {
                SDL_DestroyTexture(m_pSdlTexture);
                m_pSdlTexture = nullptr;
            }
        }

        if (m_pSdlTexture == nullptr)
        {
            m_pSdlTexture = SDL_CreateTexture(m_pSdlRender, SDL_PIXELFORMAT_IYUV,
                SDL_TEXTUREACCESS_STREAMING, m_pVideoFrame->m_nWidth, m_pVideoFrame->m_nHeight);
            if (m_pSdlTexture == nullptr)
            {
                Error("[%p][PlayWindow::Init] SDL_CreateTexture fail.return:%s", this, SDL_GetError());
                return;
            }
            m_nTextureWidth = m_pVideoFrame->m_nWidth;
            m_nTextureHeight = m_pVideoFrame->m_nHeight;
        }

        ret = SDL_UpdateTexture(m_pSdlTexture, nullptr, m_pVideoFrame->m_pData, m_pVideoFrame->m_nWidth);
    }

    int width = m_pParentWidget->width();
    int height = m_pParentWidget->height();
    if (width != m_nRenderWidth || height != m_nRenderHeight)
    {
        SDL_SetWindowSize(m_pSdlWindow, width, height);
        m_nRenderWidth = width;
        m_nRenderHeight = height;
    }

    SDL_RenderClear(m_pSdlRender);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = m_nRenderWidth + 1;
    rect.h = m_nRenderHeight;
    ret = SDL_RenderCopy(m_pSdlRender, m_pSdlTexture, nullptr, &rect);
    SDL_RenderPresent(m_pSdlRender);
}
