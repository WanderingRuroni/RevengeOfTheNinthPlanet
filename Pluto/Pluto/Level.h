#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <xnamath.h>
#include <list>
#include <algorithm>
#include <time.h>
#include "Game.h"
#include "GameSprite.h"
#include "Asteroid.h"
#include "Comet.h"
#include "Gangstar.h"
#include "Neptune.h"
#include "PowerUps.h"
#include "Satellites.h"
#include "Seahorses.h"


class Game;
class GameSprite;
class Asteroid;
class Comet;
class Gangstar;
class Neptune;
class PowerUps;
class Satellites;
class Seahorses;


class Level
{
	public:
		Level( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget, int levelID, float scrollSpeed );
		virtual ~Level( );

		float GetScrollSpeed( );

		int GetPowerUpDrop();

		Neptune* GetNeptune();

		void Initialize( );

		bool LoadContent( );
		void SetupContent( );
		void UnloadContent( );
	
		void Update( float dt );
		void Render( XMMATRIX* vpMatrix );

		
		void CheckEnemyCollision( GameSprite* sprite, list<GameSprite>* sprites );
		void CheckBossCollision( GameSprite* sprite, GameSprite* bossSprite );
		void CheckPowerUpCollision( GameSprite* sprite, list<GameSprite>* sprites );
		void CheckSpriteBulletCollision( GameSprite* sprite, list<GameSprite>* activeSprites, list<GameSprite>* inactiveSprites );
		void CheckSpritesBulletCollision( list<GameSprite>* sprites, list<GameSprite>* activeSprites, list<GameSprite>* inactiveSprites );
		bool CollisionTest( list<XMFLOAT3> box1, list<XMFLOAT3> box2 );
		bool DistanceCheck( GameSprite obj1, GameSprite obj2 );
	
	private:
		Game* game_;

		ID3D11Device* d3dDevice_;
		ID3D11DeviceContext* d3dContext_;
		IDXGISwapChain* swapChain_;
		ID3D11RenderTargetView* backBufferTarget_;

		int levelID_;
		float scrollSpeed_;
		list<GameSprite*> scrollingSprites_;

		// enemies
		Asteroid* asteroids_;
		Comet* comets_;
		Gangstar* gangstars_;
		Seahorses* seahorses_;
		
		// bosses
		Neptune* neptune_;

		// powerups
		PowerUps* powerUps_;
		Satellites* satellites_;

		int powerUpDrop;
		float deathCooldown_;
};

#endif