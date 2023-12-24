#include "Platform.hpp"
#define DEG_TO_RAD(x) x/180.0F*3.14159265353

void Platform::onResize(size_t w, size_t h)
{
	this->width = w;
	this->height = h;
	mCenter = sf::Vector2f(w/2.0f,h/2.0f);
	oX[0] = sf::Vertex(sf::Vector2f(0,mCenter.y), sf::Color(0, 255, 0, 255));
	oX[1] = sf::Vertex(sf::Vector2f(w,mCenter.y), sf::Color(0, 255, 0, 255));
	oY[0] = sf::Vertex(sf::Vector2f(mCenter.x, -(int)h), sf::Color(0, 255, 0, 255));
	oY[1] = sf::Vertex(sf::Vector2f(mCenter.x, h), sf::Color(0, 255, 0, 255));
	mThrowAngleCursor[0] = sf::Vertex(mCenter, sf::Color(255,0,0,255));
	calcAngleCursor();
}

void Platform::onChangeWorld(size_t newWidth, size_t newHeight)
{
	this->width = newWidth;
	this->height = newHeight;
	onMoveMap(mLastOffset);
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(oX, sizeof oX / sizeof(sf::Vertex) , sf::PrimitiveType::Lines, states);
	target.draw(oY, sizeof oY / sizeof(sf::Vertex) , sf::PrimitiveType::Lines, states);
	target.draw(this->mThrowAngleCursor,2,sf::PrimitiveType::Lines,states);
}

void Platform::onMoveMap(const sf::Vector2f& offset)
{
	mLastOffset = offset;
	oY[0] = sf::Vertex(sf::Vector2f(mCenter.x, offset.y - height), sf::Color(0, 255, 0, 255));
	oY[1] = sf::Vertex(sf::Vector2f(mCenter.x,offset.y + height), sf::Color(0, 255, 0, 255));
	oX[1] = sf::Vertex(sf::Vector2f(offset.x + width, mCenter.y), sf::Color(0, 255, 0, 255));
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
	this->mThrowAngleCursor[1] = sf::Vertex(this->mCenter + sf::Vector2f(resX, -resY), sf::Color(255,0,0,255));
}
