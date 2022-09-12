#include "KeyStatus.h"

void KeyStatus::updateKeyStatus(bool keyDown){
	if (keyDown) {
		if (isHolding)	isPressed = true;
		isHolding = true;
	}
	else {
		if (isHolding) {
			isReleased = true;
		}
		else {
			isReleased = false;
		}
		isPressed = false;
		isHolding = false;
	}
}
