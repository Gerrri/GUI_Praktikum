#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
HINSTANCE Instanz;
int PASCAL WinMain(HINSTANCE,HINSTANCE,LPSTR, int);
LRESULT CALLBACK Fensterfunktion (HWND, UINT, WPARAM, LPARAM);
BOOL FAR PASCAL UmrechnungsFunktion(HWND, UINT, WPARAM, LPARAM);





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
            DialogBox(Instanz,"Umrechnung",fenster,UmrechnungsFunktion);
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

BOOL FAR PASCAL UmrechnungsFunktion(HWND BezugDialog,UINT nachricht,WPARAM parameter1,LPARAM parameter2)
{
    char Puffer[40];
    double Temperatur;
    static int minPos = 1;
    static int maxPos = 3;
    static int nachKomma = 1;
    static int gewaehlteRichtung = 110;

    switch(nachricht)
    {
    case WM_INITDIALOG:
        CheckRadioButton(BezugDialog,110,111,gewaehlteRichtung);
        SetScrollRange(GetDlgItem(BezugDialog,120),SB_CTL,minPos,maxPos,FALSE);
        SetScrollPos(GetDlgItem(BezugDialog,120),SB_CTL,nachKomma,TRUE);
        wsprintf(Puffer,"%i",nachKomma);
        SetDlgItemText(BezugDialog,210,Puffer);

		
        return TRUE;

    case WM_HSCROLL   :
        switch(parameter1)
        {
        case SB_LINEUP:
            nachKomma--;
            break;
        case SB_LINEDOWN:
            nachKomma++;
            break;
        }
        if (nachKomma>maxPos)
            nachKomma = maxPos;
        if (nachKomma < minPos)
            nachKomma = minPos;
        SetScrollPos(GetDlgItem(BezugDialog,120),SB_CTL,nachKomma,TRUE);
        wsprintf(Puffer,"%i",nachKomma);
        SetDlgItemText(BezugDialog,210,Puffer);
        return TRUE;

    case WM_COMMAND   :
        switch(parameter1)
        {
        case 110 :
            gewaehlteRichtung = 110;
            return TRUE;
        case 111 :
            gewaehlteRichtung = 111;
            return TRUE;
        case IDOK:
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
            sprintf_s(Puffer,"%.*lf",nachKomma,Temperatur);
            SetDlgItemText(BezugDialog,130,Puffer);
            return TRUE;
        case IDCANCEL:
            EndDialog(BezugDialog,0);
            return TRUE;
        }
    }
    return FALSE;
}
