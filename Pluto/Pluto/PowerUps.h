#ifndef _POWERUPS_H_
#define _POWERUPS_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <dinput.h>
#include <xnamath.h>
#include <vector>
#include <list>
#include "Game.h"
#include "GameSprite.h"
#include "SpriteSheet.h"

using namespace std;

class Game;
class GameSprite;
class SpriteSheet;

class PowerUps
{
	public:
		PowerUps( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget );
		virtual ~PowerUps(void);

		list<GameSprite>* GetSprites();

		void Initialize( );

		bool LoadContent( );
		void UnloadContent( );
		void Update( float dt);

		void Render( XMMATRIX* vpMatrix );

		void CreatePowerUp( XMFLOAT2 position, float rotation, XMFLOAT2 scale, string animation );

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