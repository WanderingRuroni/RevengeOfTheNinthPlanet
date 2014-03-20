#include "Neptune.h"

// position and texture coordinates of the vertex
struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};


Neptune::Neptune( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget ) : solidColorVS_( 0 ), solidColorPS_( 0 ), inputLayout_( 0 ),
																																											vertexBuffer_( 0 ), colorMap_( 0 ), colorMapSampler_( 0 ),
																																											mvpCB_( 0 )
{
	game_ = game;

	d3dDevice_ = d3dDevice;
	d3dContext_ = d3dContext;
	swapChain_ = swapChain;
	backBufferTarget_ = backBufferTarget;

	bullets_ = new Bullets( game, d3dDevice, d3dContext, swapChain, backBufferTarget );
}


Neptune::~Neptune(void)
{
}


// GETTERS

bool Neptune::GetCanBeHit()
{
	return canBeHit;
}

GameSprite* Neptune::GetSprite()
{
	return &sprite_;
}


Bullets* Neptune::GetBullets()
{
	return bullets_;
}

Seahorses* Neptune::GetSeahorses()
{
	return seahorses_;
}


// INTIALIZER


void Neptune::Initialize( )
{
	canBeHit = false;
	sweepStep = 0;
	srand( time( NULL ) );
	cooldown_ = 1.5f;
	cooldownTime_ = 0.0f;
	sweep = false;
	shoot = false;
	spawn = false;

	bullets_->Initialize( "Neptune", 5, 300.0f, 1 );
	seahorses_->Initialize( );
}


// LOAD CONTENT


bool Neptune::LoadContent( )
{
	ID3DBlob* vsBuffer = 0;

	// compile the vertex shader from fx file
    bool compileResult = game_->CompileD3DShader( "TextureMap_Sprites.fx", "VS_Main", "vs_4_0", &vsBuffer );

    if( compileResult == false )
    {
        DXTRACE_MSG( "Error compiling the vertex shader!" );
        return false;
    }

    HRESULT d3dResult;

	// create the vertex shader
    d3dResult = d3dDevice_->CreateVertexShader( vsBuffer->GetBufferPointer( ),
        vsBuffer->GetBufferSize( ), 0, &solidColorVS_ );

    if( FAILED( d3dResult ) )
    {
        DXTRACE_MSG( "Error creating the vertex shader!" );

        if( vsBuffer )
            vsBuffer->Release( );

        return false;
    }

    D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    unsigned int totalLayoutElements = ARRAYSIZE( solidColorLayout );

	// create the input layout
    d3dResult = d3dDevice_->CreateInputLayout( solidColorLayout, totalLayoutElements,
        vsBuffer->GetBufferPointer( ), vsBuffer->GetBufferSize( ), &inputLayout_ );

    vsBuffer->Release( );

    if( FAILED( d3dResult ) )
    {
        DXTRACE_MSG( "Error creating the input layout!" );
        return false;
    }

    ID3DBlob* psBuffer = 0;

	// compile the pixel shader from fx file
    compileResult = game_->CompileD3DShader( "TextureMap_Sprites.fx", "PS_Main", "ps_4_0", &psBuffer );

    if( compileResult == false )
    {
        DXTRACE_MSG( "Error compiling pixel shader!" );
        return false;
    }

	// create the pixel shader
    d3dResult = d3dDevice_->CreatePixelShader( psBuffer->GetBufferPointer( ),
        psBuffer->GetBufferSize( ), 0, &solidColorPS_ );

    psBuffer->Release( );

    if( FAILED( d3dResult ) )
    {
        DXTRACE_MSG( "Error creating pixel shader!" );
        return false;
    }


	// load the texture image
    d3dResult = D3DX11CreateShaderResourceViewFromFile( d3dDevice_,
        "Assets/Images/Neptunesheet.png", 0, 0, &colorMap_, 0 );

    if( FAILED( d3dResult ) )
    {
        DXTRACE_MSG( "Failed to load the texture image!" );
        return false;
    }

	D3D11_SAMPLER_DESC colorMapDesc;
    ZeroMemory( &colorMapDesc, sizeof( colorMapDesc ) );
    colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// create the sampler state
    d3dResult = d3dDevice_->CreateSamplerState( &colorMapDesc, &colorMapSampler_ );

    if( FAILED( d3dResult ) )
    {
        DXTRACE_MSG( "Failed to create color map sampler state!" );
        return false;
    }

    ID3D11Resource* colorTex;
    colorMap_->GetResource( &colorTex );

    D3D11_TEXTURE2D_DESC colorTexDesc;
    ( ( ID3D11Texture2D* )colorTex )->GetDesc( &colorTexDesc );
    colorTex->Release( );

    float halfWidth = ( float )colorTexDesc.Width / 2.0f;
    float halfHeight = ( float )colorTexDesc.Height / 2.0f;

	 D3D11_BUFFER_DESC vertexDesc;
    ZeroMemory( &vertexDesc, sizeof( vertexDesc ) );
    vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexDesc.ByteWidth = sizeof( VertexPos ) * 4;

	// create the vertex buffer
    d3dResult = d3dDevice_->CreateBuffer( &vertexDesc, 0, &vertexBuffer_ );

    if( FAILED( d3dResult ) )
    {
        DXTRACE_MSG( "Failed to create vertex buffer!" );
        return false;
    }


    D3D11_BUFFER_DESC constDesc;
	ZeroMemory( &constDesc, sizeof( constDesc ) );
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof( XMMATRIX );
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	// create the constant buffer
	d3dResult = d3dDevice_->CreateBuffer( &constDesc, 0, &mvpCB_ );

	if( FAILED( d3dResult ) )
    {
        return false;
    }


	// load the sprite sheet with sprite names and coordinates
	spriteSheet_ = new SpriteSheet( game_, 3, 2, ( float )colorTexDesc.Width, ( float )colorTexDesc.Height );
	spriteWidth_ = spriteSheet_->GetSheetWidth( ) / spriteSheet_->GetHorizontalSprites( );
	spriteHeight_ = spriteSheet_->GetSheetHeight( ) / spriteSheet_->GetVerticalSprites( );

	// add coordinates to animations
	vector<XMFLOAT2> neptune1;
	neptune1.push_back( XMFLOAT2( 0.0f, 0.0f ) );
	neptune1.push_back( XMFLOAT2( 1.0f, 0.0f ) );
	vector<XMFLOAT2> neptune2;
	neptune2.push_back( XMFLOAT2( 2.0f, 0.0f ) );
	neptune2.push_back( XMFLOAT2( 0.0f, 1.0f ) );
	vector<XMFLOAT2> neptune3;
	neptune3.push_back( XMFLOAT2( 1.0f, 1.0f ) );
	neptune3.push_back( XMFLOAT2( 2.0f, 1.0f ) );

	spriteSheet_->AddAnimationToMap( "fullHealth" , neptune1, 1.0f );
	spriteSheet_->AddAnimationToMap( "halfHealth" , neptune2, 1.0f );
	spriteSheet_->AddAnimationToMap( "lowHealth" , neptune3, 1.0f );

	// create template of collision box
	float spriteHalfWidth = spriteWidth_ / 2.0f;
	float spriteHalfHeight = spriteHeight_ / 2.0f;

	XMFLOAT3 pts[] =
	{
		XMFLOAT3( 0.0f, spriteHalfHeight, 1.0f ),
		XMFLOAT3( spriteHalfWidth, 0.0f, 1.0f ),
		XMFLOAT3( ( spriteHalfWidth / 2.0f ), -( spriteHalfHeight / 2.0f ), 1.0f ),
		XMFLOAT3(0.0f, -(spriteHalfHeight * .85), 1.0f),
		XMFLOAT3( -( spriteHalfWidth / 2.0f ), -( spriteHalfHeight / 2.0f ), 1.0f ),
		XMFLOAT3( -spriteHalfWidth, 0.0f, 1.0f ),
		XMFLOAT3( 0.0f, spriteHalfHeight, 1.0f )
	};

	for( int i = 0; i < 7; i++ )
	{
		collisionTemplate_.push_back( pts[i] );
	}

	// load bullets
	bullets_->LoadContent( "Assets/Images/Trident.png", "Neptune" );

	seahorses_ = new Seahorses( game_,  d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );
	
	if( !seahorses_->LoadContent( ) )
		return false;
	
	Initialize( );

    return true;
}


// UNLOAD CONTENT


void Neptune::UnloadContent( )
{
	bullets_->UnloadContent();
	
	if( colorMapSampler_ ) colorMapSampler_->Release( );
    if( colorMap_ ) colorMap_->Release( );
	if( solidColorVS_ ) solidColorVS_->Release( );
    if( solidColorPS_ ) solidColorPS_->Release( );
    if( inputLayout_ ) inputLayout_->Release( );
    if( vertexBuffer_ ) vertexBuffer_->Release( );
	
	if( mvpCB_ ) mvpCB_->Release( );

    colorMapSampler_ = 0;
    colorMap_ = 0;
	solidColorVS_ = 0;
    solidColorPS_ = 0;
    inputLayout_= 0;
    vertexBuffer_ = 0;

    mvpCB_ = 0;
}

void Neptune::Update( float dt )
{
	// update sprite
	XMFLOAT2 spritePos = sprite_.GetPosition( );

	// bring the sprite onto the screen
	if( !sprite_.GetIsActive( ) )
	{
		spritePos.y -= 75.0f * dt;

		// if the sprite is near the screen and is not active, set it to be active
		if( spritePos.y < game_->GetScreenHeight( ) + ( sprite_.GetHeight( ) / 2 ) )
		{
			sprite_.SetIsActive( true );
		}
	}
	// finish entering the screen
	else if( spritePos.y > game_->GetScreenHeight( ) - ( sprite_.GetHeight( ) / 2 ) )
	{
		sprite_.SetFwd(0,-1);
		spritePos.x += 75.0f * sprite_.GetFwd( ).x * dt;
		spritePos.y += 75.0f * sprite_.GetFwd( ).y * dt;
	}
	// if all the way on screen...
	else
	{
		// choose a behavior
		canBeHit = true;
		if(!shoot && !sweep && !spawn)
		{
			pattern = rand() % 20;

			if(pattern <= 8)
			{
				shoot = true;
				sweep = false;
				spawn = false;
			}
			else if(pattern <= 16)
			{
				sweep = true;
				shoot = false;
				spawn = false;
			}
			else
			{
				spawn = true;
				sweep = false;
				shoot = false;
			}
		}

		// get the sprite's shoot time
		float shootTime = sprite_.GetShootTime( );

		if(seahorses_->GetSprites()->empty())
		{
			minionsAlive = false;
		}
		else
		{
			minionsAlive = true;
		}

		if(cooldownTime_ >= cooldown_)
		{
			// sweep
			if(sweep)
			{
				if(sweepStep == 0 && sprite_.GetPosition().x > sprite_.GetWidth()/2)
				{
					sprite_.SetFwd(-0.75, -0.75);
					spritePos.x += sprite_.GetVelocity() * sprite_.GetFwd( ).x * dt;
					spritePos.y += sprite_.GetVelocity() * sprite_.GetFwd( ).y * dt;
				}
				else if(sweepStep == 0 && sprite_.GetPosition().x <= sprite_.GetWidth()/2)
				{
					sweepStep = 1;
				}

				if(sweepStep == 1 &&  sprite_.GetPosition().x < (game_->GetScreenWidth() - (sprite_.GetWidth()/2)))
				{
					sprite_.SetFwd(1.0, 0.0);
					spritePos.x += sprite_.GetVelocity() * sprite_.GetFwd( ).x * dt;
					spritePos.y += sprite_.GetVelocity() * sprite_.GetFwd( ).y * dt;
				}
				else if(sweepStep == 1 && sprite_.GetPosition().x >= (game_->GetScreenWidth() - (sprite_.GetWidth()/2)))
				{
					sweepStep = 2;
				}

				if(sweepStep == 2 && (sprite_.GetPosition().x > game_->GetScreenWidth()/2))
				{
					sprite_.SetFwd(-0.75, 0.75);
					spritePos.x += sprite_.GetVelocity() * sprite_.GetFwd( ).x * dt;
					spritePos.y += sprite_.GetVelocity() * sprite_.GetFwd( ).y * dt;
				}
				else if((sweepStep == 2 && sprite_.GetPosition().x <= game_->GetScreenWidth()/2))
				{
					sweepStep = 0;
					sweep = false;
					cooldownTime_ = 0.0f;
				}
			}

			// shoot trident
			else if(shoot)
			{
				if( !bullets_->GetInactiveSprites( )->empty( ) && shootTime >= 0.4f)
				{
					float angle;
					float fwdOffset = -3.14f / 2;

					shootTime = 0;
					if(bullets_->GetInactiveSprites( )->size( ) >= 5 && !bullets_->GetInactiveSprites( )->empty( ) )
					{
						// move the first inactive bullet to the back of the list of active bullets
						angle = 3.14f / 6;
						bullets_->GetInactiveSprites( )->front( ).SetPosition( sprite_.GetPosition( ) );
						bullets_->GetInactiveSprites( )->front( ).SetRotation( angle );
						bullets_->GetInactiveSprites( )->front( ).SetFwd( cos( angle + fwdOffset ), sin( angle + fwdOffset ) );
						bullets_->GetActiveSprites( )->push_back(bullets_->GetInactiveSprites( )->front( ));
						bullets_->GetInactiveSprites( )->pop_front( );

						angle = 3.14f / 12;
						bullets_->GetInactiveSprites( )->front( ).SetPosition( sprite_.GetPosition( ) );
						bullets_->GetInactiveSprites( )->front( ).SetRotation( angle );
						bullets_->GetInactiveSprites( )->front( ).SetFwd( cos( angle + fwdOffset ), sin( angle + fwdOffset ) );
						bullets_->GetActiveSprites( )->push_back(bullets_->GetInactiveSprites( )->front( ));
						bullets_->GetInactiveSprites( )->pop_front( );
						
						angle = 0.0f;
						bullets_->GetInactiveSprites( )->front( ).SetPosition( sprite_.GetPosition( ) );
						bullets_->GetInactiveSprites( )->front( ).SetRotation( angle );
						bullets_->GetInactiveSprites( )->front( ).SetFwd( cos( angle + fwdOffset ), sin( angle + fwdOffset ) );
						bullets_->GetActiveSprites( )->push_back(bullets_->GetInactiveSprites( )->front( ));
						bullets_->GetInactiveSprites( )->pop_front( );

						angle = -3.14f / 12;
						bullets_->GetInactiveSprites( )->front( ).SetPosition( sprite_.GetPosition( ) );
						bullets_->GetInactiveSprites( )->front( ).SetRotation( angle );
						bullets_->GetInactiveSprites( )->front( ).SetFwd( cos( angle + fwdOffset ), sin( angle + fwdOffset ) );
						bullets_->GetActiveSprites( )->push_back(bullets_->GetInactiveSprites( )->front( ));
						bullets_->GetInactiveSprites( )->pop_front( );

						angle = -3.14f / 6;
						bullets_->GetInactiveSprites( )->front( ).SetPosition( sprite_.GetPosition( ) );
						bullets_->GetInactiveSprites( )->front( ).SetRotation( angle );
						bullets_->GetInactiveSprites( )->front( ).SetFwd( cos( angle + fwdOffset ), sin( angle + fwdOffset ) );
						bullets_->GetActiveSprites( )->push_back(bullets_->GetInactiveSprites( )->front( ));
						bullets_->GetInactiveSprites( )->pop_front( );
					}
				}
				else if(shootTime < cooldown_)
				{
					shootTime += dt;
				}

				if(bullets_->GetInactiveSprites()->empty())
				{
					shoot = false;
					cooldownTime_ = 0.0f;
					shootTime = 0.4;
				}
			}
			else if(spawn && !minionsAlive)
			{
				spawn = false;
				seahorses_->CreateSeahorse(sprite_.GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f));
				seahorses_->CreateSeahorse(sprite_.GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f));

				for(list<GameSprite>::iterator s = seahorses_->GetSprites()->begin( ); s != seahorses_->GetSprites()->end(); s++)
				{
					s->SetIsActive(true);
				}

				cooldownTime_ = 0.0f;
			}
		}
		else
		{
			cooldownTime_ += dt;
		}

		sprite_.SetShootTime( shootTime );
	}

	// update seahorses
	seahorses_->Update(dt);

	// update bullets
	if( !bullets_->GetActiveSprites()->empty( ) )
	{
		list<GameSprite>::iterator b = bullets_->GetActiveSprites()->begin( );
		while( b != bullets_->GetActiveSprites()->end( ) )
		{
			XMFLOAT2 bulletPos = b->GetPosition( );
			bulletPos.x += b->GetVelocity( ) * b->GetFwd( ).x * dt;
			bulletPos.y += b->GetVelocity( ) * b->GetFwd( ).y * dt;
			b->SetPosition( bulletPos );

			// check if the bullet is off screen and put it into the inactive bullets array
			if( b->GetPosition( ).y < 0 - b->GetHeight( ) / 2 )
			{
				bullets_->GetInactiveSprites()->push_back( *b );
				b = bullets_->GetActiveSprites()->erase( b );
			}
			else
			{
				b++;
			}
		}
	}

	sprite_.SetPosition( spritePos );
}


// RENDER


void Neptune::Render( XMMATRIX* vpMatrix )
{
	bullets_->Render( vpMatrix );
	seahorses_->Render( vpMatrix );
	
	unsigned int stride = sizeof( VertexPos );
    unsigned int offset = 0;

    d3dContext_->IASetInputLayout( inputLayout_ );
    d3dContext_->IASetVertexBuffers( 0, 1, &vertexBuffer_, &stride, &offset );
    d3dContext_->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

    d3dContext_->VSSetShader( solidColorVS_, 0, 0 );
    d3dContext_->PSSetShader( solidColorPS_, 0, 0 );
    d3dContext_->PSSetShaderResources( 0, 1, &colorMap_ );
    d3dContext_->PSSetSamplers( 0, 1, &colorMapSampler_ );

	// render sprite
	if( sprite_.GetIsActive( ) )
		spriteSheet_->RenderSprite( &sprite_, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );
}


// ADDITIONAL FUNCTIONS


void Neptune::CreateNeptune( XMFLOAT2 position, float rotation, XMFLOAT2 scale )
{
	sprite_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 400.0f, position, 240, 1, rotation, scale );
	sprite_.SetFwd(0.0f, -1.0f);
	sprite_.SetCurrentAnimation( "fullHealth" );

	sprite_.SetShootTime( 0.4f );
}

