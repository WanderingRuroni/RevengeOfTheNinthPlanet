#ifndef _NEPTUNE_H_
#define _NEPTUNE_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3DCompiler.h>
#include <xnamath.h>
#include "Game.h"
#include "GameSprite.h"
#include "Bullets.h"
#include "Seahorses.h"

class Game;
class GameSprite;
class Bullets;
class Seahorses;

class Neptune
{
public:
	Neptune(Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget);
	virtual ~Neptune(void);

	bool GetCanBeHit();

	GameSprite* GetSprite();
	Bullets* GetBullets();
	Seahorses* GetSeahorses();

	void Initialize( );

	bool LoadContent();
	void UnloadContent();

	void Update(float dt);
	void Render(XMMATRIX* vpMatrix);

	void CreateNeptune( XMFLOAT2 position, float rotation = 0.0f, XMFLOAT2 scale = XMFLOAT2( 1.0f, 1.0f ) );

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
	Bullets* bullets_;
	Seahorses* seahorses_;
	bool canBeHit;
	int sweepStep;
	int pattern;
	bool sweep;
	bool shoot;
	bool spawn;
	bool minionsAlive;
	float cooldown_;
	float cooldownTime_;
};

#endif