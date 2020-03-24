#include <wchar.h>
#include <Windows.h>

HWND window = NULL;
HWND av = NULL;
HWND bv = NULL;
HWND tobv = NULL;
HWND toav = NULL;

WCHAR table[59] = L"fZodR9XQDSUm21yCkr6zBqiveYah8bt4xsWpHnJE7jL5VG3guMTKNPAwcF";
unsigned long long x = 177451812ULL;
unsigned long long a = 8728348608ULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
size_t inverse(WCHAR);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSW windowclass;
    windowclass.style = CS_HREDRAW | CS_VREDRAW;
    windowclass.lpfnWndProc = WndProc;
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 0;
    windowclass.hInstance = hInstance;
    windowclass.hIcon = NULL;
    windowclass.hCursor = LoadCursorW(NULL, MAKEINTRESOURCEW(32512));
    windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    windowclass.lpszMenuName = NULL;
    windowclass.lpszClassName = L"avbv";
    if (RegisterClassW(&windowclass) == 0) {
        return 0;
    }
    RECT clientarea = {0, 0, 300, 150};
    if (!AdjustWindowRect(&clientarea, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE)) {
        return 0;
    }
    window = CreateWindowExW(WS_EX_TOPMOST, L"avbv", L"Bilibili av-bv converter", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, clientarea.right - clientarea.left, clientarea.bottom - clientarea.top, NULL, NULL, hInstance, NULL);
    if (window == NULL) {
        return 0;
    }
    HFONT CourierNew = CreateFontW(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Courier New");
    av = CreateWindowExW(0L, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 5, 5, 290, 55, window, (HMENU)100, hInstance, NULL);
    if (av == NULL) {
        return 0;
    }
    SendMessageW(av, WM_SETFONT, (WPARAM)CourierNew, TRUE);
    SendMessageW(av, EM_LIMITTEXT, 12, 0);
    bv = CreateWindowExW(0L, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 5, 90, 290, 55, window, (HMENU)101, hInstance, NULL);
    if (bv == NULL) {
        return 0;
    }
    SendMessageW(bv, WM_SETFONT, (WPARAM)CourierNew, TRUE);
    SendMessageW(bv, EM_LIMITTEXT, 12, 0);
    HFONT MSShellDlg = CreateFontW(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Shell Dlg");
    tobv = CreateWindowExW(0L, L"BUTTON", L"↓ AV→BV", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 175, 65, 100, 20, window, (HMENU)102, hInstance, NULL);
    if (tobv == NULL) {
        return 0;
    }
    SendMessageW(tobv, WM_SETFONT, (WPARAM)MSShellDlg, TRUE);
    toav = CreateWindowExW(0L, L"BUTTON", L"↑ BV→AV", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 25, 65, 100, 20, window, (HMENU)103, hInstance, NULL);
    if (toav == NULL) {
        return 0;
    }
    SendMessageW(toav, WM_SETFONT, (WPARAM)MSShellDlg, TRUE);
    ShowWindow(window, nShowCmd);
    UpdateWindow(window);
    MSG message;
    while (GetMessageW(&message, NULL, 0U, 0U)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    DeleteObject(MSShellDlg);
    DeleteObject(CourierNew);
    return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WCHAR buffer[13] = {12};
    unsigned long long id = 0LL;
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 102:
            SendMessageW(av, EM_GETLINE, 0, (LPARAM)buffer);
            if (buffer[0] != L'a' && buffer[0] != L'A' || buffer[1] != L'v' && buffer[1] != L'V') {
                MessageBoxW(hWnd, L"Invalid av identifier", L"Error", MB_ICONHAND | MB_OK);
                goto abort_102;
            }
            for (size_t i = 2; buffer[i] != L'\0'; i += 1) {
                if (buffer[i] < L'0' || buffer[i] > L'9') {
                    MessageBoxW(hWnd, L"Invalid av identifier", L"Error", MB_ICONHAND | MB_OK);
                    goto abort_102;
                }
                id = id * 10 + (buffer[i] - L'0');
            }
            if (id == 0ULL) {
                MessageBoxW(hWnd, L"Invalid av identifier", L"Error", MB_ICONHAND | MB_OK);
                goto abort_102;
            }
            id = (id ^ x) + a;
            buffer[0] = L'B';
            buffer[1] = L'V';
            buffer[2] = L'1';
            buffer[3] = table[id / (58 * 58) % 58];
            buffer[4] = table[id / (58 * 58 * 58 * 58) % 58];
            buffer[5] = L'4';
            buffer[6] = table[id / (58 * 58 * 58 * 58 * 58) % 58];
            buffer[7] = L'1';
            buffer[8] = table[id / (58 * 58 * 58) % 58];
            buffer[9] = L'7';
            buffer[10] = table[id / 58 % 58];
            buffer[11] = table[id % 58];
            SendMessageW(bv, WM_SETTEXT, 0, (LPARAM)buffer);
        abort_102:
            break;
        case 103:
            SendMessageW(bv, EM_GETLINE, 0, (LPARAM)buffer);
            if (lstrlenW(buffer) != 12 || buffer[0] != L'B' && buffer[0] != L'b' || buffer[1] != L'V' && buffer[1] != L'v' || buffer[2] != L'1' || buffer[5] != L'4' || buffer[7] != L'1' || buffer[9] != L'7') {
                MessageBoxW(hWnd, L"Invalid bv identifier", L"Error", MB_ICONHAND | MB_OK);
                break;
            }
            id += inverse(buffer[11]);
            id += inverse(buffer[10]) * 58;
            id += inverse(buffer[3]) * 58 * 58;
            id += inverse(buffer[8]) * 58 * 58 * 58;
            id += inverse(buffer[4]) * 58 * 58 * 58 * 58;
            id += inverse(buffer[6]) * 58 * 58 * 58 * 58 * 58;
            id = id - a ^ x;
            swprintf(buffer, 13, L"av%llu", id);
            SendMessageW(av, WM_SETTEXT, 0, (LPARAM)buffer);
            break;
        default:
            break;
        }
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

size_t inverse(WCHAR ch)
{
    for (size_t i = 0; i < 58; i += 1) {
        if (table[i] == ch) {
            return i;
        }
    }
    return 58;
}
