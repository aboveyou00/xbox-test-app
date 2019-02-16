#pragma once
#include "GameObject.h"

class PlayerGameObject : public GameObject
{
public:
    PlayerGameObject();
    virtual ~PlayerGameObject();

    virtual void Update(DX::StepTimer const &timer) override;

    virtual GraphicsObject *CreateGraphicsObject(const std::shared_ptr<DX::DeviceResources> &deviceResources) override;
};
