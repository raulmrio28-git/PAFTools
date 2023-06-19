#pragma once
#ifdef RGBMANIPULATE_EXPORTS
#define RGBMANIPULATE_API __declspec(dllexport)
#else
#define RGBMANIPULATE_API __declspec(dllimport)
#endif

RGBMANIPULATE_API extern BOOL ConvertBufferToARGB32(BYTE *pBuff, QUAD *pOutBuff, QUAD nWidth, QUAD nHeight, BYTE nBPP);