//#include "pch.h"
#include <iostream>
#include <string>
#include <fpdfview.h>

using namespace std;


int main()
{
	FPDF_InitLibrary();


	// FPDFBitmap_Create
	cout << endl << "FPDFBitmap_Create" << endl;

	for (int i = 0; i < 100; i++) {
		cout << i << " ";

		FPDF_BITMAP bmp = FPDFBitmap_Create(2500, 3500, 1);

		unsigned long errId = FPDF_GetLastError();
		if (errId) {
			cout << endl << "FPDFBitmap_Create throws " << to_string(errId) << endl;
			break;
		}

		FPDFBitmap_Destroy(bmp);
	}


	// FPDFBitmap_CreateEx
	cout << endl << "FPDFBitmap_CreateEx" << endl;

	for (int i = 0; i < 100; i++) {
		cout << i << " ";

		int width = 2500;
		int height = 3500;
		int channels = 4;

		char* buffer = new char[width * height * 4];
		FPDF_BITMAP bmp = FPDFBitmap_CreateEx(width, height, FPDFBitmap_BGRA, buffer, width * channels);

		unsigned long errId = FPDF_GetLastError();
		if (errId) {
			cout << endl << "FPDFBitmap_CreateEx throws " << to_string(errId) << endl;
			break;
		}

		FPDFBitmap_Destroy(bmp);
		delete buffer;
	}

	FPDF_DestroyLibrary();
}
