#include "Windows.h"
#include <memory.h>
#include "resource.h"
#include "GameTimer.h"
#include "Game.h"


LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );


// initialize the window
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow )
{
	UNREFERENCED_PARAMETER( prevInstance );
	UNREFERENCED_PARAMETER( cmdLine );

	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof( WNDCLASSEX );
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
	wndClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "PlutoWindowClass";
	wndClass.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ICON1 ) );
	wndClass.hIconSm = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ICON1 ) );

	if( !RegisterClassEx( &wndClass ) )
		return -1;

	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

	HWND hwnd = CreateWindowA( "PlutoWindowClass", "Pluto's Revenge", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL );

	if( !hwnd )
		return -1;

	ShowWindow( hwnd, cmdShow );

	Game game;
	GameTimer timer;

	// initialize the game
	bool result = game.Initialize( hInstance, hwnd, &timer );

	if( result == false )
		return -1;

	game.SetGameState( MENU );

	MSG msg = { 0 };

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			game.Update( timer.GetDeltaTime( ) );
			game.Render( );
			if( game.GetHud( )->GetSprite( )->GetCurrentAnimation( ) == "empty")
			{
				game.SetGameState( MENU );
				game.GetSplashScreen()->SetScreenState( END );
			}
			else if( game.GetNeptune( )->GetSprite( )->GetHealth( ) <= 0)
			{
				game.SetGameState( MENU );
				game.GetSplashScreen()->SetScreenState( VICTORY );
			}
		}
	}

	// shutdown
	// this calls game.Shutdown( )
	return static_cast<int>( msg.wParam );
}


LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT paintStruct;
    HDC hDC;

    switch( message )
    {
        case WM_PAINT:
            hDC = BeginPaint( hwnd, &paintStruct );
            EndPaint( hwnd, &paintStruct );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hwnd, message, wParam, lParam );
    }

    return 0;
}