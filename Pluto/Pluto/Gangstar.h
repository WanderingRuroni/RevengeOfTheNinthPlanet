#ifndef _GANGSTAR_H_
#define _GANGSTAR_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3DCompiler.h>
#include <xnamath.h>
#include "Game.h"
#include "GameSprite.h"
#include "SpriteSheet.h"
#include "Bullets.h"

class Game;
class GameSprite;
class SpriteSheet;
class Bullets;

class Gangstar
{
public:
	Gangstar(Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget);
	virtual ~Gangstar(void);

	list<GameSprite>* GetSprites();
	Bullets* GetBullets();

	void Initialize( );

	bool LoadContent();
	void UnloadContent();

	void Update(float dt);
	void Render(XMMATRIX* vpMatrix);

	void CreateGangstar( XMFLOAT2 position, float rotation = 0.0f, XMFLOAT2 scale = XMFLOAT2( 1.0f, 1.0f ) );

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

	map<GameSprite*, float> bulletsMap_;
	Bullets* bullets_;

	// attributes used during gangstars' behaviors
	float shootCooldown_;
	float dive;
};

#endif
