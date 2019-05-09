//#include "pch.h"
#include <string>
#include <fpdfview.h>
#include "PdfiumWindowsX86Crash.h"

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#endif

using namespace std;


int main()
{
    printProcessMemoryInfo();


    FPDF_InitLibrary();


    // FPDFBitmap_Create
    printf("\nFPDFBitmap_Create\n");

    for (int i = 0; i < 100; i++)
    {
        printf("%d ", i);

        FPDF_BITMAP bmp = FPDFBitmap_Create(2500, 3500, 1);

        unsigned long errId = FPDF_GetLastError();
        if (errId)
        {
            printf("\n[ERROR] FPDFBitmap_Create throws %lu\n", errId);
            printProcessMemoryInfo();
            break;
        }

        FPDFBitmap_Destroy(bmp);
    }


    // FPDFBitmap_CreateEx
    printf("\nFPDFBitmap_CreateEx\n");

    SetLastError(0);  // Reset error

    for (int i = 0; i < 100; i++)
    {
        printf("%d ", i);

        int width = 2500;
        int height = 3500;
        int channels = 4;

        char* buffer;
        try
        {
            buffer = new char[width * height * channels];
        }
        catch (const bad_alloc& e)
        {
            printf("\n[ERROR] FPDFBitmap_CreateEx buffer allocation failed: %s\n", e.what());
            printProcessMemoryInfo();
            break;
        }

        FPDF_BITMAP bmp = FPDFBitmap_CreateEx(width, height, FPDFBitmap_BGRA, buffer, width * channels);

        unsigned long errId = FPDF_GetLastError();
        if (errId)
        {
            printf("\n[ERROR] FPDFBitmap_CreateEx throws %lu\n", errId);
            printProcessMemoryInfo();
            break;
        }

        FPDFBitmap_Destroy(bmp);
        delete buffer;
    }

    FPDF_DestroyLibrary();
}


void printProcessMemoryInfo()
{
#ifdef _WIN32
    float MB_DIVISOR = 1000000;

    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

    printf("Process Virtual Memory: %.2f MB\n", pmc.PrivateUsage / MB_DIVISOR);
    printf("Process RAM: %.2f MB\n", pmc.WorkingSetSize / MB_DIVISOR);
    printf("Process Peak RAM: %.2f MB\n", pmc.PeakWorkingSetSize / MB_DIVISOR);
#else
    printf("No memory info available for this platform\n");
#endif
}
