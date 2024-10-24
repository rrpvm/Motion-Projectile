#pragma once
#include "KeyInfo.hpp"
class KeyEventListener {
public:
	virtual void onKeyChanged(BaseKeys key, KeyEventType eventType) = 0;
};