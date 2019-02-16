#include "pch.h"
#include "PlayerGameObject.h"
#include "PlayerGraphicsObject.h"

PlayerGameObject::PlayerGameObject()
{
}
PlayerGameObject::~PlayerGameObject()
{
}

void PlayerGameObject::Update(DX::StepTimer const &timer)
{
    GameObject::Update(timer);
}

GraphicsObject *PlayerGameObject::CreateGraphicsObject(const std::shared_ptr<DX::DeviceResources> &deviceResources)
{
    return new PlayerGraphicsObject(*this, deviceResources);
}
