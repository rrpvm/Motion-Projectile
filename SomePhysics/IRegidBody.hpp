#include <SFML/Graphics.hpp>
class IRegidBody {

public:
	void init(float gravity, float alpha, float impulse);
protected:
	 float getFlightTime(float alpha);
	 float getScalarSpeed(float impulse);

	 float getHorizontalSpeed(float alpha);
	 float getVerticalSpeed(float alpha);

	 float getYPositionByTime(float time) const;
	 float getXPositionByTime(float time) const;
protected:
	float mMass = 0.0f;//kg
	float mSpeed = 0.0f;//m/s
	float mSpeedOx = 0.0f; //m/s
	float mSpeedOy = 0.0f; //m/s
	float mGravity = 0.0f;//m/s^2
};