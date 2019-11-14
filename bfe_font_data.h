#ifndef __bfe_font_data__h__
#define __bfe_font_data__h__

//                                                         ( x/8 * y )* count
BFE_API bfe_byte_t bfe_font_data_16x16_unknown           [ (16/8 * 16)*   1 ];
BFE_API bfe_byte_t bfe_font_data_08x16_ascii_low         [ ( 8/8 * 16)* 128 ];

#if (1==BFE_CONFIG_UNICODE_HANGUL) || (1==BFE_CONFIG_CP949_HANGUL)
BFE_API bfe_byte_t bfe_font_data_16x16_hangul_johab844   [ (16/8 * 16)*( (19*8)+(21*4)+(27*4) ) ];
#endif

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
BFE_API bfe_byte_t bfe_font_data_16x16_cp949_special_1128[ (16/8 * 16)*1128 ];
#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)
BFE_API bfe_byte_t bfe_font_data_16x16_cp949_hanja_4888  [ (16/8 * 16)*4888 ];
#endif

#endif




