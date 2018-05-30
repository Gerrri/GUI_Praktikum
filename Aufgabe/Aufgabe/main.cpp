#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
HINSTANCE Instanz;
int PASCAL WinMain(HINSTANCE,HINSTANCE,LPSTR, int);
LRESULT CALLBACK Fensterfunktion (HWND, UINT, WPARAM, LPARAM);



BOOL FAR PASCAL Farbwechsler_Dialog(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE dieseInstanz,HINSTANCE vorherigeInstanz,LPSTR Kommando, int Fenstertyp)
{
    MSG Meldung;
    HWND Hauptfenster;
    Instanz = dieseInstanz;
    if(!vorherigeInstanz)
    {
        WNDCLASSEX wincl;
        wincl.style = 0;
        wincl.lpfnWndProc = Fensterfunktion;
        wincl.cbClsExtra = 0;
        wincl.cbWndExtra = 0;
        wincl.hInstance = dieseInstanz;
        wincl.hIcon = 0;
        wincl.hIconSm = 0;
        wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
        wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
        wincl.lpszMenuName = "SimpelMenue";
        wincl.lpszClassName = "Einfach";
        wincl.cbSize = sizeof (WNDCLASSEX);
        if (!RegisterClassEx (&wincl))
            return 255;
    }
    Hauptfenster = CreateWindowEx (
                       0,
                       "Einfach",
                       "Hello MS Winworld",
                       WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT,
                       CW_USEDEFAULT,
                       CW_USEDEFAULT,
                       CW_USEDEFAULT,
                       NULL,
                       NULL,
                       dieseInstanz,
                       NULL );
    if (!Hauptfenster)
        return 255;
    ShowWindow (Hauptfenster, Fenstertyp);
    while (GetMessage (&Meldung, NULL, 0, 0))
        DispatchMessage(&Meldung);
    return Meldung.wParam;
}
LRESULT CALLBACK Fensterfunktion(HWND fenster,UINT nachricht,WPARAM parameter1,LPARAM parameter2)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static int x1,x2,y1,y2;


    switch(nachricht)
    {






    case WM_MOUSEMOVE:
        x1=x2;
        y1=y2;
        x2 = LOWORD(parameter2);
        y2 = HIWORD(parameter2);
        if(parameter1 & MK_LBUTTON)
        {
            InvalidateRect(fenster,NULL,FALSE);
        }
        return 0;


    case WM_RBUTTONDBLCLK:
        InvalidateRect(fenster,NULL,TRUE);
        return 0;


    case WM_COMMAND  :
        switch(parameter1)
        {

        case 100 :
            DialogBox(Instanz,"Umrechnung",fenster,Farbwechsler_Dialog);
            return 0;


        case 200 :
            SendMessage(fenster,WM_CLOSE,0,0L);
            return 0;
        }
        break;


    case WM_DESTROY  :
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(fenster,nachricht,parameter1,parameter2);
}



char Puffer[40];
//Aktualisiert die Scrollbar und schreibt in den EditText (farb_wert)
void Sync_Edit(HWND BezugDialog, int scroll_ID, int farb_wert, int edit_ID ) {
	SetScrollPos(GetDlgItem(BezugDialog, scroll_ID), SB_CTL, farb_wert, TRUE);
	wsprintf(Puffer, "%i", farb_wert);
	SetDlgItemText(BezugDialog, edit_ID, Puffer);
}
//chreibt in den EditText und Aktualiseirt die Scrollbar (farb_wert)
void Sync_Scroll(HWND BezugDialog, int scroll_ID, int farb_wert, int edit_ID) {
	wsprintf(Puffer, "%i", farb_wert);
	SetDlgItemText(BezugDialog, edit_ID, Puffer);
	SetScrollPos(GetDlgItem(BezugDialog, scroll_ID), SB_CTL, farb_wert, TRUE);
}



BOOL FAR PASCAL Farbwechsler_Dialog(HWND BezugDialog,UINT nachricht,WPARAM parameter1,LPARAM parameter2)
{
    //Skalierung der Scroll Bars
    static int minPos = 0;
    static int maxPos = 255;
	//Startwert der Farbwerte
	static int	R1 = 5,
				R2 = 1,
				G1 = 1,
				G2 = 1,
				B1 = 1,
				B2 = 1;


	//ID der Aktuellen Dialogs (der in der GUI betätigt wurde)
	int ID = GetDlgCtrlID((HWND)parameter2);
    

    switch(nachricht)
    {
	case  EM_GETMODIFY:
		R1 = 5;
		return TRUE;
    case WM_INITDIALOG:
		// Scroll Balken Range Festgelegt (0-255)
		SetScrollRange(GetDlgItem(BezugDialog, 120), SB_CTL, minPos, maxPos, FALSE);
		SetScrollRange(GetDlgItem(BezugDialog, 121), SB_CTL, minPos, maxPos, FALSE);
		SetScrollRange(GetDlgItem(BezugDialog, 122), SB_CTL, minPos, maxPos, FALSE);
		SetScrollRange(GetDlgItem(BezugDialog, 123), SB_CTL, minPos, maxPos, FALSE);
		SetScrollRange(GetDlgItem(BezugDialog, 124), SB_CTL, minPos, maxPos, FALSE);
		SetScrollRange(GetDlgItem(BezugDialog, 125), SB_CTL, minPos, maxPos, FALSE);
		SetScrollRange(GetDlgItem(BezugDialog, 126), SB_CTL, minPos, maxPos, FALSE);

		

        // Kreis Dialog erste Synchronisation mit Variablen
		Sync_Edit(BezugDialog, 120, R1, 100);
		Sync_Edit(BezugDialog, 121, G1, 101);
		Sync_Edit(BezugDialog, 122, B1, 102);
		Sync_Edit(BezugDialog, 123, R2, 103);
		Sync_Edit(BezugDialog, 124, G2, 104);
		Sync_Edit(BezugDialog, 125, B2, 105);

        return TRUE;

    case WM_HSCROLL   :

		
        switch(parameter1)
        {
        case SB_LINEUP:
			// Wenn Rechts gedrückt wurde wird überprüft, bei welchem Dialog
			if (ID == 120) { R1--; }
			if (ID == 121) { G1--; }
			if (ID == 122) { B1--; }
			if (ID == 123) { R2--; }
			if (ID == 124) { G2--; }
			if (ID == 125) { B2--; }
			break;

        case SB_LINEDOWN:
			// Wenn Links gedrückt wurde wird überprüft, bei welchem Dialog
			if (ID == 120) { R1++; }
			if (ID == 121) { G1++; }
			if (ID == 122) { B1++; }
			if (ID == 123) { R2++; }
			if (ID == 124) { G2++; }
			if (ID == 125) { B2++; }
			break;
        }

		//Wenn Wert > als MaxWert wird er auf MaxWert gesetzt
		if (R1 > maxPos) { R1 = maxPos; }
		if (G1 > maxPos) { G1 = maxPos; }
		if (B1 > maxPos) { B1 = maxPos; }
		if (R2 > maxPos) { R2 = maxPos; }
		if (G2 > maxPos) { G2 = maxPos; }
		if (B2 > maxPos) { B2 = maxPos; }



		//Wenn Wert < als MinWert wird er auf MinWert gesetzt
		if (R1 < minPos) { R1 = minPos; }
		if (G1 < minPos) { G1 = minPos; }
		if (B1 < minPos) { B1 = minPos; }
		if (R2 < minPos) { R2 = minPos; }
		if (G2 < minPos) { G2 = minPos; }
		if (B2 < minPos) { B2 = minPos; }


		//Aktualisiere Alle Edits
		Sync_Edit(BezugDialog, 120, R1, 100);
		Sync_Edit(BezugDialog, 121, G1, 101);
		Sync_Edit(BezugDialog, 122, B1, 102);
		Sync_Edit(BezugDialog, 123, R2, 103);
		Sync_Edit(BezugDialog, 124, G2, 104);
		Sync_Edit(BezugDialog, 125, B2, 105);
		

        return TRUE;

    case WM_COMMAND   :
        
	

		switch(parameter1)
        {
        case 100 :
			//Sync_Scroll(BezugDialog, 120, 25, 100);
            return TRUE;
        case 111 :
            
            return TRUE;
        case IDOK:
            /*
			GetDlgItemText(BezugDialog,100,Puffer,10);
            Temperatur = atof(Puffer);
            if (gewaehlteRichtung==111)
            {
                Temperatur = 9. * Temperatur/5.+32.;
            }
            else
            {
                Temperatur = 5./9.*(Temperatur - 32.);
            }
            sprintf_s(Puffer,"%.*lf",R1,Temperatur);
            SetDlgItemText(BezugDialog,130,Puffer);
            
			*/
			return TRUE;
        case IDCANCEL:
            
			EndDialog(BezugDialog,0);
            return TRUE;
			
        }





    }
    return FALSE;
}
