#ifndef _BULLETS_H_
#define _BULLETS_H_

//#define KEYDOWN(name,key) ( name[key] & 0x80 )

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <dinput.h>
#include <xnamath.h>
#include <list>
#include <map>
#include <algorithm>
#include "Game.h"
#include "GameSprite.h"
#include "SpriteSheet.h"

using namespace std;


class Game;
class GameSprite;
class SpriteSheet;


class Bullets
{
	public:
		Bullets( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget );
		virtual ~Bullets( );

		list<GameSprite>* GetActiveSprites( );
		list<GameSprite>* GetInactiveSprites( );

		void Initialize( string bulletType, int amount, float velocity, int attack );

		bool LoadContent( char* filePath, string bulletType );
		void UnloadContent( );

		void Render( XMMATRIX* vpMatrix );

	private:
		Game* game_;

		ID3D11Device* d3dDevice_;
		ID3D11DeviceContext* d3dContext_;
		IDXGISwapChain* swapChain_;
		ID3D11RenderTargetView* backBufferTarget_;

		ID3D11VertexShader* solidColorVS_;
		ID3D11PixelShader* solidColorPS_;
		ID3D11InputLayout* inputLayout_;
		ID3D11Buffer* vertexBuffer_;
		ID3D11ShaderResourceView* colorMap_;
		ID3D11SamplerState* colorMapSampler_;

		ID3D11Buffer* mvpCB_;

		SpriteSheet* spriteSheet_;
		float spriteWidth_;
		float spriteHeight_;

		list<GameSprite> activeSprites_;
		list<GameSprite> inactiveSprites_;

		list<GameSprite[3]> activeSpritesShotgun_;
		list<GameSprite[3]> inactiveSpritesShotgun_;

		// for keeping track of various different types of bullets used in the game
		map<string, list<XMFLOAT3>> collisionTemplates_;
};

#endif