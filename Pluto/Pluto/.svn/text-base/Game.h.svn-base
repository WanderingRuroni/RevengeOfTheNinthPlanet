 #ifndef _GAME_H_
#define _GAME_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <dinput.h>
#include <xact3.h>
#include <xnamath.h>
#include <list>
#include <algorithm>
#include "GameTimer.h"
#include "GameSprite.h"
#include "FontManager.h"
#include "Pluto.h"
#include "Neptune.h"
#include "Background.h"
#include "SplashScreen.h"
#include "Level.h"
#include "Hud.h"


class GameTimer;
class GameSprite;
class FontManager;
class Pluto;
class Neptune;
class Hud;
class Background;
class SplashScreen;
class Level;


enum GameState { MENU = 0, GAME = 1, PAUSE = 2 };
enum ScreenState { START = 0, INSTRUCTIONS = 1, CREDITS = 2, VICTORY = 3, END = 4 };
enum HealthState { GREEN = 3, YELLOW = 2, RED = 1, NONE = 0 };
enum BulletType { PLUTO_REGULAR = 0, PLUTO_RAPID = 1, PLUTO_BEAM = 2, PLUTO_SHOTGUN = 3, PLUTO_HUGE = 4 };


// audio attributes
struct stXACTAudio
{
   IXACT3WaveBank *waveBank;
   IXACT3SoundBank *soundBank;
   void *waveBankData;
   void *soundBankData;
};


class Game
{
	public:
		Game( );
		virtual ~Game( );

		int GetGameState( );
		Hud* GetHud( );
		Pluto* GetPluto( );
		Neptune* GetNeptune( );
		float GetScreenWidth( );
		float GetScreenHeight( );
		float GetDeltaTime( );
		SplashScreen* GetSplashScreen( );
		Level* GetCurrentLevel( );

		// getters for the window
		HINSTANCE GetInstance();
		HWND GetWindow();
		GameTimer* GetTimer();

		void SetGameState( int state );
		void SetMousePosX( long mx );
		void SetMousePosY( long my );
		void SetMouseWheel( long mw );

		bool Initialize( HINSTANCE hInstance, HWND hwnd, GameTimer* timer );
		void Shutdown( );

		bool LoadContent( );
		void UnloadContent( );

		void Update( float dt );
		void Render( );

		void Reset( );
		void NextLevel( );
		void PlaySound( string sound );
		bool CompileD3DShader( char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer );
		bool SetupXACT( IXACT3Engine** audioEngine );
		bool LoadXACTAudio( IXACT3Engine* audioEngine, stXACTAudio& audio, char* waveBank, char* soundBank );
		void* LoadBankFile( char* filePath, DWORD& fileSize );
		bool LoadWaveBank( IXACT3Engine* audioEngine, stXACTAudio& audio, char* waveBankFile );
		bool LoadSoundBank( IXACT3Engine* audioEngine, stXACTAudio& audio, char* soundBankFile );

	private:
		HINSTANCE hInstance_;
		HWND hwnd_;
		GameTimer* timer_;

		D3D_DRIVER_TYPE driverType_;
		D3D_FEATURE_LEVEL featureLevel_;
		
		ID3D11Device* d3dDevice_;
		ID3D11DeviceContext* d3dContext_;
		IDXGISwapChain* swapChain_;
		ID3D11RenderTargetView* backBufferTarget_;
		
		XMMATRIX vpMatrix_;
		ID3D11BlendState* alphaBlendState_;

		// input
		LPDIRECTINPUT8 directInput_;
		LPDIRECTINPUTDEVICE8 keyboardDevice_;
		char keyboardKeys_[256];
		char prevKeyboardKeys_[256];
		LPDIRECTINPUTDEVICE8 mouseDevice_;
		DIMOUSESTATE mouseState_;
        DIMOUSESTATE prevMouseState_;
        long mousePosX_;
        long mousePosY_;
        long mouseWheel_;

		// sound
        stXACTAudio audioBanks_;
        IXACT3Engine* soundEngine_;

		int gameState_;
		int currentLevel_;
		bool isActive;

		Level* level1_;

		Pluto* pluto_;
		Background* background_;
		SplashScreen* splashScreen_;
		Hud* hud_;

		float screenWidth_;
		float screenHeight_;

		// temp
		float collisionDebug;
};

#endif