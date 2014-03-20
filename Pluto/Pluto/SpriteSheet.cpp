#include "SpriteSheet.h"


// position and texture coordinates of the vertex
struct VertexPos
{
    XMFLOAT3 pos;
    XMFLOAT2 tex0;
};


SpriteSheet::SpriteSheet( Game* game, int horizontalSprites, int verticalSprites, float sheetWidth, float sheetHeight )
{
	game_ = game;
	horizontalSprites_ = horizontalSprites;
	verticalSprites_ = verticalSprites;
	sheetWidth_ = sheetWidth;
	sheetHeight_ = sheetHeight;
}


SpriteSheet::~SpriteSheet( )
{
}


// GETTERS


map<string, vector<XMFLOAT2>>* SpriteSheet::GetAnimationMap( )
{
	return &animationMap_;
}


map<string, float>* SpriteSheet::GetDurationMap( )
{
	return &durationMap_;
}


int SpriteSheet::GetHorizontalSprites( )
{
	return horizontalSprites_;
}


int SpriteSheet::GetVerticalSprites( )
{
	return verticalSprites_;
}


float SpriteSheet::GetSheetWidth( )
{
	return sheetWidth_;
}


float SpriteSheet::GetSheetHeight( )
{
	return sheetHeight_;
}

bool SpriteSheet::GetActivate()
{
	return activate_;
}


// ADDITIONAL FUNCTIONS


void SpriteSheet::AddAnimationToMap( string name, vector<XMFLOAT2> animation, float frameDuration )
{
	animationMap_[name] = animation;
	durationMap_[name] = frameDuration;
}


// creates sprites
GameSprite SpriteSheet::CreateSprite( list<XMFLOAT3> collisionTemplate, float width, float height, float velocity, XMFLOAT2 position, int health, int attack, float rotation, XMFLOAT2 scale )
{
	GameSprite sprite;
	sprite.SetCollisionBox( collisionTemplate );
	sprite.SetWidth( width );
	sprite.SetHeight( height );
	sprite.SetVelocity( velocity );
	sprite.SetPosition( position );
	sprite.SetHealth( health );
	sprite.SetAttack( attack );
	sprite.SetRotation( rotation );
	sprite.SetScale( scale );

	return sprite;
}


void SpriteSheet::RenderSprite( GameSprite* sprite, ID3D11DeviceContext* d3dContext, ID3D11Buffer* vertexBuffer, ID3D11Buffer* mvpCB, XMMATRIX* vpMatrix )
{
	XMMATRIX world = sprite->GetWorldMatrix( );
	XMMATRIX mvp = XMMatrixMultiply( world, *vpMatrix );
	mvp = XMMatrixTranspose( mvp );

	d3dContext->UpdateSubresource( mvpCB, 0, 0, &mvp, 0, 0 );
	d3dContext->VSSetConstantBuffers( 0, 1, &mvpCB );

	// draw the current sprite
	map<string, vector<XMFLOAT2>>::iterator a = animationMap_.find( sprite->GetCurrentAnimation( ) );
	map<string, float>::iterator f = durationMap_.find( sprite->GetCurrentAnimation( ) );

	// don't draw if the animation is not in the map
	if( a != animationMap_.end( ) )
	{
		unsigned int currentSprite = sprite->GetCurrentSprite( );

		if ( f != durationMap_.end( ) && f->second != -1)
		{
			float frameTime = sprite->GetFrameTime( );

			frameTime += game_->GetDeltaTime( );
			if( frameTime >= f->second )
			{
				currentSprite++;

				if( currentSprite >= a->second.size( ) )
				{
					currentSprite = 0;
				}

				// set the current sprite to the next one in the animation
				sprite->SetCurrentSprite( currentSprite );

				frameTime = 0.0f;
			}

			sprite->SetFrameTime( frameTime );

			// add delta time to the time since this sprite has been on this animation
			sprite->SetChangeAnimationTime( sprite->GetChangeAnimationTime( ) + game_->GetDeltaTime( ) );
		}

		// draw the first sprite in the animtation (background animations only have one sprite per animation)
		activate_ = DrawSprite( a->second.at( currentSprite ).x, a->second.at( currentSprite ).y, sprite->GetWidth( ), sprite->GetHeight( ), sheetWidth_, sheetHeight_, d3dContext, vertexBuffer );
	}
}


// sets up the vertex positions and texture coordinates and draws the sprite
bool SpriteSheet::DrawSprite( float texX, float texY, float texWidth, float texHeight, float sheetWidth, float sheetHeight, ID3D11DeviceContext* d3dContext, ID3D11Buffer* vertexBuffer )
{
    // texture's width on screen
	float widthOnScreen = texWidth / game_->GetScreenWidth( );

    // texture's height on screen
	float heightOnScreen = texHeight / game_->GetScreenHeight( );
    
    // texture's texel width
    float texelWidth = texWidth / sheetWidth;

	// texture's texel height
	float texelHeight = texHeight / sheetHeight;

    D3D11_MAPPED_SUBRESOURCE mapResource;
    HRESULT d3dResult = d3dContext->Map( vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource );

    if( FAILED( d3dResult ) )
    {
        DXTRACE_MSG( "Failed to map resource!" );
        return false;
    }

    // point to our vertex buffer's internal data
    VertexPos *spritePtr = ( VertexPos* )mapResource.pData;

	// set the vertex positions
	spritePtr[0].pos = XMFLOAT3( texWidth / 2, texHeight / 2, 1.0f );
    spritePtr[1].pos = XMFLOAT3( texWidth / 2, -texHeight / 2, 1.0f );
    spritePtr[2].pos = XMFLOAT3( -texWidth / 2, texHeight / 2, 1.0f );
    spritePtr[3].pos = XMFLOAT3( -texWidth / 2, -texHeight / 2, 1.0f );

	// align the texture
    spritePtr[0].tex0 = XMFLOAT2( texelWidth * ( texX + 1 ), texelHeight * texY );
    spritePtr[1].tex0 = XMFLOAT2( texelWidth * ( texX + 1 ), texelHeight * ( texY + 1 ) );
    spritePtr[2].tex0 = XMFLOAT2( texelWidth * texX, texelHeight * texY );
    spritePtr[3].tex0 = XMFLOAT2( texelWidth * texX, texelHeight * ( texY + 1 ) );

	// unmap the buffer and draw all the vertices
    d3dContext->Unmap( vertexBuffer, 0 );
    d3dContext->Draw( 4, 0 );

	activate_ = false;
	
	return true;
}