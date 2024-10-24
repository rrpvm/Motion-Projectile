#pragma once
#include "ApplicationKeyController.hpp"
#include <vector>
constexpr size_t PRESSED_ARR_SIZE = 256;
 class BaseApplicationKeyController : public ApplicationKeyController {
private:
	bool bPressedArrays[PRESSED_ARR_SIZE] = { false };
	std::vector<KeyEventListener*> mSubscribers = std::vector<KeyEventListener*>();
	BaseKeys processEventCode(sf::Keyboard::Key code);
	virtual bool hasSubscriber(const KeyEventListener* mSubscriber) override;
	virtual void notifyAll(BaseKeys key, KeyEventType eventyType) override;
public:
	~BaseApplicationKeyController();
	virtual void subscribe( KeyEventListener* subscriber);
	virtual void removeSubscriber(const KeyEventListener* subscriber);
	virtual void processKeyboard(sf::Event::KeyEvent* event, KeyEventType eventType);
};