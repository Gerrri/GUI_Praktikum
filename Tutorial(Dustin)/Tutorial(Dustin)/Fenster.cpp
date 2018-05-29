/*
#include <Windows.h>



//(Handle auf Window, Message typ, Paramter k�nnen je nach uMessage interpretiert werden)
LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:			//Wenn man hier unterscheiden will Anweisung+break pro Case (logisch)
	case WM_DESTROY:		//jetzt wir bei jedem fall der untere Code ausgef�hrt 
		PostQuitMessage(0);
		return(0);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	HWND hWnd;
	WNDCLASS  wc;
	MSG msg;
	
	//Strukt wird Initailisiert mit allen Attributen = NULL [also wie unten]
	// so m�ssen nur zu �ndernde Variablen ge�ndert werden
	wc = {};
	
	
	
	wc.style = CS_HREDRAW | CS_VREDRAW; // damit Ganzes Windows Aktualisiert wird (Vertikal und Horizontal [verordert])
	wc.lpfnWndProc = MessageHandler;						//Message Handler 
	wc.cbClsExtra = 0;										//UNKOWN -> Siehe Win Doku
	wc.cbWndExtra = 0;										//UNKOWN -> Siehe Win Doku
	wc.hInstance = hInstance;								//hInstance von oben
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);					// StandardLogo				NULL = Standard	-,
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				// StandardCursor			NULL = Standard	  -> Akutelle eintr�ge = Standard
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// Farbe des Windows		NULL = Standard	-�
	wc.lpszMenuName = NULL;									// Men� hier �bergeben
	wc.lpszClassName = "WINAPITest";						// Struktur wird an diesen Namen gebunden

	// wc muss in Windows Registriert werden
	RegisterClass(&wc);	 // hier kann es zum Fehler kommen 


	// Window Handler festlegen
	hWnd = CreateWindow("WINAPITest", "Windows Name (Oben)", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance,0);		
	
	// WS_OVERLAPPEDWINDOW setzt viele Parameter [Fenstereigenschaften]
	// CW_USEDEFAULT Windows darf Position aussuchen x + y
	// 800 & 600 Windows gr��e (Breite & H�he)
	// 0 -> Parent Window
	// 0 -> Men�
	// hInstance -> aktuelle Instanz
	// irgendwelche Paramter xD


	//Ruft Windows auf
	ShowWindow(hWnd, nCmdShow);
	SetForegroundWindow(hWnd);	// Fenster in Vordergrund	(nicht notwendig)
	SetFocus(hWnd);				// Focus auf Windows		(nicht notwendig)
	UpdateWindow(hWnd);			// Aktualisiert Windows -> (sollte gemacht werden)
	//ShowCursor(false); //Blende Maus Cursor aus (hahaha!) :D


	//Update des Windows -> Message auswerten

	//Events/Message abfragen
	while (true) {
		BOOL result = GetMessage(&msg,0,0,0); // Bekommt Message von Windows oder wartet darauf (MSG, Events auf ein Fenster Limitieren,....) -> Gibt BOOL zur�ck (ist int, warum auch immer)
		if (result > 0) {
			TranslateMessage(&msg);			// Msg �bersetzen
			DispatchMessage(&msg);			// Handled die Message in der CALLBACK
		}
		else {
			// Fehlerfall (result <=0)
			return result; 
		}
	}

	return 0;
}

*/