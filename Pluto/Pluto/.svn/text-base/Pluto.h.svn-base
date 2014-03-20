#ifndef _PLUTO_H_
#define _PLUTO_H_

#define KEYDOWN(name, key) ( name[key] & 0x80 )

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <dinput.h>
#include <xnamath.h>
#include <vector>
#include <list>
#include <algorithm>
#include "Game.h"
#include "GameSprite.h"
#include "SpriteSheet.h"
#include "Bullets.h"


class Game;
class GameSprite;
class SpriteSheet;
class Bullets;

class Pluto
{
	public:
		Pluto( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget );
		virtual ~Pluto( );

		GameSprite* GetSprite( );
		Bullets* GetBulletsRegular( );
		Bullets* Pluto::GetBulletsRapid( );
		Bullets* Pluto::GetBulletsBeam( );
		Bullets* Pluto::GetBulletsShotgun( );
		Bullets* Pluto::GetBulletsHuge( );
		int GetWeapon( );
		float GetScore( );

		void SetWeapon( int weapon );
		void SetScore( float score );

		void Initialize( );

		bool LoadContent( );
		void UnloadContent( );
	
		void Update( float dt, char* keyboardKeys, char* prevKeyboardKeys );
		void Render( XMMATRIX* vpMatrix );

		void UpdateBullets( float dt, list<GameSprite>* activeSprites, list<GameSprite>* inactiveSprites );

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
		Bullets* bulletsRegular_;
		Bullets* bulletsRapid_;
		Bullets* bulletsBeam_;
		Bullets* bulletsShotgun_;
		Bullets* bulletsHuge_;

		int weapon_;
		float score_;
};

#endif