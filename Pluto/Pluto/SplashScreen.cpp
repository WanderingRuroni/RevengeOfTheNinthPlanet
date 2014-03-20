#include "SplashScreen.h"


// position and texture coordinates of the vertex
struct VertexPos
{
    XMFLOAT3 pos;
    XMFLOAT2 tex0;
};


SplashScreen::SplashScreen( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget ) : solidColorVS_( 0 ), solidColorPS_( 0 ), inputLayout_( 0 ),
																																											vertexBuffer_( 0 ), colorMap_( 0 ), colorMapSampler_( 0 ),
																																											mvpCB_( 0 )
{
	game_ = game;

	d3dDevice_ = d3dDevice;
	d3dContext_ = d3dContext;
	swapChain_ = swapChain;
	backBufferTarget_ = backBufferTarget;

	// create mouse cursor
	mouseCursor_ = new MouseCursor( game, d3dDevice, d3dContext, swapChain, backBufferTarget );

	// create score manager
	score_ = new FontManager( game, d3dDevice, d3dContext, swapChain, backBufferTarget, -0.2f, -0.9f );
}


SplashScreen::~SplashScreen( )
{
}


// GETTERS


GameSprite* SplashScreen::GetSprite( )
{
	return &sprite_;
}


int SplashScreen::GetScreenState( )
{
	return screenState_;
}


// INITIALIZER


void SplashScreen::Initialize( )
{
	// start the splash screen at the starting state
	screenState_ = START;

	mouseCursor_->Initialize( );
}


// SETTERS


// switch the screen state to the one given
void SplashScreen::SetScreenState( int state )
{
	screenState_ = state;
}


// LOAD CONTENT


bool SplashScreen::LoadContent( )
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
        "Assets/Images/Menu.png", 0, 0, &colorMap_, 0 );

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
	spriteSheet_ = new SpriteSheet( game_, 3, 6, ( float )colorTexDesc.Width, ( float )colorTexDesc.Height );
	spriteWidth_ = spriteSheet_->GetSheetWidth( ) / spriteSheet_->GetHorizontalSprites( );
	spriteHeight_ = spriteSheet_->GetSheetHeight( ) / spriteSheet_->GetVerticalSprites( );

	// add coordinates to animations
	vector<XMFLOAT2> menu;
	menu.push_back( XMFLOAT2( 0.0f, 0.0f ) );
	spriteSheet_->AddAnimationToMap( "menu" , menu, -1 );

	vector<XMFLOAT2> menu_play;
	menu_play.push_back( XMFLOAT2( 1.0f, 0.0f ) );
	spriteSheet_->AddAnimationToMap( "menu_play" , menu_play, -1 );

	vector<XMFLOAT2> menu_instructions;
	menu_instructions.push_back( XMFLOAT2( 0.0f, 1.0f ) );
	spriteSheet_->AddAnimationToMap( "menu_instructions" , menu_instructions, -1 );

	vector<XMFLOAT2> menu_credits;
	menu_credits.push_back( XMFLOAT2( 1.0f, 1.0f ) );
	spriteSheet_->AddAnimationToMap( "menu_credits" , menu_credits, -1 );

	vector<XMFLOAT2> menu_exit;
	menu_exit.push_back( XMFLOAT2( 0.0f, 2.0f ) );
	spriteSheet_->AddAnimationToMap( "menu_exit" , menu_exit, -1 );

	vector<XMFLOAT2> instructions;
	instructions.push_back( XMFLOAT2( 1.0f, 2.0f ) );
	spriteSheet_->AddAnimationToMap( "instructions" , instructions, -1 );

	vector<XMFLOAT2> instructions_back;
	instructions_back.push_back( XMFLOAT2( 0.0f, 3.0f ) );
	spriteSheet_->AddAnimationToMap( "instructions_back" , instructions_back, -1 );

	vector<XMFLOAT2> credits;
	credits.push_back( XMFLOAT2( 1.0f, 3.0f ) );
	spriteSheet_->AddAnimationToMap( "credits" , credits, -1 );

	vector<XMFLOAT2> credits_back;
	credits_back.push_back( XMFLOAT2( 0.0f, 4.0f ) );
	spriteSheet_->AddAnimationToMap( "credits_back" , credits_back, -1 );

	vector<XMFLOAT2> game_over;
	game_over.push_back( XMFLOAT2( 1.0f, 4.0f ) );
	spriteSheet_->AddAnimationToMap( "game_over" , game_over, -1 );

	vector<XMFLOAT2> game_over_replay;
	game_over_replay.push_back( XMFLOAT2( 0.0f, 5.0f ) );
	spriteSheet_->AddAnimationToMap( "game_over_replay" , game_over_replay, -1 );

	vector<XMFLOAT2> game_over_menu;
	game_over_menu.push_back( XMFLOAT2( 1.0f, 5.0f ) );
	spriteSheet_->AddAnimationToMap( "game_over_menu" , game_over_menu, -1 );

	vector<XMFLOAT2> victory;
	victory.push_back( XMFLOAT2( 2.0f, 0.0f ) );
	spriteSheet_->AddAnimationToMap( "victory" , victory, -1 );

	vector<XMFLOAT2> victory_replay;
	victory_replay.push_back( XMFLOAT2( 2.0f, 1.0f ) );
	spriteSheet_->AddAnimationToMap( "victory_replay" , victory_replay, -1 );

	vector<XMFLOAT2> victory_back;
	victory_back.push_back( XMFLOAT2( 2.0f, 2.0f ) );
	spriteSheet_->AddAnimationToMap( "victory_back" , victory_back, -1 );

	// create sprite menu
	sprite_ = spriteSheet_->CreateSprite( collisionTemplate_, spriteWidth_, spriteHeight_, 0.0f, XMFLOAT2( game_->GetScreenWidth( ) / 2, game_->GetScreenHeight( ) / 2 ) );
	sprite_.SetCurrentAnimation( "menu" );

	// load button positions on splash screen
	play_ = XMFLOAT4( 500.0f, 595.0f, game_->GetScreenHeight( ) - 391.0f, game_->GetScreenHeight( ) - 330.0f );
	instructions_ = XMFLOAT4( 500.0f, 762.0f, game_->GetScreenHeight( ) - 451.0f, game_->GetScreenHeight( ) - 390.0f );
	credits_ = XMFLOAT4( 500.0f, 652.0f, game_->GetScreenHeight( ) - 511.0f, game_->GetScreenHeight( ) - 450.0f );
	exit_ = XMFLOAT4( 500.0f, 586.0f, game_->GetScreenHeight( ) - 571.0f, game_->GetScreenHeight( ) - 510.0f );
	replay_ = XMFLOAT4( 84.0f, 235.0f, game_->GetScreenHeight( ) - 577.0f, game_->GetScreenHeight( ) - 506.0f );
	menu_ = XMFLOAT4( 611.0f, 721.0f, game_->GetScreenHeight( ) - 570.0f, game_->GetScreenHeight( ) - 509.0f );
	back_ = XMFLOAT4( 616.0f, 722.0f, game_->GetScreenHeight( ) - 560.0f, game_->GetScreenHeight( ) - 499.0f );

	// load mouse cursor
	if( !mouseCursor_->LoadContent( ) )
		return false;

	// load score
	if( !score_->LoadContent( ) )
		return false;

	Initialize( );

    return true;
}


// UNLOAD CONTENT


void SplashScreen::UnloadContent( )
{
	// unload score
	score_->UnloadContent( );

	// unload splash screen
	mouseCursor_->UnloadContent( );

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


void SplashScreen::Update( float dt, DIMOUSESTATE mouseState, long mousePosX, long mousePosY, long mouseWheel )
{
	// update the mouse position
	mouseCursor_->GetSprite( )->SetPosition( XMFLOAT2( ( float ) mousePosX, ( float ) mousePosY ) );

	switch( screenState_ )
	{
		case START:
			if( mousePosX > play_.x && mousePosX < play_.y && mousePosY > play_.z && mousePosY < play_.w )
			{
				sprite_.SetCurrentAnimation( "menu_play" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					// if button clicks...
					game_->PlaySound( "thud" );

					game_->SetGameState(GAME);
				}
			}
			else if( mousePosX > instructions_.x && mousePosX < instructions_.y && mousePosY > instructions_.z && mousePosY < instructions_.w )
			{
				sprite_.SetCurrentAnimation( "menu_instructions" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					// if button clicks...
					game_->PlaySound( "thud" );

					sprite_.SetCurrentAnimation( "instructions" );
					screenState_ = INSTRUCTIONS;
				}
			}
			else if( mousePosX > credits_.x && mousePosX < credits_.y && mousePosY > credits_.z && mousePosY < credits_.w )
			{
				sprite_.SetCurrentAnimation( "menu_credits" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					// if button clicks...
					game_->PlaySound( "thud" );

					sprite_.SetCurrentAnimation( "credits" );
					screenState_ = CREDITS;
				}
			}
			else if( mousePosX > exit_.x && mousePosX < exit_.y && mousePosY > exit_.z && mousePosY < exit_.w )
			{
				sprite_.SetCurrentAnimation( "menu_exit" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					game_->PlaySound( "thud" );

					// if button clicks...
					PostQuitMessage(0);
				}
			}
			else
			{
				sprite_.SetCurrentAnimation( "menu" );
			}

			break;

		case INSTRUCTIONS:
			if( mousePosX > back_.x && mousePosX < back_.y && mousePosY > back_.z && mousePosY < back_.w )
			{
				sprite_.SetCurrentAnimation( "instructions_back" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					// if button clicks...
					game_->PlaySound( "thud" );

					sprite_.SetCurrentAnimation( "menu" );
					screenState_ = START;
				}
			}
			else
			{
				sprite_.SetCurrentAnimation( "instructions" );
			}

			break;

		case CREDITS:
			if( mousePosX > back_.x && mousePosX < back_.y && mousePosY > back_.z && mousePosY < back_.w )
			{
				sprite_.SetCurrentAnimation( "credits_back" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					// if button clicks...
					game_->PlaySound( "thud" );

					sprite_.SetCurrentAnimation( "menu" );
					screenState_ = START;
				}
			}
			else
			{
				sprite_.SetCurrentAnimation( "credits" );
			}

			break;

		case END:
			if( mousePosX > replay_.x && mousePosX < replay_.y && mousePosY > replay_.z && mousePosY < replay_.w )
			{
				sprite_.SetCurrentAnimation( "game_over_replay" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					// if button clicks...
					game_->PlaySound( "thud" );

					HINSTANCE h = game_->GetInstance();
					HWND hw = game_->GetWindow();
					GameTimer* gt = game_->GetTimer();

					game_->Reset( );
					game_->SetGameState(GAME);
				}
			}
			else if( mousePosX > menu_.x && mousePosX < menu_.y && mousePosY > menu_.z && mousePosY < menu_.w )
			{
				sprite_.SetCurrentAnimation( "game_over_menu" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					// if button clicks...
					game_->PlaySound( "thud" );

					HINSTANCE h = game_->GetInstance();
					HWND hw = game_->GetWindow();
					GameTimer* gt = game_->GetTimer();
					
					game_->Reset( );
					game_->SetGameState(MENU);
				}
			}
			else
			{
				sprite_.SetCurrentAnimation( "game_over" );
			}

			break;
		case VICTORY:
			//back button
			if( mousePosX > back_.x && mousePosX < back_.y && mousePosY > back_.z && mousePosY < back_.w )
			{
				sprite_.SetCurrentAnimation( "victory_back" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					// if button clicks...
					game_->PlaySound( "thud" );

					HINSTANCE h = game_->GetInstance();
					HWND hw = game_->GetWindow();
					GameTimer* gt = game_->GetTimer();

					game_->Reset( );
					game_->SetGameState(MENU);
				}
			}

			else if( mousePosX > replay_.x && mousePosX < replay_.y && mousePosY > replay_.z && mousePosY < replay_.w )
			{
				sprite_.SetCurrentAnimation( "victory_replay" );

				// get intput and update accordingly
				if( BUTTONDOWN( mouseState, 0 ) )
				{
					// if button clicks...
					game_->PlaySound( "thud" );

					HINSTANCE h = game_->GetInstance();
					HWND hw = game_->GetWindow();
					GameTimer* gt = game_->GetTimer();

					game_->Reset( );
					game_->SetGameState(GAME);
				}
			}

			else
			{
				sprite_.SetCurrentAnimation( "victory" );
			}

			break;
		default:
			break;
	}

	game_->SetMousePosX( mousePosX + mouseState.lX );
	game_->SetMousePosY( mousePosY - mouseState.lY );
	game_->SetMouseWheel( mouseWheel + mouseState.lZ );
}


// RENDER


void SplashScreen::Render( XMMATRIX* vpMatrix )
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

	// render cursor
	mouseCursor_->Render( vpMatrix );

	// render score
	if( screenState_ == END || screenState_ == VICTORY )
		score_->Render( "Score: ", game_->GetPluto( )->GetScore( ) );
}