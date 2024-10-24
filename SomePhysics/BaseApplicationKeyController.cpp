#include "BaseApplicationController.hpp"
BaseKeys BaseApplicationKeyController::processEventCode(sf::Keyboard::Key code)
{
	BaseKeys key;
	switch (code)
	{
	case sf::Keyboard::Up:
		key = BaseKeys::MOVE_UP;
		break;
	case sf::Keyboard::Down:
		key = BaseKeys::MOVE_DOWN;

		break;
	default:
		key = UNDEFINED;
	}
	return key;
}
bool BaseApplicationKeyController::hasSubscriber(const KeyEventListener* mSubscriber) {
	for (auto subscriber : mSubscribers) {
		if (mSubscriber == subscriber) return true;
	}
	return false;
}

void BaseApplicationKeyController::notifyAll(BaseKeys key, KeyEventType eventyType) {
	for (auto subscriber : mSubscribers) {
		if (subscriber == nullptr) {
			continue;//remove, but not today
		}
		subscriber->onKeyChanged(key, eventyType);
	}
}

BaseApplicationKeyController::~BaseApplicationKeyController() {
	for (auto subscriber : mSubscribers) {
		delete subscriber;
	}
	mSubscribers.clear();
};
void BaseApplicationKeyController::subscribe( KeyEventListener* subscriber) {
	if (hasSubscriber(subscriber))return;
	mSubscribers.push_back(subscriber);

};
void BaseApplicationKeyController::removeSubscriber(const KeyEventListener* subscriber) {
	size_t idx = 0;
	for (auto it : mSubscribers) {
		if (subscriber == it) {
			mSubscribers.erase(mSubscribers.begin() + idx);
			delete subscriber;
			return;
		}
		idx++;
	}
	throw std::exception("no suck item in class");
};
void BaseApplicationKeyController::processKeyboard(sf::Event::KeyEvent* event, KeyEventType eventType) {
	if (event == nullptr) {
		throw std::exception("event is null");
	}
	if (event->code >= PRESSED_ARR_SIZE) {
		throw std::exception("too big event code");
	}

	auto prevState = bPressedArrays[event->code];
	auto newState = eventType == KeyEventType::PRESSED;
	bPressedArrays[event->code] = newState;
	if (prevState != newState) {
		notifyAll(processEventCode(event->code), eventType);
	}
}

