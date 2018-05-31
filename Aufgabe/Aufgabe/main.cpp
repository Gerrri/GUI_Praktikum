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
void Sync_Edit_Scroll(HWND BezugDialog, int scroll_ID, int farb_wert, int edit_ID ) {
	SetScrollPos(GetDlgItem(BezugDialog, scroll_ID), SB_CTL, farb_wert, TRUE);
	wsprintf(Puffer, "%i", farb_wert);
	SetDlgItemText(BezugDialog, edit_ID, Puffer);
}



BOOL FAR PASCAL Farbwechsler_Dialog(HWND BezugDialog,UINT nachricht,WPARAM parameter1,LPARAM parameter2)
{
    //Skalierung der Scroll Bars
    static int minPos = 0;
    static int maxPos = 255;
	//Startwert der Farbwerte
	static int	R1 = 1, R1_E,
				R2 = 1, R2_E,
				G1 = 1, G1_E,
				G2 = 1, G2_E,
				B1 = 1, B1_E,
				B2 = 1, B2_E;


	//ID der Aktuellen Dialogs (der in der GUI betätigt wurde)
	int ID = GetDlgCtrlID((HWND)parameter2);
    

    switch(nachricht)
    {
	case EM_GETMODIFY:
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
		Sync_Edit_Scroll(BezugDialog, 120, R1, 100);
		Sync_Edit_Scroll(BezugDialog, 121, G1, 101);
		Sync_Edit_Scroll(BezugDialog, 122, B1, 102);
		Sync_Edit_Scroll(BezugDialog, 123, R2, 103);
		Sync_Edit_Scroll(BezugDialog, 124, G2, 104);
		Sync_Edit_Scroll(BezugDialog, 125, B2, 105);

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
		Sync_Edit_Scroll(BezugDialog, 120, R1, 100);
		Sync_Edit_Scroll(BezugDialog, 121, G1, 101);
		Sync_Edit_Scroll(BezugDialog, 122, B1, 102);
		Sync_Edit_Scroll(BezugDialog, 123, R2, 103);
		Sync_Edit_Scroll(BezugDialog, 124, G2, 104);
		Sync_Edit_Scroll(BezugDialog, 125, B2, 105);
		

        return TRUE;

    case WM_COMMAND   :
        
	

		switch(parameter1)
        {

        case IDOK:
          
			R1_E = GetDlgItemInt(BezugDialog, 100, NULL, FALSE);
			G1_E = GetDlgItemInt(BezugDialog, 101, NULL, FALSE);
			B1_E = GetDlgItemInt(BezugDialog, 102, NULL, FALSE);
			R2_E = GetDlgItemInt(BezugDialog, 103, NULL, FALSE);
			G2_E = GetDlgItemInt(BezugDialog, 104, NULL, FALSE);
			B2_E = GetDlgItemInt(BezugDialog, 105, NULL, FALSE);



			//Prüft ob sich Edittext Wert und Farbwert unterscheiden , wenn Ja Aktualisierung von Farbwert zu editTextWert
			if (R1 != R1_E && R1_E <= maxPos && R1_E >= minPos) { R1 = R1_E; }
			if (G1 != G1_E && G1_E <= maxPos && G1_E >= minPos) { G1 = G1_E; }
			if (B1 != B1_E && B1_E <= maxPos && B1_E >= minPos) { B1 = B1_E; }
			if (R2 != R2_E && R2_E <= maxPos && R2_E >= minPos) { R2 = R2_E; } 
			if (G2 != G2_E && G2_E <= maxPos && G2_E >= minPos) { G2 = G2_E; }
			if (B2 != B2_E && B2_E <= maxPos && B2_E >= minPos) { B2 = B2_E; }


			//Aktualisiere Alle Edits
			Sync_Edit_Scroll(BezugDialog, 120, R1, 100);
			Sync_Edit_Scroll(BezugDialog, 121, G1, 101);
			Sync_Edit_Scroll(BezugDialog, 122, B1, 102);
			Sync_Edit_Scroll(BezugDialog, 123, R2, 103);
			Sync_Edit_Scroll(BezugDialog, 124, G2, 104);
			Sync_Edit_Scroll(BezugDialog, 125, B2, 105);
			


			return TRUE;
        case IDCANCEL:
            
			EndDialog(BezugDialog,0);
            return TRUE;
			
        }





    }
    return FALSE;
}
