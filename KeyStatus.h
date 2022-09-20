#pragma once
class KeyStatus{
public:
	bool isPressed = false;
	bool isHolding = false;
	bool isReleased = false;

	void updateKeyStatus(bool keyDown);
};

