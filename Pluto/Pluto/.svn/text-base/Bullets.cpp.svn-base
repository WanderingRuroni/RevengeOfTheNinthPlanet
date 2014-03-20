#include "Bullets.h"

// position and texture coordinates of the vertex
struct VertexPos
{
    XMFLOAT3 pos;
    XMFLOAT2 tex0;
};


Bullets::Bullets( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget ) : solidColorVS_( 0 ), solidColorPS_( 0 ), inputLayout_( 0 ),
																																											vertexBuffer_( 0 ), colorMap_( 0 ), colorMapSampler_( 0 ),
																																											mvpCB_( 0 )
{
	game_ = game;

	d3dDevice_ = d3dDevice;
	d3dContext_ = d3dContext;
	swapChain_ = swapChain;
	backBufferTarget_ = backBufferTarget;
}


Bullets::~Bullets()
{
}


// GETTERS


list<GameSprite>* Bullets::GetActiveSprites( )
{
	return &activeSprites_;
}

list<GameSprite>* Bullets::GetInactiveSprites( )
{
	return &inactiveSprites_;
}


// INITIALIZER


void Bullets::Initialize( string bulletType, int amount, float velocity, int attack )
{
	activeSprites_.clear( );
	inactiveSprites_.clear( );

	// populate the list of inactive bullets and initialize the sprites
	for( int i = 0; i < amount; i++ )
	{
		inactiveSprites_.push_back( spriteSheet_->CreateSprite( collisionTemplates_[bulletType], spriteWidth_, spriteHeight_, velocity, XMFLOAT2(0.0f,0.0f), 3, attack ));
		inactiveSprites_.back( ).SetCurrentAnimation( bulletType );
	}
}


// LOAD CONTENT


bool Bullets::LoadContent( char* filePath, string bulletType )
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
        filePath, 0, 0, &colorMap_, 0 );

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
	spriteSheet_ = new SpriteSheet( game_, 1, 1, ( float )colorTexDesc.Width, ( float )colorTexDesc.Height );
	spriteWidth_ = spriteSheet_->GetSheetWidth( ) / spriteSheet_->GetHorizontalSprites( );
	spriteHeight_ = spriteSheet_->GetSheetHeight( ) / spriteSheet_->GetVerticalSprites( );

	// add coordinates to animations
	vector<XMFLOAT2> shooting;
	shooting.push_back( XMFLOAT2( 0.0f, 0.0f ) );

	spriteSheet_->AddAnimationToMap( bulletType , shooting, -1 );

	// create templates of collision boxes

	list<XMFLOAT3> boundPluto, boundPlutoRapid, boundPlutoHuge, boundSeaHorse, boundNeptune;

	float spriteHalfWidth = spriteWidth_ / 2.0f;
	float spriteHalfHeight = spriteHeight_ / 2.0f;


	XMFLOAT3 pts1[] =
	{
		XMFLOAT3(0.0f, spriteHalfHeight, 1.0f),
		XMFLOAT3(spriteHalfWidth, 0.0f, 1.0f),
		XMFLOAT3(0.0f, -spriteHalfHeight, 1.0f),
		XMFLOAT3(-spriteHalfWidth, 0.0f, 1.0f),
		XMFLOAT3(0.0f, spriteHalfHeight, 1.0f)
	};

	XMFLOAT3 pts2[] =
	{
		XMFLOAT3(-spriteHalfWidth, spriteHalfHeight, 1.0f),
		XMFLOAT3(spriteHalfWidth, spriteHalfHeight, 1.0f),
		XMFLOAT3(spriteHalfWidth, -spriteHalfHeight, 1.0f),
		XMFLOAT3(-spriteHalfWidth, -spriteHalfHeight, 1.0f),
		XMFLOAT3(-spriteHalfWidth, spriteHalfHeight, 1.0f)
	};

	XMFLOAT3 pts3[] =
	{
		XMFLOAT3(0.0f, spriteHalfHeight, 1.0f),
		XMFLOAT3(spriteHalfWidth, (spriteHalfHeight/2.0f), 1.0f),
		XMFLOAT3((spriteHalfWidth/3.0f), (spriteHalfHeight/4.0f), 1.0f),
		XMFLOAT3(0.0f, -spriteHalfHeight, 1.0f),
		XMFLOAT3(-(spriteHalfWidth/3.0f), (spriteHalfHeight/4.0f), 1.0f),
		XMFLOAT3(-spriteHalfWidth, (spriteHalfHeight/2.0f), 1.0f),
		XMFLOAT3(0.0f, spriteHalfHeight, 1.0f)
	};

	XMFLOAT3 pts4[] =
	{
		XMFLOAT3(spriteHalfWidth, 0.0f, 1.0f), 
		XMFLOAT3(spriteHalfWidth * cos(XM_PI/3), -spriteHalfHeight * sin(XM_PI/3), 1.0f), 
		XMFLOAT3(-spriteHalfWidth * cos(XM_PI/3), -spriteHalfHeight * sin(XM_PI/3), 1.0f),
		XMFLOAT3(-spriteHalfWidth, 0.0f, 1.0f),
		XMFLOAT3(-spriteHalfWidth * cos(XM_PI/3), spriteHalfHeight * sin(XM_PI/3), 1.0f), 
		XMFLOAT3(spriteHalfWidth * cos(XM_PI/3), spriteHalfHeight * sin(XM_PI/3), 1.0f),
		XMFLOAT3(spriteHalfWidth, 0.0f, 1.0f)
	};

	XMFLOAT3 pts5[] =
	{
		XMFLOAT3(spriteHalfWidth, 0.0f, 1.0f), 
		XMFLOAT3(spriteHalfWidth * cos(XM_PI/3), -spriteHalfHeight * sin(XM_PI/3), 1.0f), 
		XMFLOAT3(-spriteHalfWidth * cos(XM_PI/3), -spriteHalfHeight * sin(XM_PI/3), 1.0f),
		XMFLOAT3(-spriteHalfWidth, 0.0f, 1.0f),
		XMFLOAT3(-spriteHalfWidth * cos(XM_PI/3), spriteHalfHeight * sin(XM_PI/3), 1.0f), 
		XMFLOAT3(spriteHalfWidth * cos(XM_PI/3), spriteHalfHeight * sin(XM_PI/3), 1.0f),
		XMFLOAT3(spriteHalfWidth, 0.0f, 1.0f)
	};

	for( int i = 0; i < 5; i++ )
	{
		boundPluto.push_back( pts1[i] );
		boundSeaHorse.push_back( pts2[i] );
	}

	for( int j = 0; j < 7; j++ )
	{
		boundNeptune.push_back(pts3[j]);
		boundPlutoRapid.push_back(pts4[j]);
		boundPlutoHuge.push_back(pts5[j]);
	}

	collisionTemplates_["Pluto"] = boundPluto;
	collisionTemplates_["PlutoRapid"] = boundPlutoRapid;
	collisionTemplates_["PlutoHuge"] = boundPlutoRapid;
	collisionTemplates_["SeaHorse"] = boundSeaHorse;
	collisionTemplates_["Neptune"] = boundNeptune;

    return true;
}


// UNLOAD CONTENT


void Bullets::UnloadContent( )
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


// RENDER


void Bullets::Render( XMMATRIX* vpMatrix )
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

	// render sprites
	for( list<GameSprite>::iterator s = activeSprites_.begin( ); s != activeSprites_.end( ); s++ )
	{
		spriteSheet_->RenderSprite( &*s, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );
	}
}