#include "StuffToBeDrawn.h"
#include "Shell.h"

void StuffToBeDrawn::updateCropRect() {
	cropRect.left = cropRect.top = 0;
	cropRect.right = textureWidth;
	cropRect.bottom = textureHeight;
}

D3DXVECTOR2 StuffToBeDrawn::getTopLeftPosition(D3DXVECTOR2 position) {
	return getTopLeftPosition(position, horizontalAlign, verticalAlign);
}

D3DXVECTOR2 StuffToBeDrawn::getTopLeftPosition(D3DXVECTOR2 position, int horizontalAlign, int verticalAlign)
{
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
	positionRect.top = getPosition().y;
	positionRect.bottom = getPosition().y + textureHeight;
	positionRect.left = getPosition().x;
	positionRect.right = getPosition().x + textureWidth;
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

D3DXVECTOR2 StuffToBeDrawn::getPosition() {
	return transformation.getPosition(); 
}

void StuffToBeDrawn::setPosition(D3DXVECTOR2 position, int horizontalAlign, int verticalAlign) {
	relativePosition = position;
	transformation.setPosition(getTopLeftPosition(position));
	updatePositionRect();
}

void StuffToBeDrawn::setPositionY(float y)
{
	relativePosition.y = y;
	transformation.setPositionY(y);
	updatePositionRect();
}

void StuffToBeDrawn::setPositionX(float x)
{
	transformation.setPositionX(x);
	updatePositionRect();
}

void StuffToBeDrawn::addPosition(D3DXVECTOR2 vector) {
	transformation.addPosition(vector);
	updatePositionRect();
}
void StuffToBeDrawn::subtractPosition(D3DXVECTOR2 vector) {
	transformation.subtractPosition(vector);
	updatePositionRect();
}
void StuffToBeDrawn::multiplyPosition(float n) {
	transformation.multiplyPosition(n);
	updatePositionRect();
}
void StuffToBeDrawn::dividePosition(float n) {
	transformation.dividePosition(n);
	updatePositionRect();
}

