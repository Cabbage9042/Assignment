#pragma once
class KeyStatus{
public:
	bool isPressed = false;
	bool isHolding = false;
	bool isReleased = true;

	void updateKeyStatus(bool keyDown);
};

