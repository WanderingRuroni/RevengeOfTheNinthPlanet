#ifndef _MOUSE_CURSOR_H_
#define _MOUSE_CURSOR_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <xnamath.h>
#include "Game.h"
#include "GameSprite.h"
#include "SpriteSheet.h"


class Game;
class GameSprite;
class SpriteSheet;


class MouseCursor
{
	public:
		MouseCursor( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget );
		virtual ~MouseCursor( );
		
		GameSprite* GetSprite( );

		void Initialize( );
		
		bool LoadContent( );
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

		GameSprite sprite_;
		list<XMFLOAT3> collisionTemplate_;
};

#endif