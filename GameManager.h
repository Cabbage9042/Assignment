#pragma once
#include <vector>
#include "Game.h"
#include "Shell.h"
#include "MainMenu.h"

#define gameFPS 60

//physics
#define Gravity 1.5
#define JumpForce -25

enum { arial25, franklin100 };

class GameManager{
public:
	static std::vector<Game*>* levelVector;


	//font
	static std::vector<LPD3DXFONT>* fonts;


	//gameover is lose or win
	static int playerHasWin;

	void InitializeGame();
	void UninitializeGame();
	void InitializeFonts();
	static void uninitializeLevelVector();
	void uninitializeFonts();

	static void CreateTexture(LPCSTR filePath, vector<Texture*>* textures,
		int textureWidth, int textureHeight, D3DXVECTOR2 position,
		int alignForm = leftAlign, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	static void ReleaseTextures(vector<Texture*>* textures);

	static void CreateText(vector<Text*>* texts, LPCSTR text, LPD3DXFONT font, D3DXVECTOR2 position,
		int alignFrom = leftAlign, D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	static void ReleaseTexts(vector<Text*>* text);
	static void CreateSprite(vector<Sprite*>* sprites, LPCSTR filePath,
		int textureWidth, int textureHeight,
		int spriteWidth, int spriteHeight,
		int spriteRow, int spriteColumn,
		int currentColumn, int currentRow,
		int maxFrame,
		D3DXVECTOR2 position,
		int alignForm = leftAlign, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	static void ReleaseSprite(vector<Sprite*>* sprites);
	static void CreateLine(vector<Line*>* vertices, Line* line);
	static void ReleaseLines(vector<Line*>* vertices);
	
	//render
	static void RenderBegin();
	static void RenderEnd();


	static void updateKeyStatus(bool keyDown, KeyStatus* key);
	static bool rectIsEqual(RECT a, RECT b);
	static int randomNumber(int from, int until); //included from , excluded until
};

