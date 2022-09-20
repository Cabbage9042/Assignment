#include "KeyStatus.h"

void KeyStatus::updateKeyStatus(bool keyDown) {
	//if key is being pressed
	if (keyDown) {
		//
		if (!isHolding) {
			isPressed = true; //isPressed is only true the moment key is pressed
		}
		
		isHolding = true; //holding is always true if key is down
	}

	//if key is not being pressed
	else {
		if (isHolding) {
			isReleased = true; // if key was down, is release is true (at the moment key is release)
		}
		else {
			isReleased = false;
		}
		isPressed = false;
		isHolding = false;
	}
}
