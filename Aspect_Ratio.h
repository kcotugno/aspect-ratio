/*
 * Aspect_Ratio.h
 *
 * Copyright (c) 2011 Kevin Cotugno.
 *
 * Created on 6/24/11.
 */

#pragma once

#ifndef ASPECT_RATIO_H
#define ASPECT_RATIO_H

typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned short		u_int16;
typedef unsigned long		u_long;
typedef short int			int16;

#define PF_TABLE_BITS		12
#define PF_TABLE_SZ_16		4096

#include "AEConfig.h"

#ifdef AE_OS_WIN
	typedef unsigned short PixelType;
	#include <Windows.h>
#endif

#include "entry.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_Macros.h"
#include "Param_Utils.h"
#include "AE_EffectCBSuites.h"
#include "String_Utils.h"
#include "AE_GeneralPlug.h"
#include "AEFX_ChannelDepthTpl.h"
#include "AEGP_SuiteHandler.h"
#include "PF_Suite_Helper.h"

#include "Aspect_Ratio_Strings.h"

/* Versioning information */

#define	MAJOR_VERSION	1
#define	MINOR_VERSION	0
#define	BUG_VERSION		0
#define	STAGE_VERSION	PF_Stage_RELEASE
#define	BUILD_VERSION	1


enum
{
	ASPECT_RATIO_RECT_TYPE_TOP = 0,
	ASPECT_RATIO_RECT_TYPE_BOTTOM
};


/* Parameter defaults */

#define ASPECT_PRESET_NUM 5
#define ASPECT_PRESET_DFLT 4

#define ASPECT_RATIO_AMOUT_MIN	1.0f
#define ASPECT_RATIO_AMOUT_MAX	5.0f
#define ASPECT_RATIO_AMOUT_DFLT	2.40f
#define ASPECT_RATIO_AMOUT_PREC 2


enum {
	ASPECT_INPUT = 0,
	ASPECT_PRESET,
	ASPECT_AMOUNT,
	ASPECT_NUM_PARAMS
};

enum {
	ASPECT_PRESET_ID = 1,
	ASPECT_AMOUNT_ID
};

enum {
	ASPECT_PRESET_178 = 1,
	ASPECT_PRESET_185,
	ASPECT_PRESET_239,
	ASPECT_PRESET_240,
	ASPECT_PRESET_255,
	ASPECT_PRESET_CUSTOM
};


#ifdef __cplusplus
	extern "C" {
#endif
	
DllExport	PF_Err 
EntryPointFunc(	
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra) ;

#ifdef __cplusplus
}
#endif

#endif // ASPECT_RATIO_H