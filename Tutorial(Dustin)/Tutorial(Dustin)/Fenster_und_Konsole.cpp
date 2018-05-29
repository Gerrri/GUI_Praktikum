/*
WICHTIG : Immer nur einer der Main cpp´s einkommentieren, sonst gibt es Linker Fehler (logisch)

	Gleicher Code wie Fenster.cpp mit Modifikation: 
		1.	"int WINAPI WinMain(...)" gegen "int main()" ausgetauscht wurde
		2.	HINSTANCE  wurde in main() selbst Definiert
		3.  showWindow() -> zweites Paramter: SW_SHOW=5, da Paramet aus WinMain fehlte
		4.	Testausgabe auf Konsole hinzugefügt
*/



#include <Windows.h>
#include <iostream> // Zur Testausgabe



//(Handle auf Window, Message typ, Paramter können je nach uMessage interpretiert werden)
LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:			//Wenn man hier unterscheiden will Anweisung+break pro Case (logisch)
	case WM_DESTROY:		//jetzt wir bei jedem fall der untere Code ausgeführt 
		PostQuitMessage(0);
		return(0);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int main() {

	HINSTANCE hInstance = GetModuleHandle(0);
	
	
	HWND hWnd;
	WNDCLASS  wc;
	MSG msg;
	
	//Strukt wird Initailisiert mit allen Attributen = NULL [also wie unten]
	// so müssen nur zu ändernde Variablen geändert werden
	wc = {};
	
	
	
	wc.style = CS_HREDRAW | CS_VREDRAW; // damit Ganzes Windows Aktualisiert wird (Vertikal und Horizontal [verordert])
	wc.lpfnWndProc = MessageHandler;						//Message Handler 
	wc.cbClsExtra = 0;										//UNKOWN -> Siehe Win Doku
	wc.cbWndExtra = 0;										//UNKOWN -> Siehe Win Doku
	wc.hInstance = hInstance;								//hInstance von oben
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);					// StandardLogo				NULL = Standard	-,
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				// StandardCursor			NULL = Standard	  -> Akutelle einträge = Standard
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// Farbe des Windows		NULL = Standard	-´
	wc.lpszMenuName = NULL;									// Menü hier Übergeben
	wc.lpszClassName = "WINAPITest";						// Struktur wird an diesen Namen gebunden

	// wc muss in Windows Registriert werden
	RegisterClass(&wc);	 // hier kann es zum Fehler kommen 


	// Window Handler festlegen
	hWnd = CreateWindow("WINAPITest", "Windows Name (Oben)", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance,0);		
	
	// WS_OVERLAPPEDWINDOW setzt viele Parameter [Fenstereigenschaften]
	// CW_USEDEFAULT Windows darf Position aussuchen x + y
	// 800 & 600 Windows größe (Breite & Höhe)
	// 0 -> Parent Window
	// 0 -> Menü
	// hInstance -> aktuelle Instanz
	// irgendwelche Paramter xD


	//Ruft Windows auf
	ShowWindow(hWnd, SW_SHOW);  
	SetForegroundWindow(hWnd);	// Fenster in Vordergrund	(nicht notwendig)
	SetFocus(hWnd);				// Focus auf Windows		(nicht notwendig)
	UpdateWindow(hWnd);			// Aktualisiert Windows -> (sollte gemacht werden)
	//ShowCursor(false); //Blende Maus Cursor aus (hahaha!) :D

	// Testausgabe auf der Konsole
	std::cout << "Test ausgabe auf der Console zum Debuggen  :D" << std::endl;


	//Update des Windows -> Message auswerten

	//Events/Message abfragen
	while (true) {
		BOOL result = GetMessage(&msg,0,0,0); // Bekommt Message von Windows oder wartet darauf (MSG, Events auf ein Fenster Limitieren,....) -> Gibt BOOL zurück (ist int, warum auch immer)
		if (result > 0) {
			TranslateMessage(&msg);			// Msg Übersetzen
			DispatchMessage(&msg);			// Handled die Message in der CALLBACK
		}
		else {
			// Fehlerfall (result <=0)
			return result; 
		}
	}

	return 0;
}

