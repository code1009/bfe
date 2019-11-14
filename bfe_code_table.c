/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "bfe.h"

//===========================================================================
#if (1 == BFE_CONFIG_CP949_HANGUL)
#include "bfe_code_table_cp949_hangul_11172_to_unicode.h"
#endif

#if (1 == BFE_CONFIG_UNICODE_SPECIAL)
#include "bfe_code_table_cp949_special_1128_to_unicode.h"
#endif

#if (1 == BFE_CONFIG_UNICODE_HANJA)
#include "bfe_code_table_cp949_hanja_4888_to_unicode.h"
#endif

//===========================================================================
#if (1 == BFE_CONFIG_CODE_CONVERSION)
#include "bfe_code_table_unicode_to_cp949_hangul_11172.h"
#endif





