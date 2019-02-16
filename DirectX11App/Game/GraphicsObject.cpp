#include "pch.h"
#include "GraphicsObject.h"

GraphicsObject::GraphicsObject(const std::shared_ptr<DX::DeviceResources> &deviceResources)
    : m_deviceResources(deviceResources)
{
}
GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::CreateDeviceDependentResources()
{
}

void GraphicsObject::CreateWindowSizeDependentResources()
{
}

void GraphicsObject::ReleaseDeviceDependentResources()
{
}
