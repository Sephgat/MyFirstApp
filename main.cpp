#include <Windows.h>
#include <cstdio>
#include <iostream>
using namespace std;
LRESULT CALLBACK ApWindow(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Define the window class
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = ApWindow;
    wc.hInstance = hInstance;
    //style of the cursor
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    //Name the
    wc.lpszClassName = "MyWindowClass";
    RegisterClassEx(&wc);

    // "HWND" = window handler used to
    HWND hwnd = CreateWindowEx(0,"MyWindowClass","My First App",
        WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT,800, 600,
        NULL,NULL,hInstance,NULL);





    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


LRESULT CALLBACK ApWindow(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT windowSize;
    GetClientRect(hwnd, &windowSize);

    int middleX = (windowSize.right) / 2;
    int middleY = (windowSize.bottom) / 2;
    WORD SAYHELLO;
    WORD NAME;
    WORD TEXTBOX;


    switch (uMsg){

        case WM_CREATE: {
            //they have to go in this order otherwise it breaks
            // reasoning for this is due to the fact that the input will read anything that came before it, EX. in
            //this case if TEXTBOX was before NAME it would input what "please enter your name in the text box below"
            // more over, more study of this is required.

            //HMENU is the ID TAG in this case NAME is the way you can differ from the other boxes
            //L"string_name" just turns a normal sting into wstring which turns it into a smaller storage 16 bit => 8 bit
            // WS"" ES"" SS" ar just styling patterns
            // L"Edit" is what allow text to be entered
            // L"Static" is a read only. therefore no text cn be entered
            // L"Button" is the button prop.
            // after styling, it follows (x-axis,y-axis,length, height)
            //hwnd is the grouper that allow them to be on the same app window

            //middle
            CreateWindowW(L"Edit", L"Name", WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL | ES_CENTER, middleX - 100, middleY, 200, 25,
                          hwnd, (HMENU) NAME,NULL, NULL);
            //Top

            CreateWindowW(L"Static", L"please enter your name in the text box below", WS_VISIBLE | WS_BORDER | WS_CHILD| SS_LEFT, middleX - 150, middleY - 50, 300, 25,
                          hwnd,(HMENU) TEXTBOX,NULL , NULL);
            //Bottom
            CreateWindowW(L"Button", L"Say Hello", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, middleX - 50, middleY + 50, 100, 25, hwnd,
                          (HMENU) SAYHELLO, NULL, NULL);
        }
            break;
        case WM_COMMAND:


            if (LOWORD(wParam) == SAYHELLO && HIWORD(wParam) == BN_CLICKED)
            {
                // Get the text from the edit control
                wchar_t buffer[256];
                GetDlgItemTextW(hwnd, NAME, buffer, 256);

                //Message area Alex Remember this is the area where the popup is.
                wstring greeting = L"Hello, " + wstring(buffer) + L"!";
                MessageBoxW(hwnd, greeting.c_str(), L"Greeting", MB_OK);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


