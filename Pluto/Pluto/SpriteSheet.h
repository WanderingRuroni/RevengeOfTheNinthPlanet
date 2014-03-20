#ifndef _SPRITE_SHEET_H_
#define _SPRITE_SHEET_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <xnamath.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "Game.h"
#include "GameSprite.h"

using namespace std;


class Game;
class GameSprite;


class SpriteSheet
{
    public:
		SpriteSheet( Game* game, int horizontalSprites, int verticalSprites, float sheetWidth, float sheetHeight );
        virtual ~SpriteSheet( );

		map<string, vector<XMFLOAT2>>* GetAnimationMap( );
		map<string, float>* GetDurationMap( );
		int GetHorizontalSprites( );
		int GetVerticalSprites( );
		float GetSheetWidth( );
		float GetSheetHeight( );
		bool GetActivate();

		void AddAnimationToMap( string name, vector<XMFLOAT2> animation, float frameDuration );
		GameSprite CreateSprite( list<XMFLOAT3> collisionTemplate, float width, float height, float velocity = 0.0f, XMFLOAT2 position = XMFLOAT2( 0.0f, 0.0f ), int health = 3, int attack = 0, float rotation = 0.0f, XMFLOAT2 scale = XMFLOAT2( 1.0f, 1.0f ) );
		void RenderSprite( GameSprite* sprite, ID3D11DeviceContext* d3dContext, ID3D11Buffer* vertexBuffer, ID3D11Buffer* mvpCB, XMMATRIX* vpMatrix );
		bool DrawSprite( float texX, float texY, float texWidth, float texHeight, float sheetWidth, float sheetHeight, ID3D11DeviceContext* d3dContext, ID3D11Buffer* vertexBuffer );

    private:
		Game* game_;

        map<string, vector<XMFLOAT2>> animationMap_;
		map<string, float> durationMap_;

        int horizontalSprites_;
        int verticalSprites_;
		float sheetWidth_;
		float sheetHeight_;

		bool activate_;
};

#endif