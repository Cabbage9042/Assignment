#include "TransformationMatrix.h"

TransformationMatrix::TransformationMatrix() {

	position = D3DXVECTOR2(0.0f, 0.0f);

	scalingRotation = 0.0f;
	rotation = 0.0f;

	rotationCenter = D3DXVECTOR2(0.0f, 0.0f);
	scalingCenter = D3DXVECTOR2(0.0f, 0.0f);
	scaling = D3DXVECTOR2(1.0f, 1.0f);


}

TransformationMatrix::TransformationMatrix(D3DXVECTOR2 position){
	this->position = position;
	this->scalingRotation = 0.0f;
	this->rotation = 0.0f;
	this->rotationCenter = D3DXVECTOR2(0.0f, 0.0f);
	this->scalingCenter = D3DXVECTOR2(0.0f, 0.0f);
	this->scaling = D3DXVECTOR2(1.0f, 1.0f);

}

TransformationMatrix::TransformationMatrix(D3DXVECTOR2 position, D3DXVECTOR2 rotationCenter, D3DXVECTOR2 scalingCenter, D3DXVECTOR2 scaling, float scalingRotation, float rotation) {
	this->position = position;
	this->scalingRotation = scalingRotation;
	this->rotation = rotation;
	this->rotationCenter = rotationCenter;
	this->scalingCenter = scalingCenter;
	this->scaling = scaling;

}

void TransformationMatrix::UpdateMatrix() {
	D3DXMatrixTransformation2D(&matrix, &scalingCenter, scalingRotation,
		&scaling, &rotationCenter, rotation, &position);
}

D3DXVECTOR2 TransformationMatrix::getPosition()
{
	return position;
}

void TransformationMatrix::setPosition(D3DXVECTOR2 position)
{
	this->position = position;
}

void TransformationMatrix::setPositionX(float x)
{
	position.x = x;
}

void TransformationMatrix::setPositionY(float y)
{
	position.y = y;
}

void TransformationMatrix::addPosition(D3DXVECTOR2 vector)
{
	this->position += vector;
}

void TransformationMatrix::subtractPosition(D3DXVECTOR2 vector)
{
	this->position -= vector;
}

void TransformationMatrix::multiplyPosition(float n)
{
	this->position *= n;
}

void TransformationMatrix::dividePosition(float n)
{
	this->position /= n;
}



