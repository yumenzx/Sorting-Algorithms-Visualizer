#ifndef UNICODE
#define UNICODE
#endif 


#include "visualizerFunction.h"
#include <iostream>
#include <thread>
#include <Windows.h>
#include <CommCtrl.h>


#define WINDOW_WIDTH 1220
#define WINDOW_HEIGHT 620

#define SORT_BUTTON 0
#define SHUFFLE_BUTTON 1

HWND hwndTrackNrSamples;
HWND hwndTrackSortingSpeed;

SortingMethod sortingMethod;
bool shouldRun;
bool shouldShuffle;
int n;
int sortingSpeed;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sorting Algorithm Visualizer App";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Sorting Algorithm Visualizer",    // Window text
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}


	HWND view = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 5, 5, 900, 570, hwnd, NULL, hInstance, NULL);
	visualizerArg visualizerArg(view,true,sortingMethod, shouldRun, shouldShuffle, n, sortingSpeed);

	n = 10;
	shouldRun = false;
	shouldShuffle = false;
	sortingSpeed = 0; // nu se foloseste inca
	sortingMethod = SortingMethod::BUBLE_SORT;

	std::thread t(visualizer, &visualizerArg);
	
	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	visualizerArg.appIsOpen = false;
	t.detach();

	return 0;
}

void createItems(HWND hwnd);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		createItems(hwnd);
		break;

	case WM_HSCROLL:

		n = SendMessage(hwndTrackNrSamples, TBM_GETPOS, 0, 0);
		sortingSpeed = SendMessage(hwndTrackSortingSpeed, TBM_GETPOS, 0, 0);

		break;

	case WM_COMMAND:
	{
		switch (wParam)
		{
		case SORT_BUTTON:
			shouldRun ^= true;
			break;
		case SHUFFLE_BUTTON:
			shouldShuffle = true;
			break;
		default:
			break;
		}

		if (HIWORD(wParam) == CBN_SELCHANGE)
			// If the user makes a selection from the list:
			//   Send CB_GETCURSEL message to get the index of the selected list item.
			//   Send CB_GETLBTEXT message to get the item.
			//   Display the item in a messagebox.
		{
			int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			//TCHAR ListItem[256];
		//	(TCHAR)SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT, (WPARAM)ItemIndex, (LPARAM)ListItem);
			//MessageBox(hwnd, (LPCWSTR)ListItem, TEXT("Item Selected"), MB_OK);

			switch (ItemIndex)
			{
			case 0:
				sortingMethod = SortingMethod::BUBLE_SORT;
				break;
			case 1:
				sortingMethod = SortingMethod::SELECTION_SORT;
				break;
			case 2:
				sortingMethod = SortingMethod::INSERTION_SORT;
				break;
			case 3:
				sortingMethod = SortingMethod::QUICK_SORT;
				break;
			case 4:
				sortingMethod = SortingMethod::MERGE_SORT;
				break;
			default:
				break;
			}
		}
	}

	return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void createItems(HWND hwnd)
{
	// DROP DOWN BOX
	// algorithm selection drop down box
	HWND hWndComboBox = CreateWindow(TEXT("COMBOBOX"), TEXT("drop down box"),
		CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, WINDOW_WIDTH - 200, 100, 150, 150, hwnd, NULL, NULL, NULL);
	// add items to combo box
	SendMessage(hWndComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT("Bubble Sort"));
	SendMessage(hWndComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT("Selection Sort"));
	SendMessage(hWndComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT("Insertion Sort"));
	SendMessage(hWndComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT("Quick Sort"));
	SendMessage(hWndComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT("Merge Sort"));
	// select the first item from combo box
	SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
	
	// BUTTONS
	// Sort button
	CreateWindow(TEXT("BUTTON"), TEXT("Sort"), WS_CHILD | WS_VISIBLE, WINDOW_WIDTH-200, 450, 80, 40, hwnd, (HMENU)SORT_BUTTON, NULL, NULL);

	// Shuffle button
	CreateWindow(TEXT("BUTTON"), TEXT("Shuffle"), WS_CHILD | WS_VISIBLE, WINDOW_WIDTH - 200, 500, 80, 40, hwnd, (HMENU)SHUFFLE_BUTTON, NULL, NULL);

	//TRACKBARS
	// nr of samples trackbar
	hwndTrackNrSamples = CreateWindowEx(0, TRACKBAR_CLASS, TEXT("nr of samples"), WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE, WINDOW_WIDTH - 250, 200, 200, 50, hwnd, NULL, NULL, NULL);
	SendMessage(hwndTrackNrSamples, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(10, 300)); // range
	SendMessage(hwndTrackNrSamples, TBM_SETPAGESIZE, 0, (LPARAM)10); // size of laps

	// sorting speed trackbar
	hwndTrackSortingSpeed = CreateWindowEx(0, TRACKBAR_CLASS, TEXT("sorting speed"), WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE, WINDOW_WIDTH - 250, 300, 200, 50, hwnd, NULL, NULL, NULL);
	SendMessage(hwndTrackNrSamples, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 100)); // range
	SendMessage(hwndTrackNrSamples, TBM_SETPAGESIZE, 0, (LPARAM)10); // size of laps
}