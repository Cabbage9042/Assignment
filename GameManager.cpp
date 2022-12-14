#include "GameManager.h"
std::vector<Game*>* GameManager::levelVector = new std::vector<Game*>;
std::vector<LPD3DXFONT>* GameManager::fonts;

int GameManager::playerHasWin = 0;


void GameManager::InitializeFonts() {
	LPD3DXFONT font = NULL;

	HRESULT hr = D3DXCreateFont(Shell::directXManager.d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	fonts->push_back(font);

	hr = D3DXCreateFont(Shell::directXManager.d3dDevice, 100, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Franklin Gothic Medium", &font);

	fonts->push_back(font);

	font = NULL;
}

void GameManager::InitializeGame() {

	Shell::windowManager.CreateMyWindow();
	Shell::directXManager.CreateMyDX(Shell::windowManager.g_hWnd);
	Shell::directXManager.CreateMyDInput(Shell::windowManager.g_hWnd);
	Shell::audioManager.InitializeAudio();



	fonts = new vector<LPD3DXFONT>;
	InitializeFonts();


	levelVector->push_back(new MainMenu());
	levelVector->back()->InitializeLevel();


}



void GameManager::uninitializeLevelVector() {
	for (int i = levelVector->size() - 1; i >= 0; i--) {
		levelVector->at(i)->UninitializeLevel();
		delete levelVector->at(i);
		levelVector->at(i) = NULL;
	}
	delete levelVector;
	levelVector = NULL;
}



void GameManager::uninitializeFonts() {
	delete fonts;
	fonts = NULL;
}

void GameManager::CreateTexture(LPCSTR filePath, vector<Texture*>* textures,
	int textureWidth, int textureHeight, D3DXVECTOR2 position,
	int horizontalAlign, int verticalAlign, D3DCOLOR color) {
	LPDIRECT3DTEXTURE9 texture = NULL;
	HRESULT hr = D3DXCreateTextureFromFile(Shell::directXManager.d3dDevice, filePath, &texture);
	if (FAILED(hr)) {
		cout << filePath << " failed" << endl;
	}

	textures->push_back(new Texture(texture, textureWidth, textureHeight, position, horizontalAlign,verticalAlign, color));
	texture = NULL;
}

void GameManager::ReleaseTextures(vector<Texture*>* textures) {
	for (int i = textures->size() - 1; i >= 0; i--) {
		textures->at(i)->Release();
		delete textures->at(i);
		textures->at(i) = NULL;
	}

	delete textures;
	textures = NULL;
}


void GameManager::CreateSprite(vector<Sprite*>* sprites, LPCSTR filePath,
	int textureWidth, int textureHeight,
	int spriteWidth, int spriteHeight,
	int spriteRow, int spriteColumn,
	int currentCol, int currentRow,
	int maxFrame,
	D3DXVECTOR2 position,
	int horizontalAlign, int verticalAlign, D3DCOLOR color) {
	LPDIRECT3DTEXTURE9 texture = NULL;
	HRESULT hr = D3DXCreateTextureFromFile(Shell::directXManager.d3dDevice, filePath, &texture);
	if (FAILED(hr)) {
		cout << filePath << " failed" << endl;
	}

	sprites->push_back(new Sprite(texture, textureWidth, textureHeight, spriteWidth, spriteHeight,
		spriteRow, spriteColumn, currentCol, currentRow, maxFrame, position, horizontalAlign,verticalAlign, color));
	texture = NULL;
}

void GameManager::ReleaseSprite(vector<Sprite*>* sprites) {
	for (int i = sprites->size() - 1; i >= 0; i--) {
		sprites->at(i)->Release();
		delete sprites->at(i);
		sprites->at(i) = NULL;
	}

	delete sprites;
	sprites = NULL;
}

void GameManager::CreateLine(vector<Line*>* vertices, Line* line) {
	vertices->push_back(line);
}

void GameManager::ReleaseLines(vector<Line*>* vertices) {
	for (int i = vertices->size() - 1; i >= 0; i--) {
		vertices->back()->Release();
		delete vertices->back();
		vertices->back() = NULL;
		vertices->pop_back();
		vertices->shrink_to_fit();
	}

	delete vertices;
	vertices = NULL;
}


void GameManager::ReleaseAudios(vector<Audio*>* audios)
{
	for (int i = audios->size() - 1; i >= 0; i--) {
		audios->back()->Release();
		delete audios->back();
		audios->back() = NULL;
		audios->pop_back();
		audios->shrink_to_fit();
	}

	delete audios;
	audios = NULL;
}

void GameManager::UninitializeGame() {

	uninitializeLevelVector();
	uninitializeFonts();
	Shell::audioManager.UninitializeAudio();
	Shell::directXManager.CleanUpMyDInput();
	Shell::directXManager.CleanUpMyDX();
	Shell::windowManager.CleanUpMyWindow();
}


void GameManager::RenderBegin() {
	HRESULT hr = Shell::directXManager.d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	if (FAILED(hr)) {
		cout << "Clear sprite brush failed" << endl;
	}

	//	Begin the scene
	Shell::directXManager.d3dDevice->BeginScene();
	Shell::directXManager.spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

}

void GameManager::RenderEnd() {

	//	End sprite drawing
	Shell::directXManager.spriteBrush->End();

	//	End the scene
	Shell::directXManager.d3dDevice->EndScene();

	//	Present the back buffer to screen
	Shell::directXManager.d3dDevice->Present(NULL, NULL, NULL, NULL);
}



bool GameManager::rectIsEqual(RECT a, RECT b)
{
	return (
		a.left == b.left &&
		a.right == b.right &&
		a.top == b.top &&
		a.bottom == b.bottom
		);
}

int GameManager::randomNumber(int from, int until)
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	srand(time.QuadPart);
	return (rand() % (until - from)) + from;
}

void GameManager::CreateText(vector<Text*>* texts, LPCSTR text, LPD3DXFONT font, D3DXVECTOR2 position, int horizontalAlign, int verticalAlign, D3DXCOLOR color) {
	texts->push_back(new Text(text, font, position, horizontalAlign,verticalAlign, color));
}

void GameManager::ReleaseTexts(vector<Text*>* texts) {
	for (int i = texts->size() - 1; i >= 0; i--) {
		texts->at(i)->Release();
		delete texts->at(i);
		texts->at(i) = NULL;
	}
	delete texts;
	texts = NULL;
}