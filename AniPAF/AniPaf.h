/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT ANIMATION PAF (PDK ANIMATION FORMAT) MANAGER

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "PeanutInclude.h"

#ifndef		_BNSOFT_PEANUT_ANIPAF_H_
#define		_BNSOFT_PEANUT_ANIPAF_H_

//	AniPaf style type
#define		APSTY_CIRCULAR				0x80000000
#define		APSTY_FULLIMAGE				0x40000000

typedef		T_HANDLE				H_PAF;
typedef		T_HANDLE				H_ANIFILE;

typedef struct
{
	H_ANIFILE			hFile;
	QUAD				Style;
	T_POS				X;
	T_POS				Y;
	T_NUM				FrameNum;
	int					Duration;
	T_ID				CurrentFrameID;
	QUAD*				pFrameOffset;
	QUAD				CurrentImageWidth;
	QUAD				CurrentImageHeight;
	BYTE				CurrentImageColorBit;
	BYTE*				pCurrentImageData;
	int				CurrentImageDataSize;
	BOOL				bJpg;
	BYTE*				pFileBuf;
	int				nFileSize;
	int				nFilePos;
} TAniPaf;

typedef		TAniPaf			TAniPAF;
typedef		TAniPaf			stAniPAF;

#ifdef ANIPAF_EXPORTS
#define ANIPAF_API __declspec(dllexport)
#else
#define ANIPAF_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

ANIPAF_API extern H_PAF		AniPaf_Create(T_CSTR pcszFileName, QUAD Style, T_POS X, T_POS Y, int Duration);
ANIPAF_API extern BOOL		AniPaf_Destroy(H_PAF hAP);

ANIPAF_API extern BOOL		AniPaf_ModifyStyle(H_PAF hAP, QUAD RemoveStyle, QUAD AddStyle);
ANIPAF_API extern BOOL		AniPaf_SetPos(H_PAF hAP, T_POS X, T_POS Y);
ANIPAF_API extern BOOL		AniPaf_SetDuration(H_PAF hAP, int Duration);

ANIPAF_API extern T_SIZE		AniPaf_GetWidth(H_PAF hAP);
ANIPAF_API extern T_SIZE		AniPaf_GetHeight(H_PAF hAP);
ANIPAF_API extern T_NUM		AniPaf_GetColorNum(H_PAF hAP);
ANIPAF_API extern T_NUM		AniPaf_GetFrameNum(H_PAF hAP);
ANIPAF_API extern int		AniPaf_GetDuration(H_PAF hAP);
ANIPAF_API extern T_ID		AniPaf_GetCurrentFrameID(H_PAF hAP);
ANIPAF_API extern BYTE*		AniPaf_GetCurrentImage(H_PAF hAP);
ANIPAF_API extern BOOL		AniPaf_DrawFirstFrame(H_PAF hAP, BOOL bRefresh);
ANIPAF_API extern BOOL		AniPaf_DrawCurrentFrame(H_PAF hAP, BOOL bRefresh);
ANIPAF_API extern BOOL		AniPaf_DrawNextFrame(H_PAF hAP, BOOL bRefresh);
ANIPAF_API extern BOOL		AniPaf_DrawPrevFrame(H_PAF hAP, BOOL bRefresh);

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif	//	_BNSOFT_PEANUT_ANIPAF_H_