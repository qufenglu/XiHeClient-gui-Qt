#pragma once
#include <memory>
#include "XiheClient.h"

class App
{
public:
    App();
    ~App();
    std::shared_ptr<XIheClient> GetClient();
    void SetClient(const std::shared_ptr<XIheClient>& client);
    void ReleaseClient();

private:
    std::shared_ptr<XIheClient> m_pXiheClient;
};
