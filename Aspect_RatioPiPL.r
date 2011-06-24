#include "AEConfig.h"

#ifndef AE_OS_WIN
	#include <AE_General.r>
#endif
	
resource 'PiPL' (16000) {
	{	/* array properties: 12 elements */
		/* [1] */
		Kind {
			AEEffect
		},
		/* [2] */
		Name {
			"Aspect Ratio"
		},
		/* [3] */
		Category {
			"Kevin Cotugno"
		},
#ifdef AE_OS_WIN
		CodeWin32X86 {"EntryPointFunc"},
#else
	#ifdef AE_OS_MAC
		CodeMachOPowerPC {"EntryPointFunc"},
		CodeMacIntel32 {"EntryPointFunc"},
	#endif
#endif
		/* [6] */
		AE_PiPL_Version {
			2,
			0
		},
		/* [7] */
		AE_Effect_Spec_Version {
			12,
			12
		},
		/* [8] */
		AE_Effect_Version {
			525825	/* 1.1 */
		},
		/* [9] */
		AE_Effect_Info_Flags {
			0
		},
		/* [10] */
		AE_Effect_Global_OutFlags {
			96

		},
		AE_Effect_Global_OutFlags_2 {
			0x00000000
		},
		/* [11] */
		AE_Effect_Match_Name {
			"ADBE Aspect_Ratio"
		},
		/* [12] */
		AE_Reserved_Info {
			0
		}
	}
};

