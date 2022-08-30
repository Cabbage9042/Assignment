#pragma once

#include <d3d9.h>
#include <d3dx9.h>


class TransformationMatrix{
public:
	D3DXMATRIX matrix;

	D3DXVECTOR2 position;
	D3DXVECTOR2 rotationCenter;
	D3DXVECTOR2 scalingCenter;
	D3DXVECTOR2 scaling;
	float scalingRotation;
	float rotation;

	TransformationMatrix();
	TransformationMatrix(D3DXMATRIX matrix);
	TransformationMatrix(D3DXVECTOR2 position);
	TransformationMatrix(D3DXVECTOR2 position,
		D3DXVECTOR2 rotationCenter,
		D3DXVECTOR2 scalingCenter,
		D3DXVECTOR2 scaling,
		float scalingRotation,
		float rotation);
	void UpdateMatrix();
};

