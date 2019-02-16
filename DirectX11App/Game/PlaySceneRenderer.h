#pragma once
#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

class GameObject;
class GraphicsObject;

namespace DirectX11App
{
    class PlaySceneRenderer
    {
    public:
        PlaySceneRenderer(const std::shared_ptr<DX::DeviceResources> &deviceResources);

        void CreateDeviceDependentResources();
        void CreateWindowSizeDependentResources();
        void ReleaseDeviceDependentResources();

        void Update(DX::StepTimer const &timer);
        void Render();

    private:
        void CreateScene();

        std::shared_ptr<DX::DeviceResources> m_deviceResources;

        std::vector<GameObject*> m_gameObjects;
        std::map<GameObject*, GraphicsObject*> m_graphicsObjects;

        bool m_loadingComplete;
    };
}
