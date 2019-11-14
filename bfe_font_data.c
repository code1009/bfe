/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "bfe.h"

//===========================================================================
#include "bfe_font_data_16x16_unknown.h"
#include "bfe_font_data_08x16_ascii_low.h"

#if (1==BFE_CONFIG_UNICODE_HANGUL) || (1==BFE_CONFIG_CP949_HANGUL)
#include "bfe_font_data_16x16_hangul_johab844.h"
#endif

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
#include "bfe_font_data_16x16_cp949_special_1128.h"
#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)
#include "bfe_font_data_16x16_cp949_hanja_4888.h"
#endif




