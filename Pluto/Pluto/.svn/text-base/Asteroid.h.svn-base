#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <xnamath.h>
#include <list>
#include <algorithm>
#include "Game.h"
#include "GameSprite.h"
#include "SpriteSheet.h"

class Game;
class GameSprite;
class SpriteSheet;

class Asteroid
{
	public:
		Asteroid( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget );
		virtual ~Asteroid(void);

		list<GameSprite>* GetSprites();

		void Initialize( );

		bool LoadContent( );
		void UnloadContent( );
	
		void Update( float dt );
		void Render( XMMATRIX* vpMatrix );

		void CreateAsteroid( XMFLOAT2 position, float rotation = 0.0f, XMFLOAT2 scale = XMFLOAT2( 1.0f, 1.0f ) );

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

		list<GameSprite> sprites_;
		list<XMFLOAT3> collisionTemplate_;
};

#endif
