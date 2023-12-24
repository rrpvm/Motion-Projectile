#include "BaseRigidBody.hpp"

void BaseRigidBody::revalidate(float alpha, float impulse)
{
	mMaxX = INT_MIN;
	mMaxY = INT_MIN;
	this->init(mGravity, alpha, impulse);
	this->mPlaytime = this->getFlightTime(alpha);
	this->mPlayState = 0;

	float dwOffset = this->mPlaytime / RENDER_STEPS;
	
	for (int step = 0; step <= RENDER_STEPS; step++) {
		float flTime = dwOffset * step;
		float y = getYPositionByTime(flTime);
		float x = getXPositionByTime(flTime);
		precalculated[step] =  sf::Vector2f(x,-y);
		if (x > mMaxX)mMaxX = x;
		if (y > mMaxY)mMaxY = y;
	}
}

void BaseRigidBody::onResize(sf::Vector2f& mCenter)
{
	this->origin = mCenter;
}

void BaseRigidBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const auto  workingRectSize = sf::Vector2f(origin.x, origin.y);
	auto pos = sf::Vector2f(0, 0);
	sf::Vertex vertex[RENDER_STEPS  + 1] = {
		{this->origin + pos}
	};
	int i = 0;
	auto minX = workingRectSize.x > mMaxX ? mMaxX : workingRectSize.x;
	auto minY = workingRectSize.y > mMaxY ? mMaxY : workingRectSize.y;
	for (auto& pos : precalculated) {
		vertex[i] = { this->origin + sf::Vector2f(pos.x, pos.y ) };
	//	vertex[i] = { this->origin + sf::Vector2f(pos.x / mMaxX * minX, pos.y / mMaxY * minY) };
		i++;
	}
	target.draw(vertex, RENDER_STEPS + 1 , sf::PrimitiveType::LineStrip, states);
	
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
