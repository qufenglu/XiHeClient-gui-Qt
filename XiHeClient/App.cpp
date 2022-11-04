#include "App.h"

App::App()
{
    m_pXiheClient = nullptr;
}

App::~App()
{
    m_pXiheClient = nullptr;
}

 std::shared_ptr<XIheClient> App::GetClient()
 {
     return m_pXiheClient;
 }

 void App::SetClient(const std::shared_ptr<XIheClient>& client)
 {
     m_pXiheClient = client;
 }

  void App::ReleaseClient()
  {
      m_pXiheClient = nullptr;
  }
