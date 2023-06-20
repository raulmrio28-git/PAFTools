// AniPAF.c : Defines the exported functions for the DLL.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "AniPAF.h"

#define		DBGPRINT(Error, String)		printf_s("[E%04d] %s(%d) : %s", Error, __FILE__, __LINE__, String)

QUAD swap_uint32(QUAD val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

BYTE*		AniPaf_Decode1BitPafBuffer(BYTE *pResBuffer, BYTE *pInBuffer, QUAD nInSize) {
	QUAD nCountRun;
	QUAD nCountLiteral;
	BYTE bPixel;
	BYTE bRleValue;
	QUAD nTempValue;
	QUAD nTempOutSize = 0;
	BYTE bCurrentByte = 0;
	QUAD nBitCount = 0;

	while (nTempOutSize < nInSize) {
		nCountRun = 0;
		bRleValue = *pInBuffer++;
		switch (bRleValue & 0xC0)
		{
		case 0x00:
			nCountRun = bRleValue >> 1;
			bPixel = bRleValue & 1;
			break;
		case 0x40:
			if (bRleValue & 0x20) {
				nTempValue = *pInBuffer << 8 | pInBuffer[1];
				pInBuffer += 2;
				nCountRun = ((bRleValue & 0x1f) << 15) | nTempValue >> 1;
				bPixel = nTempValue & 1;
			}
			else {
				nTempValue = *pInBuffer++;
				nCountRun = ((bRleValue & 0x1f) << 7) | nTempValue >> 1;
				bPixel = nTempValue & 1;
			}
			break;
		case 0x80:
			for (nCountLiteral = 0; nCountLiteral < 6; nCountLiteral++) {
				bCurrentByte |= ((bRleValue >> (5 - nCountLiteral)) & 1) << (7 - nBitCount);
				nBitCount++;
				if (nBitCount == 8) {
					pResBuffer[nTempOutSize++] ^= bCurrentByte;
					bCurrentByte = 0;
					nBitCount = 0;
				}
			}
			break;
		case 0xc0:
			nTempValue = *pInBuffer++;

			if (!nTempValue) {
				for (nCountLiteral = 0; nCountLiteral < 6; nCountLiteral++) {
					bCurrentByte |= ((bRleValue >> (5 - nCountLiteral)) & 1) << (7 - nBitCount);
					nBitCount++;
					if (nBitCount == 8) {
						pResBuffer[nTempOutSize++] ^= bCurrentByte;
						bCurrentByte = 0;
						nBitCount = 0;
					}
				}
			}
			else {
				nTempValue |= (bRleValue & 0x3f) << 8;

				for (nCountLiteral = 0; nCountLiteral < 14; nCountLiteral++) {
					bCurrentByte |= ((nTempValue >> (13 - nCountLiteral)) & 1) << (7 - nBitCount);
					nBitCount++;
					if (nBitCount == 8) {
						pResBuffer[nTempOutSize++] ^= bCurrentByte;
						bCurrentByte = 0;
						nBitCount = 0;
					}
				}
			}
			break;
		}

		while (nCountRun--) {
			bCurrentByte |= bPixel << (7 - nBitCount);
			nBitCount++;
			if (nBitCount == 8) {
				pResBuffer[nTempOutSize++] ^= bCurrentByte;
				bCurrentByte = 0;
				nBitCount = 0;
			}
		}
	}
	if (nBitCount > 0) {
		*pResBuffer ^= bCurrentByte;
	}
	return pResBuffer;
}

BYTE*		AniPaf_Decode2BitPafBuffer(BYTE *pResBuffer, BYTE *pInBuffer, QUAD nInSize) {
	QUAD nCountRun;
	QUAD nCountLiteral;
	BYTE bPixel;
	BYTE bRleValue;
	QUAD nTempValue;
	QUAD nTempOutSize = 0;
	BYTE bCurrentByte = 0;
	QUAD nBitCount = 0;

	while (nTempOutSize < nInSize) {
		nCountRun = 0;
		bRleValue = *pInBuffer++;
		switch (bRleValue & 0xC0)
		{
		case 0x00:
			nCountRun = bRleValue >> 2;
			bPixel = bRleValue & 3;
			break;
		case 0x40:
			if (bRleValue & 0x20) {
				nTempValue = *pInBuffer << 8 | pInBuffer[1];
				pInBuffer += 2;
				nCountRun = ((bRleValue & 0x1f) << 14) | nTempValue >> 2;
				bPixel = nTempValue & 3;
			}
			else {
				nTempValue = *pInBuffer++;
				nCountRun = ((bRleValue & 0x1f) << 6) | nTempValue >> 2;
				bPixel = nTempValue & 3;
			}
			break;
		case 0x80:
			for (nCountLiteral = 0; nCountLiteral < 6; nCountLiteral += 2) {
				bCurrentByte |= ((bRleValue >> (4 - nCountLiteral)) & 3) << (6 - nBitCount);
				nBitCount += 2;
				if (nBitCount == 8) {
					pResBuffer[nTempOutSize++] ^= bCurrentByte;
					bCurrentByte = 0;
					nBitCount = 0;
				}
			}
			break;
		case 0xc0:
			nTempValue = *pInBuffer++;

			if (!nTempValue) {
				for (nCountLiteral = 0; nCountLiteral < 6; nCountLiteral += 2) {
					bCurrentByte |= ((bRleValue >> (4 - nCountLiteral)) & 3) << (6 - nBitCount);
					nBitCount += 2;
					if (nBitCount == 8) {
						pResBuffer[nTempOutSize++] ^= bCurrentByte;
						bCurrentByte = 0;
						nBitCount = 0;
					}
				}
			}
			else {
				nTempValue |= (bRleValue & 0x3f) << 8;

				for (nCountLiteral = 0; nCountLiteral < 14; nCountLiteral += 2) {
					bCurrentByte |= ((nTempValue >> (12 - nCountLiteral)) & 3) << (6 - nBitCount);
					nBitCount += 2;
					if (nBitCount == 8) {
						pResBuffer[nTempOutSize++] ^= bCurrentByte;
						bCurrentByte = 0;
						nBitCount = 0;
					}
				}
			}
			break;
		}

		while (nCountRun--) {
			bCurrentByte |= bPixel << (6 - nBitCount);
			nBitCount += 2;
			if (nBitCount == 8) {
				pResBuffer[nTempOutSize++] ^= bCurrentByte;
				bCurrentByte = 0;
				nBitCount = 0;
			}
		}
	}
	if (nBitCount > 0) {
		*pResBuffer ^= bCurrentByte;
	}
	return pResBuffer;
}

BYTE*		AniPaf_Decode8BitPafBuffer(BYTE *pResBuffer, BYTE *pInBuffer, QUAD nInSize, QUAD *pnOutSize)
{
	QUAD nCurrSize = 0;
	BYTE cTempVal, cPix;
	QUAD nCount = 0;
	QUAD nOutSize = 0;
	while (nCurrSize < nInSize)
	{
		cTempVal = *pInBuffer; //curr byte
		if ((cTempVal >> 6) == 0x3) //Is the curr byte a count?
		{
			if (cTempVal & 0x20) //Count over 32
			{
				if (cTempVal & 0x10) //Count is over 4095
				{
					nCount = pInBuffer[2] | (pInBuffer[1] << 8) | ((cTempVal & 0xf) << 16);
					cPix = pInBuffer[3];
					pInBuffer += 4;
					nCurrSize += 4;
				}
				else //Nope, count's between 33-4095
				{
					nCount = pInBuffer[1] | ((cTempVal & 0xf) << 8);
					cPix = pInBuffer[2];
					pInBuffer += 3;
					nCurrSize += 3;
				}
			}
			else //Nope, count's between 1-32
			{
				nCount = cTempVal & 0x1f;
				cPix = pInBuffer[1];
				pInBuffer += 2;
				nCurrSize += 2;
			}
			while (nCount--)
			{
				pResBuffer[nOutSize++] ^= cPix;
			}
		}
		else //Nope, treat it as pixel
		{
			cPix = *pInBuffer;
			pResBuffer[nOutSize++] ^= cPix;
			pInBuffer++;
			nCurrSize++;
		}

	}
	*pnOutSize = nOutSize;
	return pResBuffer;
}

BYTE*		AniPaf_Decode16BitPafBuffer(BYTE *pResBuffer, BYTE *pInBuffer, QUAD nInSize, QUAD *pnOutSize)
{
	QUAD nCurrSize = 0;
	BYTE cTempVal, cPix1, cPix2;
	QUAD nCount = 0;
	QUAD nOutSize = 0;
	while (nCurrSize < nInSize)
	{
		cTempVal = *pInBuffer; //curr byte
		nCount = 0;
		if ((cTempVal >> 6) == 0x3) //Is the curr byte a count?
		{
			if (cTempVal & 0x20) //Count over 32
			{
				if (cTempVal & 0x10) //Count is over 4095
				{
					nCount = pInBuffer[2] + (pInBuffer[1] << 8) + ((cTempVal & 0xf) << 16);
					cPix1 = pInBuffer[3];
					cPix2 = pInBuffer[4];
					pInBuffer += 5;
					nCurrSize += 5;
				}
				else //Nope, count's between 33-4095
				{
					nCount = pInBuffer[1] + ((cTempVal & 0xf) << 8);
					cPix1 = pInBuffer[2];
					cPix2 = pInBuffer[3];
					pInBuffer += 4;
					nCurrSize += 4;
				}
			}
			else //Nope, count's between 1-32
			{
				nCount = cTempVal & 0x1f;
				cPix1 = pInBuffer[1];
				cPix2 = pInBuffer[2];
				pInBuffer += 3;
				nCurrSize += 3;
			}
			while (nCount--)
			{
				pResBuffer[nOutSize++] ^= cPix1;
				pResBuffer[nOutSize++] ^= cPix2;
			}
		}
		else //Nope, treat it as pixel
		{
			cPix1 = *pInBuffer;
			cPix2 = pInBuffer[1];
			pResBuffer[nOutSize++] ^= cPix1;
			pResBuffer[nOutSize++] ^= cPix2;
			pInBuffer += 2;
			nCurrSize += 2;
		}

	}
	*pnOutSize = nOutSize;
	return pResBuffer;
}

BYTE*		AniPaf_Decode24BitPafBuffer(BYTE *pResBuffer, BYTE *pInBuffer, QUAD nInSize, QUAD *pnOutSize)
{
	QUAD nCurrSize = 0;
	BYTE cTempVal, cPix1, cPix2, cPix3;
	QUAD nCount = 0;
	QUAD nOutSize = 0;
	while (nCurrSize < nInSize)
	{
		cTempVal = *pInBuffer; //curr byte
		if ((cTempVal >> 6) == 0x3) //Is the curr byte a count?
		{
			if (cTempVal & 0x20) //Count over 32
			{
				if (cTempVal & 0x10) //Count is over 4095
				{
					nCount = pInBuffer[2] + (pInBuffer[1] << 8) + ((cTempVal & 0xf) << 16);
					cPix1 = pInBuffer[3];
					cPix2 = pInBuffer[4];
					cPix3 = pInBuffer[5];
					pInBuffer += 6;
					nCurrSize += 6;
				}
				else //Nope, count's between 33-4095
				{
					nCount = pInBuffer[1] + ((cTempVal & 0xf) << 8);
					cPix1 = pInBuffer[2];
					cPix2 = pInBuffer[3];
					cPix3 = pInBuffer[4];
					pInBuffer += 5;
					nCurrSize += 5;
				}
			}
			else //Nope, count's between 1-32
			{
				nCount = cTempVal & 0x1f;
				cPix1 = pInBuffer[1];
				cPix2 = pInBuffer[2];
				cPix3 = pInBuffer[3];
				pInBuffer += 4;
				nCurrSize += 4;
			}
			while (nCount-- != 0)
			{
				pResBuffer[nOutSize++] ^= cPix1;
				pResBuffer[nOutSize++] ^= cPix2;
				pResBuffer[nOutSize++] ^= cPix3;
			}
		}
		else //Nope, treat it as pixel
		{
			cPix1 = *pInBuffer;
			cPix2 = pInBuffer[1];
			cPix3 = pInBuffer[2];
			pResBuffer[nOutSize++] ^= cPix1;
			pResBuffer[nOutSize++] ^= cPix2;
			pResBuffer[nOutSize++] ^= cPix3;
			pResBuffer += 3;
			pInBuffer += 3;
			nCurrSize += 3;
		}

	}
	*pnOutSize = nOutSize;
	return pResBuffer;
}

BYTE*		AniPaf_Decode32BitPafBuffer(BYTE *pResBuffer, BYTE *pInBuffer, QUAD nInSize, QUAD *pnOutSize)
{
	QUAD nCurrSize = 0;
	BYTE cTempVal, cPix1, cPix2, cPix3, cPix4;
	QUAD nCount = 0;
	QUAD nOutSize = 0;
	while (nCurrSize < nInSize)
	{
		cTempVal = *pInBuffer; //curr byte
		if ((cTempVal >> 6) == 0x3) //Is the curr byte a count?
		{
			if (cTempVal & 0x20) //Count over 32
			{
				if (cTempVal & 0x10) //Count is over 4095
				{
					nCount = pInBuffer[2] + (pInBuffer[1] << 8) + ((cTempVal & 0xf) << 16);
					cPix1 = pInBuffer[3];
					cPix2 = pInBuffer[4];
					cPix3 = pInBuffer[5];
					cPix4 = pInBuffer[6];
					pInBuffer += 7;
					nCurrSize += 7;
				}
				else //Nope, count's between 33-4095
				{
					nCount = pInBuffer[1] + ((cTempVal & 0xf) << 8);
					cPix1 = pInBuffer[2];
					cPix2 = pInBuffer[3];
					cPix3 = pInBuffer[4];
					cPix4 = pInBuffer[5];
					pInBuffer += 6;
					nCurrSize += 6;
				}
			}
			else //Nope, count's between 1-32
			{
				nCount = cTempVal & 0x1f;
				cPix1 = pInBuffer[1];
				cPix2 = pInBuffer[2];
				cPix3 = pInBuffer[3];
				cPix4 = pInBuffer[4];
				pInBuffer += 5;
				nCurrSize += 5;
			}
			while (nCount-- != 0)
			{
				pResBuffer[nOutSize++] ^= cPix1;
				pResBuffer[nOutSize++] ^= cPix2;
				pResBuffer[nOutSize++] ^= cPix3;
				pResBuffer[nOutSize++] ^= cPix4;
			}
		}
		else //Nope, treat it as pixel
		{
			cPix1 = *pInBuffer;
			cPix2 = pInBuffer[1];
			cPix3 = pInBuffer[2];
			cPix4 = pInBuffer[3];
			pResBuffer[nOutSize++] ^= cPix1;
			pResBuffer[nOutSize++] ^= cPix2;
			pResBuffer[nOutSize++] ^= cPix3;
			pResBuffer[nOutSize++] ^= cPix4;
			pInBuffer += 4;
			nCurrSize += 4;
		}

	}
	*pnOutSize = nOutSize;
	return pResBuffer;
}

BOOL		AniPaf_DecodeFrame(TAniPaf *PafHandle, QUAD CurrentFrameID)
{
	QUAD nBuffSize; //compressed buffer size
	QUAD nCurrLen = 0; //length of buffer read...
	BYTE *pTempBuffer; //file read...
	BYTE *pTemp = PafHandle->pCurrentImageData;

	DBGPRINT(PN_ERR_FIRST, "Frame decode!!!!!!!!");
	if (!PafHandle || PafHandle->FrameNum <= CurrentFrameID || !PafHandle->CurrentImageColorBit)
	{
		if (!PafHandle)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP = NULL!!!");
		if (PafHandle->FrameNum <= CurrentFrameID)
			DBGPRINT(PN_ERR_OUT_OF_RANGE, "hAP->FrameNum over CurrentFrameID!!!");
		if (!PafHandle->CurrentImageColorBit)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->CurrentImageColorBit is not valid!!!");
		return FALSE;
	}
	nBuffSize = PafHandle->pFrameOffset[CurrentFrameID + 1] - PafHandle->pFrameOffset[CurrentFrameID];
	pTempBuffer = (BYTE*)malloc(nBuffSize);
	fseek((FILE*)PafHandle->hFile, PafHandle->pFrameOffset[CurrentFrameID], SEEK_SET);
	switch (PafHandle->CurrentImageColorBit)
	{
	case 18:
	case 32:
		fread(pTempBuffer, nBuffSize, 1, (FILE*)PafHandle->hFile);
		AniPaf_Decode32BitPafBuffer(pTemp, pTempBuffer, nBuffSize, &nCurrLen);
		break;
	case 24:
		fread(pTempBuffer, nBuffSize, 1, (FILE*)PafHandle->hFile);
		AniPaf_Decode24BitPafBuffer(pTemp, pTempBuffer, nBuffSize, &nCurrLen);
		break;
	case 16:
		fread(pTempBuffer, nBuffSize, 1, (FILE*)PafHandle->hFile);
		AniPaf_Decode16BitPafBuffer(pTemp, pTempBuffer, nBuffSize, &nCurrLen);
		break;
	case 8:
		fread(pTempBuffer, nBuffSize, 1, (FILE*)PafHandle->hFile);
		AniPaf_Decode8BitPafBuffer(pTemp, pTempBuffer, nBuffSize, &nCurrLen);
		break;
	case 2:
		fread(pTempBuffer, nBuffSize, 1, (FILE*)PafHandle->hFile);
		AniPaf_Decode2BitPafBuffer(pTemp, pTempBuffer, PafHandle->CurrentImageDataSize);
		break;
	case 1:
		fread(pTempBuffer, nBuffSize, 1, (FILE*)PafHandle->hFile);
		AniPaf_Decode1BitPafBuffer(pTemp, pTempBuffer, PafHandle->CurrentImageDataSize);
		break;
	}
	return TRUE;
}

void *zfmalloc(size_t size)
{
	void *pMyPtr = malloc(size);
	zeromem(pMyPtr, size);
	return pMyPtr;
}

BOOL		AniPaf_Init(TAniPaf *PAFStruct, T_CSTR pcszFileName, QUAD Style, T_POS X, T_POS Y, int Duration)
{
	int PtrsOffset = 0; //Depends on PAF type
	QUAD TempFrameNum = 0; //Acts as a i/j for frame point allocation
	QUAD TempOffset = 0; //Acts as a temp offset number
	int WidthBySize; // hAP->CurrentImageWidth * hAP->CurrentImageColorBit
	char TempBuffer[20]; //Temporary file buffer (max size is 20 for PAF2)

	if (!PAFStruct)
	{
		DBGPRINT(PN_ERR_INVALID_PARAM, "hAP = NULL!!!");
		return FALSE;
	}
	fopen_s(&PAFStruct->hFile, (char*)pcszFileName, "rb");
	if (!PAFStruct->hFile)
	{
		DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->hFile = NULL!!!");
		return FALSE;
	}
	fread(TempBuffer, 20, 1, PAFStruct->hFile);
	if (memcmp("PAF", TempBuffer, 3))
	{
		fclose((FILE*)PAFStruct->hFile);
		free(PAFStruct->hFile);
		DBGPRINT(PN_ERR_ILLIGAL_FORMAT, "<- PAF -> mark is not found. Illegal format of PAF.");
		return FALSE;
	}
	switch (TempBuffer[3])
	{
	case '1':
		PAFStruct->CurrentImageColorBit = TempBuffer[4];
		PAFStruct->CurrentImageWidth = (BYTE)TempBuffer[5];
		PAFStruct->CurrentImageHeight = (BYTE)TempBuffer[6];
		PAFStruct->FrameNum = (BYTE)TempBuffer[7];
		PtrsOffset = 8;
		break;
	case '2':
		PAFStruct->CurrentImageColorBit = *(QUAD*)&TempBuffer[4];
		PAFStruct->CurrentImageWidth = *(QUAD*)&TempBuffer[8];
		PAFStruct->CurrentImageHeight = *(QUAD*)&TempBuffer[12];
		PAFStruct->FrameNum = *(QUAD*)&TempBuffer[16];
		PtrsOffset = 20;
		break;
	case '3':
		PAFStruct->CurrentImageColorBit = TempBuffer[4];
		PAFStruct->CurrentImageWidth = *(QUAD*)&TempBuffer[5];
		PAFStruct->CurrentImageHeight = *(QUAD*)&TempBuffer[9];
		PAFStruct->FrameNum = (BYTE)TempBuffer[13];
		PtrsOffset = 14;
		break;
	}
	PAFStruct->Style = Style;
	PAFStruct->X = X;
	PAFStruct->Y = Y;
	PAFStruct->Duration = Duration;
	PAFStruct->CurrentFrameID = 0;
	fseek((FILE*)PAFStruct->hFile, -9, SEEK_END);
	fread(TempBuffer, 9, 1, (FILE*)PAFStruct->hFile);
	if (memcmp(TempBuffer, "EndOfPAF", 9))
	{
		fclose((FILE*)PAFStruct->hFile);
		DBGPRINT(PN_ERR_ILLIGAL_FORMAT, "<- EndOFPAF -> mark is not found. Illegal format of PAF.");
		return FALSE;
	}
	fseek((FILE*)PAFStruct->hFile, PtrsOffset, SEEK_SET);
	if (!PAFStruct->CurrentImageWidth
		|| !PAFStruct->CurrentImageHeight
		|| !PAFStruct->FrameNum
		|| PAFStruct->CurrentImageColorBit != 1 && PAFStruct->CurrentImageColorBit != 2 && PAFStruct->CurrentImageColorBit != 8 && PAFStruct->CurrentImageColorBit != 16 && PAFStruct->CurrentImageColorBit != 18 && PAFStruct->CurrentImageColorBit != 24 && PAFStruct->CurrentImageColorBit != 32
		|| (PAFStruct->pFrameOffset = (QUAD*)malloc(sizeof(QUAD)*(PAFStruct->FrameNum + 2)), !PAFStruct->pFrameOffset))
	{
		fclose((FILE*)PAFStruct->hFile);
		if (!PAFStruct->CurrentImageWidth)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->CurrentImageWidth = 0!!!");
		if (!PAFStruct->CurrentImageHeight)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->CurrentImageHeight = 0!!!");
		if (!PAFStruct->FrameNum)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->FrameNum = 0!!!");
		if (PAFStruct->CurrentImageColorBit != 1 && PAFStruct->CurrentImageColorBit != 2 && PAFStruct->CurrentImageColorBit != 8 && PAFStruct->CurrentImageColorBit != 16 && PAFStruct->CurrentImageColorBit != 18 && PAFStruct->CurrentImageColorBit != 24 && PAFStruct->CurrentImageColorBit != 32)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->CurrentImageColorBit is not valid!!!");
		if (!PAFStruct->pFrameOffset)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->OffsetBuffer = NULL!!!");
		return FALSE;
	}
	while (TempFrameNum <= PAFStruct->FrameNum)
	{
		fread((void*)&TempOffset, 4, 1, (FILE*)PAFStruct->hFile);
		PAFStruct->pFrameOffset[TempFrameNum++] = swap_uint32(TempOffset);
	}
	switch (PAFStruct->CurrentImageColorBit)
	{
	case 1:
		WidthBySize = PAFStruct->CurrentImageWidth >> 3;
		break;
	case 2:
		WidthBySize = PAFStruct->CurrentImageWidth >> 2;
		break;
	case 8:
		WidthBySize = PAFStruct->CurrentImageWidth;
		break;
	case 16:
		WidthBySize = 2 * PAFStruct->CurrentImageWidth;
		break;
	case 24:
		WidthBySize = 3 * PAFStruct->CurrentImageWidth;
		break;
	case 18:
	case 32:
		WidthBySize = 4 * PAFStruct->CurrentImageWidth;
		break;
	}
	PAFStruct->CurrentImageDataSize = WidthBySize * PAFStruct->CurrentImageHeight;
	PAFStruct->pCurrentImageData = (BYTE*)malloc(PAFStruct->CurrentImageDataSize + 1);
	if (!PAFStruct->pCurrentImageData)
	{
		DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->pCurrentImageData = NULL!!! Freeing hAP->pFrameOffset!!!");
		free(PAFStruct->pFrameOffset);
		fclose((FILE*)PAFStruct->hFile);
		return FALSE;
	}
	zeromem(PAFStruct->pCurrentImageData, PAFStruct->CurrentImageDataSize + 1);
	AniPaf_DecodeFrame(PAFStruct, 0);
	return TRUE;
}

H_PAF		AniPaf_Create(T_CSTR pcszFileName, QUAD Style, T_POS X, T_POS Y, int Duration)
{
	TAniPaf *PafHandle = (TAniPaf*)zfmalloc(sizeof(TAniPaf));
	DBGPRINT(PN_ERR_FIRST, "Initializing hAP");
	if (!PafHandle)
	{
		DBGPRINT(PN_ERR_INVALID_PARAM, "hAP = NULL!!!");
		return NULL;
	}
	if (!AniPaf_Init(PafHandle, pcszFileName, Style, X, Y, Duration))
	{
		free(PafHandle);
		DBGPRINT(PN_ERR_ERROR, "Function AniPaf_Init() returned FALSE!!!");
		return NULL;
	}
	return PafHandle;
}

BOOL		AniPaf_DestroyRest(TAniPaf *PAFStruct)
{
	if (!PAFStruct)
	{
		DBGPRINT(PN_ERR_INVALID_PARAM, "hAP = NULL!!!");
		return FALSE;
	}
	if (PAFStruct->pCurrentImageData)
	{
		free(PAFStruct->pCurrentImageData);
	}
	if (PAFStruct->pFrameOffset)
	{
		free(PAFStruct->pFrameOffset);
	}
	if (fclose((FILE*)PAFStruct->hFile)) //0 - OK, EOF - failure
	{
		DBGPRINT(PN_ERR_ERROR, "fclose(hAP->hFile) FAIL!!!");
		return FALSE;
	}
	return TRUE;
}

BOOL		AniPaf_Destroy(H_PAF hAP)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Destroy hAP!!!");
	if (!PafHandle || !AniPaf_DestroyRest(PafHandle))
	{
		DBGPRINT(PN_ERR_INVALID_PARAM, "hAP = NULL!!! Maybe already destroyed?");
		return FALSE;
	}
	free(PafHandle);
	return TRUE;
}

BOOL		AniPaf_ModifyStyle(H_PAF hAP, QUAD RemoveStyle, QUAD AddStyle)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Set Style");
	if (PafHandle)
	{
		PafHandle->Style = PafHandle->Style & ~RemoveStyle | AddStyle;
		return TRUE;
	}
}

BOOL		AniPaf_SetPos(H_PAF hAP, T_POS X, T_POS Y)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Set Position");
	if (PafHandle)
	{
		PafHandle->X = X;
		PafHandle->Y = Y;
		return TRUE;
	}
}

BOOL		AniPaf_SetDuration(H_PAF hAP, int Duration)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Setting Duration");
	if (PafHandle)
	{
		PafHandle->Duration = Duration;
		return TRUE;
	}
}

T_SIZE		AniPaf_GetWidth(H_PAF hAP)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Get Width");
	if (PafHandle && PafHandle->pCurrentImageData)
		return PafHandle->CurrentImageWidth;
}

T_SIZE		AniPaf_GetHeight(H_PAF hAP)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Get Height");
	if (PafHandle && PafHandle->pCurrentImageData)
		return PafHandle->CurrentImageHeight;
}

T_NUM		AniPaf_GetColorNum(H_PAF hAP)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Get Image BPP");
	if (PafHandle)
		return PafHandle->CurrentImageColorBit;
}

T_NUM		AniPaf_GetFrameNum(H_PAF hAP)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Get Frames");
	if (PafHandle)
		return PafHandle->FrameNum;
}

int			AniPaf_GetDuration(H_PAF hAP)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Get Frames");
	if (PafHandle)
		return PafHandle->Duration;
}

T_ID		AniPaf_GetCurrentFrameID(H_PAF hAP)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Get CurrentFrameID");
	if (PafHandle)
		return PafHandle->CurrentFrameID;
	else
		return -1;
}

BYTE		*AniPaf_GetCurrentImage(H_PAF hAP)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Get Frames");
	if (PafHandle)
		return PafHandle->pCurrentImageData;
}

BOOL		AniPaf_DrawCurrentFrame(H_PAF hAP, BOOL bRefresh)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Drawing recent frame");
	if (!PafHandle || !PafHandle->pCurrentImageData)
	{
		if (!PafHandle)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP = NULL!!!");
		if (!PafHandle->pCurrentImageData)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->pCurrentImageData = NULL!!!");
		return FALSE;
	}
	if (PafHandle->CurrentImageDataSize)
	{
		//place your draw frame code here...
	}
	else
	{
		//place your draw frame code here...
	}
	return TRUE;
}

BOOL		AniPaf_DrawFirstFrame(H_PAF hAP, BOOL bRefresh)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	int WidthBySize = 0; // r1
	int i; // r0
	DBGPRINT(PN_ERR_FIRST, "Draw first frame");
	if (!PafHandle || !PafHandle->pCurrentImageData)
	{
		if (!PafHandle)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP = NULL!!!");
		if (!PafHandle->pCurrentImageData)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->pCurrentImageData = NULL!!!");
		return FALSE;
	}
	switch (PafHandle->CurrentImageColorBit)
	{
	case 1:
		WidthBySize = PafHandle->CurrentImageWidth >> 3;
		break;
	case 2:
		WidthBySize = PafHandle->CurrentImageWidth >> 2;
		break;
	case 8:
		WidthBySize = PafHandle->CurrentImageWidth;
		break;
	case 16:
		WidthBySize = 2 * PafHandle->CurrentImageWidth;
		break;
	case 24:
		WidthBySize = 3 * PafHandle->CurrentImageWidth;
		break;
	case 18:
	case 32:
		WidthBySize = 4 * PafHandle->CurrentImageWidth;
		break;
	}
	PafHandle->CurrentImageDataSize = WidthBySize * PafHandle->CurrentImageHeight;
	PafHandle->CurrentFrameID = 0;
	zeromem(PafHandle->pCurrentImageData, PafHandle->CurrentImageDataSize + 1);
	AniPaf_DecodeFrame(PafHandle, 0);
	if (PafHandle->CurrentImageDataSize)
		return AniPaf_DrawCurrentFrame(hAP, bRefresh);
	return TRUE;
}

BOOL		AniPaf_DrawNextFrame(H_PAF hAP, BOOL bRefresh)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	DBGPRINT(PN_ERR_FIRST, "Drawing next frame");
	if (!PafHandle || !PafHandle->pCurrentImageData)
	{
		if (!PafHandle)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP = NULL!!!");
		if (!PafHandle->pCurrentImageData)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->pCurrentImageData = NULL!!!");
		return FALSE;
	}
	if (PafHandle->CurrentFrameID >= PafHandle->FrameNum - 1)
	{
		if ((int)PafHandle->Style < 0)
			return AniPaf_DrawFirstFrame((H_PAF)PafHandle, bRefresh);
	}
	PafHandle->CurrentFrameID++;
	AniPaf_DecodeFrame(PafHandle, PafHandle->CurrentFrameID);
	if (PafHandle->CurrentImageDataSize)
		return AniPaf_DrawCurrentFrame((H_PAF)PafHandle, bRefresh);
	return TRUE;
}

BOOL		AniPaf_DrawPrevFrame(H_PAF hAP, BOOL bRefresh)
{
	TAniPaf *PafHandle = (TAniPaf *)hAP;
	int WidthBySize = 0; // r1
	int i;
	DBGPRINT(PN_ERR_FIRST, "Drawing previous frame");
	if (!PafHandle || !PafHandle->pCurrentImageData)
	{
		if (!PafHandle)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP = NULL!!!");
		if (!PafHandle->pCurrentImageData)
			DBGPRINT(PN_ERR_INVALID_PARAM, "hAP->pCurrentImageData = NULL!!!");
		return FALSE;
	}
	if (PafHandle->CurrentFrameID)
	{
		AniPaf_DecodeFrame(PafHandle, PafHandle->CurrentFrameID);
		PafHandle->CurrentFrameID--;
	}
	else
	{
		PafHandle->CurrentFrameID = PafHandle->FrameNum - 1;
		switch (PafHandle->CurrentImageColorBit)
		{
		case 1:
			WidthBySize = PafHandle->CurrentImageWidth >> 3;
			break;
		case 2:
			WidthBySize = PafHandle->CurrentImageWidth >> 2;
			break;
		case 8:
			WidthBySize = PafHandle->CurrentImageWidth;
			break;
		case 16:
			WidthBySize = 2 * PafHandle->CurrentImageWidth;
			break;
		case 24:
			WidthBySize = 3 * PafHandle->CurrentImageWidth;
			break;
		case 18:
		case 32:
			WidthBySize = 4 * PafHandle->CurrentImageWidth;
			break;
		}
		zeromem(PafHandle->pCurrentImageData, WidthBySize * PafHandle->CurrentImageHeight + 1);
		for (i = 0; PafHandle->CurrentFrameID >= i; i++)
			AniPaf_DecodeFrame(PafHandle, i);
	}
	if (PafHandle->CurrentImageDataSize)
		return AniPaf_DrawCurrentFrame(hAP, bRefresh);
	return TRUE;
}
