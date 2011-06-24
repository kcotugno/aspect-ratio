/*
 * Aspect_Ratio_Strings.cpp
 *
 * Copyright (c) 2011 Kevin Cotugno.
 *
 * Created on 6/24/11.
 */
#include "Aspect_Ratio.h"

typedef struct {
	unsigned long	index;
	char			str[256];
} TableString;



TableString		g_strs[StrID_NUMTYPES] = {
	StrID_NONE,						"",
	StrID_Name,						"Aspect Ratio",
	StrID_Description,				"Adjust the aspect ratio of the image by creating a letterbox over the image.\r\rCopyright (c) 2011 Kevin Cotugno.",
	StrID_MoreInfo,					"en.wikipedia.org/wiki/Aspect_ratio_(image)",
	StrID_NewHight,					"New Height",
	StrID_NewHight_Description,		"The new comp height is",
	StrID_Aspcet_Preset_Name,		"Presets",
	StrID_Aspect_Preset_Choices,	"(1.78:1 or 16x9) Standard widescreen ratio of HDTV's.|"
									"(1.85:1) 35mm widescreen for theatrical films.|"
									"(2.39:1) 35mm anamorphic for theatrical films.|"
									"(2.40:1) 2.39 films converted for disc.|"
									"(2.55:1) Orignal aspect ratio of CinemaScope.|"
									"Custom",
	StrID_Aspect_Amount_Param_Name,	"Aspect Ratio",
	StrID_Err_LoadSuite,			"Error loading suite.",
	StrID_Err_FreeSuite,			"Error releasing suite.",
};


char	*GetStringPtr(int strNum)
{
	return g_strs[strNum].str;
}
