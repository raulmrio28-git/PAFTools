#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "..\AniPAF\PeanutInclude.h"
#include "Main.h"

QUAD	Conv1BppPixTo32(BYTE myPix)
{
	if (myPix == 0)
		return 0xffffffff;
	if (myPix == 1)
		return 0xff000000;
}

QUAD	Conv2BppPixTo32(BYTE myPix)
{
	if (myPix == 0)
		return 0xffffffff;
	if (myPix == 1)
		return 0xff555555;
	if (myPix == 2)
		return 0xffaaaaaa;
	if (myPix == 3)
		return 0xff000000;
}

BOOL ConvertBufferToARGB32(BYTE *pBuff, QUAD *pOutBuff, QUAD nWidth, QUAD nHeight, BYTE nBPP)
{
	int myCurrPixels = 0;
	int x = 0, y = 0;
	int currbit = 0;
	int currwidth = 0;
	if (!pBuff||!pOutBuff||!nWidth||!nHeight||!nBPP) return FALSE;
	if (nBPP == 1) {
		currwidth = nWidth + (((nWidth % 8) != 0) * 8);
		for (y = 0; y < nHeight; y++) {
			for (x = 0; x < currwidth; x+=8) {
				BYTE val = pBuff[y * (currwidth>>3) + (x>>3)];
				for (currbit = 0; currbit < 8 && (x+currbit) < nWidth; currbit++)
					pOutBuff[y * nWidth + x + currbit] = Conv1BppPixTo32((val>>(7-currbit)) & 0x1);
			}
		}
	}
	if (nBPP == 2) {
		currwidth = nWidth + (((nWidth % 4) != 0) * 4);
		for (y = 0; y < nHeight; y++) {
			for (x = 0; x < currwidth; x += 4) {
				BYTE val = pBuff[y * (currwidth >> 2) + (x >> 2)];
				for (currbit = 0; currbit < 4 && (x + currbit) < nWidth; currbit++)
					pOutBuff[y * nWidth + x + currbit] = Conv2BppPixTo32((val >> (6 - currbit*2)) & 0x3);
			}
		}
	}
	else if (nBPP == 8) {
		for (y = 0; y < nHeight; y++) {
			for (x = 0; x < nWidth; x++) {
				BYTE val = pBuff[y * nWidth + x];
				pOutBuff[y * nWidth + x] = (val & 0x7) << 5 | ((val>>3) & 0x7) << 13 | ((val >> 6) & 0x3) << 22 | 0xff000000;
			}
		}
	}
	else if (nBPP == 16) {
		for (y = 0; y < nHeight; y++) {
			for (x = 0; x < nWidth; x++) {
				WORD val = pBuff[2* (y * nWidth + x)] | pBuff[(2 * (y * nWidth + x))+1] << 8;
				pOutBuff[y * nWidth + x] = (val & 0x1f) << 3 | ((val >> 5) & 0x3f) << 10 | ((val >> 11) & 0x1f) << 19 | 0xff000000;
			}
		}
	}
	else if (nBPP == 18) {
		for (y = 0; y < nHeight; y++) {
			for (x = 0; x < nWidth; x++) {
				QUAD val = pBuff[4 * (y * nWidth + x)] | pBuff[(4 * (y * nWidth + x)) + 1] << 8 | pBuff[(4 * (y * nWidth + x)) + 2] << 16 | pBuff[(4 * (y * nWidth + x)) + 3] << 24;
				pOutBuff[y * nWidth + x] = ((val >> 14) & 0x3f) << 2 | ((val >> 20) & 0x3f) << 10 | ((val>>26) & 0x3f) << 18 | 0xff000000;
			}
		}
	}
	else if (nBPP == 24) {
		for (y = 0; y < nHeight; y++) {
			for (x = 0; x < nWidth; x++) {
				QUAD val = pBuff[3 * (y * nWidth + x)] | pBuff[(3 * (y * nWidth + x)) + 1] << 8 | pBuff[(3 * (y * nWidth + x)) + 2] << 16;
				pOutBuff[y * nWidth + x] = val | 0xff000000;
			}
		}
	}
	else if (nBPP == 32) {
		for (y = 0; y < nHeight; y++) {
			for (x = 0; x < nWidth; x++) {
				QUAD val = pBuff[4 * (y * nWidth + x)] | pBuff[(4 * (y * nWidth + x)) + 1] << 8 | pBuff[(4 * (y * nWidth + x)) + 2] << 16 | pBuff[(4 * (y * nWidth + x)) + 3] << 24;
				pOutBuff[y * nWidth + x] = val;
			}
		}
	}
	return TRUE;
}