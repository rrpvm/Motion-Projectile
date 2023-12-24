#include "Platform.hpp"
#define DEG_TO_RAD(x) x/180.0F*3.14159265353

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->oX, states);
	target.draw(this->oY, states);
	target.draw(this->mThrowAngleCursor,2,sf::PrimitiveType::Lines,states);
}

float Platform::angleSpeedUnit()
{
	return 15.0f;
}

void Platform::onMoveUp(float elapsedMs)
{
	//ms to s;
	angle = angle + (angleSpeedUnit() * elapsedMs / 1000.0);
	if (angle > 90.0f) {
		angle = 90.0F;
	}
	calcAngleCursor();
}

void Platform::onMoveDown(float elapsedMs)
{
	angle = angle - (angleSpeedUnit() * elapsedMs / 1000.0);
	if (angle < 0.0f) {
		angle = 0.0F;
	}
	calcAngleCursor();
}

void Platform::calcAngleCursor()
{
	auto resX = abs(this->cursorLength * cos(DEG_TO_RAD(angle)));
	auto resY = this->cursorLength * sin(DEG_TO_RAD(angle));
	this->mThrowAngleCursor[1] = this->mCenter + sf::Vector2f(resX, -resY);
}
