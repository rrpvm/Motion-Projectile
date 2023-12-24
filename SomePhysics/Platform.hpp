#include <SFML/Graphics.hpp>
#include "ITrajectoryController.hpp"
class Platform : public sf::Drawable,ITrajectoryController  {

public:
	Platform(size_t w, size_t h) {
		onResize(w, h);
	}
	void onResize(size_t w, size_t h);
	void onChangeWorld(size_t newWidth, size_t newHeight);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	void onMoveMap(const sf::Vector2f& offset);
	void onMoveUp(float elapsedMs) override;
	void onMoveDown(float elapsedMs) override;
	sf::Vector2f& getCenter() { return mCenter; }
	float angle = 90.0F;//start pos and 
	float angleSpeedUnit() override;
private:
	size_t width = 0u;
	size_t height = 0u;
	sf::Vector2f mLastOffset = sf::Vector2f(0,0);
	sf::Vector2f mCenter;
	void calcAngleCursor();
	const float cursorLength = 616.0f;
	sf::Vertex oX[2] = {};
	sf::Vertex oY[2] = {};
	sf::Vertex mThrowAngleCursor[2] = {
		sf::Vertex(sf::Vector2f(0, 0),sf::Color(255,0,0,255)),
		sf::Vertex(sf::Vector2f(0, 0))
	};

};