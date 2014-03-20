#ifndef _HUD_H_
#define _HUD_H_

#define KEYDOWN(name, key) ( name[key] & 0x80 )

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <dinput.h>
#include <xnamath.h>
#include <list>
#include <algorithm>
#include "Game.h"
#include "GameSprite.h"
#include "SpriteSheet.h"
#include "FontManager.h"


class Game;
class GameSprite;
class SpriteSheet;
class FontManager;


class Hud
{
	public:
		Hud( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget );
		virtual ~Hud( );

		GameSprite* GetSprite( );
		int GetHealthState( );

		void SetHealthState( int state );

		void Initialize( );
		
		bool LoadContent( );
		void UnloadContent( );
	
		void Update( float dt, int lives, char* keyboardKeys, char* prevKeyboardKeys );
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

		FontManager* score_;
		FontManager* fps_;

		int healthState_;
		float changeTime_;
		bool showFPS_;

		SpriteSheet* spriteSheet_;
		float spriteWidth_;
		float spriteHeight_;
		
		GameSprite sprite_;
		list<XMFLOAT3> collisionTemplate_;
};

#endif