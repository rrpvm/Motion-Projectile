#include "BaseRigidBody.hpp"

void BaseRigidBody::revalidate(float alpha, float impulse)
{
	this->init(mGravity, alpha, impulse);
	this->mPlaytime = this->getFlightTime(alpha);
	this->mPlayState = 0;
}

void BaseRigidBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	const  auto mSteps = 24;

	auto mStep = this->mPlaytime / mSteps;
	auto pos = sf::Vector2f(0, 0);
	sf::Vertex vertex[mSteps + 1] = {
		{this->origin + pos}
	};
	for (int step = 0; step <= mSteps; step++) {
		float value = mStep * step;
		float y = getYPositionByTime(value);
		float x = getXPositionByTime(value);
		pos.x = x;
		pos.y = -y;
		vertex[step] = { this->origin + pos };
	}
	target.draw(vertex, mSteps + 1, sf::PrimitiveType::LineStrip, states);
}

void BaseRigidBody::play(float elapsedMs)
{
	/*if (this->mPlayState > this->mPlaytime) {
		mPlayState = 0;
	}
 	auto y = this->getYPositionByTime(mPlayState, this->mSpeed0, this->mGravity);
	auto x = this->getXPositionByTime(this->mPlayState, this->mSpeed0);
	this->position.x = x;
	this->position.y = -y;
	this->mPlayState += elapsedMs/1000.0;
	*/
}
