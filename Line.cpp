#include "Line.h"

Line::Line(std::vector<D3DXVECTOR2>* vertices,bool closing, float size, D3DCOLOR color){
	this->vertices = vertices;
	this->size = size;
	this->color = color;
	this->closing = closing;

	if (closing) {
		vertices->push_back(vertices->front());
	}

}


void Line::Release(){
	delete vertices;
	vertices = NULL;
}

void Line::DrawLines(std::vector<Line*>* vertices){
	Shell::directXManager.lineBrush->Begin();

	for (int i = 0; i < vertices->size(); i++) {
		vertices->at(i)->Draw();
	
	}

	
	Shell::directXManager.lineBrush->End();
}


void Line::Draw(){
	
	Shell::directXManager.lineBrush->SetWidth(size);
	Shell::directXManager.lineBrush->Draw(vertices->data(), vertices->size(),color);

	
}

