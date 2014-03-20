#include "Pluto.h"


// position and texture coordinates of the vertex
struct VertexPos
{
    XMFLOAT3 pos;
    XMFLOAT2 tex0;
};


Pluto::Pluto( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget ) : solidColorVS_( 0 ), solidColorPS_( 0 ), inputLayout_( 0 ),
																																											vertexBuffer_( 0 ), colorMap_( 0 ), colorMapSampler_( 0 ),
																																											mvpCB_( 0 )
{
	game_ = game;

	d3dDevice_ = d3dDevice;
	d3dContext_ = d3dContext;
	swapChain_ = swapChain;
	backBufferTarget_ = backBufferTarget;

	// create bullets
	bulletsRegular_ = new Bullets( game, d3dDevice, d3dContext, swapChain, backBufferTarget );
	bulletsRapid_ = new Bullets( game, d3dDevice, d3dContext, swapChain, backBufferTarget );
	bulletsBeam_ = new Bullets( game, d3dDevice, d3dContext, swapChain, backBufferTarget );
	bulletsShotgun_ = new Bullets( game, d3dDevice, d3dContext, swapChain, backBufferTarget );
	bulletsHuge_ = new Bullets( game, d3dDevice, d3dContext, swapChain, backBufferTarget );
}


Pluto::~Pluto( )
{
}


// GETTERS


GameSprite* Pluto::GetSprite( )
{
	return &sprite_;
}


Bullets* Pluto::GetBulletsRegular( )
{
	return bulletsRegular_;
}


Bullets* Pluto::GetBulletsRapid( )
{
	return bulletsRapid_;
}


Bullets* Pluto::GetBulletsBeam( )
{
	return bulletsBeam_;
}


Bullets* Pluto::GetBulletsShotgun( )
{
	return bulletsShotgun_;
}


Bullets* Pluto::GetBulletsHuge( )
{
	return bulletsHuge_;
}


int Pluto::GetWeapon( )
{
	return weapon_;
}


float Pluto::GetScore( )
{
	return score_;
}


// SETTERS


void Pluto::SetWeapon( int weapon )
{
	if( weapon >= PLUTO_REGULAR && weapon <= PLUTO_HUGE )
		weapon_ = weapon;
}


void Pluto::SetScore( float score )
{
	score_ = score;
}


// INITIALIZER


void Pluto::Initialize( )
{
	weapon_ = 0;
	score_ = 0.0f;

	sprite_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 200.0f, XMFLOAT2( 400.0f, 100.0f ), 3, 10 );
	sprite_.SetCurrentAnimation("pluto");

	bulletsRegular_->Initialize( "Pluto", 5, 450.0f, 4 );
	bulletsRapid_->Initialize( "PlutoRapid", 15, 750.0f, 3 );
	bulletsBeam_->Initialize( "Pluto", 1, 450.0f, 1 );
	bulletsShotgun_->Initialize( "Pluto", 9, 400.0f, 4 );
	bulletsHuge_->Initialize( "PlutoHuge", 1, 350.0f, 8 );
}


// LOAD CONTENT


bool Pluto::LoadContent( )
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
        "Assets/Images/Pluto.png", 0, 0, &colorMap_, 0 );

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
	spriteSheet_ = new SpriteSheet( game_, 6, 1, ( float )colorTexDesc.Width, ( float )colorTexDesc.Height );
	spriteWidth_ = spriteSheet_->GetSheetWidth( ) / spriteSheet_->GetHorizontalSprites( );
	spriteHeight_ = spriteSheet_->GetSheetHeight( ) / spriteSheet_->GetVerticalSprites( );

	// add coordinates to animations
	vector<XMFLOAT2> pluto;
	pluto.push_back( XMFLOAT2( 0.0f, 0.0f ) );
	vector<XMFLOAT2> invulnerable;
	invulnerable.push_back( XMFLOAT2( 0.0f, 0.0f ) );
	invulnerable.push_back( XMFLOAT2( 1.0f, 0.0f ) );
	invulnerable.push_back( XMFLOAT2( 2.0f, 0.0f ) );
	invulnerable.push_back( XMFLOAT2( 3.0f, 0.0f ) );
	invulnerable.push_back( XMFLOAT2( 4.0f, 0.0f ) );
	invulnerable.push_back( XMFLOAT2( 5.0f, 0.0f ) );
	invulnerable.push_back( XMFLOAT2( 4.0f, 0.0f ) );
	invulnerable.push_back( XMFLOAT2( 3.0f, 0.0f ) );
	invulnerable.push_back( XMFLOAT2( 2.0f, 0.0f ) );
	invulnerable.push_back( XMFLOAT2( 1.0f, 0.0f ) );

	spriteSheet_->AddAnimationToMap( "pluto" , pluto, -1 );
	spriteSheet_->AddAnimationToMap( "invulnerable", invulnerable, 0.05 );

	// create template of collision box
	float spriteHalfWidth = spriteWidth_ / 2.0f;
	float spriteHalfHeight = spriteHeight_ / 2.0f;

	XMFLOAT3 pts[] =
	{
		XMFLOAT3( spriteHalfWidth, 0.0f, 1.0f ), 
		XMFLOAT3( spriteHalfWidth * cos( XM_PI / 3 ), -spriteHalfHeight * sin (XM_PI / 3 ), 1.0f ), 
		XMFLOAT3( -spriteHalfWidth * cos( XM_PI / 3 ), -spriteHalfHeight * sin( XM_PI / 3 ), 1.0f ),
		XMFLOAT3( -spriteHalfWidth, 0.0f, 1.0f ),
		XMFLOAT3( -spriteHalfWidth * cos( XM_PI / 3 ), spriteHalfHeight * sin( XM_PI / 3 ), 1.0f ), 
		XMFLOAT3( spriteHalfWidth * cos(XM_PI / 3), spriteHalfHeight * sin( XM_PI / 3 ), 1.0f ),
		XMFLOAT3( spriteHalfWidth, 0.0f, 1.0f )
	};

	for( int i = 0; i < 7; i++)
	{
		collisionTemplate_.push_back(pts[i]);
	}

	// load bullets
	if( !bulletsRegular_->LoadContent( "Assets/Images/IceBullet1.png", "Pluto" ) )
		return false;

	if( !bulletsRapid_->LoadContent( "Assets/Images/IceBullet2.png", "PlutoRapid" ) )
		return false;

	if( !bulletsBeam_->LoadContent( "Assets/Images/IceBullet1.png", "Pluto" ) )
		return false;

	if( !bulletsShotgun_->LoadContent( "Assets/Images/IceBullet1.png", "Pluto" ) )
		return false;

	if( !bulletsHuge_->LoadContent( "Assets/Images/IceBullet3.png", "PlutoHuge" ) )
		return false;

	Initialize( );

    return true;
}


// UNLOAD CONTENT


void Pluto::UnloadContent( )
{
	bulletsRegular_->UnloadContent( );
	bulletsRapid_->UnloadContent( );
	bulletsBeam_->UnloadContent( );
	bulletsShotgun_->UnloadContent( );
	bulletsHuge_->UnloadContent( );

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


// UPDATE


void Pluto::Update( float dt, char* keyboardKeys, char* prevKeyboardKeys )
{
	XMFLOAT2 spritePos = sprite_.GetPosition();

	// if spacebar is pressed create a bullet at pluto's current position
	if( KEYDOWN( keyboardKeys, DIK_SPACE ) && !KEYDOWN( prevKeyboardKeys, DIK_SPACE ) )
	{
		switch( weapon_ )
		{
			case PLUTO_REGULAR:

				// shoot if there are available bullets
				if( !bulletsRegular_->GetInactiveSprites( )->empty( ) )
				{
					// move the first inactive bullet to the back of the list of active bullets			
					bulletsRegular_->GetActiveSprites( )->push_back( bulletsRegular_->GetInactiveSprites( )->front( ) );
					bulletsRegular_->GetInactiveSprites( )->pop_front( );

					bulletsRegular_->GetActiveSprites( )->back( ).SetPosition( sprite_.GetPosition( ) );
				}

				break;

			case PLUTO_RAPID:

				// shoot if there are available bullets
				if( !bulletsRapid_->GetInactiveSprites( )->empty( ) )
				{
					// move the first inactive bullet to the back of the list of active bullets			
					bulletsRapid_->GetActiveSprites( )->push_back( bulletsRapid_->GetInactiveSprites( )->front( ) );
					bulletsRapid_->GetInactiveSprites( )->pop_front( );

					bulletsRapid_->GetActiveSprites( )->back( ).SetPosition( sprite_.GetPosition( ) );
				}

				break;

			case PLUTO_BEAM:

				// shoot if there are available bullets
				if( !bulletsBeam_->GetInactiveSprites( )->empty( ) )
				{
					// move the first inactive bullet to the back of the list of active bullets			
					bulletsBeam_->GetActiveSprites( )->push_back( bulletsBeam_->GetInactiveSprites( )->front( ) );
					bulletsBeam_->GetInactiveSprites( )->pop_front( );

					bulletsBeam_->GetActiveSprites( )->back( ).SetPosition( sprite_.GetPosition( ) );
				}

				break;

			case PLUTO_SHOTGUN:
				
				if(bulletsShotgun_->GetInactiveSprites( )->size( ) >= 3 && !bulletsShotgun_->GetInactiveSprites( )->empty( ) )
				{
					float rotation;
					float fwdOffset = 3.14f / 2;

					// move the first inactive bullet to the back of the list of active bullets		
					rotation = 0.0f;
					bulletsShotgun_->GetInactiveSprites( )->front( ).SetRotation( rotation );
					bulletsShotgun_->GetInactiveSprites( )->front().SetFwd( cos( rotation + fwdOffset ), sin( rotation + fwdOffset ) );
					bulletsShotgun_->GetActiveSprites( )->push_back( bulletsShotgun_->GetInactiveSprites( )->front( ) );
					bulletsShotgun_->GetInactiveSprites( )->pop_front( );
					bulletsShotgun_->GetActiveSprites( )->back( ).SetPosition( sprite_.GetPosition( ) );

					rotation = -3.14 / 6;
					bulletsShotgun_->GetInactiveSprites( )->front().SetRotation( rotation );//-0.524f );
					bulletsShotgun_->GetInactiveSprites( )->front().SetFwd( cos( rotation + fwdOffset ), sin( rotation + fwdOffset ) );
					bulletsShotgun_->GetActiveSprites( )->push_back( bulletsShotgun_->GetInactiveSprites( )->front( ) );
					bulletsShotgun_->GetInactiveSprites( )->pop_front( );
					bulletsShotgun_->GetActiveSprites( )->back( ).SetPosition( sprite_.GetPosition( ) );

					rotation = 3.14 / 6;
					bulletsShotgun_->GetInactiveSprites( )->front().SetRotation( rotation );
					bulletsShotgun_->GetInactiveSprites( )->front().SetFwd( cos( rotation + fwdOffset ), sin( rotation + fwdOffset ) );
					bulletsShotgun_->GetActiveSprites( )->push_back( bulletsShotgun_->GetInactiveSprites( )->front( ) );
					bulletsShotgun_->GetInactiveSprites( )->pop_front( );
					bulletsShotgun_->GetActiveSprites( )->back( ).SetPosition( sprite_.GetPosition( ) );
				}

				break;

			case PLUTO_HUGE:

				// shoot if there are available bullets
				if( !bulletsHuge_->GetInactiveSprites( )->empty( ) )
				{
					// move the first inactive bullet to the back of the list of active bullets			
					bulletsHuge_->GetActiveSprites( )->push_back( bulletsHuge_->GetInactiveSprites( )->front( ) );
					bulletsHuge_->GetInactiveSprites( )->pop_front( );

					bulletsHuge_->GetActiveSprites( )->back( ).SetPosition( sprite_.GetPosition( ) );
				}

				break;

			default:
				break;
		}
	}

	// down button event
	if(KEYDOWN(keyboardKeys, DIK_S))
	{
		spritePos.y -= sprite_.GetVelocity( ) * dt;
		if(spritePos.y - sprite_.GetHeight()/2 <= 0)
		{
			spritePos.y += sprite_.GetVelocity( ) * dt;
		}
		sprite_.SetPosition(spritePos);
	}
		
	// up button event
	if(KEYDOWN(keyboardKeys, DIK_W))
	{
		spritePos.y += sprite_.GetVelocity( ) * dt;
		if(spritePos.y + sprite_.GetHeight()/2 >= game_->GetScreenHeight())
		{
			spritePos.y -= sprite_.GetVelocity( ) * dt;
		}
		sprite_.SetPosition(spritePos);
	}

	// left button event
	if(KEYDOWN(keyboardKeys, DIK_A))
	{
		spritePos.x -= sprite_.GetVelocity( ) * dt;
		if(spritePos.x - sprite_.GetWidth()/2 <= 0)
		{
			spritePos.x += sprite_.GetVelocity( ) * dt;
		}
		sprite_.SetPosition(spritePos);
	}

	// right button event
	if(KEYDOWN(keyboardKeys, DIK_D))
	{
		spritePos.x += sprite_.GetVelocity( ) * dt;
		if(spritePos.x + sprite_.GetWidth()/2 >= game_->GetScreenWidth())
		{
			spritePos.x -= sprite_.GetVelocity( ) * dt;
		}
		sprite_.SetPosition(spritePos);
	}

	// if there are active bullets on screen move them and check if they are on screen
	if( !bulletsRegular_->GetActiveSprites( )->empty( ) )
	{
		UpdateBullets( dt, bulletsRegular_->GetActiveSprites( ), bulletsRegular_->GetInactiveSprites( ) );
	}

	if( !bulletsRapid_->GetActiveSprites( )->empty( ) )
	{
		UpdateBullets( dt, bulletsRapid_->GetActiveSprites( ), bulletsRapid_->GetInactiveSprites( ) );
	}

	if( !bulletsBeam_->GetActiveSprites( )->empty( ) )
	{
		UpdateBullets( dt, bulletsBeam_->GetActiveSprites( ), bulletsBeam_->GetInactiveSprites( ) );
	}

	if( !bulletsShotgun_->GetActiveSprites( )->empty( ) )
	{
		UpdateBullets( dt, bulletsShotgun_->GetActiveSprites( ), bulletsShotgun_->GetInactiveSprites( ) );
	}

	if( !bulletsHuge_->GetActiveSprites( )->empty( ) )
	{
		UpdateBullets( dt, bulletsHuge_->GetActiveSprites( ), bulletsHuge_->GetInactiveSprites( ) );
	}
}


// RENDER


void Pluto::Render( XMMATRIX* vpMatrix )
{
	// render bullets

	if( !bulletsRegular_->GetActiveSprites( )->empty( ) )
	{
		bulletsRegular_->Render( vpMatrix );
	}

	if( !bulletsRapid_->GetActiveSprites( )->empty( ) )
	{
		bulletsRapid_->Render( vpMatrix );
	}

	if( !bulletsBeam_->GetActiveSprites( )->empty( ) )
	{
		bulletsBeam_->Render( vpMatrix );
	}

	if( !bulletsShotgun_->GetActiveSprites( )->empty( ) )
	{
		bulletsShotgun_->Render( vpMatrix );
	}

	if( !bulletsHuge_->GetActiveSprites( )->empty( ) )
	{
		bulletsHuge_->Render( vpMatrix );
	}

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
	spriteSheet_->RenderSprite( &sprite_, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );
}


// ADDITIONAL FUNCTIONS


void Pluto::UpdateBullets( float dt, list<GameSprite>* activeSprites, list<GameSprite>* inactiveSprites )
{
	list<GameSprite>::iterator b = activeSprites->begin( );
	while( b != activeSprites->end( ) )
	{
		XMFLOAT2 bulletPos = b->GetPosition( );
		bulletPos.x += b->GetVelocity( ) * b->GetFwd( ).x * dt;
		bulletPos.y += b->GetVelocity( ) * b->GetFwd( ).y * dt;
		b->SetPosition( bulletPos );

		// check if the bullet is off screen and put it into the inactive bullets array
		if( b->GetPosition( ).y > game_->GetScreenHeight( ) + ( b->GetHeight( ) / 2) )
		{
			inactiveSprites->push_back( *b );
			b = activeSprites->erase( b );
		}
		else
		{
			b++;
		}
	}
}