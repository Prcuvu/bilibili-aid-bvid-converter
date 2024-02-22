#define WINVER 0x0400
#define _WIN32_WINNT 0x0400
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define XOR_CODE (23442827791579ULL)
#define MASK_CODE (2251799813685247ULL)

#define MAX_AID (2251799813685248ULL)
#define MIN_AID (1ULL)

#define BASE (58ULL)
#define BV_LEN ((size_t)12)

static char const ALPHABET[BASE] = {
    'F', 'c', 'w', 'A', 'P', 'N', 'K', 'T', 'M', 'u', 'g', '3', 'G', 'V', '5', 'L',
    'j', '7', 'E', 'J', 'n', 'H', 'p', 'W', 's', 'x', '4', 't', 'b', '8', 'h', 'a',
    'Y', 'e', 'v', 'i', 'q', 'B', 'z', '6', 'r', 'k', 'C', 'y', '1', '2', 'm', 'U',
    'S', 'D', 'Q', 'X', '9', 'R', 'd', 'o', 'Z', 'f'
};

static WORD CALLBACK reverse(WCHAR character)
{
#define CASE(letter, number) case L##letter: return MAKEWORD(TRUE, number);

    switch (character) {
    CASE('F',  0) CASE('c',  1) CASE('w',  2) CASE('A',  3) CASE('P',  4) CASE('N',  5) CASE('K',  6) CASE('T',  7) CASE('M',  8) CASE('u',  9) CASE('g', 10) CASE('3', 11) CASE('G', 12) CASE('V', 13) CASE('5', 14) CASE('L', 15)
    CASE('j', 16) CASE('7', 17) CASE('E', 18) CASE('J', 19) CASE('n', 20) CASE('H', 21) CASE('p', 22) CASE('W', 23) CASE('s', 24) CASE('x', 25) CASE('4', 26) CASE('t', 27) CASE('b', 28) CASE('8', 29) CASE('h', 30) CASE('a', 31)
    CASE('Y', 32) CASE('e', 33) CASE('v', 34) CASE('i', 35) CASE('q', 36) CASE('B', 37) CASE('z', 38) CASE('6', 39) CASE('r', 40) CASE('k', 41) CASE('C', 42) CASE('y', 43) CASE('1', 44) CASE('2', 45) CASE('m', 46) CASE('U', 47)
    CASE('S', 48) CASE('D', 49) CASE('Q', 50) CASE('X', 51) CASE('9', 52) CASE('R', 53) CASE('d', 54) CASE('o', 55) CASE('Z', 56) CASE('f', 57)
    default:
        return MAKEWORD(FALSE, 0xFF);
    }

#undef CASE
}

HWND window = NULL;
HWND aid_edit = NULL;
HWND bvid_edit = NULL;
HWND to_bvid_button = NULL;
HWND to_aid_button = NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSW window_class;
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = WndProc;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = hInstance;
    window_class.hIcon = NULL;
    window_class.hCursor = LoadCursorW(NULL, MAKEINTRESOURCEW(32512));
    window_class.hbrBackground = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = L"bilibili-aid-bvid-converter";
    if (RegisterClassW(&window_class) == 0) {
        return 0;
    }
    RECT client_area = {0, 0, 300, 150};
    if (!AdjustWindowRect(&client_area, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE)) {
        return 0;
    }
    window = CreateWindowExW(WS_EX_TOPMOST, L"bilibili-aid-bvid-converter", L"Bilibili aid-bvid converter", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, client_area.right - client_area.left, client_area.bottom - client_area.top, NULL, NULL, hInstance, NULL);
    if (window == NULL) {
        return 0;
    }
    HFONT CourierNew = CreateFontW(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Courier New");
    aid_edit = CreateWindowExW(0L, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 5, 5, 290, 55, window, (HMENU)100, hInstance, NULL);
    if (aid_edit == NULL) {
        return 0;
    }
    (void)SendMessageW(aid_edit, WM_SETFONT, (WPARAM)CourierNew, TRUE);
    (void)SendMessageW(aid_edit, EM_LIMITTEXT, 18, 0);
    HFONT MSShellDlg = CreateFontW(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Shell Dlg");
    to_bvid_button = CreateWindowExW(0L, L"BUTTON", L"↓ aid→bvid", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 175, 65, 100, 20, window, (HMENU)102, hInstance, NULL);
    if (to_bvid_button == NULL) {
        return 0;
    }
    (void)SendMessageW(to_bvid_button, WM_SETFONT, (WPARAM)MSShellDlg, TRUE);
    bvid_edit = CreateWindowExW(0L, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 5, 90, 290, 55, window, (HMENU)101, hInstance, NULL);
    if (bvid_edit == NULL) {
        return 0;
    }
    (void)SendMessageW(bvid_edit, WM_SETFONT, (WPARAM)CourierNew, TRUE);
    (void)SendMessageW(bvid_edit, EM_LIMITTEXT, 12, 0);
    to_aid_button = CreateWindowExW(0L, L"BUTTON", L"↑ bvid→aid", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 25, 65, 100, 20, window, (HMENU)103, hInstance, NULL);
    if (to_aid_button == NULL) {
        return 0;
    }
    (void)SendMessageW(to_aid_button, WM_SETFONT, (WPARAM)MSShellDlg, TRUE);
    (void)ShowWindow(window, SW_SHOWDEFAULT);
    (void)UpdateWindow(window);
    MSG message;
    while (GetMessageW(&message, NULL, 0U, 0U)) {
        if (!IsDialogMessageW(window, &message)) {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }
    (void)DeleteObject(MSShellDlg);
    (void)DeleteObject(CourierNew);
    (void)DeleteObject(window_class.hbrBackground);
    return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WCHAR buffer[19] = {18};
    WCHAR temp;
    unsigned long long aid = 0ULL;

#define SWAP(list, x, y) { temp = list[x]; list[x] = list[y]; list[y] = temp; }

    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 102:
            (void)SendMessageW(aid_edit, EM_GETLINE, 0, (LPARAM)buffer);

            if (buffer[0] != L'a' && buffer[0] != L'A' || buffer[1] != L'v' && buffer[1] != L'V') {
                (void)MessageBoxW(hWnd, L"Invalid aid string", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                goto abort_102;
            }

            for (size_t i = 2; buffer[i] != L'\0'; i += 1) {
                if (buffer[i] < L'0' || buffer[i] > L'9') {
                    (void)MessageBoxW(hWnd, L"Invalid aid string", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                    goto abort_102;
                }
                aid = aid * 10ULL + (buffer[i] - L'0');
            }

            if (aid < MIN_AID) {
                (void)MessageBoxW(hWnd, L"aid value is too small", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                goto abort_102;
            }

            if (aid >= MAX_AID) {
                (void)MessageBoxW(hWnd, L"aid value is too large", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                goto abort_102;
            }

            buffer[0] = L'B';
            buffer[1] = L'V';
            buffer[2] = L'1';
            buffer[BV_LEN] = L'\0';
            aid = (MAX_AID | aid) ^ XOR_CODE;
            for (size_t i = BV_LEN - 1; aid != 0; i -= 1) {
                buffer[i] = ALPHABET[aid % BASE];
                aid /= BASE;
            }

            SWAP(buffer, 3, 9);
            SWAP(buffer, 4, 7);

            (void)SendMessageW(bvid_edit, WM_SETTEXT, 0, (LPARAM)buffer);

        abort_102:
            break;
        case 103:
            {
                size_t length = (size_t)SendMessageW(bvid_edit, EM_GETLINE, 0, (LPARAM)buffer);

                if (length == 0) {
                    (void)MessageBoxW(hWnd, L"bvid string is empty", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                    goto abort_103;
                }
                if (length < BV_LEN) {
                    (void)MessageBoxW(hWnd, L"bvid string is too short", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                    goto abort_103;
                }
                if (length > BV_LEN) {
                    (void)MessageBoxW(hWnd, L"bvid string is to long", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                    goto abort_103;
                }
            }

            if (buffer[0] != L'B' && buffer[0] != L'b' || buffer[1] != L'V' && buffer[1] != L'v' || buffer[2] != L'1') {
                (void)MessageBoxW(hWnd, L"bvid string must be prefixed with \"BV1\" case-insensitive", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                goto abort_103;
            }

            SWAP(buffer, 3, 9);
            SWAP(buffer, 4, 7);

            for (size_t i = 3; i < BV_LEN; i += 1) {
                WORD result = reverse(buffer[i]);
                if (!LOBYTE(result)) {
                    WCHAR const error_message[38] = {
                        L'b', L'v', L'i', L'd', L' ', L's', L't', L'r', L'i', L'n', L'g', L' ', L'c', L'o', L'n', L't', L'a', L'i', L'n', L's', L' ', L'i', L'n', L'v', L'a', L'l', L'i', L'd', L' ', L'l', L'e', L't', L't', L'e', L'r', L' ', buffer[i], L'\0'
                    };
                    (void)MessageBoxW(hWnd, error_message, L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                    goto abort_103;
                }
                aid = aid * BASE + (unsigned long long)HIBYTE(result);
            }

            if (aid >= (MAX_AID << 1)) {
                (void)MessageBoxW(hWnd, L"bvid value is too large", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                goto abort_103;
            }

            if (aid < MAX_AID) {
                (void)MessageBoxW(hWnd, L"bvid value is too small", L"Error", MB_ICONHAND | MB_OK | MB_DEFBUTTON1 | MB_APPLMODAL);
                goto abort_103;
            }

            aid = (aid & MASK_CODE) ^ XOR_CODE;

            {
                size_t i = 17;
                while (aid != 0ULL) {
                    buffer[i--] = aid % 10 + 0x30;
                    aid /= 10;
                }
                buffer[i--] = L'v';
                buffer[i] = L'a';

                (void)SendMessageW(aid_edit, WM_SETTEXT, 0, (LPARAM)(buffer + i));
            }
        abort_103:
            break;
        default:
            break;
        }
        return 0;
    default:
        return DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }

#undef SWAP
}
