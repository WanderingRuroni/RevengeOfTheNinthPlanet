#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <xnamath.h>
#include <string>
#include <sstream>
#include "Game.h"
#include "GameSprite.h"

using namespace std;


class Game;


class FontManager
{
	public:
		FontManager( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget, float screenX, float screenY );
		virtual ~FontManager( );

		bool LoadContent( );
		void UnloadContent( );

		void Render( string label, float numbers );

	private:
		bool DrawString( char* message, float startX, float startY );

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

		float screenX_;
		float screenY_;
};

#endif

