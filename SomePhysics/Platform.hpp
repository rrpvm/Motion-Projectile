#include <SFML/Graphics.hpp>
#include "ITrajectoryController.hpp"
class Platform : public sf::Drawable,ITrajectoryController  {

public:
	Platform(size_t w, size_t h) {
		const float startX = w * offset_value;
		const float startY = h * offset_value;
		const float height = h - (h * offset_value * 2);
		const float width = w - (w * offset_value * 2);
		oX.setFillColor(sf::Color(255, 0, 0, 255));
		oY.setFillColor(sf::Color(255, 0, 0, 255));
		oX.setSize(sf::Vector2f(width, 1));
		oY.setSize(sf::Vector2f(1, height));
		oX.setPosition(sf::Vector2f(startX,startY + height));
		oY.setPosition(sf::Vector2f(startX, startY));
		mCenter = sf::Vector2f(startX, startY + height);
		mThrowAngleCursor[0] = mCenter;
		calcAngleCursor();
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	float angleSpeedUnit() override;
	void onMoveUp(float elapsedMs) override;
	void onMoveDown(float elapsedMs) override;
	sf::Vector2f& getCenter() { return mCenter; }
	float angle = 90.0F;//start pos and 
private:
	void calcAngleCursor();
	sf::Vector2f mCenter;

	const float cursorLength = 200.0;
	const float offset_value = 0.25f;
	sf::RectangleShape oX;
	sf::RectangleShape oY;
	sf::Vertex mThrowAngleCursor[2] = {
		sf::Vertex(sf::Vector2f(0, 0)),
		sf::Vertex(sf::Vector2f(0, 0))
	};

};