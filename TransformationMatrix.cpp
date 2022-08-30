#include "TransformationMatrix.h"

TransformationMatrix::TransformationMatrix() {

	position = D3DXVECTOR2(0.0f, 0.0f);

	scalingRotation = 0.0f;
	rotation = 0.0f;

	rotationCenter = D3DXVECTOR2(0.0f, 0.0f);
	scalingCenter = D3DXVECTOR2(0.0f, 0.0f);
	scaling = D3DXVECTOR2(1.0f, 1.0f);

	UpdateMatrix();

}

TransformationMatrix::TransformationMatrix(D3DXVECTOR2 position){
	this->position = position;
	this->scalingRotation = 0.0f;
	this->rotation = 0.0f;
	this->rotationCenter = D3DXVECTOR2(0.0f, 0.0f);
	this->scalingCenter = D3DXVECTOR2(0.0f, 0.0f);
	this->scaling = D3DXVECTOR2(1.0f, 1.0f);

	UpdateMatrix();
}

TransformationMatrix::TransformationMatrix(D3DXVECTOR2 position, D3DXVECTOR2 rotationCenter, D3DXVECTOR2 scalingCenter, D3DXVECTOR2 scaling, float scalingRotation, float rotation) {
	this->position = position;
	this->scalingRotation = scalingRotation;
	this->rotation = rotation;
	this->rotationCenter = rotationCenter;
	this->scalingCenter = scalingCenter;
	this->scaling = scaling;

	UpdateMatrix();
}

void TransformationMatrix::UpdateMatrix() {
	D3DXMatrixTransformation2D(&matrix, &scalingCenter, scalingRotation,
		&scaling, &rotationCenter, rotation, &position);
}

