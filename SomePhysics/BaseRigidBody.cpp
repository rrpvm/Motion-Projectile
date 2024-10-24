#include "BaseRigidBody.hpp"



void BaseRigidBody::modulate(float thrownAngle, float throwImpulse, float thrownPlatformGravity)
{
	this->init(thrownPlatformGravity, thrownAngle, throwImpulse);
	revalidate(thrownAngle, throwImpulse);
}

void BaseRigidBody::revalidate(float angle, float impulse)
{
	this->mPlaytime = this->getFlightTime(angle);
	this->mPlayState = 0;

	float dwOffset = this->mPlaytime / RENDER_STEPS;
	
	for (int step = 0; step < RENDER_STEPS; step++) {
		float flTime = dwOffset * step;
		float y = getYPositionByTime(flTime);
		float x = getXPositionByTime(flTime);
		precalculated[step] =	sf::Vertex( sf::Vector2f(x,-y), this->mRigidBodyColor);
	}
}



void BaseRigidBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const auto  workingRectSize = sf::Vector2f(0.0f,0.0f);
	auto pos = sf::Vector2f(0, 0);
	target.draw(this->precalculated, RENDER_STEPS , sf::PrimitiveType::LineStrip, states);
	auto massText = sf::Text(std::to_string(this->mMass), mFont, 24u);
	auto endText = sf::Text(std::to_string(precalculated[RENDER_STEPS - 1].position.x), mFont, 24u);
	massText.setPosition(precalculated[RENDER_STEPS/2].position);
	endText.setPosition(precalculated[RENDER_STEPS-1].position);
	target.draw(massText);
	target.draw(endText);
}