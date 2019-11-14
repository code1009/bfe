#ifndef __bfe_code_table__h__
#define __bfe_code_table__h__



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if (1 == BFE_CONFIG_CP949_HANGUL)
BFE_API bfe_wchar_t   bfe_code_table_cp949_hangul_11172_to_unicode [11172];
#endif

#if (1 == BFE_CONFIG_UNICODE_SPECIAL)
BFE_API bfe_wchar_t   bfe_code_table_cp949_special_1128_to_unicode [1128];
#endif

#if (1 == BFE_CONFIG_UNICODE_HANJA)
BFE_API bfe_wchar_t   bfe_code_table_cp949_hanja_4888_to_unicode   [4888];
#endif

//===========================================================================
#if (1 == BFE_CONFIG_CODE_CONVERSION)
BFE_API bfe_uchar16_t bfe_code_table_unicode_to_cp949_hangul_11172 [11172];
#endif





#endif




