#include "IRegidBody.hpp"
#define RENDER_STEPS 24
class BaseRigidBody : public IRegidBody, public sf::Drawable {
public:
	BaseRigidBody(float worldGravity,float mMassKg, sf::Vector2f& mCenter) {
		mGravity = worldGravity;
		this->mMass = mMassKg;
		this->origin = mCenter;
		init(worldGravity, 0.0f, 0.0f);
	}
	void revalidate(float alpha,float impulse);
	void onResize(sf::Vector2f& mCenter);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	void play(float elapsed);
private:
	sf::Vector2f origin;
	float mPlayState = 0.0f;
	float mPlaytime = 0.0f;
	float mMaxX = 0.0f;
	float mMaxY = 0.0f;
	sf::Vector2f precalculated[RENDER_STEPS + 1] = {};
};