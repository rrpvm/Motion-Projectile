#pragma once
#include "KeyInfo.hpp"
#include "KeyEventListener.hpp"
#include <SFML/Graphics.hpp>


class ApplicationKeyController{
protected:
	virtual bool hasSubscriber(const KeyEventListener* mSubscriber) {
		return false;
	};
	virtual void notifyAll(BaseKeys key, KeyEventType eventyType) = 0;
public:
	virtual void subscribe( KeyEventListener* subscriber) = 0;
	virtual void removeSubscriber(const KeyEventListener* subscriber) = 0;
	virtual void processKeyboard(sf::Event::KeyEvent* event, KeyEventType eventType) = 0;
};