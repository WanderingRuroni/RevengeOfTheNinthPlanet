#include "Background.h"


// position and texture coordinates of the vertex
struct VertexPos
{
    XMFLOAT3 pos;
    XMFLOAT2 tex0;
};


Background::Background( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget ) : solidColorVS_( 0 ), solidColorPS_( 0 ), inputLayout_( 0 ),
																																											vertexBuffer_( 0 ), colorMap_( 0 ), colorMapSampler_( 0 ),
																																											mvpCB_( 0 )
{
	game_ = game;

	d3dDevice_ = d3dDevice;
	d3dContext_ = d3dContext;
	swapChain_ = swapChain;
	backBufferTarget_ = backBufferTarget;
}


Background::~Background( )
{
}


// GETTERS


GameSprite* Background::GetSpriteCloseA( )
{
	return &spriteCloseA_;
}


GameSprite* Background::GetSpriteCloseB( )
{
	return &spriteCloseB_;
}

GameSprite* Background::GetSpriteMiddleA( )
{
	return &spriteMiddleA_;
}

GameSprite* Background::GetSpriteMiddleB( )
{
	return &spriteMiddleB_;
}

GameSprite* Background::GetSpriteFarA( )
{
	return &spriteFarA_;
}

GameSprite* Background::GetSpriteFarB( )
{
	return &spriteFarB_;
}


// INITIALIZE


void Background::Initialize( )
{
	// create sprite close A
	spriteCloseA_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 75.0f );
	spriteCloseA_.SetPosition( XMFLOAT2( game_->GetScreenWidth( ) / 2, game_->GetScreenHeight( ) / 2 ) );
	spriteCloseA_.SetCurrentAnimation( "close_stars" );

	// create sprite close B
	spriteCloseB_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 75.0f );
	spriteCloseB_.SetPosition( XMFLOAT2( game_->GetScreenWidth( ) / 2, ( game_->GetScreenHeight( ) / 2) + spriteCloseB_.GetHeight( ) ) );
	spriteCloseB_.SetCurrentAnimation( "close_stars" );

	// create sprite middle A
	spriteMiddleA_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 65.0f );
	spriteMiddleA_.SetPosition( XMFLOAT2( game_->GetScreenWidth( ) / 2, game_->GetScreenHeight( ) / 2 ) );
	spriteMiddleA_.SetCurrentAnimation( "middle_stars" );

	// create sprite middle A
	spriteMiddleB_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 65.0f );
	spriteMiddleB_.SetPosition( XMFLOAT2( game_->GetScreenWidth( ) / 2, ( game_->GetScreenHeight( ) / 2) + spriteMiddleB_.GetHeight( ) ) );
	spriteMiddleB_.SetCurrentAnimation( "middle_stars" );

	// create sprite far A
	spriteFarA_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 55.0f );
	spriteFarA_.SetPosition( XMFLOAT2( game_->GetScreenWidth( ) / 2, game_->GetScreenHeight( ) / 2 ) );
	spriteFarA_.SetCurrentAnimation( "far_stars" );

	// create sprite far B
	spriteFarB_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 55.0f );
	spriteFarB_.SetPosition( XMFLOAT2( game_->GetScreenWidth( ) / 2, ( game_->GetScreenHeight( ) / 2) + spriteFarB_.GetHeight( ) ) );
	spriteFarB_.SetCurrentAnimation( "far_stars" );
}


// LOAD CONTENT


bool Background::LoadContent( )
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
        "Assets/Images/Background.png", 0, 0, &colorMap_, 0 );

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
	spriteSheet_ = new SpriteSheet( game_, 3, 1, ( float )colorTexDesc.Width, ( float )colorTexDesc.Height );
	spriteWidth_ = spriteSheet_->GetSheetWidth( ) / spriteSheet_->GetHorizontalSprites( );
	spriteHeight_ = spriteSheet_->GetSheetHeight( ) / spriteSheet_->GetVerticalSprites( );
	
	// add coordinates to animations
	vector<XMFLOAT2> close_stars;
	close_stars.push_back( XMFLOAT2( 0.0f, 0.0f ) );

	vector<XMFLOAT2> middle_stars;
	middle_stars.push_back( XMFLOAT2( 1.0f, 0.0f ) );

	vector<XMFLOAT2> far_stars;
	far_stars.push_back( XMFLOAT2( 2.0f, 0.0f ) );

	spriteSheet_->AddAnimationToMap( "close_stars" , close_stars, -1 );
	spriteSheet_->AddAnimationToMap( "middle_stars" , middle_stars, -1 );
	spriteSheet_->AddAnimationToMap( "far_stars" , far_stars, -1 );

	Initialize( );

    return true;
}


// UNLOAD CONTENT


void Background::UnloadContent( )
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


// UPDATE


void Background::Update( float dt )
{
	// update sprite close A
	UpdateBackground( &spriteCloseA_, dt );

	// update sprite close B
	UpdateBackground( &spriteCloseB_, dt );

	// update sprite middle A
	UpdateBackground( &spriteMiddleA_, dt );

	// update sprite middle B
	UpdateBackground( &spriteMiddleB_, dt );

	// update sprite far A
	UpdateBackground( &spriteFarA_, dt );

	// update sprite far B
	UpdateBackground( &spriteFarB_, dt );
}


// RENDER


void Background::Render( XMMATRIX* vpMatrix )
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

	// render sprite close A
	spriteSheet_->RenderSprite( &spriteCloseA_, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );

	// render sprite close B
	spriteSheet_->RenderSprite( &spriteCloseB_, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );

	// render sprite middle A
	spriteSheet_->RenderSprite( &spriteMiddleA_, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );

	// render sprite middle B
	spriteSheet_->RenderSprite( &spriteMiddleB_, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );

	// render sprite far A
	spriteSheet_->RenderSprite( &spriteFarA_, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );

	// render sprite far B
	spriteSheet_->RenderSprite( &spriteFarB_, d3dContext_, vertexBuffer_, mvpCB_, vpMatrix );
}


// ADDITIONAL FUNCTIONS


// scrolls a background sprite based on the time from the last update
void Background::UpdateBackground( GameSprite* sprite, float dt )
{
	XMFLOAT2 spritePos = sprite->GetPosition( );
	spritePos.y -= sprite->GetVelocity( ) * dt;
	sprite->SetPosition( spritePos );
	if( spritePos.y < -( sprite->GetHeight( ) / 2 ) )
	{
		spritePos.y += ( 2 * sprite->GetHeight( ) );
		sprite->SetPosition( spritePos );
	}
}