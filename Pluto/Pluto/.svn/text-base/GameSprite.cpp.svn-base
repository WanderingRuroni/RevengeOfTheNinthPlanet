#include "GameSprite.h"


GameSprite::GameSprite( )
{
	// initialize position and rotation
	position_.x = position_.y = rotation_ = 0.0f;

	// initialize scale
    scale_.x = scale_.y = 1.0f;

	fwd_.x = 0.0f;
	fwd_.y = 1.0f;

	shootTime_ = 0.0f;
	numberOfShots_ = 0;
	isActive_ = false;
}


GameSprite::~GameSprite( )
{
}


// GETTERS


XMMATRIX GameSprite::GetWorldMatrix( )
{
    XMMATRIX translation = XMMatrixTranslation( position_.x, position_.y, 0.0f );
    XMMATRIX rotationZ = XMMatrixRotationZ( rotation_ );
    XMMATRIX scale = XMMatrixScaling( scale_.x, scale_.y, 1.0f );

    return ( XMMatrixTranslation( 0.0f, 0.0f, 0.0f ) * XMMatrixRotationZ( 0.0f ) * scale ) * ( XMMatrixTranslation( 0.0f, 0.0f, 0.0f ) * rotationZ * XMMatrixScaling( 1.0f, 1.0f, 1.0f ) ) * ( translation * XMMatrixRotationZ( 0.0f ) * XMMatrixScaling( 1.0f, 1.0f, 1.0f ) );
}


XMFLOAT2 GameSprite::GetPosition()
{
	return position_;
}


float GameSprite::GetRotation( )
{
	return rotation_;
}


list<XMFLOAT3>* GameSprite::GetCollisionBox()
{
	return &collisionBox_;
}


float GameSprite::GetWidth( )
{
	return width_ * scale_.x;
}


float GameSprite::GetHeight( )
{
	return height_ * scale_.y;
}


float GameSprite::GetVelocity( )
{
	return velocity_;
}


int GameSprite::GetCurrentSprite( )
{
	return currentSprite_;
}


XMFLOAT2 GameSprite::GetFwd()
{
	return fwd_;
}

XMFLOAT2 GameSprite::GetOriginalPos()
{
	return origPos_;
}


int GameSprite::GetHealth()
{
	return health_;
}


int GameSprite::GetAttack()
{
	return attack_;
}

int GameSprite::GetNumBullets()
{
	return numBullets_;
}


string GameSprite::GetCurrentAnimation( )
{
	return currentAnimation_;
}


bool GameSprite::GetIsActive( )
{
	return isActive_;
}


// used for animations
float GameSprite::GetFrameTime( )
{
	return frameTime_;
}


// gets time since the animation of this game sprite was changed
float GameSprite::GetChangeAnimationTime( )
{
	return changeAnimationTime_;
}


// used for shooting bullets
float GameSprite::GetShootTime( )
{
	return shootTime_;
}


int GameSprite::GetNumberOfShots( )
{
	return numberOfShots_;
}


// SETTERS


void GameSprite::SetCollisionBox(list<XMFLOAT3> box)
{
	collisionBox_ = box;
}


void GameSprite::SetPosition(XMFLOAT2 position)
{
	// update the collision box
	for ( list<XMFLOAT3>::iterator c = collisionBox_.begin( ); c != collisionBox_.end( ); c++ )
	{
		// component is equal to the old component added to the change of position
		c->x += ( position.x - position_.x );
		c->y += ( position.y - position_.y );
	}

    position_ = position;
}


void GameSprite::SetRotation( float rotation )
{
	// update the collision box
	for ( list<XMFLOAT3>::iterator c = collisionBox_.begin( ); c != collisionBox_.end( ); c++ )
	{
		// get the old component
		float x = c->x;
		float y = c->y;

		// calculate new component using the old component and the change of rotation (in radians) in the rotation formula
		c->x = ( ( ( x - position_.x ) * cos( rotation - rotation_ ) ) - ( ( y - position_.y ) * sin( rotation - rotation_ ) ) ) + position_.x;
		c->y = ( ( ( x - position_.x ) * sin( rotation - rotation_ ) ) + ( ( y - position_.y ) * cos( rotation - rotation_ ) ) ) + position_.y;
	}

    rotation_ = rotation;
}


void GameSprite::SetScale( XMFLOAT2 scale )
{
	// update the collision box
	for ( list<XMFLOAT3>::iterator c = collisionBox_.begin( ); c != collisionBox_.end( ); c++ )
	{
		// get component of point at the zeroed position
		// add it to that component times the change in scale 
		// add the position back on
		c->x = ( c->x - position_.x ) + ( ( c->x - position_.x ) * ( scale.x - scale_.x ) ) + position_.x;
		c->y = ( c->y - position_.y ) + ( ( c->y - position_.y ) * ( scale.y - scale_.y ) ) + position_.y;
	}

    scale_ = scale;
}


void GameSprite::SetWidth( float width )
{
	width_ = width;
}


void GameSprite::SetHeight( float height )
{
	height_ = height;
}


void GameSprite::SetVelocity( float velocity )
{
	velocity_ = velocity;
}


void GameSprite::SetCurrentSprite( int currentSprite )
{
	currentSprite_ = currentSprite;
	frameTime_ = 0.0f;
}


void GameSprite::SetFwd(float fwdX, float fwdY)
{
	fwd_.x = fwdX;
	fwd_.y = fwdY;
}

void GameSprite::SetOriginalPos( XMFLOAT2 pos )
{
	origPos_ = pos;
}


void GameSprite::SetHealth(int health)
{
	health_ = health;
}


void GameSprite::SetAttack(int attack)
{
	attack_ = attack;
}

void GameSprite::SetNumBullets( int numB )
{
	numBullets_ = numB;
}


void GameSprite::SetCurrentAnimation( string currentAnimation )
{
	currentAnimation_ = currentAnimation;
	changeAnimationTime_ = 0.0f;
	SetCurrentSprite( 0 );
}


void GameSprite::SetIsActive( bool flag )
{
	isActive_ = flag;
}


void GameSprite::SetFrameTime( float time )
{
	frameTime_ = time;
}


void GameSprite::SetChangeAnimationTime( float time)
{
	changeAnimationTime_ = time;
}


void GameSprite::SetShootTime( float time )
{
	shootTime_ = time;
}


// used for shooting a specified number of bullets then doing a behavior
void GameSprite::SetNumberOfShots( int number )
{
	numberOfShots_ = number;
}