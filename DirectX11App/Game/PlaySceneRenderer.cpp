#include "pch.h"
#include "PlaySceneRenderer.h"
#include "PlayerGameObject.h"
#include "GraphicsObject.h"

DirectX11App::PlaySceneRenderer::PlaySceneRenderer(const std::shared_ptr<DX::DeviceResources> &deviceResources)
    : m_loadingComplete(false),
      m_deviceResources(deviceResources)
{
    CreateScene();

    CreateDeviceDependentResources();
    CreateWindowSizeDependentResources();
}

void DirectX11App::PlaySceneRenderer::CreateScene()
{
    m_gameObjects.push_back(new PlayerGameObject());

    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
    {
        auto gameObj = *it;
        auto graphicsObj = gameObj->CreateGraphicsObject(m_deviceResources);
        if (graphicsObj != nullptr)
        {
            m_graphicsObjects[gameObj] = graphicsObj;
        }
    }
}

void DirectX11App::PlaySceneRenderer::CreateDeviceDependentResources()
{
    for (auto it = m_graphicsObjects.begin(); it != m_graphicsObjects.end(); it++)
    {
        auto pair = *it;
        auto graphicsObj = pair.second;
        graphicsObj->CreateDeviceDependentResources();
    }
}

void DirectX11App::PlaySceneRenderer::CreateWindowSizeDependentResources()
{
    for (auto it = m_graphicsObjects.begin(); it != m_graphicsObjects.end(); it++)
    {
        auto pair = *it;
        auto graphicsObj = pair.second;
        graphicsObj->CreateWindowSizeDependentResources();
    }
}

void DirectX11App::PlaySceneRenderer::ReleaseDeviceDependentResources()
{
    for (auto it = m_graphicsObjects.begin(); it != m_graphicsObjects.end(); it++)
    {
        auto pair = *it;
        auto graphicsObj = pair.second;
        graphicsObj->ReleaseDeviceDependentResources();
    }
}

void DirectX11App::PlaySceneRenderer::Update(DX::StepTimer const &timer)
{
    for (auto it = m_graphicsObjects.begin(); it != m_graphicsObjects.end(); it++)
    {
        auto pair = *it;
        auto gameObj = pair.first;
        gameObj->Update(timer);
    }
}

void DirectX11App::PlaySceneRenderer::Render()
{
    for (auto it = m_graphicsObjects.begin(); it != m_graphicsObjects.end(); it++)
    {
        auto pair = *it;
        auto graphicsObj = pair.second;
        graphicsObj->Render();
    }
}
