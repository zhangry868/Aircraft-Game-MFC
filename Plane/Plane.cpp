// Plane.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Plane.h"
#include "GameWorld.h"
#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HDC hdc,mdc ,bufdc,transbufdc;
HWND hWnd;
HBITMAP picture,bg,Laser,Bomb,General,Hp,Protect,boss1;
GameWorld game;
// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PLANE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PLANE));

	TranslateAccelerator(msg.hwnd, hAccelTable, &msg);
	// ����Ϣѭ��:
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		game.update();
		
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLANE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PLANE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   MoveWindow(hWnd , 10 , 10 , 1024 , 768 , true);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   hdc = GetDC(hWnd);
   mdc = CreateCompatibleDC(hdc);
   bufdc = CreateCompatibleDC(hdc);

   bmp = CreateCompatibleBitmap(hdc , 1024 ,768);
	SelectObject(mdc , bmp);

	picture = (HBITMAP)LoadImageA(NULL,"picture.bmp",IMAGE_BITMAP,720,400,LR_LOADFROMFILE);
	Laser = (HBITMAP)LoadImageA(NULL , "Laser.bmp", IMAGE_BITMAP,  20 , 20 , LR_LOADFROMFILE);
	Bomb = (HBITMAP)LoadImageA(NULL , "Bomb.bmp", IMAGE_BITMAP,  20 , 20 , LR_LOADFROMFILE);
	General = (HBITMAP)LoadImageA(NULL , "General.bmp", IMAGE_BITMAP,  20 , 20 , LR_LOADFROMFILE);
	Hp = (HBITMAP)LoadImageA(NULL , "Hp.bmp", IMAGE_BITMAP,  20 , 20 , LR_LOADFROMFILE);
	Protect = (HBITMAP)LoadImageA(NULL , "Protect.bmp", IMAGE_BITMAP,  20 , 20 , LR_LOADFROMFILE);
	bg = (HBITMAP)LoadImageA(NULL , "bg.bmp", IMAGE_BITMAP , 1031 , 768 , LR_LOADFROMFILE);
	boss1 = (HBITMAP)LoadImageA(NULL , "boss.bmp", IMAGE_BITMAP , 182 , 186 , LR_LOADFROMFILE);

	game.CreateEnemy();
	game.start();

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;


	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
		{
			//���ͼƬ
			DeleteDC(mdc);
			DeleteDC(bufdc);
			DeleteObject(picture);
			ReleaseDC(hWnd,hdc);
			PostQuitMessage(0);	
		}
		if(wParam == VK_UP)
		{
			game.OpenState(0);
		}		
		if(wParam == VK_LEFT)
		{
			game.OpenState(2);
		}	
		if(wParam ==  VK_RIGHT)
		{
			game.OpenState(3);
		}	
		if(wParam ==  VK_DOWN)
		{
			game.OpenState(1);
		}			
		if(wParam == VK_SPACE)
		{
			game.OpenState(4);
		}
		if(wParam == VK_RETURN)
		{
			game.Bomb();
		}
		break;
	case WM_KEYUP:
		if(wParam == VK_UP)
		{
			game.CloseState(0);
		}
		if(wParam == VK_DOWN)
		{
			game.CloseState(1);
		}
		if(wParam == VK_LEFT)
		{
			game.CloseState(2);
		}
		if(wParam == VK_RIGHT)
		{
			game.CloseState(3);
		}
		if(wParam == VK_SPACE)
		{
			game.CloseState(4);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		//���ͼƬ
		DeleteDC(mdc);
		DeleteDC(bufdc);
		DeleteObject(picture);
		ReleaseDC(hWnd,hdc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
