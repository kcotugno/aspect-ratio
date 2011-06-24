/*
 * Aspect_Ratio.cpp
 *
 * Copyright (c) 2011 Kevin Cotugno.
 *
 * Created on 6/24/11.
 */
#include "Aspect_Ratio.h"


static A_short 
RoundPixelData(A_FpLong cur_val)
{
	int rnd_dec = 0;

	if((cur_val + 0.5) >= (A_short(cur_val) + 1))
		rnd_dec = (A_short)cur_val + 1;
	else
		rnd_dec = (A_short)cur_val;

	return rnd_dec;
}

static void
CalculateRectSize(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	PF_Rect			*rect,
	int				rect_type)
{
	A_FpLong LongCalcValue = ((A_FpLong)in_data->width / params[ASPECT_AMOUNT]->u.fs_d.value) *
						((A_FpLong)in_data->pixel_aspect_ratio.num / (A_FpLong)in_data->pixel_aspect_ratio.den);

	LongCalcValue = (A_FpLong)in_data->height - LongCalcValue;
	LongCalcValue /= 2.0;

	A_short FinalValue = RoundPixelData(LongCalcValue / ((A_FpLong)in_data->downsample_x.den / (A_FpLong)in_data->downsample_x.num));

	if(rect_type == ASPECT_RATIO_RECT_TYPE_TOP) {
		rect->bottom	= FinalValue;
		rect->left		= (A_short)output->width;
		rect->right		= 0;
		rect->top		= 0;
	} else {
		rect->bottom	= (A_short)output->height;
		rect->left		= (A_short)output->width;
		rect->right		= 0;
		rect->top		= (A_short)output->height - FinalValue;
	}
}

static A_long
GetNewCompHeight(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	return (A_long)RoundPixelData(((A_FpLong)in_data->width / params[ASPECT_AMOUNT]->u.fs_d.value) *
					((A_FpLong)in_data->pixel_aspect_ratio.num / (A_FpLong)in_data->pixel_aspect_ratio.den));
}

static PF_Err 
About (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	
	suites.ANSICallbacksSuite1()->sprintf(	out_data->return_msg,
											"%s %d.%d\r\r%s\r\rMore info on aspect ratios:\r%s",
											STR(StrID_Name), 
											MAJOR_VERSION, 
											MINOR_VERSION, 
											STR(StrID_Description),
											STR(StrID_MoreInfo));
	return PF_Err_NONE;
}

static PF_Err
NewSizeDialog (
			PF_InData	*in_data,
			PF_OutData	*out_data,
			PF_ParamDef	*params[],
			PF_LayerDef	*output)
{
	AEGP_SuiteHandler suites(in_data->pica_basicP);

	A_short height = (A_short)GetNewCompHeight(	in_data,
										out_data,
										params,
										output);

	suites.ANSICallbacksSuite1()->sprintf(	out_data->return_msg,
											"%s %hd pixels.",
											STR(StrID_NewHight_Description),
											height);

	return PF_Err_NONE;
}

static PF_Err 
GlobalSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err err					= PF_Err_NONE;

	out_data->my_version = PF_VERSION(	MAJOR_VERSION, 
										MINOR_VERSION,
										BUG_VERSION, 
										STAGE_VERSION, 
										BUILD_VERSION);

	out_data->out_flags = 	PF_OutFlag_I_DO_DIALOG|
							PF_ParamFlag_SUPERVISE;

	return err;
}


static PF_Err 
ParamsSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err		err		= PF_Err_NONE;
	PF_ParamDef	def;
	PF_EffectUISuite1 *EffectUISuiteP = NULL;

	AEFX_CLR_STRUCT(def);

	def.flags = PF_ParamFlag_CANNOT_TIME_VARY |
				PF_ParamFlag_SUPERVISE;

	PF_ADD_POPUP(	STR(StrID_Aspcet_Preset_Name),
					ASPECT_PRESET_NUM,
					ASPECT_PRESET_DFLT,
					STR(StrID_Aspect_Preset_Choices),
					ASPECT_PRESET_ID);

	AEFX_CLR_STRUCT(def);

	def.flags = PF_ParamFlag_SUPERVISE;

	PF_ADD_FLOAT_SLIDER(STR(StrID_Aspect_Amount_Param_Name),
						ASPECT_RATIO_AMOUT_MIN,
						ASPECT_RATIO_AMOUT_MAX,
						ASPECT_RATIO_AMOUT_MIN,
						ASPECT_RATIO_AMOUT_MAX,
						0,
						ASPECT_RATIO_AMOUT_DFLT,
						ASPECT_RATIO_AMOUT_PREC,
						0,
						0,
						ASPECT_AMOUNT_ID);
	
	AEFX_CLR_STRUCT(def);

	out_data->num_params = ASPECT_NUM_PARAMS;

	ERR(AEFX_AcquireSuite(	in_data,
							out_data,
							kPFEffectUISuite,
							kPFEffectUISuiteVersion1,
							"Couldn't load suite.",
							(void**)&EffectUISuiteP));

	EffectUISuiteP->PF_SetOptionsButtonName(	in_data->effect_ref,
												STR(StrID_NewHight));

	ERR(AEFX_ReleaseSuite(	in_data,
							out_data,
							kPFEffectUISuite,
							kPFEffectUISuiteVersion1,
							"Couldn't release suite"));

	return err;
}

static PF_Err
HandleChangedParam (
	PF_InData					*in_data,
	PF_OutData					*out_data,
	PF_ParamDef					*params[],
	PF_LayerDef					*output,
	PF_UserChangedParamExtra	*extra)
{
	PF_Err				err					= PF_Err_NONE;

	// Change the preset popup to the correct value when the user manually selects a value for the aspect slider.
	if (extra->param_index == ASPECT_AMOUNT) {
		
		// Let AE know to update the parameter.
		params[ASPECT_PRESET]->uu.change_flags = PF_ChangeFlag_CHANGED_VALUE;

		if((params[ASPECT_AMOUNT]->u.fs_d.value >= 1.7755001) && (params[ASPECT_AMOUNT]->u.fs_d.value <= 1.785)) {
			params[ASPECT_PRESET]->u.pd.value = ASPECT_PRESET_178;
		}

		else if((params[ASPECT_AMOUNT]->u.fs_d.value >= 1.84) && (params[ASPECT_AMOUNT]->u.fs_d.value <= 1.855)) {
			params[ASPECT_PRESET]->u.pd.value = ASPECT_PRESET_185;
		}

		else if((params[ASPECT_AMOUNT]->u.fs_d.value >= 2.385) && (params[ASPECT_AMOUNT]->u.fs_d.value <= 2.395)) {
			params[ASPECT_PRESET]->u.pd.value = ASPECT_PRESET_239;
		}

		else if((params[ASPECT_AMOUNT]->u.fs_d.value >= 2.395) && (params[ASPECT_AMOUNT]->u.fs_d.value <= 2.405)) {
			params[ASPECT_PRESET]->u.pd.value = ASPECT_PRESET_240;
		}

		else if((params[ASPECT_AMOUNT]->u.fs_d.value >= 2.545) && (params[ASPECT_AMOUNT]->u.fs_d.value <= 2.555)) {
			params[ASPECT_PRESET]->u.pd.value = ASPECT_PRESET_255;
		}

		else {
			params[ASPECT_PRESET]->u.pd.value = ASPECT_PRESET_CUSTOM;
		}


	// Change the apect slider value to match the correct value of the preset the user selected.
	} else if (extra->param_index == ASPECT_PRESET) {

		// Let AE know to update the parameter.
		params[ASPECT_AMOUNT]->uu.change_flags = PF_ChangeFlag_CHANGED_VALUE;

		switch (params[ASPECT_PRESET]->u.pd.value) {
		
			case ASPECT_PRESET_178:
				params[ASPECT_AMOUNT]->u.fs_d.value = 1.7777777;
				break;

			case ASPECT_PRESET_185:
				params[ASPECT_AMOUNT]->u.fs_d.value = 1.85;
				break;

			case ASPECT_PRESET_239:
				params[ASPECT_AMOUNT]->u.fs_d.value = 2.39;
				break;

			case ASPECT_PRESET_240:
				params[ASPECT_AMOUNT]->u.fs_d.value = 2.40;
				break;

			case ASPECT_PRESET_255:
				params[ASPECT_AMOUNT]->u.fs_d.value = 2.55;
				break;
		}
	}

	return err;
}

static PF_Err 
Render (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err				err		= PF_Err_NONE;
	AEGP_SuiteHandler	suites(in_data->pica_basicP);
	PF_Pixel *PixelColorBlack = new PF_Pixel;
	PF_Rect *TopRect = new PF_Rect, *BottomRect = new PF_Rect;

	PixelColorBlack->alpha	= 0;
	
	ERR(suites.WorldTransformSuite1()->copy(	in_data->effect_ref,
												&params[ASPECT_INPUT]->u.ld,
												output,
												NULL,
												NULL));
	// Get the top rect.
	CalculateRectSize(	in_data,
						out_data,
						params,
						output,
						TopRect,
						ASPECT_RATIO_RECT_TYPE_TOP);
	
	// Get the bottom rect.
	CalculateRectSize(	in_data,
						out_data,
						params,
						output,
						BottomRect,
						ASPECT_RATIO_RECT_TYPE_BOTTOM);


	// Top letterbox.
	ERR(suites.FillMatteSuite1()->fill(	in_data->effect_ref,
										PixelColorBlack,
										TopRect,
										output));

	// Bottom letterbox.
	ERR(suites.FillMatteSuite1()->fill(	in_data->effect_ref,
											PixelColorBlack,
											BottomRect,
											output));

	// Clean up memory.
	delete PixelColorBlack;
	delete TopRect;
	delete BottomRect;

	return err;
}

DllExport	
PF_Err 
EntryPointFunc (
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra)
{
	PF_Err		err = PF_Err_NONE;
	
	try {
		switch (cmd) {
			case PF_Cmd_ABOUT:

				err = About(in_data,
							out_data,
							params,
							output);
				break;
									
			case PF_Cmd_GLOBAL_SETUP:

				err = GlobalSetup(	in_data,
									out_data,
									params,
									output);
				break;
				
			case PF_Cmd_PARAMS_SETUP:

				err = ParamsSetup(	in_data,
									out_data,
									params,
									output);
				break;

			case PF_Cmd_DO_DIALOG:

				err = NewSizeDialog(	in_data,
										out_data,
										params,
										output);
				break;
				
			case PF_Cmd_RENDER:

				err = Render(	in_data,
								out_data,
								params,
								output);
				break;

			case PF_Cmd_USER_CHANGED_PARAM:

				err = HandleChangedParam(	in_data,
											out_data,
											params,
											output,
											reinterpret_cast<PF_UserChangedParamExtra*>(extra));

				break;
		}
	}
	catch(PF_Err &thrown_err){
		err = thrown_err;
	}
	return err;
}
