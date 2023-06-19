#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "..\AniPAF\PeanutInclude.h"
#include "Main.h"

QUAD Rgb332Pal[] =
{
	0xff000000,
	0xff000055,
	0xff0000aa,
	0xff0000ff,
	0xff002400,
	0xff002455,
	0xff0024aa,
	0xff0024ff,
	0xff004800,
	0xff004855,
	0xff0048aa,
	0xff0048ff,
	0xff006c00,
	0xff006c55,
	0xff006caa,
	0xff006cff,
	0xff009000,
	0xff009055,
	0xff0090aa,
	0xff0090ff,
	0xff00b400,
	0xff00b455,
	0xff00b4aa,
	0xff00b4ff,
	0xff00d800,
	0xff00d855,
	0xff00d8aa,
	0xff00d8ff,
	0xff00fc00,
	0xff00fc55,
	0xff00fcaa,
	0xff00fcff,
	0xff240000,
	0xff240055,
	0xff2400aa,
	0xff2400ff,
	0xff242400,
	0xff242455,
	0xff2424aa,
	0xff2424ff,
	0xff244800,
	0xff244855,
	0xff2448aa,
	0xff2448ff,
	0xff246c00,
	0xff246c55,
	0xff246caa,
	0xff246cff,
	0xff249000,
	0xff249055,
	0xff2490aa,
	0xff2490ff,
	0xff24b400,
	0xff24b455,
	0xff24b4aa,
	0xff24b4ff,
	0xff24d800,
	0xff24d855,
	0xff24d8aa,
	0xff24d8ff,
	0xff24fc00,
	0xff24fc55,
	0xff24fcaa,
	0xff24fcff,
	0xff480000,
	0xff480055,
	0xff4800aa,
	0xff4800ff,
	0xff482400,
	0xff482455,
	0xff4824aa,
	0xff4824ff,
	0xff484800,
	0xff484855,
	0xff4848aa,
	0xff4848ff,
	0xff486c00,
	0xff486c55,
	0xff486caa,
	0xff486cff,
	0xff489000,
	0xff489055,
	0xff4890aa,
	0xff4890ff,
	0xff48b400,
	0xff48b455,
	0xff48b4aa,
	0xff48b4ff,
	0xff48d800,
	0xff48d855,
	0xff48d8aa,
	0xff48d8ff,
	0xff48fc00,
	0xff48fc55,
	0xff48fcaa,
	0xff48fcff,
	0xff6c0000,
	0xff6c0055,
	0xff6c00aa,
	0xff6c00ff,
	0xff6c2400,
	0xff6c2455,
	0xff6c24aa,
	0xff6c24ff,
	0xff6c4800,
	0xff6c4855,
	0xff6c48aa,
	0xff6c48ff,
	0xff6c6c00,
	0xff6c6c55,
	0xff6c6caa,
	0xff6c6cff,
	0xff6c9000,
	0xff6c9055,
	0xff6c90aa,
	0xff6c90ff,
	0xff6cb400,
	0xff6cb455,
	0xff6cb4aa,
	0xff6cb4ff,
	0xff6cd800,
	0xff6cd855,
	0xff6cd8aa,
	0xff6cd8ff,
	0xff6cfc00,
	0xff6cfc55,
	0xff6cfcaa,
	0xff6cfcff,
	0xff900000,
	0xff900055,
	0xff9000aa,
	0xff9000ff,
	0xff902400,
	0xff902455,
	0xff9024aa,
	0xff9024ff,
	0xff904800,
	0xff904855,
	0xff9048aa,
	0xff9048ff,
	0xff906c00,
	0xff906c55,
	0xff906caa,
	0xff906cff,
	0xff909000,
	0xff909055,
	0xff9090aa,
	0xff9090ff,
	0xff90b400,
	0xff90b455,
	0xff90b4aa,
	0xff90b4ff,
	0xff90d800,
	0xff90d855,
	0xff90d8aa,
	0xff90d8ff,
	0xff90fc00,
	0xff90fc55,
	0xff90fcaa,
	0xff90fcff,
	0xffb40000,
	0xffb40055,
	0xffb400aa,
	0xffb400ff,
	0xffb42400,
	0xffb42455,
	0xffb424aa,
	0xffb424ff,
	0xffb44800,
	0xffb44855,
	0xffb448aa,
	0xffb448ff,
	0xffb46c00,
	0xffb46c55,
	0xffb46caa,
	0xffb46cff,
	0xffb49000,
	0xffb49055,
	0xffb490aa,
	0xffb490ff,
	0xffb4b400,
	0xffb4b455,
	0xffb4b4aa,
	0xffb4b4ff,
	0xffb4d800,
	0xffb4d855,
	0xffb4d8aa,
	0xffb4d8ff,
	0xffb4fc00,
	0xffb4fc55,
	0xffb4fcaa,
	0xffb4fcff,
	0xffd80000,
	0xffd80055,
	0xffd800aa,
	0xffd800ff,
	0xffd82400,
	0xffd82455,
	0xffd824aa,
	0xffd824ff,
	0xffd84800,
	0xffd84855,
	0xffd848aa,
	0xffd848ff,
	0xffd86c00,
	0xffd86c55,
	0xffd86caa,
	0xffd86cff,
	0xffd89000,
	0xffd89055,
	0xffd890aa,
	0xffd890ff,
	0xffd8b400,
	0xffd8b455,
	0xffd8b4aa,
	0xffd8b4ff,
	0xffd8d800,
	0xffd8d855,
	0xffd8d8aa,
	0xffd8d8ff,
	0xffd8fc00,
	0xffd8fc55,
	0xffd8fcaa,
	0xffd8fcff,
	0xfffc0000,
	0xfffc0055,
	0xfffc00aa,
	0xfffc00ff,
	0xfffc2400,
	0xfffc2455,
	0xfffc24aa,
	0xfffc24ff,
	0xfffc4800,
	0xfffc4855,
	0xfffc48aa,
	0xfffc48ff,
	0xfffc6c00,
	0xfffc6c55,
	0xfffc6caa,
	0xfffc6cff,
	0xfffc9000,
	0xfffc9055,
	0xfffc90aa,
	0xfffc90ff,
	0xfffcb400,
	0xfffcb455,
	0xfffcb4aa,
	0xfffcb4ff,
	0xfffcd800,
	0xfffcd855,
	0xfffcd8aa,
	0xfffcd8ff,
	0xfffcfc00,
	0xfffcfc55,
	0xfffcfcaa,
	0xfffcfcff
};

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
	int padding = 0;
	int currbit = 0;
	if (!pBuff||!pOutBuff||!nWidth||!nHeight||!nBPP) return FALSE;
	if (nBPP == 1) {
		for (y = 0; y < nHeight; y++) {
			for (x = 0; x < (nWidth/8); x++) {
				BYTE val = pBuff[y * (nWidth / 8) + x];
				for (currbit = 0; currbit < 8; currbit++)
					pOutBuff[y * nWidth + (x * 8) + currbit] = Conv1BppPixTo32((val >> (7 - currbit)) & 1);

			}
			padding = nWidth % 8;
		}
	}
	else if (nBPP == 2) {
		for (y = 0; y < nHeight; y++) {
			for (x = 0; x < nWidth; x += 4 - padding) {
				BYTE val = pBuff[y * (nWidth >> 2) + (x >> 2)];
				for (currbit = 0; currbit < 6; currbit+=2)
					pOutBuff[y * nWidth + (x * 4) + currbit] = Conv1BppPixTo32((val >> (4 - currbit)) & 3);
			}
			padding = nWidth % 4;
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