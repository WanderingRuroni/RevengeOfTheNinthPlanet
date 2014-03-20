#include "Level.h"


// position of the end points of a line segment (used for collision)
struct Line
{
    XMFLOAT3 p1;
    XMFLOAT3 p2;
};


Level::Level( Game* game, ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* backBufferTarget, int levelID, float scrollSpeed )
{
	game_ = game;

	d3dDevice_ = d3dDevice;
	d3dContext_ = d3dContext;
	swapChain_ = swapChain;
	backBufferTarget_ = backBufferTarget;

	levelID_ = levelID;
	scrollSpeed_ = scrollSpeed;

	powerUpDrop = 0;

	switch( levelID_ )
	{
		case 1:
			// enemies
			asteroids_ = new Asteroid( game_,  d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );
			comets_ = new Comet( game_,  d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );
			gangstars_ = new Gangstar( game_,  d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );
			seahorses_ = new Seahorses( game_,  d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );
		
			// boss
			neptune_ = new Neptune( game_,  d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );

			// powerups
			satellites_ = new Satellites( game_,  d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );
			powerUps_ = new PowerUps( game_,  d3dDevice_, d3dContext_, swapChain_, backBufferTarget_ );

			break;

		default:
			break;
	}

	deathCooldown_ = 3.0f;
	srand(time(NULL));
}


Level::~Level( )
{
}


// GETTERS


float Level::GetScrollSpeed( )
{
	return scrollSpeed_;
}

int Level::GetPowerUpDrop()
{
	return powerUpDrop;
}

Neptune* Level::GetNeptune()
{
	return neptune_;
}


// INITIALIZER


void Level::Initialize( )
{
	// initialize asteroids
	if( asteroids_ != NULL )
		asteroids_->Initialize( );
	
	// initialize comets
	if( comets_ != NULL )
		comets_->Initialize( );

	// initialize gangstars
	if( gangstars_ != NULL )
		gangstars_->Initialize( );

	// initialize seahorses
	if( seahorses_ != NULL )
		seahorses_->Initialize( );
	
	// initialize neptune
	if( neptune_ != NULL )
		neptune_->Initialize( );

	// initialize powerups
	if( powerUps_ != NULL )
		powerUps_->Initialize( );

	SetupContent( );
}


// LOAD CONTENT


// only load managers of the assets in the level
bool Level::LoadContent( )
{
	// load enemies

	// load asteroids
	if( asteroids_ != NULL )
	{
		if( !asteroids_->LoadContent( ) )
			return false;
	}
	
	// load comets
	if( comets_ != NULL )
	{
		if( !comets_->LoadContent( ) )
			return false;
	}

	// load gangstars
	if( gangstars_ != NULL )
	{
		if( !gangstars_->LoadContent( ) )
			return false;
	}

	// load seahorses
	if( seahorses_ != NULL )
	{
		if( !seahorses_->LoadContent( ) )
			return false;
	}

	// load bosses

	// load neptune
	if( neptune_ != NULL )
	{
		if( !neptune_->LoadContent( ) )
			return false;
	}


	// load powerups
	if( powerUps_ != NULL )
	{
		if( !powerUps_->LoadContent( ) )
			return false;
	}

	return true;
}


void Level::SetupContent( )
{
	switch( levelID_ )
	{
		case 1:
			
#pragma region create all asteroids
	
			asteroids_->CreateAsteroid( XMFLOAT2( 450.0f, 1200.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 1300.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 1400.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 150.0f, 1500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 300.0f, 2000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 600.0f, 2100.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 450.0f, 2200.0f ), 0.0f );

			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 2300.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 600.0f, 2350.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 350.0f, 2400.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 2450.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 700.0f, 2500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 2550.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 450.0f, 2600.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 300.0f, 2650.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 2700.0f ), 0.0f );
			
			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 3000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 3000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 300.0f, 3000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 3000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 3000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 600.0f, 3000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 700.0f, 3000.0f ), 0.0f );

			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 4000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 4050.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 250.0f, 4100.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 4150.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 650.0f, 4200.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 150.0f, 4250.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 350.0f, 4300.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 550.0f, 4350.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 4400.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 450.0f, 4450.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 4500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 650.0f, 4550.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 4600.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 300.0f, 4650.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 4700.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 700.0f, 4750.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 4800.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 4850.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 550.0f, 4900.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 150.0f, 4950.0f ), 0.0f );

			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 5000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 5100.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 250.0f, 5200.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 600.0f, 5300.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 5400.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 700.0f, 5500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 350.0f, 5600.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 550.0f, 5600.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 5700.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 5800.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 600.0f, 5900.0f ), 0.0f );

			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 6500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 300.0f, 6500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 6500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 6500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 600.0f, 6500.0f ), 0.0f );

			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 7000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 7050.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 250.0f, 7100.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 7150.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 650.0f, 7200.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 150.0f, 7250.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 350.0f, 7300.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 550.0f, 7350.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 7400.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 450.0f, 7450.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 7500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 650.0f, 7550.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 7600.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 300.0f, 7650.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 7700.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 700.0f, 7750.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 7800.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 7850.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 550.0f, 7900.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 150.0f, 7950.0f ), 0.0f );

			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 9000.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 9050.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 250.0f, 9100.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 9150.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 650.0f, 9200.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 150.0f, 9250.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 350.0f, 9300.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 550.0f, 9350.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 9400.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 450.0f, 9450.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 9500.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 650.0f, 9550.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 500.0f, 9600.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 300.0f, 9650.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 100.0f, 9700.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 700.0f, 9750.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 400.0f, 9800.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 200.0f, 9850.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 550.0f, 9900.0f ), 0.0f );
			asteroids_->CreateAsteroid( XMFLOAT2( 150.0f, 9950.0f ), 0.0f );
#pragma endregion 

#pragma region create all comets

			comets_->CreateComet( XMFLOAT2( 350.0f, 1050.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 150.0f, 1100.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 1200.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 1300.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 1400.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 1500.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 1700.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 1800.0f ), 0.0f );
			
			comets_->CreateComet( XMFLOAT2( 100.0f, 1900.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 150.0f, 1925.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 1950.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 1975.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 2000.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 2025.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 2050.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 2075.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 700.0f, 2300.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 2325.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 2350.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 2375.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 2400.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 2425.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 2450.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 2475.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 400.0f, 3100.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 3125.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 3125.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 3150.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 3150.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 3175.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 3175.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 500.0f, 3300.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 3325.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 3325.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 3350.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 3350.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 3375.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 3375.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 300.0f, 3200.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 3225.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 3225.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 3250.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 3250.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 3275.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 150.0f, 3275.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 300.0f, 3600.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 3625.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 3650.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 3675.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 3700.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 3725.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 3750.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 3775.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 3800.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 750.0f, 3825.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 3850.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 3875.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 3900.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 3925.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 300.0f, 3950.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 3975.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 4000.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 4025.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 4050.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 4075.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 4100.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 4125.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 4150.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 750.0f, 4175.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 4200.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 4225.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 4250.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 4275.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 500.0f, 5000.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 5025.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 5025.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 5050.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 5050.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 5075.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 5075.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 400.0f, 5400.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 5425.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 5425.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 5450.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 5450.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 5475.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 5475.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 200.0f, 5800.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 5800.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 5825.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 5825.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 5850.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 5850.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 5875.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 5875.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 5900.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 5925.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 100.0f, 6000.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 6025.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 6050.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 700.0f, 6075.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 6100.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 6125.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 6150.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 6175.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 6200.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 6225.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 300.0f, 6250.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 6275.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 6300.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 6325.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 6350.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 6375.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 6400.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 6425.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 6450.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 6475.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 250.0f, 6500.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 6525.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 6550.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 6575.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 6600.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 700.0f, 6625.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 6650.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 6675.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 6700.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 6725.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 300.0f, 6750.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 700.0f, 6775.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 6800.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 6825.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 6850.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 6875.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 100.0f, 7000.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 7025.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 7050.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 700.0f, 7075.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 7100.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 7125.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 7150.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 7175.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 7200.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 7225.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 300.0f, 7250.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 7275.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 7300.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 7325.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 7350.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 7375.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 7400.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 7425.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 7450.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 7475.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 500.0f, 8000.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 8025.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 8025.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 8050.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 8050.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 8075.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 8075.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 400.0f, 8400.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 8425.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 8425.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 8450.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 8450.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 8475.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 8475.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 300.0f, 9250.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 9275.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 9300.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 9325.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 9350.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 9375.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 9400.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 9425.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 9450.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 9475.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 250.0f, 9500.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 9525.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 9550.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 9575.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 9600.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 700.0f, 9625.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 9650.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 9675.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 9700.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 9725.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 300.0f, 9750.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 700.0f, 9775.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 200.0f, 9800.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 9825.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 100.0f, 9850.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 9875.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 500.0f, 9500.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 9525.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 9525.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 400.0f, 9550.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 600.0f, 9550.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 650.0f, 9575.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 9575.0f ), 0.0f );

			comets_->CreateComet( XMFLOAT2( 400.0f, 9600.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 450.0f, 9625.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 350.0f, 9625.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 300.0f, 9650.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 500.0f, 9650.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 550.0f, 9675.0f ), 0.0f );
			comets_->CreateComet( XMFLOAT2( 250.0f, 9675.0f ), 0.0f );
#pragma endregion 

#pragma region create all gangstars
			
			gangstars_->CreateGangstar( XMFLOAT2( 100.0f, 1100.0f ), 0.0f );

			gangstars_->CreateGangstar( XMFLOAT2( 200.0f, 3100.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 300.0f, 3100.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 400.0f, 3100.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 500.0f, 3100.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 600.0f, 3100.0f ), 0.0f );

			gangstars_->CreateGangstar( XMFLOAT2( 300.0f, 4550.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 500.0f, 4550.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 200.0f, 4900.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 600.0f, 4900.0f ), 0.0f );

			gangstars_->CreateGangstar( XMFLOAT2( 100.0f, 5200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 300.0f, 5200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 500.0f, 5200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 700.0f, 5200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 200.0f, 5400.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 400.0f, 5400.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 600.0f, 5400.0f ), 0.0f );

			gangstars_->CreateGangstar( XMFLOAT2( 100.0f, 6200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 300.0f, 6200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 500.0f, 6200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 700.0f, 6200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 200.0f, 6400.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 400.0f, 6400.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 600.0f, 6400.0f ), 0.0f );
			
			gangstars_->CreateGangstar( XMFLOAT2( 200.0f, 7400.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 400.0f, 7400.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 600.0f, 7400.0f ), 0.0f );

			gangstars_->CreateGangstar( XMFLOAT2( 100.0f, 8200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 300.0f, 8200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 500.0f, 8200.0f ), 0.0f );
			gangstars_->CreateGangstar( XMFLOAT2( 700.0f, 8200.0f ), 0.0f );

			gangstars_->CreateGangstar( XMFLOAT2( 200.0f, 8500.0f ), 0.0f );

			gangstars_->CreateGangstar( XMFLOAT2( 550.0f, 8500.0f ), 0.0f );

			gangstars_->CreateGangstar( XMFLOAT2( 350.0f, 8600.0f ), 0.0f );
#pragma endregion 

#pragma region create all seahorses
		
			seahorses_->CreateSeahorse( XMFLOAT2( 300.0f, 1250.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 1400.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 200.0f, 1500.0f ), 0.0f );
			
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 2250.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 2300.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 2350.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 2250.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 2300.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 2350.0f ), 0.0f );

			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 3350.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 3400.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 3450.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 3500.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 3550.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 3600.0f ), 0.0f );

			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 3350.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 3400.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 3450.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 3500.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 3550.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 3600.0f ), 0.0f );

			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 7350.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 7400.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 7450.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 7350.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 7400.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 7450.0f ), 0.0f );

			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 7850.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 7900.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 300.0f, 7850.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 300.0f, 7900.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 500.0f, 7850.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 500.0f, 7900.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 7850.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 7900.0f ), 0.0f );

			seahorses_->CreateSeahorse( XMFLOAT2( 200.0f, 8350.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 200.0f, 8400.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 400.0f, 8350.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 500.0f, 8400.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 600.0f, 8350.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 600.0f, 8400.0f ), 0.0f );

			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 9050.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 200.0f, 9100.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 300.0f, 9050.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 400.0f, 9100.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 500.0f, 9050.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 600.0f, 9100.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 9050.0f ), 0.0f );

			seahorses_->CreateSeahorse( XMFLOAT2( 100.0f, 9650.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 200.0f, 9700.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 300.0f, 9650.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 400.0f, 9700.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 500.0f, 9650.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 600.0f, 9700.0f ), 0.0f );
			seahorses_->CreateSeahorse( XMFLOAT2( 700.0f, 9650.0f ), 0.0f );
#pragma endregion 

			// create neptune
			neptune_->CreateNeptune(  XMFLOAT2( 400.0f, 10500.0f ), 0.0f ); //900

			break;
		
		// setup other levels here

		default:
			break;
	}
}


// UNLOAD CONTENT


void Level::UnloadContent( )
{
	scrollingSprites_.clear( );
	
	// unload enemies

	// unload asteroids
	if( asteroids_ != NULL )
	{
		asteroids_->UnloadContent( );
	}

	// unload comets
	if( comets_ != NULL )
	{
		comets_->UnloadContent( );
	}

	// unload gangstars
	if( gangstars_ != NULL )
	{
		gangstars_->UnloadContent( );
	}

	// unload seahorses
	if( seahorses_ != NULL )
	{
		seahorses_->UnloadContent();
	}

	// unload bosses

	// unload neptune
	if( neptune_ != NULL )
	{
		neptune_->UnloadContent();
	}

	/*
	// unload powerups

	// unload satellites
	if( satellites_ != NULL )
	{
		satellites_->UnloadContent();
	}
	*/

	// unload powerups
	if( powerUps_ != NULL )
	{
		powerUps_->UnloadContent();
	}

}


// UPDATE


void Level::Update( float dt )
{
	// update enemies

	// update asteroids
	if( asteroids_ != NULL ) 
	{
		asteroids_->Update( dt );
	}

	// update comets
	if( comets_ != NULL )
	{
		comets_->Update( dt );
	}

	// update gangstars
	if( gangstars_ != NULL )
	{
		gangstars_->Update( dt );
	}

	// update seahorses
	if( seahorses_ != NULL )
	{
		seahorses_->Update( dt );
	}

	// update bosses

	// update neptune
	if( neptune_ != NULL )
	{
		neptune_->Update( dt );
	}

	/*
	// update powerups

	// update satellites
	if( satellites_ != NULL )
	{
		satellites_->Update( dt );
	}
	*/

	// update powerups
	if( powerUps_ != NULL )
	{
		powerUps_->Update( dt );
	}

	// check for collisions involving pluto
	if( game_->GetPluto()->GetSprite()->GetCurrentAnimation() == "pluto" )
	{
		// check for enemy/pluto collisons

		// check for asteroid collisions with pluto
		if( asteroids_ != NULL && !asteroids_->GetSprites( )->empty( ) )
		{
			CheckEnemyCollision( game_->GetPluto( )->GetSprite( ), asteroids_->GetSprites( ) );
		}

		// check for comet collisions with pluto
		if( comets_ != NULL && !comets_->GetSprites( )->empty( ) )
		{
			CheckEnemyCollision( game_->GetPluto( )->GetSprite( ), comets_->GetSprites( ) );
		}

		// check for pluto/gangstar related collisions
		if( gangstars_ != NULL )
		{
			// check for gangstar collisions with pluto
			if( !gangstars_->GetSprites( )->empty( ) )
			{
				CheckEnemyCollision( game_->GetPluto( )->GetSprite( ), gangstars_->GetSprites( ) );
			}

			// check for gangstar bullet collisions with pluto
			if( !gangstars_->GetBullets( )->GetActiveSprites( )->empty( ) )
			{
				CheckSpriteBulletCollision( game_->GetPluto( )->GetSprite( ), gangstars_->GetBullets( )->GetActiveSprites( ), gangstars_->GetBullets( )->GetInactiveSprites( ) );
			}
		}

		// check for pluto/seahorse related collisions
		if( seahorses_ != NULL )
		{
			// check for seahorse collisions with pluto
			if( !seahorses_->GetSprites( )->empty( ) )
			{
				CheckEnemyCollision( game_->GetPluto( )->GetSprite( ), seahorses_->GetSprites( ) );
			}

			// check for seahorse bullet collisions with pluto
			if( !seahorses_->GetBullets( )->GetActiveSprites( )->empty( ) )
			{
				CheckSpriteBulletCollision( game_->GetPluto( )->GetSprite( ), seahorses_->GetBullets( )->GetActiveSprites( ), seahorses_->GetBullets( )->GetInactiveSprites( ) );
			}
		}

		// check for pluto/neptune related collisions
		if( neptune_ != NULL )
		{
			// check for neptune collisions with pluto
			if(neptune_->GetSprite()->GetIsActive())
			{
				CheckBossCollision( game_->GetPluto( )->GetSprite( ), neptune_->GetSprite() );
			}

			// check for neptune seahorse collisions with pluto
			if( !neptune_->GetSeahorses()->GetSprites()->empty() )
			{
				CheckEnemyCollision( game_->GetPluto( )->GetSprite( ), neptune_->GetSeahorses()->GetSprites( ) );
			}

			// check for neptune seahorse bullet collisions with pluto
			if( !neptune_->GetSeahorses()->GetSprites()->empty() )
			{
				CheckSpriteBulletCollision( game_->GetPluto( )->GetSprite( ), neptune_->GetSeahorses()->GetBullets( )->GetActiveSprites( ), neptune_->GetSeahorses()->GetBullets( )->GetInactiveSprites( ) );
			}

			// check for neptune bullet collisions with pluto
			if( !neptune_->GetBullets( )->GetActiveSprites( )->empty( ) )
			{
				CheckSpriteBulletCollision( game_->GetPluto( )->GetSprite( ), neptune_->GetBullets( )->GetActiveSprites( ), neptune_->GetBullets( )->GetInactiveSprites( ) );
			}
		}
	}
	else if(game_->GetPluto()->GetSprite()->GetCurrentAnimation() == "invulnerable")
	{
		GameSprite* plutoSprite = game_->GetPluto( )->GetSprite( );
		float deathTime = plutoSprite->GetChangeAnimationTime( );

		if(deathTime >= deathCooldown_)
		{
			plutoSprite->SetCurrentAnimation("pluto");
		}
	}

	// check for enemy/pluto bullets related collisons

	// check for asteroid collisions with pluto's bullets
	if( asteroids_ != NULL && !asteroids_->GetSprites( )->empty( ) )
	{
		if( !game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( asteroids_->GetSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( asteroids_->GetSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( asteroids_->GetSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( asteroids_->GetSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( asteroids_->GetSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetInactiveSprites( ) );
	}

	// check for comet collisions with pluto's bullets
	if( comets_ != NULL && !comets_->GetSprites( )->empty( ) )
	{
		if( !game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( comets_->GetSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( comets_->GetSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( comets_->GetSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( comets_->GetSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( comets_->GetSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetInactiveSprites( ) );
	}

	// check for gangstar collisions with pluto's bullets
	if( gangstars_ != NULL && !gangstars_->GetSprites( )->empty( ) )
	{
		if( !game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( gangstars_->GetSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( gangstars_->GetSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( gangstars_->GetSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( gangstars_->GetSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( gangstars_->GetSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetInactiveSprites( ) );
	}

	// check for seahorse collisions with pluto's bullets
	if( seahorses_ != NULL && !seahorses_->GetSprites( )->empty( ) )
	{
		if( !game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( seahorses_->GetSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( seahorses_->GetSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( seahorses_->GetSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( seahorses_->GetSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetInactiveSprites( ) );

		if( !game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( )->empty( ) )
			CheckSpritesBulletCollision( seahorses_->GetSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetInactiveSprites( ) );
	}

	if( neptune_ != NULL )
	{
		// check for neptune collisions with pluto's bullets
		if(neptune_->GetCanBeHit())
		{
			if( !game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( )->empty( ) )
				CheckSpriteBulletCollision( neptune_->GetSprite( ), game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetInactiveSprites( ) );

			if( !game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( )->empty( ) )
				CheckSpriteBulletCollision( neptune_->GetSprite( ), game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetInactiveSprites( ) );

			if( !game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( )->empty( ) )
				CheckSpriteBulletCollision( neptune_->GetSprite( ), game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetInactiveSprites( ) );

			if( !game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( )->empty( ) )
				CheckSpriteBulletCollision( neptune_->GetSprite( ), game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetInactiveSprites( ) );

			if( !game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( )->empty( ) )
				CheckSpriteBulletCollision( neptune_->GetSprite( ), game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetInactiveSprites( ) );
		}

		// check neptunes seahorses for collisions with pluto's bullets
		if( !neptune_->GetSeahorses()->GetSprites( )->empty( ) )
		{
			if( !game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( )->empty( ) )
				CheckSpritesBulletCollision( neptune_->GetSeahorses()->GetSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRegular( )->GetInactiveSprites( ) );

			if( !game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( )->empty( ) )
				CheckSpritesBulletCollision( neptune_->GetSeahorses()->GetSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsRapid( )->GetInactiveSprites( ) );

			if( !game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( )->empty( ) )
				CheckSpritesBulletCollision( neptune_->GetSeahorses()->GetSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsBeam( )->GetInactiveSprites( ) );

			if( !game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( )->empty( ) )
				CheckSpritesBulletCollision( neptune_->GetSeahorses()->GetSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsShotgun( )->GetInactiveSprites( ) );

			if( !game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( )->empty( ) )
				CheckSpritesBulletCollision( neptune_->GetSeahorses()->GetSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetActiveSprites( ), game_->GetPluto( )->GetBulletsHuge( )->GetInactiveSprites( ) );
		}
	}

	// check for powerup collisions with pluto
	if( powerUps_ != NULL && !powerUps_->GetSprites( )->empty( ) )
	{
		CheckPowerUpCollision( game_->GetPluto( )->GetSprite( ), powerUps_->GetSprites( ) );
	}
}


// RENDER


void Level::Render( XMMATRIX* vpMatrix )
{
	// render enemies

	// render asteroids
	if( asteroids_ != NULL )
	{
		asteroids_->Render( vpMatrix );
	}

	// render comets
	if( comets_ != NULL )
	{
		comets_->Render( vpMatrix );
	}

	// render gangstars
	if( gangstars_ != NULL )
	{
		gangstars_->Render( vpMatrix );
	}

	// render seahorses
	if( seahorses_ != NULL )
	{
		seahorses_->Render( vpMatrix );
	}

	// render bosses

	// render neptune
	if( neptune_ != NULL )
	{
		neptune_->Render( vpMatrix );
	}

	/*
	// render powerups

	// render satellites
	if( satellites_ != NULL )
	{
		satellites_->Render( vpMatrix );
	}
	*/

	if( powerUps_ != NULL )
	{
		powerUps_->Render( vpMatrix );
	}

}


// ADDITIONAL FUNCTIONS


// check for collisions between a sprite and a list of sprites (pluto and enemies)
void Level::CheckEnemyCollision( GameSprite* sprite, list<GameSprite>* sprites )
{
	// check for collision between a sprite and a list of sprites
	for( list<GameSprite>::iterator s = sprites->begin( ); s != sprites->end( ); s++ )
	{
		if( DistanceCheck( *( sprite ), *s ) )
		{
			if( CollisionTest( *( sprite->GetCollisionBox( ) ), *s->GetCollisionBox( ) ) )
			{
				// if there is a collision, apply damage
				s->SetHealth( s->GetHealth( ) - sprite->GetAttack( ) );
				sprite->SetHealth( sprite->GetHealth( ) - s->GetAttack( ) );

				if(sprite == game_->GetPluto()->GetSprite())
				{
					sprite->SetCurrentAnimation("invulnerable");
					game_->PlaySound("thud");
				}
				
				if( s->GetHealth() <= 0 )
				{
					sprites->erase( s );
					break;
				}
			}
		}
	}
}


// check for collision between pluto and a boss sprite
void Level::CheckBossCollision( GameSprite* sprite, GameSprite* bossSprite )
{
	if( DistanceCheck( *( sprite ), *( bossSprite ) ) )
	{
		if( CollisionTest( *( sprite->GetCollisionBox( ) ), *( bossSprite->GetCollisionBox( ) ) ) )
		{
			// if there is a collision, apply damage
			sprite->SetHealth( sprite->GetHealth( ) - bossSprite->GetAttack( ) );

			if(sprite == game_->GetPluto()->GetSprite())
			{
				sprite->SetCurrentAnimation("invulnerable");
				game_->PlaySound("thud");
			}
		}
	}
}

// check for collisions between a sprite and a list of powerup sprites
void Level::CheckPowerUpCollision( GameSprite* sprite, list<GameSprite>* sprites )
{
	// get pluto
	Pluto* pluto = game_->GetPluto( );

	// get score
	float score = pluto->GetScore( );

	// check for collision between a sprite and a list of sprites
	for( list<GameSprite>::iterator s = sprites->begin( ); s != sprites->end( ); s++ )
	{
		if( DistanceCheck( *( sprite ), *s ) )
		{
			if( CollisionTest( *( sprite->GetCollisionBox( ) ), *s->GetCollisionBox( ) ) )
			{
				// if there is a collision, change weapon
				if(!s->GetCurrentAnimation().compare("normal"))
				{
					pluto->SetWeapon(0);
				}
				else if(!s->GetCurrentAnimation().compare("rapid"))
				{
					pluto->SetWeapon(1);
				}
				else if(!s->GetCurrentAnimation().compare("shotgun"))
				{
					pluto->SetWeapon(3);
				}
				else if(!s->GetCurrentAnimation().compare("huge"))
				{
					pluto->SetWeapon(4);
				}
				else if(!s->GetCurrentAnimation().compare("health"))
				{
					int plutoHealth = pluto->GetSprite()->GetHealth();
					if(plutoHealth != 3 && plutoHealth != 0)
					{
						plutoHealth++;
						pluto->GetSprite()->SetHealth(plutoHealth);
					}
					if(plutoHealth == 3)
						score += 50.0f;
				}
				sprites->erase( s );

				score += 5.0f;
				pluto->SetScore( score );

				break;
			}
		}
	}
}


// collision between bullets and one sprite (pluto or boss sprite, list of active bullet sprites, list of inactive bullet sprites)
void Level::CheckSpriteBulletCollision( GameSprite* sprite, list<GameSprite>* activeSprites, list<GameSprite>* inactiveSprites )
{
	// check for collision between active bullets and satellites
	list<GameSprite>::iterator as = activeSprites->begin( );
	while( as != activeSprites->end( ) )
	{
		bool collision = false;
		if( DistanceCheck( *as, *sprite ) )
		{
			collision = CollisionTest( ( *as->GetCollisionBox( ) ), *sprite->GetCollisionBox( ) );
			if( collision )
			{
				Pluto* pluto = game_->GetPluto( );
				float score = pluto->GetScore( );

				sprite->SetHealth(sprite->GetHealth() - as->GetAttack());

				// if the sprite is neptune
 				if(sprite == neptune_->GetSprite())
				{
					if(sprite->GetHealth() <= 0)
					{
						score += 50.0f;
					}
					else if(sprite->GetHealth() <= 60)
					{
						if(sprite->GetCurrentAnimation().compare("lowHealth") != 0)
						{
							sprite->SetCurrentAnimation("lowHealth");
						}
					}
					else if(sprite->GetHealth() <= 120)
					{
						if(sprite->GetCurrentAnimation().compare("halfHealth") != 0)
						{
							sprite->SetCurrentAnimation("halfHealth");
						}
					}

					game_->PlaySound( "smash" );
					score += 5.0f;
				}
				// if the sprite is pluto
				else if(sprite == game_->GetPluto()->GetSprite())
				{
					sprite->SetCurrentAnimation("invulnerable");
					game_->PlaySound("thud");
				}

				inactiveSprites->push_back(*as);
				as = activeSprites->erase(as);

				pluto->SetScore( score );
			}
		}
		if( !collision )
		{
			as++;
		}
	}
}


// collision between bullets and enemies (list of sprites, list of active bullet sprites, list of inactive bullet sprites)
void Level::CheckSpritesBulletCollision( list<GameSprite>* sprites, list<GameSprite>* activeSprites, list<GameSprite>* inactiveSprites )
{
	// check for collision between active bullets and satellites
	list<GameSprite>::iterator as = activeSprites->begin( );
	while( as != activeSprites->end( ) )
	{
		bool collision = false;
		for( list<GameSprite>::iterator s = sprites->begin( ); s != sprites->end( ); s++ )
		{
			if( DistanceCheck( *as, *s ) )
			{
				collision = CollisionTest( ( *as->GetCollisionBox( ) ), *s->GetCollisionBox( ) );
				if( collision )
				{
					Pluto* pluto = game_->GetPluto( );
					float score = pluto->GetScore( );

					score += 5.0f;
					
					s->SetHealth(s->GetHealth() - as->GetAttack());

 					if(s->GetHealth() <= 0)
					{
 						powerUpDrop = rand() % 20;
 						if(powerUpDrop >= 17)
						{
							powerUpDrop = rand() % 22;

							if(powerUpDrop < 5)
							{
								if(game_->GetPluto()->GetWeapon() == PLUTO_REGULAR)
								{
									powerUps_->CreatePowerUp( s->GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f), "rapid" );
								}
								else
								{
 									powerUps_->CreatePowerUp( s->GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f), "normal" );
								}
							}
							else if(powerUpDrop < 10)
							{
								if(game_->GetPluto()->GetWeapon() == PLUTO_RAPID)
								{
									powerUps_->CreatePowerUp( s->GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f), "shotgun" );
								}
								else
								{
									powerUps_->CreatePowerUp( s->GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f), "rapid" );
								}
							}
							else if(powerUpDrop < 15)
							{
								if(game_->GetPluto()->GetWeapon() == PLUTO_SHOTGUN)
								{
									powerUps_->CreatePowerUp( s->GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f), "huge" );
								}
								else
								{
									powerUps_->CreatePowerUp( s->GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f), "shotgun" );
								}
							}
							else if(powerUpDrop < 20)
							{
								if(game_->GetPluto()->GetWeapon() == PLUTO_HUGE)
								{
									powerUps_->CreatePowerUp( s->GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f), "normal" );
								}
								else
								{
									powerUps_->CreatePowerUp( s->GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f), "huge" );
								}
							}
							else
							{
								powerUps_->CreatePowerUp( s->GetPosition(), 0.0f, XMFLOAT2(1.0f, 1.0f), "health" ); 
							}
						}

						sprites->erase(s);
						score += 10.0f;
					}

					if(as->GetCurrentAnimation( ) != "PlutoHuge")
					{
						inactiveSprites->push_back(*as);
						as = activeSprites->erase(as);
					}

					pluto->SetScore( score );
					game_->PlaySound( "smash" );

					break;
				}
			}
		}
		if( !collision )
		{
			as++;
		}
	}
}


// test for collisions between two sprites
bool Level::CollisionTest( list<XMFLOAT3> box1, list<XMFLOAT3> box2 )
{
	// set up variables
	XMFLOAT3 pt1, pt2, pt3, pt4;
	float r, s, denom;
	Line l1, l2;

	// save every line in the first bounding box
	for( list<XMFLOAT3>::iterator b = box1.begin( ); next( b ) != box1.end(); b++ )
	{
		pt1 = *b;
		pt2 = *next( b );

		l1.p1 = pt1;
		l1.p2 = pt2;

		// save every line in the second bounding box
		for( list<XMFLOAT3>::iterator c = box2.begin( ); next( c ) != box2.end( ); c++ )
		{
			pt3 = *c;
			pt4 = *next( c );

			l2.p1 = pt3;
			l2.p2 = pt4;

			// check for collision between the lines
			denom = ( ( l1.p2.x - l1.p1.x ) * ( l2.p2.y - l2.p1.y ) ) - ( ( l1.p2.y - l1.p1.y ) * ( l2.p2.x - l2.p1.x ) );
				
			if( denom == 0 )
			{
				continue;
			}

			r = ( ( l1.p1.y - l2.p1.y ) * ( l2.p2.x - l2.p1.x ) - ( l1.p1.x - l2.p1.x ) * ( l2.p2.y - l2.p1.y ) ) / denom;
			s = ( ( l1.p1.y - l2.p1.y ) * ( l1.p2.x - l1.p1.x ) - ( l1.p1.x - l2.p1.x ) * ( l1.p2.y - l1.p1.y ) ) / denom;

			if( r <= 1 && r >= 0 )
			{
				if( s <= 1 && s >= 0 )
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool Level::DistanceCheck( GameSprite obj1, GameSprite obj2 )
{
	float safeDistance, distDiff;

	XMFLOAT2 obj1Position = obj1.GetPosition( );
	float obj1Width = obj1.GetWidth( );
	float obj1Height = obj1.GetHeight( );

	XMFLOAT2 obj2Position = obj2.GetPosition( );
	float obj2Width = obj2.GetWidth( );
	float obj2Height = obj2.GetHeight( );
	
	// find the squared distance between the objects
	distDiff = ( obj2Position.x - obj1Position.x ) * ( obj2Position.x - obj1Position.x ) + ( obj2Position.y - obj1Position.y ) * ( obj2Position.y - obj1Position.y );//((obj2.GetPosition().x * obj2.GetPosition().x) - (obj1.GetPosition().x * obj1.GetPosition().x)) + ((obj2.GetPosition().y * obj2.GetPosition().y) - (obj1.GetPosition().y * obj1.GetPosition().y));
	
	// find a minimum distance at which to check for collision between the objects
	if( obj1Width > obj1Height )
	{
		if( obj2Width > obj2Height )
		{
			safeDistance = obj1Width * obj1Width + obj2Width * obj2Width;
		}
		else
		{
			safeDistance = obj1Width * obj1Width + obj2Height * obj2Height;
		}
	}
	else
	{
		if( obj2Width > obj2Height)
		{
			safeDistance = obj1Height * obj1Height + obj2Width * obj2Width;
		}
		else
		{
			safeDistance = obj1Height * obj1Height + obj2Height * obj2Height;
		}
	}

	// if the distance between objects is within the safedistance, continue to check for collision
	if( distDiff <= ( safeDistance/2 ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}