#include "Shell.h"
#include "MainMenu.h"

WindowManager Shell::windowManager;
DirectXManager Shell::directXManager;
std::vector<Game*>* Shell::levelVector = new std::vector<Game*>;
std::vector<LPD3DXFONT>* Shell::fonts;



void Shell::InitializeFonts() {
	LPD3DXFONT font = NULL;

	HRESULT hr = D3DXCreateFont(directXManager.d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	fonts->push_back(font);

	hr = D3DXCreateFont(directXManager.d3dDevice, 100, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Franklin Gothic Medium", &font);

	fonts->push_back(font);

	font = NULL;
}

void Shell::InitializeGame() {

	windowManager.CreateMyWindow();
	directXManager.CreateMyDX(windowManager.g_hWnd);
	directXManager.CreateMyDInput(windowManager.g_hWnd);
	levelVector->push_back(new MainMenu());

	fonts = new vector<LPD3DXFONT>;
	InitializeFonts();

	levelVector->back()->InitializeLevel();

}



void Shell::uninitializeLevelVector() {
	for (int i = levelVector->size() - 1; i >= 0; i--) {
		levelVector->at(i)->UninitializeLevel();
		delete levelVector->at(i);
		levelVector->at(i) = NULL;
	}
	delete levelVector;
	levelVector = NULL;
}



void Shell::uninitializeFonts() {
	delete fonts;
	fonts = NULL;
}

void Shell::CreateTexture(LPCSTR filePath, vector<Texture*>* textures,
	int textureWidth, int textureHeight,  D3DXVECTOR2 position,
	int alignForm, D3DCOLOR color ) {
	LPDIRECT3DTEXTURE9 texture = NULL;
	HRESULT hr = D3DXCreateTextureFromFile(Shell::directXManager.d3dDevice, filePath, &texture);
	if (FAILED(hr)) {
		cout << filePath << " failed" << endl;
	}

	textures->push_back(new Texture(texture, textureWidth, textureHeight, position,alignForm,color));
	texture = NULL;
}

void Shell::ReleaseTextures(vector<Texture*>* textures) {
	for (int i = textures->size() - 1; i >= 0; i--) {
		textures->at(i)->Release();
		delete textures->at(i);
		textures->at(i) = NULL;
	}
	
	delete textures;
	textures = NULL;
}


void Shell::CreateSprite(vector<Sprite*>* sprites, LPCSTR filePath,
	int textureWidth, int textureHeight,
	int spriteWidth, int spriteHeight,
	int spriteRow, int spriteColumn,
	int currentCol,int currentRow,
	int maxFrame,
	D3DXVECTOR2 position,
	int alignFrom, D3DCOLOR color) {
	LPDIRECT3DTEXTURE9 texture = NULL;
	HRESULT hr = D3DXCreateTextureFromFile(Shell::directXManager.d3dDevice, filePath, &texture);
	if (FAILED(hr)) {
		cout << filePath << " failed" << endl;
	}

	sprites->push_back(new Sprite(texture,textureWidth,textureHeight,spriteWidth,spriteHeight,
		spriteRow,spriteColumn,currentCol,currentRow,maxFrame,position,alignFrom, color));
	texture = NULL;
}

void Shell::ReleaseSprite(vector<Sprite*>* sprites) {
	for (int i = sprites->size() - 1; i >= 0; i--) {
		sprites->at(i)->Release();
		delete sprites->at(i);
		sprites->at(i) = NULL;
	}

	delete sprites;
	sprites = NULL;
}

void Shell::UninitializeGame() {

	uninitializeLevelVector();
	uninitializeFonts();
	directXManager.CleanUpMyDInput();
	directXManager.CleanUpMyDX();
	windowManager.CleanUpMyWindow();
}


void Shell::RenderBegin() {
	HRESULT hr = directXManager.d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	if (FAILED(hr)) {
		cout << "Clear sprite brush failed" << endl;
	}

	//	Begin the scene
	directXManager.d3dDevice->BeginScene();
	directXManager.spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

}

void Shell::RenderEnd() {

	//	End sprite drawing
	directXManager.spriteBrush->End();

	//	End the scene
	directXManager.d3dDevice->EndScene();

	//	Present the back buffer to screen
	directXManager.d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Shell::CreateText(vector<Text*>* texts,LPCSTR text, LPD3DXFONT font, D3DXVECTOR2 position, int alignFrom, D3DXCOLOR color) {
	texts->push_back(new Text(text, font, position, alignFrom, color));
}

void Shell::ReleaseTexts(vector<Text*>* texts)
{
	for (int i = texts->size() - 1; i >= 0; i--) {
		texts->at(i)->Release();
		delete texts->at(i);
		texts->at(i) = NULL;
	}
	delete texts;
	texts = NULL;
}
