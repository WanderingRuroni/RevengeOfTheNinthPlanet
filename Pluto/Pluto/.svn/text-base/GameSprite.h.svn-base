#ifndef _GAME_SPRITE_H_
#define _GAME_SPRITE_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <xnamath.h>
#include <math.h>
#include <list>
#include <algorithm>
#include <string>

using namespace std;


class GameSprite
{
    public:
        GameSprite( );
        virtual ~GameSprite( );

        XMMATRIX GetWorldMatrix( );
		XMMATRIX GetWorldMatrix( float rotation );
		XMMATRIX GetWorldMatrix( XMFLOAT2 position );
		XMFLOAT2 GetPosition( );
		float GetRotation( );
		list<XMFLOAT3>* GetCollisionBox( );
		float GetWidth( );
		float GetHeight( );
		float GetVelocity( );
		int GetCurrentSprite( );
		string GetCurrentAnimation( );
		int GetHealth( );
		int GetAttack( );
		int GetNumBullets( );
		XMFLOAT2 GetFwd( );
		XMFLOAT2 GetOriginalPos( );
		bool GetIsActive( );
		float GetFrameTime( );
		float GetChangeAnimationTime( );
		float GetShootTime( );
		int GetNumberOfShots( );

		void SetCollisionBox( list<XMFLOAT3> box );
        void SetPosition( XMFLOAT2 position );
        void SetRotation( float rotation );
        void SetScale( XMFLOAT2 scale );
		void SetWidth( float width );
		void SetHeight( float height );
		void SetVelocity( float velocity );
		void SetCurrentSprite( int currentSprite );
		void SetCurrentAnimation( string currentAnimation );
		void SetHealth( int newHealth);
		void SetAttack( int newAttack);
		void SetNumBullets( int numB );
		void SetFwd( float fwdX, float fwdY );
		void SetOriginalPos( XMFLOAT2 pos );
		void SetIsActive( bool flag );
		void SetFrameTime( float time );
		void SetChangeAnimationTime( float time );
		void SetShootTime( float time );
		float dive;

		void SetNumberOfShots( int number );


    private:
		bool isActive_;

        XMFLOAT2 position_;
        float rotation_;
        XMFLOAT2 scale_;

		XMFLOAT2 fwd_;
		XMFLOAT2 origPos_;

		list<XMFLOAT3> collisionBox_;
		int currentSprite_;
		string currentAnimation_;
		float frameTime_;
		float changeAnimationTime_;
		float shootTime_;
		int numberOfShots_;

		float width_;
		float height_;
		float velocity_;

		int health_;
		int attack_;

		int numBullets_;

};

#endif