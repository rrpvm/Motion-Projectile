#include "Platform.hpp"
#define DEG_TO_RAD(x) x/180.0F*3.14159265353
const sf::Vector2f emptyVector = sf::Vector2f(0, 0);
void Platform::onResize(size_t w, size_t h)
{
	this->width = w;
	this->height = h;
	
	if (this->axisX != nullptr) {
		delete[] axisX;
	}
	if (this->axisY != nullptr) {
		delete[] axisY;
	}
	this->axisX = new sf::Vertex[2]{
		sf::Vertex(sf::Vector2f(-(int)width / 2.f, 0.0f),  sf::Color(0, 255, 0, 255)),
		sf::Vertex(sf::Vector2f(width / 2.f,0.0f),  sf::Color(0, 255, 0, 255)),
	};
	this->axisY = new sf::Vertex[2]{
		sf::Vertex(sf::Vector2f(0.0f, -(int)h / 2.f),  sf::Color(0, 255, 0, 255)),
		sf::Vertex(sf::Vector2f(0.0f, h / 2.f),  sf::Color(0, 255, 0, 255)),
	};
	calcAngleCursor();
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(axisX, sizeof(sf::Vertex)*2 / sizeof(sf::Vertex), sf::PrimitiveType::Lines, states);
	target.draw(axisY, sizeof(sf::Vertex)*2 / sizeof(sf::Vertex), sf::PrimitiveType::Lines, states);
	target.draw(this->mThrowAngleCursor, 2, sf::PrimitiveType::Lines, states);
	for (auto entity : entities) {
		target.draw(*entity);
	}
	auto angleText = sf::Text(std::to_string(this->thrownAngle), mFont, 20u);
	angleText.setPosition(mThrowAngleCursor[1].position);
	target.draw(angleText);
}
void Platform::spawnRigidBody(IRegidBody* body)
{
	entities.push_back(body);
}
float Platform::angleSpeedUnit()
{
	return 15.0f;
}

void Platform::update(float elapsedMs)
{
	if (mDirection == PlatformDirection::NONE)return;
	auto velocityModule = getVelocityModule();
	thrownAngle = thrownAngle + (velocityModule * elapsedMs / 1000.0);
	if (thrownAngle > 90.0f) {
		thrownAngle = 90.0F;
	}
	else if (thrownAngle < 0.0F) {
		thrownAngle = 0.0F;
	}
	calcAngleCursor();
	for (const auto& entity : entities) {
		entity->modulate(this->thrownAngle, this->thrownImpuplse, this->platformGravity);
	}
}

void Platform::onKeyChanged(BaseKeys key, KeyEventType eventType)
{
	if (key == BaseKeys::MOVE_UP && eventType == KeyEventType::PRESSED) {
		this->mDirection = PlatformDirection::UP;
	}
	else if (key == BaseKeys::MOVE_DOWN && eventType == KeyEventType::PRESSED) {
		this->mDirection = PlatformDirection::DOWN;
	}
	else {
		this->mDirection = PlatformDirection::NONE;
	}
}

void Platform::calcAngleCursor()
{
	auto resX = abs(this->cursorLength * cos(DEG_TO_RAD(thrownAngle)));
	auto resY = this->cursorLength * sin(DEG_TO_RAD(thrownAngle));
	if (this->mThrowAngleCursor != nullptr) {
		delete[] mThrowAngleCursor;
	}
	static sf::Color fAngleCursorColor = sf::Color(255, 0, 0, 255);
	this->mThrowAngleCursor = new sf::Vertex[2]{ sf::Vertex(emptyVector,fAngleCursorColor), sf::Vertex(sf::Vector2f(resX, -resY), fAngleCursorColor) };
}
float Platform::getVelocityModule()
{
	int multplier = 0;
	if (mDirection == PlatformDirection::DOWN) {
		multplier = -1;
	}
	else if (mDirection == PlatformDirection::UP) {
		multplier = 1;
	}
	else multplier = 0;
	return angleSpeedUnit() * multplier;
}
