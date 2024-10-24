#include <SFML/Graphics.hpp>
#include "KeyEventListener.hpp"
#include "BaseGameObject.hpp"
#include "IRegidBody.hpp"
class Platform : public sf::Drawable,public KeyEventListener,BaseGameObject   {

public:
	Platform(size_t w, size_t h) {
		if (!mFont.loadFromFile("arialmt.ttf")) {
			throw std::exception("no font in folder");
		}
		onResize(w, h);

	}
	~Platform() {
		delete[] axisX;
		delete[] axisY;
		delete[] mThrowAngleCursor;
		for (auto body : entities) {
			delete body;
		}
		entities.clear();
	}
	void onResize(size_t w, size_t h);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	void spawnRigidBody(IRegidBody* body);

	//BaseGameObject
	virtual void update(float elapsedMs) override;
	//KeyEventListener
	virtual void onKeyChanged(BaseKeys key, KeyEventType eventType) override;
private:
	const float cursorLength = 616.0f;
	float thrownAngle = 90.0F;//платформа задает
	float thrownImpuplse = 100.0F;//platform sets
	float platformGravity = 9.81F;//платформа задает
	size_t width = 0u;
	size_t height = 0u;
	sf::Vertex* mThrowAngleCursor;
	sf::Vertex* axisX;
	sf::Vertex* axisY;
	sf::Font mFont;
	std::vector<IRegidBody*>entities;
	void calcAngleCursor();
	float getVelocityModule();
	float angleSpeedUnit();
	enum PlatformDirection {
		UP, DOWN, NONE
	};
	PlatformDirection mDirection = PlatformDirection::NONE;
};