#pragma once

#include <d3d9.h>
#include <d3dx9.h>


class TransformationMatrix {
private:
	D3DXVECTOR2 position;
public:
	D3DXMATRIX matrix;

	D3DXVECTOR2 rotationCenter;
	D3DXVECTOR2 scalingCenter;
	D3DXVECTOR2 scaling;
	float scalingRotation;
	float rotation;

	TransformationMatrix();
	TransformationMatrix(D3DXVECTOR2 position);
	TransformationMatrix(D3DXVECTOR2 position,
		D3DXVECTOR2 rotationCenter,
		D3DXVECTOR2 scalingCenter,
		D3DXVECTOR2 scaling,
		float scalingRotation,
		float rotation);
	void UpdateMatrix();

	D3DXVECTOR2 getPosition();
	void setPosition(D3DXVECTOR2 vector);
	void setPositionX(float x);
	void setPositionY(float y);
	void addPosition(D3DXVECTOR2 vector);
	void subtractPosition(D3DXVECTOR2 vector);
	void multiplyPosition(float n);
	void dividePosition(float n);
};

