#include "PowerUps.h"

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

PowerUps::PowerUps(Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget ) : solidColorVS_( 0 ), solidColorPS_( 0 ), inputLayout_( 0 ),
																																											vertexBuffer_( 0 ), colorMap_( 0 ), colorMapSampler_( 0 ),
																																											mvpCB_( 0 )
{
	game_ = game;

	d3dDevice_ = d3dDevice;
	d3dContext_ = d3dContext;
	swapChain_ = swapChain;
	backBufferTarget_ = backBufferTarget;
}


PowerUps::~PowerUps(void)
{
}


// GETTERS


list<GameSprite>* PowerUps::GetSprites()
{
	return &sprites_;
}


// INITIALIZER


void PowerUps::Initialize( )
{
	sprites_.clear( );
}


// LOAD CONTENT


bool PowerUps::LoadContent()
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
        "Assets/Images/PowerUps.png", 0, 0, &colorMap_, 0 );

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
	spriteSheet_ = new SpriteSheet( game_, 5, 1, ( float )colorTexDesc.Width, ( float )colorTexDesc.Height );
	spriteWidth_ = spriteSheet_->GetSheetWidth( ) / spriteSheet_->GetHorizontalSprites( );
	spriteHeight_ = spriteSheet_->GetSheetHeight( ) / spriteSheet_->GetVerticalSprites( );

	// add coordinates to animations
	vector<XMFLOAT2> huge;
	huge.push_back( XMFLOAT2( 0.0f, 0.0f ) );
	vector<XMFLOAT2> shotgun;
	shotgun.push_back( XMFLOAT2( 1.0f, 0.0f ) );
	vector<XMFLOAT2> rapid;
	rapid.push_back( XMFLOAT2( 2.0f, 0.0f ) );
	vector<XMFLOAT2> normal;
	normal.push_back( XMFLOAT2( 3.0f, 0.0f ) );
	vector<XMFLOAT2> health;
	health.push_back( XMFLOAT2( 4.0f, 0.0f ) );

	spriteSheet_->AddAnimationToMap( "huge", huge, -1 );
	spriteSheet_->AddAnimationToMap( "shotgun", shotgun, -1 );
	spriteSheet_->AddAnimationToMap( "rapid", rapid, -1 );
	spriteSheet_->AddAnimationToMap( "normal", normal, -1 );
	spriteSheet_->AddAnimationToMap( "health", health, -1 );

	float spriteHalfWidth = spriteWidth_ / 2.0f;
	float spriteHalfHeight = spriteHeight_ / 2.0f;

	XMFLOAT3 pts[] =
	{
		XMFLOAT3(halfWidth, 0.0f, 1.0f), 
		XMFLOAT3(halfWidth * cos(XM_PI/3), -halfHeight * sin(XM_PI/3), 1.0f), 
		XMFLOAT3(-halfWidth * cos(XM_PI/3), -halfHeight * sin(XM_PI/3), 1.0f),
		XMFLOAT3(-halfWidth, 0.0f, 1.0f),
		XMFLOAT3(-halfWidth * cos(XM_PI/3), halfHeight * sin(XM_PI/3), 1.0f), 
		XMFLOAT3(halfWidth * cos(XM_PI/3), halfHeight * sin(XM_PI/3), 1.0f),
		XMFLOAT3(halfWidth, 0.0f, 1.0f)
	};

	for(int i = 0; i < 7; i++)
	{
		collisionTemplate_.push_back(pts[i]);
	}

	Initialize( );

	return true;
}

void PowerUps::UnloadContent()
{
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

void PowerUps::Update( float dt )
{
	// update sprites
	for( list<GameSprite>::iterator s = sprites_.begin( ); s != sprites_.end( ); s++ )
	{
		XMFLOAT2 spritePos = s->GetPosition( );

		if( !s->GetIsActive( ) )
		{
			spritePos.y -= 75.0f * dt;

			// if the sprite is near the screen and is not active, set it to be active
			if( spritePos.y < game_->GetScreenHeight( ) + ( s->GetHeight( ) / 2 ) )
			{
				s->SetIsActive( true );
			}
		}
		else
		{
			spritePos.x += s->GetVelocity( ) * s->GetFwd( ).x * dt;
			spritePos.y += s->GetVelocity( ) * s->GetFwd( ).y * dt;
		}

		s->SetPosition( spritePos );

		// erase sprites from list if they go off the screen
		if( s->GetPosition().y < -( s->GetHeight( ) ) )
		{
			sprites_.erase( s );
			break;
		}
	}
}

void PowerUps::Render( XMMATRIX* vpMatrix_)
{
	unsigned int stride = sizeof( VertexPos );
    unsigned int offset = 0;

    d3dContext_->IASetInputLayout( inputLayout_ );
    d3dContext_->IASetVertexBuffers( 0, 1, &vertexBuffer_, &stride, &offset );
    d3dContext_->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

    d3dContext_->VSSetShader( solidColorVS_, 0, 0 );
    d3dContext_->PSSetShader( solidColorPS_, 0, 0 );
    d3dContext_->PSSetShaderResources( 0, 1, &colorMap_ );
    d3dContext_->PSSetSamplers( 0, 1, &colorMapSampler_ );

	// render seahorses
	for( list<GameSprite>::iterator s = sprites_.begin( ); s != sprites_.end( ); s++ )
	{
		//if( s->GetIsActive( ) )
			spriteSheet_->RenderSprite( &*s, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix_ );
	}
}

void PowerUps::CreatePowerUp( XMFLOAT2 position, float rotation, XMFLOAT2 scale, string animation )
{
	GameSprite sprite_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 75.0f, position, 1, 1, rotation, scale );
	sprite_.SetFwd( 0.0f, -1.0f );
	sprite_.SetIsActive( true );
	sprites_.push_back( sprite_ );
	sprites_.back( ).SetCurrentAnimation( animation );
}