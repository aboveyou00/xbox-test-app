#pragma once
#include "GraphicsObject.h"
#include "../Content/ShaderStructures.h"
#include "../Common/DeviceResources.h"

class PlayerGameObject;

class PlayerGraphicsObject : public GraphicsObject
{
public:
    PlayerGraphicsObject(PlayerGameObject &player, const std::shared_ptr<DX::DeviceResources> &deviceResources);
    virtual ~PlayerGraphicsObject();

    virtual void CreateDeviceDependentResources() override;
    virtual void CreateWindowSizeDependentResources() override;
    virtual void ReleaseDeviceDependentResources() override;

    virtual void Render() override;

private:
    PlayerGameObject &m_player;

    // Direct3D resources for cube geometry.
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

    // System resources for cube geometry.
    DirectX11App::ModelViewProjectionConstantBuffer m_constantBufferData;
    uint32 m_indexCount;

    // Variables used with the rendering loop.
    bool m_loadingComplete;
};
