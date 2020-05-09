#ifndef _BOOTVID_PCH_
#define _BOOTVID_PCH_

#include <ntifs.h>
#include <ndk/halfuncs.h>
#include <drivers/bootvid/bootvid.h>

/* Arch specific includes */
#if defined(_M_IX86) || defined(_M_AMD64)
#include "i386/pc/vga.h"
#include "i386/pc/pc.h"
#elif defined(_M_ARM)
#include "arm/arm.h"
#else
#error Unknown architecture
#endif

/* Define if FontData has upside down characters */
#undef CHAR_GEN_UPSIDE_DOWN

#define BOOTCHAR_HEIGHT 13
#define BOOTCHAR_WIDTH  8 // Each character line is encoded in a UCHAR.

#ifdef CHAR_GEN_UPSIDE_DOWN
# define GetFontPtr(_Char) &FontData[_Char * BOOTCHAR_HEIGHT] + BOOTCHAR_HEIGHT - 1;
# define FONT_PTR_DELTA (-1)
#else
# define GetFontPtr(_Char) &FontData[_Char * BOOTCHAR_HEIGHT];
# define FONT_PTR_DELTA (1)
#endif

/* Bitmap Header */
typedef struct tagBITMAPINFOHEADER
{
    ULONG biSize;
    LONG biWidth;
    LONG biHeight;
    USHORT biPlanes;
    USHORT biBitCount;
    ULONG biCompression;
    ULONG biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    ULONG biClrUsed;
    ULONG biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

/* Supported bitmap compression formats */
#define BI_RGB  0
#define BI_RLE4 2

/* Boot video standard colors */
#define COLOR_BLACK          0
#define COLOR_BLUE           1
#define COLOR_GREEN          2
#define COLOR_CYAN           3
#define COLOR_RED            4
#define COLOR_MAGENTA        5
#define COLOR_BROWN          6
#define COLOR_LIGHT_GRAY     7
#define COLOR_DARK_GRAY      8
#define COLOR_LIGHT_BLUE     9
#define COLOR_LIGHT_GREEN    10
#define COLOR_LIGHT_CYAN     11
#define COLOR_LIGHT_RED      12
#define COLOR_LIGHT_MAGENTA  13
#define COLOR_YELLOW         14
#define COLOR_WHITE          15
#define COLOR_TRANSPARENT    16
#define MAX_COLORS           16

typedef struct _PALETTE_ENTRY
{
    UCHAR Red;
    UCHAR Green;
    UCHAR Blue;
} PALETTE_ENTRY, *PPALETTE_ENTRY;

VOID
NTAPI
InitializePalette(VOID);

VOID
NTAPI
DisplayCharacter(
    _In_ CHAR Character,
    _In_ ULONG Left,
    _In_ ULONG Top,
    _In_ ULONG TextColor,
    _In_ ULONG BackColor
);

VOID
PrepareForSetPixel(VOID);

VOID
NTAPI
InitPaletteWithTable(
    _In_ PULONG Table,
    _In_ ULONG Count);

/*
 * Globals
 */
extern UCHAR VidpTextColor;
extern ULONG VidpCurrentX;
extern ULONG VidpCurrentY;
extern ULONG VidpScrollRegion[4];
extern UCHAR FontData[256 * BOOTCHAR_HEIGHT];

#endif /* _BOOTVID_PCH_ */
