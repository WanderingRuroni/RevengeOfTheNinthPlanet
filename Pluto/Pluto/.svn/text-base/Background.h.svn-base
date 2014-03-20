#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <xnamath.h>
#include <vector>
#include <map>
#include <algorithm>
#include "Game.h"
#include "GameSprite.h"
#include "SpriteSheet.h"


class Game;
class GameSprite;
class SpriteSheet;


class Background
{
	public:
		Background( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget );
		virtual ~Background( );

		GameSprite* GetSpriteCloseA( );
		GameSprite* GetSpriteCloseB( );
		GameSprite* GetSpriteMiddleA( );
		GameSprite* GetSpriteMiddleB( );
		GameSprite* GetSpriteFarA( );
		GameSprite* GetSpriteFarB( );

		void Initialize( );

		bool LoadContent( );
		void UnloadContent( );
	
		void Update( float dt );
		void Render( XMMATRIX* vpMatrix );

	private:
		void UpdateBackground( GameSprite* sprite, float dt );

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

		GameSprite spriteCloseA_;
		GameSprite spriteCloseB_;
		GameSprite spriteMiddleA_;
		GameSprite spriteMiddleB_;
		GameSprite spriteFarA_;
		GameSprite spriteFarB_;
		list<XMFLOAT3> collisionTemplate_;
};

#endif