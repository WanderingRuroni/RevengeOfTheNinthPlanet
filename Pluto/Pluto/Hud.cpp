#include "Hud.h"


// position and texture coordinates of the vertex
struct VertexPos
{
    XMFLOAT3 pos;
    XMFLOAT2 tex0;
};


Hud::Hud( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget ) : solidColorVS_( 0 ), solidColorPS_( 0 ), inputLayout_( 0 ),
																																											vertexBuffer_( 0 ), colorMap_( 0 ), colorMapSampler_( 0 ),
																																											mvpCB_( 0 )
{
	game_ = game;

	d3dDevice_ = d3dDevice;
	d3dContext_ = d3dContext;
	swapChain_ = swapChain;
	backBufferTarget_ = backBufferTarget;

	// create the score
	score_ = new FontManager( game, d3dDevice, d3dContext, swapChain, backBufferTarget, -0.95f, 0.9f );

	// create the fps
	fps_ = new FontManager( game, d3dDevice, d3dContext, swapChain, backBufferTarget, -0.95f, 0.8f );
}


Hud::~Hud( )
{
}


// GETTERS


GameSprite* Hud::GetSprite( )
{
	return &sprite_;
}


int Hud::GetHealthState( )
{
	return healthState_;
}


// SETTERS


void Hud::SetHealthState( int state )
{
	healthState_ = state;
}


// INITIALIZER


void Hud::Initialize( )
{
	// create sprite
	sprite_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 0.0f, XMFLOAT2( spriteWidth_, 0.5f * spriteHeight_ + 0.5f * spriteWidth_ ) );
	sprite_.SetCurrentAnimation( "green" );
	healthState_ = 3;
	showFPS_ = false;
}



// LOAD CONTENT


bool Hud::LoadContent( )
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
        "Assets/Images/HealthBar.png", 0, 0, &colorMap_, 0 );

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
	spriteSheet_ = new SpriteSheet( game_, 4, 3, ( float )colorTexDesc.Width, ( float )colorTexDesc.Height );
	spriteWidth_ = spriteSheet_->GetSheetWidth( ) / spriteSheet_->GetHorizontalSprites( );
	spriteHeight_ = spriteSheet_->GetSheetHeight( ) / spriteSheet_->GetVerticalSprites( );

	// add coordinates to animations
	vector<XMFLOAT2> green;
	green.push_back( XMFLOAT2( 0.0f, 0.0f ) );
	spriteSheet_->AddAnimationToMap( "green", green, -1 );

	vector<XMFLOAT2> yellow;
	yellow.push_back( XMFLOAT2( 0.0f, 1.0f ) );
	spriteSheet_->AddAnimationToMap( "yellow", yellow, -1 );
		
	vector<XMFLOAT2> red;
	red.push_back( XMFLOAT2( 0.0f, 2.0f ) );
	spriteSheet_->AddAnimationToMap( "red" , red, -1 );

	vector<XMFLOAT2> empty;
	empty.push_back( XMFLOAT2( 3.0f, 2.0f ) );
	spriteSheet_->AddAnimationToMap( "empty", empty, -1 );

	vector<XMFLOAT2> green_hit;
	green_hit.push_back( XMFLOAT2( 0.0f, 0.0f ) );
	green_hit.push_back( XMFLOAT2( 1.0f, 0.0f ) );
	green_hit.push_back( XMFLOAT2( 2.0f, 0.0f ) );
	green_hit.push_back( XMFLOAT2( 3.0f, 0.0f ) );
	spriteSheet_->AddAnimationToMap( "green_hit" , green_hit, 0.025f );

	vector<XMFLOAT2> yellow_hit;
	yellow_hit.push_back( XMFLOAT2( 0.0f, 1.0f ) );
	yellow_hit.push_back( XMFLOAT2( 1.0f, 1.0f ) );
	yellow_hit.push_back( XMFLOAT2( 2.0f, 1.0f ) );
	yellow_hit.push_back( XMFLOAT2( 3.0f, 1.0f ) );
	spriteSheet_->AddAnimationToMap( "yellow_hit" , yellow_hit, 0.025f );

	vector<XMFLOAT2> red_hit;
	red_hit.push_back( XMFLOAT2( 0.0f, 2.0f ) );
	red_hit.push_back( XMFLOAT2( 1.0f, 2.0f ) );
	red_hit.push_back( XMFLOAT2( 2.0f, 2.0f ) );
	red_hit.push_back( XMFLOAT2( 3.0f, 2.0f ) );
	spriteSheet_->AddAnimationToMap( "red_hit" , red_hit, 0.025f );

	// load score
	if( !score_->LoadContent( ) )
		return false;

	// load fps
	if( !fps_->LoadContent( ) )
		return false;

	Initialize( );

    return true;
}


// UNLOAD CONTENT


void Hud::UnloadContent( )
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

	// unload fps
	fps_->UnloadContent( );

	// unload score
	score_->UnloadContent( );
}


// UPDATE


void Hud::Update( float dt, int lives, char* keyboardKeys, char* prevKeyboardKeys  )
{
	map<string, vector<XMFLOAT2>> animationMap = *spriteSheet_->GetAnimationMap( );
	map<string, float> durationMap = *spriteSheet_->GetDurationMap( );

	switch( lives )
	{
		case GREEN:
			sprite_.SetCurrentAnimation( "green" );
			break;

		case YELLOW:
			if( healthState_ > lives )
				sprite_.SetCurrentAnimation( "green_hit" );
			else if ( sprite_.GetChangeAnimationTime( ) >= ( animationMap[sprite_.GetCurrentAnimation( )].size( ) ) * durationMap[sprite_.GetCurrentAnimation( )] )
				sprite_.SetCurrentAnimation( "yellow" );

			healthState_ = lives;
			break;

		case RED:
			if( healthState_ > lives )
				sprite_.SetCurrentAnimation( "yellow_hit" );
			else if ( sprite_.GetChangeAnimationTime( ) >= animationMap[sprite_.GetCurrentAnimation( )].size( ) * durationMap[sprite_.GetCurrentAnimation( )] )
				sprite_.SetCurrentAnimation( "red" );

			healthState_ = lives;
			break;

		case NONE:
			if( healthState_ > lives )
				sprite_.SetCurrentAnimation( "red_hit" );
			else if ( sprite_.GetChangeAnimationTime( ) >= animationMap[sprite_.GetCurrentAnimation( )].size( ) * durationMap[sprite_.GetCurrentAnimation( )] )
				sprite_.SetCurrentAnimation( "empty" );

			
			healthState_ = lives;
			break;

		default:
			break;
	}

	// if f is pressed toggle the fps
	if( KEYDOWN( keyboardKeys, DIK_F ) && !KEYDOWN( prevKeyboardKeys, DIK_F ) )
	{
		if( showFPS_ )
			showFPS_ = false;
		else
			showFPS_ = true;
	}
}


// RENDER


void Hud::Render( XMMATRIX* vpMatrix )
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

	// render sprite
	spriteSheet_->RenderSprite( &sprite_, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );

	// render score
	score_->Render( "Score: ", game_->GetPluto( )->GetScore( ) );

	// render fps if it is visible
	if( showFPS_ )
		fps_->Render( "FPS: ", game_->GetTimer( )->GetFPS( ) );
}