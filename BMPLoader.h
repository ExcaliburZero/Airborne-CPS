#pragma once
/// Cross Platform Bitmap functions and bitmap data structures

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "XPLMUtilities.h"

class BmpLoader {

public:
/// These need to be aligned
#pragma pack(push, ident, 2)
	typedef struct tagBMPFILEHEADER
	{
		short  bfType;
		int	   bfSize;
		short  bfReserved1;
		short  bfReserved2;
		int    bfOffBits;
	} BMPFILEHEADER;

	typedef struct tagBMPINFOHEADER
	{
		int     biSize;
		int     biWidth;
		int     biHeight;
		short   biPlanes;
		short   biBitCount;
		int     biCompression;
		int     biSizeImage;
		int     biXPelsPerMeter;
		int     biYPelsPerMeter;
		int     biClrUsed;
		int     biClrImportant;
	} BMPINFOHEADER;

	typedef struct	tagIMAGEDATA
	{
		unsigned char *	pData;
		int			Width;
		int			Height;
		int			Padding;
		short		Channels;
	} IMAGEDATA;

#pragma pack(pop, ident)

	static int		LoadBmp(const char *FilePath, IMAGEDATA *ImageData);
	static void		SwapRedBlue(IMAGEDATA *ImageData);

	/// Cross Platform Bitmap functions
	/// Functions to handle endian differeneces between windows, linux and mac.
#if APL
	static short Endian(short Data)
	{
		unsigned char *pBuffer = (unsigned char *)&Data;
		short Result = (short)(pBuffer[0] & 0xff) + ((short)(pBuffer[1] & 0xff) << 8);
		return(Result);
	}

	static int Endian(int Data)
	{
		unsigned char *pBuffer = (unsigned char *)&Data;

		int Result = (int)(pBuffer[0] & 0xff)
			+ ((int)(pBuffer[1] & 0xff) << 8)
			+ ((int)(pBuffer[2] & 0xff) << 16)
			+ ((int)(pBuffer[3] & 0xff) << 24);

		return(Result);
	}

	static void SwapEndian(short *Data)
	{
		*Data = Endian(*Data);
	}

	static void SwapEndian(int *Data)
	{
		*Data = Endian(*Data);
	}
#else
	/// Only the mac needs these so dummy functions for windows and linux.
	static void SwapEndian(short *Data) {}
	static void SwapEndian(int *Data) {}
#endif
};