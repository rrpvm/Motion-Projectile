#include "IRegidBody.hpp"
#define  DEG_TO_RAD(x)x/180.0*3.14159
void IRegidBody::init(float gravity, float alpha, float impulse)
{
    mGravity = gravity;
    this->getScalarSpeed(impulse);
    this->getHorizontalSpeed(alpha);
    this->getVerticalSpeed(alpha);
}
float IRegidBody::getFlightTime(float alpha)
{
    return 2 * mSpeed * sin(DEG_TO_RAD(alpha)) / mGravity;
}

float IRegidBody::getScalarSpeed(float impulse)
{
    this->mSpeed = impulse / mMass;
    return mSpeed;
}

float IRegidBody::getHorizontalSpeed(float alpha)
{
    this->mSpeedOx = this->mSpeed * cos(DEG_TO_RAD(alpha));
    return mSpeedOx;
}

float IRegidBody::getVerticalSpeed(float alpha)
{
    this->mSpeedOy = this->mSpeed * sin(DEG_TO_RAD(alpha));
    return mSpeedOy;
}

float IRegidBody::getYPositionByTime(float time) const
{
    return mSpeedOy * time - (0.5*time*time*mGravity);
}

float IRegidBody::getXPositionByTime(float time) const
{
    return this->mSpeedOx * time;
}

