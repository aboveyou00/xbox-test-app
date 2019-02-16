#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Game\PlaySceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"

// Renders Direct2D and 3D content on the screen.
namespace DirectX11App
{
    class DirectX11AppMain : public DX::IDeviceNotify
    {
    public:
        DirectX11AppMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
        ~DirectX11AppMain();
        void CreateWindowSizeDependentResources();
        void Update();
        bool Render();

        // IDeviceNotify
        virtual void OnDeviceLost();
        virtual void OnDeviceRestored();

    private:
        // Cached pointer to device resources.
        std::shared_ptr<DX::DeviceResources> m_deviceResources;

        // TODO: Replace with your own content renderers.
        std::unique_ptr<PlaySceneRenderer> m_sceneRenderer;
        std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

        // Rendering loop timer.
        DX::StepTimer m_timer;
    };
}
