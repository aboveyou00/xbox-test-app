#include "pch.h"
#include "GameObject.h"
#include "math-utils.h"

GameObject::GameObject()
    : _x(0.0), _y(0.0), _dir(0.0), _speed(0.0), _hspeed(0.0), _vspeed(0.0)
{
}
GameObject::~GameObject()
{
}

void GameObject::Update(DX::StepTimer const &timer)
{
    auto delta = timer.GetElapsedSeconds();
    _x += _hspeed * delta;
    _y += _vspeed * delta;
}

inline double GameObject::getX()
{
    return _x;
}
inline void GameObject::setX(double x)
{
    _x = x;
}
inline double GameObject::getY()
{
    return _y;
}
inline void GameObject::setY(double y)
{
    _y = y;
}

inline double GameObject::getDirection()
{
    return _dir;
}
inline void GameObject::setDirection(double direction)
{
    direction = fmod(direction, 360.0);
    if (direction < 0)
    {
        direction += 360.0;
    }
    if (direction != _dir)
    {
        _dir = direction;
        updateHVSpeed();
    }
}
inline double GameObject::getSpeed()
{
    return _speed;
}
inline void GameObject::setSpeed(double speed)
{
    if (speed < 0)
    {
        throw std::exception("Speed can't be less than 0.");
    }
    if (speed != _speed)
    {
        _speed = speed;
        updateHVSpeed();
    }
}

inline double GameObject::getHSpeed()
{
    return _hspeed;
}
inline void GameObject::setHSpeed(double hspeed)
{
    if (hspeed != _hspeed)
    {
        _hspeed = hspeed;
        updateDirectionAndSpeed();
    }
}
inline double GameObject::getVSpeed()
{
    return _vspeed;
}
inline void GameObject::setVSpeed(double vspeed)
{
    if (vspeed != _vspeed)
    {
        _vspeed = vspeed;
        updateDirectionAndSpeed();
    }
}

void GameObject::updateHVSpeed()
{
    auto radians = degToRad(_dir);
    _hspeed = -sin(radians) * _speed;
    _vspeed = cos(radians) * _speed;
}
void GameObject::updateDirectionAndSpeed()
{
    _speed = sqrt(_hspeed * _hspeed + _vspeed * _vspeed);
    _dir = pointDirection(0.0, 0.0, _hspeed, _vspeed);
}
