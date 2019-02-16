#pragma once
#include "..\Common\StepTimer.h"
#include "..\Common\DeviceResources.h"

class GraphicsObject;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void Update(DX::StepTimer const &timer);

    double getX();
    void setX(double x);
    double getY();
    void setY(double y);

    double getDirection();
    void setDirection(double direction);
    double getSpeed();
    void setSpeed(double speed);

    double getHSpeed();
    void setHSpeed(double hspeed);
    double getVSpeed();
    void setVSpeed(double vspeed);

    virtual GraphicsObject *CreateGraphicsObject(const std::shared_ptr<DX::DeviceResources> &deviceResources) = 0;

private:
    void updateHVSpeed();
    void updateDirectionAndSpeed();

    double _x, _y, _dir, _speed, _hspeed, _vspeed;
};
