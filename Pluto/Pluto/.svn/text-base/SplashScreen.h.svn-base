#ifndef _SPLASH_SCREEN_H_
#define _SPLASH_SCREEN_H_

#define BUTTONDOWN(name, key) ( name.rgbButtons[key] & 0x80 )

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <xnamath.h>
#include <list>
#include <map>
#include <algorithm>
#include "Game.h"
#include "GameSprite.h"
#include "SpriteSheet.h"
#include "MouseCursor.h"
#include "FontManager.h"


class Game;
class GameSprite;
class SpriteSheet;
class MouseCursor;
class FontManager;


class SplashScreen
{
	public:
		SplashScreen( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget );
		virtual ~SplashScreen( );

		GameSprite* GetSprite( );
		int GetScreenState( );

		void SetScreenState( int state );

		void Initialize( );

		bool LoadContent( );
		void UnloadContent( );
	
		void Update( float dt, DIMOUSESTATE mouseState, long mousePosX, long mousePosY, long mouseWheel );
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

		int screenState_;

		SpriteSheet* spriteSheet_;
		float spriteWidth_;
		float spriteHeight_;

		map<string, XMFLOAT2> spriteMap_;
		int horizontalSprites_;
		int verticalSprites_;
		float sheetWidth_;
		float sheetHeight_;

		GameSprite sprite_;
		list<XMFLOAT3> collisionTemplate_;

		XMFLOAT4 play_;
		XMFLOAT4 instructions_;
		XMFLOAT4 credits_;
		XMFLOAT4 exit_;
		XMFLOAT4 replay_;
		XMFLOAT4 menu_;
		XMFLOAT4 back_;

		MouseCursor* mouseCursor_;
		FontManager* score_;
};

#endif