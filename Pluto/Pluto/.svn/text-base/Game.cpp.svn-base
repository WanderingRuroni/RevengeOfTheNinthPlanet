#include "Game.h"


// position and texture coordinates of the vertex
struct VertexPos
{
    XMFLOAT3 pos;
    XMFLOAT2 tex0;
};


// position of the end points of a line segment (used for collision)
struct Line
{
    XMFLOAT3 p1;
    XMFLOAT3 p2;
};


Game::Game( ) : driverType_( D3D_DRIVER_TYPE_NULL ), featureLevel_( D3D_FEATURE_LEVEL_11_0 ),
				d3dDevice_( 0 ), d3dContext_( 0 ), swapChain_( 0 ), backBufferTarget_( 0 ),
				alphaBlendState_( 0 ), soundEngine_( 0 )
{
}


Game::~Game( )
{
	Shutdown( );
}


// GETTERS


int Game::GetGameState( )
{
	return gameState_;
}


Hud* Game::GetHud( )
{
	return hud_;
}


Pluto* Game::GetPluto( )
{
	return pluto_;
}


Neptune* Game::GetNeptune( )
{
	return level1_->GetNeptune();
}


float Game::GetScreenWidth( )
{
	return screenWidth_;
}


float Game::GetScreenHeight( )
{
	return screenHeight_;
}


float Game::GetDeltaTime( )
{
	return timer_->GetDeltaTime( );
}


SplashScreen* Game::GetSplashScreen( )
{
	return splashScreen_;
}


HINSTANCE Game::GetInstance()
{
	return hInstance_;
}

HWND Game::GetWindow()
{
	return hwnd_;
}

GameTimer* Game::GetTimer()
{
	return timer_;
}


Level* Game::GetCurrentLevel( )
{
	switch( currentLevel_ )
	{
		case 1:
			return level1_;
			break;

		default:
			return NULL;
			break;
	}
}


// SETTERS


// switch the game state to the one given
void Game::SetGameState( int state )
{
	switch( state )
	{
		case GAME:
			timer_->Start( );
			break;
		default:
			timer_->Stop( );
			break;
	}
	
	gameState_ = state;
}


void Game::SetMousePosX( long mousePosX ) {
	if( mousePosX_ > 0 && mousePosX_ < screenWidth_ ) {
		mousePosX_ = mousePosX;
	}
	
	if( mousePosX_ <= 0 ) {
		mousePosX_ = 1;
	}
	else if( mousePosX_ >= screenWidth_ ) {
		mousePosX_ = screenWidth_ - 1;
	}
}


void Game::SetMousePosY( long mousePosY ) {
	if( mousePosY_ > 0 && mousePosY_ < screenHeight_ ) {
		mousePosY_ = mousePosY;
	}

	if( mousePosY_ <= 0 ) {
		mousePosY_ = 1;
	}
	else if( mousePosY_ >= screenHeight_ ) {
		mousePosY_ = screenHeight_ - 1;
	}
}


void Game::SetMouseWheel( long mouseWheel ) {
	mouseWheel_ = mouseWheel;
}


// INITIALIZE AND SHUTDOWN


bool Game::Initialize( HINSTANCE hInstance, HWND hwnd, GameTimer* timer )
{
	hInstance_ = hInstance;
	hwnd_ = hwnd;
	timer_ = timer;

	RECT dimensions;
	GetClientRect( hwnd_, &dimensions );

	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions .bottom - dimensions.top;

	screenWidth_ = ( float )width;
	screenHeight_ = ( float )height;

	// set the driver types
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};

	unsigned int totalDriverTypes = ARRAYSIZE( driverTypes );

	// set the featured levels
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	unsigned int totalFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) );
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	unsigned int creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT result;
	unsigned int driver = 0;

	// create the d3d device and swap chain for each driver type
	for( driver = 0; driver < totalDriverTypes; ++driver )
	{
		result = D3D11CreateDeviceAndSwapChain( 0, driverTypes[driver], 0, creationFlags, featureLevels, totalFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &swapChain_, &d3dDevice_, &featureLevel_, &d3dContext_ );

		if( SUCCEEDED( result ) )
		{
			driverType_ = driverTypes[driver];
			break;
		}
	}

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to create the Direct3D device!" );
		return false;
	}
	ID3D11Texture2D* backBufferTexture;
	
	// get the back buffer
	result = swapChain_->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&backBufferTexture );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to get the swap chain back buffer!" );
		return false;
	}

	// create render target view
	result = d3dDevice_->CreateRenderTargetView( backBufferTexture, 0, &backBufferTarget_ );

	if( backBufferTexture )
		backBufferTexture->Release( );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to create the render target view!" );
		return false;
	}

	d3dContext_->OMSetRenderTargets( 1, &backBufferTarget_, 0 );

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	d3dContext_->RSSetViewports( 1, &viewport );

	// create menus
	splashScreen_ = new SplashScreen( this, d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );

	// create background
	background_ = new Background( this, d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );

	// create level 1
	level1_ = new Level( this, d3dDevice_, d3dContext_, swapChain_, backBufferTarget_, 1, 75.0f );

	// create the player
	pluto_ = new Pluto( this, d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );

	// create the HUD
	hud_ = new Hud( this, d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );

	// initialize the timer
	timer_->Reset( );
	timer_->Tick( );

	// initialize the input
	result = DirectInput8Create(hInstance_, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, 0);
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to create direct input 8!" );
		return false;
	}

	// keyboard device
	ZeroMemory(keyboardKeys_, sizeof(keyboardKeys_));
	ZeroMemory(prevKeyboardKeys_, sizeof(prevKeyboardKeys_));

	result = directInput_->CreateDevice(GUID_SysKeyboard, &keyboardDevice_, 0);
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to create keyboard device!" );
		return false;
	}

	result = keyboardDevice_->SetDataFormat(&c_dfDIKeyboard);
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to set up keyboard device!" );
		return false;
	}

	result = keyboardDevice_->SetCooperativeLevel(hwnd_, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to set up keyboard device!" );
		return false;
	}

	result = keyboardDevice_->Acquire();
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to acquire keyboard device!" );
		return false;
	}

	// mouse device
	mousePosX_ = mousePosY_ = mouseWheel_ = 500;

	result = directInput_->CreateDevice( GUID_SysMouse, &mouseDevice_, 0);
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to create mouse device!" );
		return false;
	}

	result = mouseDevice_->SetDataFormat( &c_dfDIMouse );
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to set up mouse device!" );
		return false;
	}

	result = mouseDevice_->SetCooperativeLevel(hwnd_, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to set up mouse device!" );
		return false;
	}

	result = mouseDevice_->Acquire();
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to acquire mouse device!" );
		return false;
	}

	// initialize the sound
	ZeroMemory( &audioBanks_, sizeof( stXACTAudio ) );

    if( SetupXACT( &soundEngine_ ) == false )
        return false;

    if( LoadXACTAudio( soundEngine_, audioBanks_, "Assets/Sounds/Win/Wave Bank.xwb", "Assets/Sounds/Win/Sound Bank.xsb" ) == false )
        return false;

	PlaySound( "background" );

	// initialize the current level to 0 and the game to active
	currentLevel_ = 0;
	isActive = true;

	return LoadContent( );
}


void Game::Shutdown( )
{
	UnloadContent( );

	if( backBufferTarget_ ) backBufferTarget_->Release( );
	if( swapChain_ ) swapChain_->Release( );
	if( d3dContext_ ) d3dContext_->Release( );
	if( d3dDevice_ ) d3dDevice_->Release( );

	d3dDevice_ = 0;
	d3dContext_ = 0;
	swapChain_ = 0;
	backBufferTarget_ = 0;
}


// LOAD CONTENT


bool Game::LoadContent( )
{
	// load pluto
	if( !pluto_->LoadContent( ) )
		return false;

	// load hud
	if( !hud_->LoadContent( ) )
		return false;

	// load levels
	if( !level1_->LoadContent( ) )
		return false;

	// load background
	if( !background_->LoadContent( ) )
		return false;

	// load splash screen
	if( !splashScreen_->LoadContent( ) )
		return false;

	XMMATRIX view = XMMatrixIdentity( );
    XMMATRIX projection = XMMatrixOrthographicOffCenterLH( 0.0f, screenWidth_, 0.0f, screenHeight_, 0.1f, 100.0f );
    vpMatrix_ = XMMatrixMultiply( view, projection );

	D3D11_BLEND_DESC blendDesc;
    ZeroMemory( &blendDesc, sizeof( blendDesc ) );
    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;	// D3D11_BLEND_ONE;		* applies some factor of alpha blending to entire texture
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;

    float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// create the blend state
    d3dDevice_->CreateBlendState( &blendDesc, &alphaBlendState_ );
    d3dContext_->OMSetBlendState( alphaBlendState_, blendFactor, 0xFFFFFFFF );

	// go to the first level
	NextLevel( );

	return true;
}


// UNLOAD CONTENT


void Game::UnloadContent( )
{
	// unload splash screen
	splashScreen_->UnloadContent( );

	// unload backgorund
	background_->UnloadContent( );

	// unload levels
	level1_->UnloadContent( );

	// unload pluto
	pluto_->UnloadContent( );

	// unload hud
	hud_->UnloadContent( );

	// unload sound
	if( audioBanks_.soundBank ) audioBanks_.soundBank->Destroy( );
    if( audioBanks_.waveBank ) audioBanks_.waveBank->Destroy( );

    if( soundEngine_ )
    {
        soundEngine_->ShutDown( );
        soundEngine_->Release( );
    }

    if( audioBanks_.soundBankData )
    {
        UnmapViewOfFile( audioBanks_.soundBankData );
        audioBanks_.soundBankData = 0;
    }

    if( audioBanks_.waveBankData )
    {
        UnmapViewOfFile( audioBanks_.waveBankData );
        audioBanks_.waveBankData = 0;
    }

	// unload input
	if( mouseDevice_ )
	{
		mouseDevice_->Unacquire();
		mouseDevice_->Release();
	}

	if( keyboardDevice_ )
	{
		keyboardDevice_->Unacquire();
		keyboardDevice_->Release();
	}
	
    if( alphaBlendState_ ) alphaBlendState_->Release( );

	mouseDevice_ = 0;
	keyboardDevice_ = 0;
    alphaBlendState_ = 0;
}


// UPDATE


void Game::Update( float dt )
{
	if( GetForegroundWindow( ) != hwnd_ && isActive )
	{
		isActive = false;
		keyboardDevice_->Unacquire( );
		mouseDevice_->Unacquire( );
	}
	else if( GetForegroundWindow( ) == hwnd_ && !isActive )
	{
		isActive = true;
		keyboardDevice_->Acquire( );
		mouseDevice_->Acquire( );
	}

	// if this window is in the foreground update and get input
	if( isActive )
	{
		// tick the timer, timer will check if paused and react accordingly
		timer_->Tick( );

		// button press event
		if(GetAsyncKeyState(VK_ESCAPE))
			PostQuitMessage(0);

		// check the game state and update accordingly
		switch( gameState_ )
		{
			case MENU:
				// update splash screen
				mouseDevice_->GetDeviceState( sizeof( mouseState_ ), ( LPVOID )&mouseState_ );
				splashScreen_->Update( dt, mouseState_, mousePosX_, mousePosY_, mouseWheel_ );
				memcpy( &prevMouseState_, &mouseState_, sizeof( mouseState_ ) );
				break;

			case GAME:
				keyboardDevice_->GetDeviceState( sizeof( keyboardKeys_ ), ( LPVOID )&keyboardKeys_ );

				// update background
				background_->Update( dt );

				// update pluto
				pluto_->Update( dt, keyboardKeys_, prevKeyboardKeys_ );

				// update hud
				hud_->Update(dt, pluto_->GetSprite( )->GetHealth( ), keyboardKeys_, prevKeyboardKeys_ );

				// update level 1
				if( currentLevel_ == 1 )
					level1_->Update( dt );

				memcpy( prevKeyboardKeys_, keyboardKeys_, sizeof( keyboardKeys_ ) );

				break;

			case PAUSE:
				break;

			default:
				break;
		}

		// do the sound
		unsigned long state = 0;

		if( soundEngine_ != 0 && audioBanks_.soundBank != 0 )
		{
			audioBanks_.soundBank->GetState( &state );

			if( state && XACT_CUESTATE_PLAYING )
				soundEngine_->DoWork( );
		}
	}
}


// RENDER


void Game::Render( )
{
	if( d3dContext_ == 0 )
        return;

	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	d3dContext_->ClearRenderTargetView( backBufferTarget_, clearColor );

	switch( gameState_ )
	{
		case MENU:
			splashScreen_->Render( &vpMatrix_ );
			break;

		case GAME:
			timer_->CalculateFPS( );

			// render background
			background_->Render( &vpMatrix_ );
			
			// render level 1
			if( currentLevel_ == 1 )
				level1_->Render( &vpMatrix_ );

			// render pluto
			pluto_->Render( &vpMatrix_ );

			// render hud
			hud_->Render(&vpMatrix_);

			break;

		case PAUSE:
			break;

		default:
			break;
	}

    swapChain_->Present( 1, 0 );
}


// ADDITIONAL FUNCTIONS


// reset the game/level
void Game::Reset( )
{
	// initalize the timer
	timer_->Reset( );
	timer_->Tick( );

	// initialize splash screen
	splashScreen_->Initialize( );

	// initialize background
	background_->Initialize( );

	// initialize pluto
	pluto_->Initialize( );

	// initialize hud
	hud_->Initialize( );

	// initalize level
	GetCurrentLevel( )->Initialize( );
}


void Game::NextLevel( )
{
	currentLevel_++;

	// initialize pluto
	pluto_->Initialize( );

	// initialize hud
	hud_->Initialize( );

	// initalize level
	GetCurrentLevel( )->Initialize( );
}


// plays a sound
void Game::PlaySound( string sound )
{
	XACTINDEX soundCue = audioBanks_.soundBank->GetCueIndex( sound.c_str( ) );
    audioBanks_.soundBank->Play( soundCue, 0, 0, 0 );
}


// creates shader to draw sprites
bool Game::CompileD3DShader( char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer )
{
    DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* errorBuffer = 0;
    HRESULT result;

    result = D3DX11CompileFromFile( filePath, 0, 0, entry, shaderModel,
        shaderFlags, 0, 0, buffer, &errorBuffer, 0 );

    if( FAILED( result ) )
    {
        if( errorBuffer != 0 )
        {
            OutputDebugStringA( ( char* )errorBuffer->GetBufferPointer( ) );
            errorBuffer->Release( );
        }

        return false;
    }
    
    if( errorBuffer != 0 )
        errorBuffer->Release( );

    return true;
}


// sound functions
// setup the xast3 sound device
bool Game::SetupXACT( IXACT3Engine** audioEngine )
{
    if( FAILED(CoInitializeEx( 0, COINIT_MULTITHREADED ) ) )
        return false;

    if( FAILED( XACT3CreateEngine( XACT_FLAG_API_AUDITION_MODE, audioEngine ) ) )
      return false;

   if( *audioEngine == 0 )
      return false;

   XACT_RUNTIME_PARAMETERS xparams = { 0 };
   xparams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;

   if( FAILED( ( *audioEngine )->Initialize( &xparams ) ) )
      return false;

    return true;
}


bool Game::LoadXACTAudio( IXACT3Engine* audioEngine, stXACTAudio& audio, char* waveBank, char* soundBank )
{
   if( LoadWaveBank( audioEngine, audio, waveBank ) == false )
      return false;

   if( LoadSoundBank( audioEngine, audio, soundBank ) == false )
      return false;

   return true;
}


void* Game::LoadBankFile( char* filePath, DWORD& fileSize )
{
    HANDLE file = CreateFile( filePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0 );

    if( file == INVALID_HANDLE_VALUE )
        return 0;

    fileSize = GetFileSize( file, 0 );

    if( fileSize == -1 )
    {
        CloseHandle( file );
        return 0;
    }

    HANDLE mapFile = CreateFileMapping( file, 0, PAGE_READONLY, 0, fileSize, 0 );

    if( !mapFile )
    {
        CloseHandle( file );
        return 0;
    }

    void *ptr = MapViewOfFile( mapFile, FILE_MAP_READ, 0, 0, 0 );

    CloseHandle( mapFile );
    CloseHandle( file );

    return ptr;
}


bool Game::LoadWaveBank( IXACT3Engine* audioEngine, stXACTAudio& audio, char* waveBankFile )
{
    DWORD fileSize = 0;
    audio.waveBankData = LoadBankFile( waveBankFile, fileSize );

    if( FAILED( audioEngine->CreateInMemoryWaveBank( audio.waveBankData,
        fileSize, 0, 0, &audio.waveBank ) ) )
    {
        return false;
    }

    return true;
}


bool Game::LoadSoundBank( IXACT3Engine* audioEngine, stXACTAudio& audio, char* soundBankFile )
{
    DWORD fileSize = 0;
    audio.soundBankData = LoadBankFile( soundBankFile, fileSize );

    if( FAILED( audioEngine->CreateSoundBank( audio.soundBankData,
        fileSize, 0, 0, &audio.soundBank ) ) )
    {
        return false;
    }

   return true;
}