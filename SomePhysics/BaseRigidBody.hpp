#include "IRegidBody.hpp"
#define RENDER_STEPS 96
class BaseRigidBody : public IRegidBody {
public:
	~BaseRigidBody() {

	};
	BaseRigidBody(float mMassKg, sf::Color rigidBodyColor) {
		this->mMass = mMassKg;
		this->mRigidBodyColor = rigidBodyColor;
		if (!mFont.loadFromFile("arialmt.ttf")) {
			throw std::exception("no font in folder");
		}
	
	};
	virtual void modulate(float thrownAngle, float throwImpulse, float thrownPlatformGravity) override;
	void revalidate(float angle,float impulse);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
private:
	float mPlayState = 0.0f;
	float mPlaytime = 0.0f;
	sf::Color mRigidBodyColor;
	sf::Vertex precalculated[RENDER_STEPS] = {};
	sf::Font mFont;
};