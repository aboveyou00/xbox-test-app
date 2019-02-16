#pragma once
#include "..\Common\DeviceResources.h"

class GraphicsObject
{
public:
    GraphicsObject(const std::shared_ptr<DX::DeviceResources> &deviceResources);
    virtual ~GraphicsObject();

    virtual void CreateDeviceDependentResources();
    virtual void CreateWindowSizeDependentResources();
    virtual void ReleaseDeviceDependentResources();

    virtual void Render() = 0;

protected:
    std::shared_ptr<DX::DeviceResources> m_deviceResources;
};
