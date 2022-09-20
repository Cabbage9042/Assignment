#include "StuffToBeDrawn.h"
#include "Shell.h"

void StuffToBeDrawn::updateCropRect() {
	cropRect.left = cropRect.top = 0;
	cropRect.right = textureWidth;
	cropRect.bottom = textureHeight;
}

D3DXVECTOR2 StuffToBeDrawn::getTopLeftPosition(D3DXVECTOR2 position) {
	D3DXVECTOR2 topLeftPosition;
	switch (horizontalAlign) {
	case leftAlign:
		topLeftPosition.x = position.x;
		break;
	case rightAlign:
		topLeftPosition.x = position.x - textureWidth;
		break;
	case centerAlign:
		topLeftPosition.x = position.x - (textureWidth / 2.0);
		break;
	}

	switch (verticalAlign) {
	case topAlign:
		topLeftPosition.y = position.y;
		break;
	case bottomAlign:
		topLeftPosition.y = position.y - textureHeight;
		break;
	case middleAlign:
		topLeftPosition.y = position.y - (textureHeight / 2.0);
		break;
	}

	return topLeftPosition;
}

void StuffToBeDrawn::updatePositionRect(){
	positionRect.top = transformation.position.y;
	positionRect.bottom = transformation.position.y + textureHeight;
	positionRect.left = transformation.position.x;
	positionRect.right = transformation.position.x + textureWidth;
}


bool StuffToBeDrawn::isHoverOn(StuffToBeDrawn* textureBelow) {
	//cout << " texture below top " << textureBelow->positionRect.top <<
	//	" bottom " << textureBelow->positionRect.bottom <<
	//	" left " << textureBelow->positionRect.left <<
	//	" right " << textureBelow->positionRect.right << endl;
	return (textureBelow->positionRect.top <= this->getPosition().y &&
		textureBelow->positionRect.bottom >= this->getPosition().y &&
		textureBelow->positionRect.left <= this->getPosition().x &&
		textureBelow->positionRect.right >= this->getPosition().x);
}

bool StuffToBeDrawn::isHoverOn(RECT rect, D3DXVECTOR2 position)
{
	return (rect.top <= position.y &&
		rect.bottom >= position.y &&
		rect.left <= position.x &&
		rect.right >= position.x);
}

bool StuffToBeDrawn::isClickedOn(StuffToBeDrawn* textureBelow, bool mouseLeftButtonClicked) {
	return (isHoverOn(textureBelow) && mouseLeftButtonClicked);
}



