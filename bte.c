/****************************************************************************
**
** File: bfe.c
**
** Created by MOON, Eui-kwon.
** Created on Nov-14th, 2019.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#ifdef _MSC_VER

#define BFE_DEBUG_TEST 1

#if 1==BFE_DEBUG_TEST
#include "stdafx.h"
#endif

#endif



//===========================================================================
#include "bfe.h"
#include "bfe_font_data.h"
#include "bfe_code_table.h"





/////////////////////////////////////////////////////////////////////////////
//
// 글자출력
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bfe_int_t bfe_cp949_hangul_11172_index (bfe_uchar16_t ch)
{
	bfe_uint_t offset;

	bfe_int_t index;


	index = -1;


	//-----------------------------------------------------------------------
	// 완성형한글.한글2350자 
	//-----------------------------------------------------------------------

	// 0xB0A1u '가' - 0xC8FEu '힝'
	if (ch>=0xB0A1u && ch<=0xC8FEu)
	{
		offset = (ch-0xB0A0u)%0x0100u;
		if (offset>0u && offset<96u)
		{
			index = (ch-0xB0A0u)/0x0100u*94u + offset - 1u;
			return index;
		}
	}


	//-----------------------------------------------------------------------
	// 확장완성형한글.추가한글8822자
	//-----------------------------------------------------------------------

	// 5696 + 3108 + 18

	// 5696자
	// 0x8141u '갂' - 0xA0FEu '좤' 
	if (ch>=0x8141u && ch<=0xA0FEu)
	{
		offset = (ch-0x8140u)%0x0100u;
		if (offset>0u && offset<191u)
		{
			if (offset >= 0x001Bu && offset<= 0x0020u)
				return -1;

			if (offset >= 0x003Bu && offset<= 0x0040u)
				return -1;

			if      (offset>0x0040u) offset -= 12u;
			else if (offset>0x0020u) offset -= 6u;

			index  = (ch-0x8140u)/0x0100u*(192u-2u-6u-6u) + offset - 1u + 2350u;
			return index;
		}
	}

	// 3108자
	// 0xA141u '좥' - 0xC5A0u '힋' 
	if (ch>=0xA141u && ch<=0xC5A0u)
	{
		offset = (ch-0xA140u)%0x0100u;
		if (offset>0u && offset<97u)
		{
			if (offset >= 0x001Bu && offset<= 0x0020u)
				return -1;

			if (offset >= 0x003Bu && offset<= 0x0040u)
				return -1;

			if      (offset>0x0040) offset -= 12u;
			else if (offset>0x0020) offset -= 6u;

			index  = (ch-0xA140u)/0x0100u*(97u-6u-6u-1u) + offset - 1u + 5696u + 2350u;
			return index;
		}
	}

	// 18자
	// 0xC641u '힍' - 0xC652u '힣' 
	if (ch>=0xC641u && ch<=0xC652u)
	{
		index = ch - 0xC640u - 1u + 3108u + 5696u + 2350u;
		return index;
	}


	return index;
}

bfe_int_t bfe_cp949_special_1128_index (bfe_uchar16_t ch)
{
	bfe_uint_t offset;


	/*
	# 완성형한글.특수문자1128자: 0xA1A1u - 0xACFEu
	  12개영역 * 94문자 = 1128문자
	     0xA1A0u
	   + 0x0C00u(12*256)
	   = 0xFEA0u
	*/
	if (0xA1A1u<=ch && ch <= 0xACFEu)
	{
		offset = (ch-0xA1A0u)%0x0100u;

		if (offset>0u && offset<96u)
		{
			return ((ch-0xA1A0u)/0x0100u)*94u + offset -1u;
		}
	}

	return -1;
}

bfe_int_t bfe_cp949_hanja_4888_index (bfe_uchar16_t ch)
{
	bfe_uint_t offset;


	/*
	# 완성형한글.한자4888자: 0xCAA1u-0xFDFEu
	  52개영역 * 94문자 = 4888문자
	     0xCAA0u
	   + 0x3400u(52*256)
	   = 0xFEA0u
	*/
	if (0xCAA1u<=ch && ch <= 0xFDFEu)
	{
		offset = (ch-0xCAA0u)%0x0100u;

		if (offset>0u && offset<96u)
		{
			return ((ch-0xCAA0u)/0x0100u)*94u + offset - 1u;
		}
	}

	return -1;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bfe_int_t bfe_hangul_johab844_choseong_set (bfe_uint_t choseong, bfe_uint_t jungseong, bfe_uint_t jongseong)
{
	bfe_int_t set;
	bfe_int_t temp;


	set = 0;

	switch (jungseong)
	{
	case  0u:       // ㅏ
	case  1u:       // ㅐ
	case  2u:       // ㅑ
	case  3u:       // ㅒ
	case  4u:       // ㅓ
	case  5u:       // ㅔ
	case  6u:       // ㅕ
	case  7u:       // ㅖ
	case 20u:       // ㅣ
		set = 0;
		break;

	case  8u:       // ㅗ
	case 12u:       // ㅛ
	case 18u:       // ㅡ
		set = 1;
		break;

	case 13u:       // ㅜ
	case 17u:       // ㅠ
		set = 2;
		break;

	case  9u:       // ㅘ
	case 10u:       // ㅙ
	case 11u:       // ㅚ
	case 19u:       // ㅢ
		set = 3;
		break;

	case 14u:       // ㅝ
	case 15u:       // ㅞ
	case 16u:       // ㅟ
		set = 4;
		break;
	}

	if (jongseong!=0u)
	{
		// 종성이 있으면
		switch (set)
		{
		case 0:
			temp = 5;
			break;

		case 1:
		case 2:
			temp = 6;
			break;

		case 3:
		case 4:
			temp = 7;
			break;
		}

		set = temp;
	}

	return set;
}

bfe_int_t bfe_hangul_johab844_jungseong_set (bfe_uint_t choseong, bfe_uint_t jungseong, bfe_uint_t jongseong)
{
	bfe_int_t set;


	if (jongseong==0u)
	{
		// 종성이 없는 경우
		if (choseong==0u || choseong==1u) // ㄱㅋ
		{
			set = 0;
		}
		else
		{
			set = 1;
		}
	}
	else
	{
		// 종성이 있는 경우
		if (choseong==0u || choseong==1u) // ㄱㅋ
		{
			set = 2;
		}
		else
		{
			set = 3;
		}
	}

	return set;
}

bfe_int_t bfe_hangul_johab844_jongseong_set (bfe_uint_t choseong, bfe_uint_t jungseong, bfe_uint_t jongseong)
{
	bfe_int_t set;


	set = 0;

	switch (jungseong)
	{
	case  0u:       // ㅏ
	case  2u:       // ㅑ
	case  9u:       // ㅘ
	case 20u:       // ㅣ
		set = 0;
		break;

	case  4u:       // ㅓ
	case  6u:       // ㅕ
	case 11u:       // ㅚ
	case 14u:       // ㅝ
	case 16u:       // ㅟ
	case 19u:       // ㅢ
		set = 1;
		break;

	case  1u:       // ㅐ
	case  3u:       // ㅒ
	case  5u:       // ㅔ
	case  7u:       // ㅖ
	case 10u:       // ㅙ
	case 15u:       // ㅞ
		set = 2;
		break;

	case  8u:       // ㅗ
	case 12u:       // ㅛ
	case 13u:       // ㅜ
	case 17u:       // ㅠ
	case 18u:       // ㅡ
		set = 3;
		break;
	}
	
	return set;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void bfe_get_font_bitmap_hangul_johab844_jamo_choseong  (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb)
{
	fb->font_bitmap_pointer = f->choseong[0] + f->font_size*index;
	fb->font_bitmap_size    = f->font_size;

	fb->font_bitmap_cx = f->font_cx;
	fb->font_bitmap_cy = f->font_cy;

	fb->font_bitmap_cx_size = f->font_cx_size;
	fb->font_bitmap_cy_size = f->font_cy_size;
}

void bfe_get_font_bitmap_hangul_johab844_jamo_jungseong (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb)
{
	fb->font_bitmap_pointer = f->jungseong[0] + f->font_size*index;
	fb->font_bitmap_size    = f->font_size;

	fb->font_bitmap_cx = f->font_cx;
	fb->font_bitmap_cy = f->font_cy;

	fb->font_bitmap_cx_size = f->font_cx_size;
	fb->font_bitmap_cy_size = f->font_cy_size;
}

void bfe_get_font_bitmap_hangul_johab844_jamo_jongseong (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb)
{
	fb->font_bitmap_pointer = f->jongseong[0] + f->font_size*index;
	fb->font_bitmap_size    = f->font_size;

	fb->font_bitmap_cx = f->font_cx;
	fb->font_bitmap_cy = f->font_cy;

	fb->font_bitmap_cx_size = f->font_cx_size;
	fb->font_bitmap_cy_size = f->font_cy_size;
}

void bfe_get_font_bitmap_hangul_johab844_jamo_moeum (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb)
{
	fb->font_bitmap_pointer = f->jungseong[0] + f->font_size*index;
	fb->font_bitmap_size    = f->font_size;

	fb->font_bitmap_cx = f->font_cx;
	fb->font_bitmap_cy = f->font_cy;

	fb->font_bitmap_cx_size = f->font_cx_size;
	fb->font_bitmap_cy_size = f->font_cy_size;
}

void bfe_get_font_bitmap_hangul_johab844_jamo_jaeum (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb)
{
	bfe_byte_t* jamo;
	bfe_uint_t  jamo_index;

	
	jamo       = BFE_NULL_POINTER;
	jamo_index = 0u;

	switch (index)
	{
	/*ㄱ*/ case 0x00u: jamo=f->choseong [0]; jamo_index= 0u;    break;
	/*ㄲ*/ case 0x01u: jamo=f->choseong [0]; jamo_index= 1u;    break;
	/*ㄳ*/ case 0x02u: jamo=f->jongseong[0]; jamo_index= 3u-1u; break;
	/*ㄴ*/ case 0x03u: jamo=f->choseong [0]; jamo_index= 2u;    break;
	/*ㄵ*/ case 0x04u: jamo=f->jongseong[0]; jamo_index= 5u-1u; break;
	/*ㄶ*/ case 0x05u: jamo=f->jongseong[0]; jamo_index= 6u-1u; break;
	/*ㄷ*/ case 0x06u: jamo=f->choseong [0]; jamo_index= 3u;    break;
	/*ㄸ*/ case 0x07u: jamo=f->choseong [0]; jamo_index= 4u;    break;
	/*ㄹ*/ case 0x08u: jamo=f->choseong [0]; jamo_index= 5u;    break;
	/*ㄺ*/ case 0x09u: jamo=f->jongseong[0]; jamo_index= 9u-1u; break;
	/*ㄻ*/ case 0x0Au: jamo=f->jongseong[0]; jamo_index=10u-1u; break;
	/*ㄼ*/ case 0x0Bu: jamo=f->jongseong[0]; jamo_index=11u-1u; break;
	/*ㄽ*/ case 0x0Cu: jamo=f->jongseong[0]; jamo_index=12u-1u; break;
	/*ㄾ*/ case 0x0Du: jamo=f->jongseong[0]; jamo_index=13u-1u; break;
	/*ㄿ*/ case 0x0Eu: jamo=f->jongseong[0]; jamo_index=14u-1u; break;
	/*ㅀ*/ case 0x0Fu: jamo=f->jongseong[0]; jamo_index=15u-1u; break;
	/*ㅁ*/ case 0x10u: jamo=f->choseong [0]; jamo_index= 6u;    break;
	/*ㅂ*/ case 0x11u: jamo=f->choseong [0]; jamo_index= 7u;    break;
	/*ㅃ*/ case 0x12u: jamo=f->choseong [0]; jamo_index= 8u;    break;
	/*ㅄ*/ case 0x13u: jamo=f->jongseong[0]; jamo_index=18u-1u; break;
	/*ㅅ*/ case 0x14u: jamo=f->choseong [0]; jamo_index= 9u;    break;
	/*ㅆ*/ case 0x15u: jamo=f->choseong [0]; jamo_index=10u;    break;
	/*ㅇ*/ case 0x16u: jamo=f->choseong [0]; jamo_index=11u;    break;
	/*ㅈ*/ case 0x17u: jamo=f->choseong [0]; jamo_index=12u;    break;
	/*ㅉ*/ case 0x18u: jamo=f->choseong [0]; jamo_index=13u;    break;
	/*ㅊ*/ case 0x19u: jamo=f->choseong [0]; jamo_index=14u;    break;
	/*ㅋ*/ case 0x1Au: jamo=f->choseong [0]; jamo_index=15u;    break;
	/*ㅌ*/ case 0x1Bu: jamo=f->choseong [0]; jamo_index=16u;    break;
	/*ㅍ*/ case 0x1Cu: jamo=f->choseong [0]; jamo_index=17u;    break;
	/*ㅎ*/ case 0x1Du: jamo=f->choseong [0]; jamo_index=18u;    break;
	}

	fb->font_bitmap_pointer = jamo + f->font_size*jamo_index;
	fb->font_bitmap_size    = f->font_size;

	fb->font_bitmap_cx = f->font_cx;
	fb->font_bitmap_cy = f->font_cy;

	fb->font_bitmap_cx_size = f->font_cx_size;
	fb->font_bitmap_cy_size = f->font_cy_size;
}

void bfe_get_font_bitmap_hangul_johab844 (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t choseong, bfe_uint_t jungseong, bfe_uint_t jongseong, bfe_font_bitmap_t* fb)
{
	//-----------------------------------------------------------------------
	fb->font_bitmap_pointer = ctx->union_font_bitmap_buffer;
	fb->font_bitmap_size    = f->font_size;

	fb->font_bitmap_cx = f->font_cx;
	fb->font_bitmap_cy = f->font_cy;

	fb->font_bitmap_cx_size = f->font_cx_size;
	fb->font_bitmap_cy_size = f->font_cy_size;


	//-----------------------------------------------------------------------
	bfe_uint_t choseong_set ;
	bfe_uint_t jungseong_set;
	bfe_uint_t jongseong_set;


	choseong_set  = bfe_hangul_johab844_choseong_set (choseong, jungseong, jongseong);
	jungseong_set = bfe_hangul_johab844_jungseong_set(choseong, jungseong, jongseong);
	jongseong_set = bfe_hangul_johab844_jongseong_set(choseong, jungseong, jongseong);


	//-----------------------------------------------------------------------
	bfe_byte_t* font_bitmap_pointer_choseong ;
	bfe_byte_t* font_bitmap_pointer_jungseong;
	bfe_byte_t* font_bitmap_pointer_jongseong;


	font_bitmap_pointer_choseong  = f->choseong [choseong_set ] + f->font_size*choseong ;
	font_bitmap_pointer_jungseong = f->jungseong[jungseong_set] + f->font_size*jungseong;
	
	if (0u!=jongseong)
	{
		font_bitmap_pointer_jongseong = f->jongseong[jongseong_set] + f->font_size*(jongseong - 1u);
	}
	else
	{
		font_bitmap_pointer_jongseong = BFE_NULL_POINTER;
	}


	//-----------------------------------------------------------------------
	bfe_byte_t* font_bitmap_pointer;
	bfe_uint_t  font_bitmap_size;
	bfe_uint_t  i;

	font_bitmap_pointer = fb->font_bitmap_pointer;
	font_bitmap_size    = fb->font_bitmap_size   ;


	if (0u==jongseong)
	{
		for(i=0u; i<font_bitmap_size; i++)
		{
			font_bitmap_pointer[i] =
				font_bitmap_pointer_choseong [i] |
				font_bitmap_pointer_jungseong[i];
		}
	}
	else
	{
		for(i=0u; i<font_bitmap_size; i++)
		{
			font_bitmap_pointer[i] =
				font_bitmap_pointer_choseong [i] |
				font_bitmap_pointer_jungseong[i] |
				font_bitmap_pointer_jongseong[i];
		}
	}
}

//===========================================================================
void bfe_get_font_bitmap (bfe_context_t* ctx, bfe_font_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb)
{
	fb->font_bitmap_pointer = f->font_data_pointer + f->font_size*index;
	fb->font_bitmap_size    = f->font_size;

	fb->font_bitmap_cx = f->font_cx;
	fb->font_bitmap_cy = f->font_cy;

	fb->font_bitmap_cx_size = f->font_cx_size;
	fb->font_bitmap_cy_size = f->font_cy_size;
}

//===========================================================================
bfe_uint_t bfe_get_wchar_type(bfe_context_t* ctx, bfe_wchar_t ch)
{
	//-----------------------------------------------------------------------
	if (0x0000u <= ch && ch<= 0x007Fu)
	{
		return BFE_CHAR_TYPE_ASCII_LOW;
	}

	if (0x0080u <= ch && ch<= 0x00FFu)
	{
		return BFE_CHAR_TYPE_ASCII_HIGH;
	}


#if (1==BFE_CONFIG_UNICODE_HANGUL)
	//-----------------------------------------------------------------------
	if (0xAC00u <= ch && ch<= 0xD7A3u) // 0xAC00u+11172자
	{
		return BFE_CHAR_TYPE_HANGUL;
	}

	if (0x1100u <= ch && ch<= 0x11FFu)
	{
		if (0x1100u <= ch && ch<= 0x1112u) // 0x1100u+초성19자
		{
			return BFE_CHAR_TYPE_HANGUL_JAMO_CHOSEONG;
		}
		if (0x1161u <= ch && ch<= 0x1175u) // 0x1161u+중성21자
		{
			return BFE_CHAR_TYPE_HANGUL_JAMO_JUNGSEONG;
		}
		if (0x11A8u <= ch && ch<= 0x11C2u) // 0x11A8u+종성28자
		{
			return BFE_CHAR_TYPE_HANGUL_JAMO_JONGSEONG;
		}
	}
	
	if (0x3131u<= ch && ch<= 0x3163u)
	{
		if (0x3131u <= ch && ch <= 0x314Eu) // 0x3131u+자음30자
		{
			return BFE_CHAR_TYPE_HANGUL_JAMO_JAEUM;
		}
		if (0x314Fu <= ch && ch <= 0x3163u) // 0x314Fu+모음21자
		{
			return BFE_CHAR_TYPE_HANGUL_JAMO_MOEUM;
		}
	}
#endif


#if (1==BFE_CONFIG_UNICODE_SPECIAL)
	//-----------------------------------------------------------------------
	// 0x00A1u '¡' - 0x00FEu 'þ'
	// 0x0111u 'đ'  - 0x0451u 'ё'
	// 0x2015u '―' - 0x266Du '♭'
	// 0x3000u '　' - 0x33DDu '㏝'
	// 0xFF01u '！' - 0xFFE6u '￦'
	if (0x00A1u<= ch && ch<= 0x00FEu)
	{
		return BFE_CHAR_TYPE_CP949_SPECIAL_1128;
	}
	if (0x0111u<= ch && ch<= 0x0451u)
	{
		return BFE_CHAR_TYPE_CP949_SPECIAL_1128;
	}
	if (0x2015u<= ch && ch<= 0x266Du)
	{
		return BFE_CHAR_TYPE_CP949_SPECIAL_1128;
	}
	if (0x3000u<= ch && ch<= 0x33DDu)
	{
		return BFE_CHAR_TYPE_CP949_SPECIAL_1128;
	}
	if (0xFF01u<= ch && ch<= 0xFFE6u)
	{
		return BFE_CHAR_TYPE_CP949_SPECIAL_1128;
	}
#endif


#if (1==BFE_CONFIG_UNICODE_HANJA)
	//-----------------------------------------------------------------------
	// 0x4E00u '一' - 0x9F9Cu '龜'
	// 0xF900u '豈' - 0xF9FFu '刺'
	// 0xFA00u '切' - 0xFA0Bu '廓'
	if (0x4E00u<= ch && ch<= 0x9F9C)
	{
		return BFE_CHAR_TYPE_CP949_HANJA_4888;
	}
	if (0xF900u<= ch && ch<= 0xF9FF)
	{
		return BFE_CHAR_TYPE_CP949_HANJA_4888;
	}
	if (0xFA00u<= ch && ch<= 0xFA0B)
	{
		return BFE_CHAR_TYPE_CP949_HANJA_4888;
	}
#endif


	return BFE_CHAR_TYPE_UNKNOWN;
}

void bfe_get_wchar_font_bitmap(bfe_context_t* ctx, bfe_wchar_t ch, bfe_font_bitmap_t* fb)
{
	bfe_uint_t char_type;
	

#if (1==BFE_CONFIG_UNICODE_HANGUL)
	bfe_uint_t choseong;
	bfe_uint_t jungseong;
	bfe_uint_t jongseong;
#endif

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_UNICODE_HANJA)
	bfe_uint_t i;
	bfe_uint_t count;
#endif

	
	char_type = bfe_get_wchar_type(ctx, ch);
	switch (char_type)
	{
	//-----------------------------------------------------------------------
	case BFE_CHAR_TYPE_ASCII_LOW:
		bfe_get_font_bitmap(ctx, ctx->font_ascii_low, ch, fb);
		return;
		break;

	case BFE_CHAR_TYPE_ASCII_HIGH:
		break;


	//-----------------------------------------------------------------------
#if (1==BFE_CONFIG_UNICODE_HANGUL)
	case BFE_CHAR_TYPE_HANGUL:
		choseong  = BFE_UNICODE_HANGUL_CHOSEONG (ch);
		jungseong = BFE_UNICODE_HANGUL_JUNGSEONG(ch);
		jongseong = BFE_UNICODE_HANGUL_JONGSEONG(ch);
		bfe_get_font_bitmap_hangul_johab844(ctx, ctx->font_hangul_johab844, choseong, jungseong, jongseong, fb);
		return;
		break;

	case BFE_CHAR_TYPE_HANGUL_JAMO_CHOSEONG:
		bfe_get_font_bitmap_hangul_johab844_jamo_choseong (ctx, ctx->font_hangul_johab844, ch-0x1100u, fb);
		return;
		break;

	case BFE_CHAR_TYPE_HANGUL_JAMO_JUNGSEONG:
		bfe_get_font_bitmap_hangul_johab844_jamo_jungseong(ctx, ctx->font_hangul_johab844, ch-0x1161u, fb);
		return;
		break;

	case BFE_CHAR_TYPE_HANGUL_JAMO_JONGSEONG:
		bfe_get_font_bitmap_hangul_johab844_jamo_jongseong(ctx, ctx->font_hangul_johab844, ch-0x11A8u, fb);
		return;
		break;

	case BFE_CHAR_TYPE_HANGUL_JAMO_JAEUM:
		bfe_get_font_bitmap_hangul_johab844_jamo_jaeum(ctx, ctx->font_hangul_johab844, ch-0x3131u, fb);
		return;
		break;

	case BFE_CHAR_TYPE_HANGUL_JAMO_MOEUM:
		bfe_get_font_bitmap_hangul_johab844_jamo_moeum(ctx, ctx->font_hangul_johab844, ch-0x314Fu, fb);
		return;
		break;
#endif


	//-----------------------------------------------------------------------
#if (1==BFE_CONFIG_UNICODE_SPECIAL)
	case BFE_CHAR_TYPE_CP949_SPECIAL_1128:
		count = 1128u;
		for (i=0u; i<count; i++)
		{
			if (bfe_code_table_cp949_special_1128_to_unicode[i]==ch)
			{
				bfe_get_font_bitmap(ctx, ctx->font_cp949_special_1128, i, fb);
				return;
			}
		}
		break;
#endif


	//-----------------------------------------------------------------------
#if (1==BFE_CONFIG_UNICODE_HANJA)
	case BFE_CHAR_TYPE_CP949_HANJA_4888:
		count = 4888u;
		for (i=0u; i<count; i++)
		{
			if (bfe_code_table_cp949_hanja_4888_to_unicode[i]==ch)
			{
				bfe_get_font_bitmap(ctx, ctx->font_cp949_hanja_4888, i, fb);
				return;
			}
		}
		break;
#endif


	//-----------------------------------------------------------------------
	case BFE_CHAR_TYPE_UNKNOWN:
	default:
		break;
	}


	//-----------------------------------------------------------------------
	bfe_get_font_bitmap(ctx, ctx->font_unknown, 0u, fb);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bfe_uint_t bfe_get_char_type(bfe_context_t* ctx, bfe_uchar16_t ch)
{
	//-----------------------------------------------------------------------
	if (0x0000u <= ch && ch<= 0x007Fu)
	{
		return BFE_CHAR_TYPE_ASCII_LOW;
	}

	if (0x0080u <= ch && ch<= 0x00FFu)
	{
		return BFE_CHAR_TYPE_ASCII_HIGH;
	}


#if (1==BFE_CONFIG_CP949_HANGUL)
	//-----------------------------------------------------------------------
	if (0xA4A1u<= ch && ch<= 0xA4D3u)
	{
		if (0xA4A1u <= ch && ch <= 0xA4BEu)
		{
			return BFE_CHAR_TYPE_HANGUL_JAMO_JAEUM;
		}
		if (0xA4BFu <= ch && ch <= 0xA4D3u)
		{
			return BFE_CHAR_TYPE_HANGUL_JAMO_MOEUM;
		}
	}

	if (ch>=0xB0A1u && ch<=0xC8FEu)
	{
		return BFE_CHAR_TYPE_HANGUL;
	}
	if (ch>=0x8141u && ch<=0xA0FEu)
	{
		return BFE_CHAR_TYPE_HANGUL;
	}
	if (ch>=0xA141u && ch<=0xC5A0u)
	{
#if (1==BFE_CONFIG_CP949_SPECIAL)
		//-------------------------------------------------------------------
		if (0xA1A1u<=ch && ch <= 0xACFEu)
		{
			return BFE_CHAR_TYPE_CP949_SPECIAL_1128;
		}
#endif
		return BFE_CHAR_TYPE_HANGUL;
	}
	if (ch>=0xC641u && ch<=0xC652u)
	{
		return BFE_CHAR_TYPE_HANGUL;
	}
#endif


#if (1==BFE_CONFIG_CP949_SPECIAL)
	//-----------------------------------------------------------------------
	if (0xA1A1u<=ch && ch <= 0xACFEu)
	{
		return BFE_CHAR_TYPE_CP949_SPECIAL_1128;
	}
#endif


#if (1==BFE_CONFIG_CP949_HANJA)
	//-----------------------------------------------------------------------
	if (0xCAA1u<=ch && ch <= 0xFDFEu)
	{
		return BFE_CHAR_TYPE_CP949_HANJA_4888;
	}
#endif


	return BFE_CHAR_TYPE_UNKNOWN;
}

void bfe_get_char_font_bitmap(bfe_context_t* ctx, bfe_uchar16_t ch, bfe_font_bitmap_t* fb)
{
	bfe_uint_t char_type;
	

#if (1==BFE_CONFIG_CP949_HANGUL) || (1==BFE_CONFIG_CP949_SPECIAL) || (1==BFE_CONFIG_CP949_HANJA)
	bfe_int_t  code_index;
#endif

#if (1==BFE_CONFIG_CP949_HANGUL)
	bfe_uint_t unicode_hangul;
	bfe_uint_t choseong;
	bfe_uint_t jungseong;
	bfe_uint_t jongseong;
#endif

	
	char_type = bfe_get_char_type(ctx, ch);
	switch (char_type)
	{
	//-----------------------------------------------------------------------
	case BFE_CHAR_TYPE_ASCII_LOW:
		bfe_get_font_bitmap(ctx, ctx->font_ascii_low, ch, fb);
		return;
		break;

	case BFE_CHAR_TYPE_ASCII_HIGH:
		break;


	//-----------------------------------------------------------------------
#if (1==BFE_CONFIG_CP949_HANGUL)
	case BFE_CHAR_TYPE_HANGUL:
		code_index = bfe_cp949_hangul_11172_index(ch);
		if (code_index>=0)
		{
			unicode_hangul = bfe_code_table_cp949_hangul_11172_to_unicode[code_index];
			choseong  = BFE_UNICODE_HANGUL_CHOSEONG (unicode_hangul);
			jungseong = BFE_UNICODE_HANGUL_JUNGSEONG(unicode_hangul);
			jongseong = BFE_UNICODE_HANGUL_JONGSEONG(unicode_hangul);
			bfe_get_font_bitmap_hangul_johab844(ctx, ctx->font_hangul_johab844, choseong, jungseong, jongseong, fb);
			return;
		}
		break;

	case BFE_CHAR_TYPE_HANGUL_JAMO_JAEUM:
		bfe_get_font_bitmap_hangul_johab844_jamo_jaeum(ctx, ctx->font_hangul_johab844, ch-0xA4A1u, fb);
		return;
		break;

	case BFE_CHAR_TYPE_HANGUL_JAMO_MOEUM:
		bfe_get_font_bitmap_hangul_johab844_jamo_moeum(ctx, ctx->font_hangul_johab844, ch-0xA4BFu, fb);
		return;
		break;
#endif


	//-----------------------------------------------------------------------
#if (1==BFE_CONFIG_CP949_SPECIAL)
	case BFE_CHAR_TYPE_CP949_SPECIAL_1128:
		code_index = bfe_cp949_special_1128_index(ch);
		if (code_index>=0)
		{
			bfe_get_font_bitmap(ctx, ctx->font_cp949_special_1128, code_index, fb);
			return;
		}
		break;
#endif


	//-----------------------------------------------------------------------
#if (1==BFE_CONFIG_CP949_HANJA)
	case BFE_CHAR_TYPE_CP949_HANJA_4888:
		code_index = bfe_cp949_hanja_4888_index(ch);
		if (code_index>=0)
		{
			bfe_get_font_bitmap(ctx, ctx->font_cp949_hanja_4888, code_index, fb);
			return;
		}
		break;
#endif


	//-----------------------------------------------------------------------
	case BFE_CHAR_TYPE_UNKNOWN:
	default:
		break;
	}


	//-----------------------------------------------------------------------
	bfe_get_font_bitmap(ctx, ctx->font_unknown, 0u, fb);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static bfe_font_t                 _bfe_default_font_unknown           ;
static bfe_font_t                 _bfe_default_font_ascii_low         ;

#if (1==BFE_CONFIG_UNICODE_HANGUL) || (1==BFE_CONFIG_CP949_HANGUL)

static bfe_font_hangul_johab844_t _bfe_default_font_hangul_johab844   ;

#endif

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
        
static bfe_font_t                 _bfe_default_font_cp949_special_1128;

#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)

static bfe_font_t                 _bfe_default_font_cp949_hanja_4888  ;

#endif

//===========================================================================
void bfe_default_font_initialize (void)
{
	//-----------------------------------------------------------------------
	bfe_font_t*                 f;
	bfe_font_hangul_johab844_t* f_hangul_johab844;

	
	//-----------------------------------------------------------------------
	f = &_bfe_default_font_unknown;
	f->font_data_pointer = bfe_font_data_16x16_unknown;
	f->font_data_size    = sizeof(bfe_font_data_16x16_unknown);
	f->font_type    = BFE_FONT_TYPE_UNKNOWN;
	f->font_count   = 1u;
	f->font_size    = f->font_data_size/f->font_count;
	f->font_cx      = 16u;
	f->font_cy      = 16u;
	f->font_cx_size = f->font_cx/8u;
	f->font_cy_size = f->font_size;


	//-----------------------------------------------------------------------
	f = &_bfe_default_font_ascii_low         ;
	f->font_data_pointer = bfe_font_data_08x16_ascii_low;
	f->font_data_size    = sizeof(bfe_font_data_08x16_ascii_low); // 2048
	f->font_type    = BFE_FONT_TYPE_ASCII_LOW;
	f->font_count   = 128u;
	f->font_size    = f->font_data_size/f->font_count;
	f->font_cx      =  8u;
	f->font_cy      = 16u;
	f->font_cx_size = f->font_cx/8u;
	f->font_cy_size = f->font_size;


	//-----------------------------------------------------------------------
#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
	f = &_bfe_default_font_cp949_special_1128;
	f->font_data_pointer = bfe_font_data_16x16_cp949_special_1128;
	f->font_data_size    = sizeof(bfe_font_data_16x16_cp949_special_1128); // 36096
	f->font_type    = BFE_FONT_TYPE_CP949_SPECIAL_1128;
	f->font_count   = 1128u;
	f->font_size    = f->font_data_size/f->font_count;
	f->font_cx      = 16u;
	f->font_cy      = 16u;
	f->font_cx_size = f->font_cx/8u;
	f->font_cy_size = f->font_size;
#endif


	//-----------------------------------------------------------------------
#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)
	f = &_bfe_default_font_cp949_hanja_4888;
	f->font_data_pointer = bfe_font_data_16x16_cp949_hanja_4888;
	f->font_data_size    = sizeof(bfe_font_data_16x16_cp949_hanja_4888); // 156416
	f->font_type    = BFE_FONT_TYPE_CP949_HANJA_4888;
	f->font_count   = 4888u;
	f->font_size    = f->font_data_size/f->font_count;
	f->font_cx      = 16u;
	f->font_cy      = 16u;
	f->font_cx_size = f->font_cx/8u;
	f->font_cy_size = f->font_size;
#endif


	//-----------------------------------------------------------------------
#if (1==BFE_CONFIG_UNICODE_HANGUL) || (1==BFE_CONFIG_CP949_HANGUL)
	f_hangul_johab844 = &_bfe_default_font_hangul_johab844;
	f_hangul_johab844->font_data_pointer = bfe_font_data_16x16_hangul_johab844;
	f_hangul_johab844->font_data_size    = sizeof(bfe_font_data_16x16_hangul_johab844); // 11008
	f_hangul_johab844->font_type    = BFE_FONT_TYPE_HANGUL_JOHAB844;
	f_hangul_johab844->font_count   = (19u*8u)+(21u*4u)+(27u*4u);
	f_hangul_johab844->font_size    = f_hangul_johab844->font_data_size/f_hangul_johab844->font_count;
	f_hangul_johab844->font_cx      = 16u;
	f_hangul_johab844->font_cy      = 16u;
	f_hangul_johab844->font_cx_size = f_hangul_johab844->font_cx/8u;
	f_hangul_johab844->font_cy_size = f_hangul_johab844->font_size;

	f_hangul_johab844->choseong [0]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*0)+(21*0)+(27*0) ) ];
	f_hangul_johab844->choseong [1]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*1)+(21*0)+(27*0) ) ];
	f_hangul_johab844->choseong [2]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*2)+(21*0)+(27*0) ) ];
	f_hangul_johab844->choseong [3]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*3)+(21*0)+(27*0) ) ];
	f_hangul_johab844->choseong [4]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*4)+(21*0)+(27*0) ) ];
	f_hangul_johab844->choseong [5]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*5)+(21*0)+(27*0) ) ];
	f_hangul_johab844->choseong [6]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*6)+(21*0)+(27*0) ) ];
	f_hangul_johab844->choseong [7]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*7)+(21*0)+(27*0) ) ];

	f_hangul_johab844->jungseong[0]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*8)+(21*0)+(27*0) ) ];
	f_hangul_johab844->jungseong[1]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*8)+(21*1)+(27*0) ) ];
	f_hangul_johab844->jungseong[2]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*8)+(21*2)+(27*0) ) ];
	f_hangul_johab844->jungseong[3]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*8)+(21*3)+(27*0) ) ];

	f_hangul_johab844->jongseong[0]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*8)+(21*4)+(27*0) ) ];
	f_hangul_johab844->jongseong[1]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*8)+(21*4)+(27*1) ) ];
	f_hangul_johab844->jongseong[2]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*8)+(21*4)+(27*2) ) ];
	f_hangul_johab844->jongseong[3]=&f_hangul_johab844->font_data_pointer[ f_hangul_johab844->font_size*( (19*8)+(21*4)+(27*3) ) ];
#endif
}

void bfe_initialize (bfe_context_t* ctx)
{
	ctx->font_unknown            = &_bfe_default_font_unknown           ;
	ctx->font_ascii_low          = &_bfe_default_font_ascii_low         ;

#if (1==BFE_CONFIG_UNICODE_HANGUL) || (1==BFE_CONFIG_CP949_HANGUL)
	ctx->font_hangul_johab844    = &_bfe_default_font_hangul_johab844;
#endif

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
	ctx->font_cp949_special_1128 = &_bfe_default_font_cp949_special_1128;
#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)
	ctx->font_cp949_hanja_4888   = &_bfe_default_font_cp949_hanja_4888;
#endif
}





/////////////////////////////////////////////////////////////////////////////
//
// 글자코드변환
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if (1==BFE_CONFIG_CODE_CONVERSION)





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bfe_bool_t bfe_cp949_hangul_to_unicode (bfe_uchar16_t cp949, bfe_wchar_t* unicode)
{
	bfe_int_t index;

	
	// 유니코드 한글 낱글자 51자: 0x3131u 'ㄱ' - 0x3163u 'ㅣ'
	// 완성형   한글 낱글자 51자: 0xA4A1u 'ㄱ' - 0xA4D3u 'ㅣ'
	if (cp949>=0xA4A1u && cp949<=0xA4D3u)
	{
		*unicode = 0x3131u + cp949-0xA4A1u;
		return BFE_TRUE;
	}


	index = bfe_cp949_hangul_11172_index (cp949);
	if (index == -1)
		return BFE_FALSE;

	*unicode = bfe_code_table_cp949_hangul_11172_to_unicode[index];

	return BFE_TRUE;
}

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)

bfe_bool_t bfe_cp949_special_to_unicode (bfe_uchar16_t cp949, bfe_wchar_t* unicode)
{
	bfe_int_t index;


	index = bfe_cp949_special_1128_index (cp949);
	if (index == -1)
		return BFE_FALSE;

	*unicode = bfe_code_table_cp949_special_1128_to_unicode[index];

	return BFE_TRUE;
}

#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)

bfe_bool_t bfe_cp949_hanja_to_unicode (bfe_uchar16_t cp949, bfe_wchar_t* unicode)
{
	bfe_int_t index;


	index = bfe_cp949_hanja_4888_index (cp949);
	if (index == -1)
		return BFE_FALSE;

	*unicode = bfe_code_table_cp949_hanja_4888_to_unicode[index];

	return BFE_TRUE;
}

#endif

//===========================================================================
bfe_int_t bfe_mbcs_to_wcs (bfe_char_t* mbcs_string, bfe_int_t mbcs_length, bfe_wchar_t* wcs_string, bfe_int_t wcs_length)
{
	bfe_wchar_t   unicode;
	bfe_uchar16_t ch2;
	bfe_byte_t    ch1;
	bfe_int_t     wcs_index;
	bfe_int_t     mbcs_index;


	wcs_index = 0;
	for (mbcs_index=0; *(mbcs_string+mbcs_index)!=0x00u; mbcs_index++)
	{
		if (wcs_length>=0 && wcs_index>=wcs_length)
			break;

		if (mbcs_length>=0 && mbcs_index>=mbcs_length)
			break;


		ch1 = *(mbcs_string+mbcs_index);
		
		if (ch1 < 0x80u)
		{
			// ASCII
			*(wcs_string+wcs_index) = ch1;
			wcs_index ++;
		}
		else
		{
			ch2 = (bfe_byte_t) *(mbcs_string+mbcs_index+1u);
			ch2 = (ch1 << 8u) | ch2;

			if      (bfe_cp949_hangul_to_unicode  (ch2, &unicode) == BFE_TRUE)
			{
				*(wcs_string+wcs_index) = unicode;
				wcs_index ++;
				mbcs_index++;
			}

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
			else if (bfe_cp949_special_to_unicode (ch2, &unicode) == BFE_TRUE)
			{
				*(wcs_string+wcs_index) = unicode;
				wcs_index ++;
				mbcs_index++;
			}
#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)
			else if (bfe_cp949_hanja_to_unicode   (ch2, &unicode) == BFE_TRUE)
			{
				*(wcs_string+wcs_index) = unicode;
				wcs_index ++;
				mbcs_index++;
			}
#endif

			else
			{
				*(wcs_string+wcs_index) = ch1;
				wcs_index ++;
			}
		}
	}
	if (wcs_index<wcs_length)
	{
		*(wcs_string+wcs_index) = 0x0000u;
	}
	
	return wcs_index;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bfe_bool_t bfe_unicode_to_cp949_hangul (bfe_wchar_t unicode, bfe_uchar16_t* cp949)
{
	bfe_int_t index;


	// 유니코드 한글 낱글자 51자: 0x3131u 'ㄱ' - 0x3163u 'ㅣ'
	// 완성형   한글 낱글자 51자: 0xA4A1u 'ㄱ' - 0xA4D3u 'ㅣ'
	if (unicode>=0x3131u && unicode<=0x3163u)
	{
		*cp949 = 0xA4A1u + unicode-0x3131u;
		return BFE_TRUE;
	}


	// 유니코드 한글 11172자: 0xAC00u '가' - 0xD7A3u '힣'
	if (unicode>=0xAC00u && unicode<=0xD7A3u)
	{
		index = unicode - 0xAC00u;
		*cp949 = bfe_code_table_unicode_to_cp949_hangul_11172[index]; 
		return BFE_TRUE;
	}

	return BFE_FALSE;
}

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)

bfe_bool_t bfe_unicode_to_cp949_special (bfe_wchar_t unicode, bfe_uchar16_t* cp949)
{
	bfe_int_t index;


	// 완성형한글.특수문자1128자: 0xA1A1u - 0xACFEu
	for (index=0; index<1128; index++)
	{
		if (unicode == bfe_code_table_cp949_special_1128_to_unicode[index])
		{
			*cp949 = 0xA1A1u + index/94u*0x0100u + index%94u;
			return BFE_TRUE;
		}
	}

	return BFE_FALSE;
}

#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)

bfe_bool_t bfe_unicode_to_cp949_hanja (bfe_wchar_t unicode, bfe_uchar16_t* cp949)
{
	bfe_int_t index;


	// 완성형한글.한자4888자: 0xCAA1u-0xFDFEu
	for (index=0; index<4888; index++)
	{
		if (unicode == bfe_code_table_cp949_hanja_4888_to_unicode[index])
		{
			*cp949 = 0xCAA1u + index/94u*0x0100u + index%94u;
			return BFE_TRUE;
		}
	}

	return BFE_FALSE;
}

#endif

//===========================================================================
bfe_int_t bfe_wcs_to_mbcs (bfe_wchar_t* wcs_string, bfe_int_t wcs_length, bfe_char_t* mbcs_string, bfe_int_t mbcs_length)
{
	bfe_wchar_t   unicode;
	bfe_byte_t    ch1;
	bfe_uchar16_t ch2;
	bfe_int_t     wcs_index;
	bfe_int_t     mbcs_index;

	
	mbcs_index = 0;
	for (wcs_index=0; *(wcs_string+wcs_index)!=0x0000u; wcs_index++)
	{
		if (wcs_length>=0 && wcs_index>=wcs_length)
			break;

		if (mbcs_length>=0 && mbcs_index>=mbcs_length)
			break;


		unicode = *(wcs_string+wcs_index);
		
		if (unicode < 0x0080u)
		{
			ch1 = (unicode & 0x00FFu);
			*(mbcs_string+mbcs_index) = ch1;
			mbcs_index ++;
		}
		else if (bfe_unicode_to_cp949_hangul  (unicode, &ch2) == BFE_TRUE)
		{		
			*(mbcs_string+mbcs_index  ) = (ch2 & 0xFF00u) >> 8u;
			*(mbcs_string+mbcs_index+1) = (ch2 & 0x00FFu);
			mbcs_index +=2;
		}

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
		else if (bfe_unicode_to_cp949_special (unicode, &ch2) == BFE_TRUE)
		{		
			*(mbcs_string+mbcs_index  ) = (ch2 & 0xFF00u) >> 8u;
			*(mbcs_string+mbcs_index+1) = (ch2 & 0x00FFu);
			mbcs_index +=2;
		}
#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)

		else if (bfe_unicode_to_cp949_hanja   (unicode, &ch2) == BFE_TRUE)
		{		
			*(mbcs_string+mbcs_index  ) = (ch2 & 0xFF00u) >> 8u;
			*(mbcs_string+mbcs_index+1) = (ch2 & 0x00FFu);
			mbcs_index +=2;
		}
#endif

		else
		{
			ch1 = (unicode & 0x00FFu);
			*(mbcs_string+mbcs_index) = ch1;
			mbcs_index ++;
		}
	}
	if (mbcs_index<mbcs_length)
	{
		*(mbcs_string+mbcs_index) = 0x00u;
	}
	
	return mbcs_index;
}

#endif





/////////////////////////////////////////////////////////////////////////////
//
// 글자입력
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#ifdef _MSC_VER

#if 1==BFE_DEBUG_TEST





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void bfe_debug_source_charset (void)
{
	/*
	# arm
	C Source File = CP949
	char   (1) :  "가" = b0 a1 00
	wchar_t(2) : L"가" = b0 00 a1 00 00 00

	C Source File = utf8
	char   (1) :  "가" = ea b0 80 00
	wchar_t(2) : L"가" = 00 ac 00 00

	# msvc
	C Source File = CP949
	char   (1) :  "가" = b0 a1 00
	wchar_t(2) : L"가" = 00 ac 00 00

	C Source File = utf8
	char   (1) :  "가" = b0 a1 00
	wchar_t(2) : L"가" = 00 ac 00 00
	*/

	char    hangul_narrow[] = {  "가" };
	wchar_t hangul_wide  [] = { L"가" };

	unsigned char* p;
	int i;
	int count;


	count = sizeof(hangul_narrow);
	p = (unsigned char*)hangul_narrow;
	printf("char   (%d) :  \"GA\" = ", sizeof(char));
	for (i = 0u; i < count; i++)
	{
		printf("%02x ", p[i] & 0xFFu);
	}
	printf("\r\n");


	count = sizeof(hangul_wide);
	p = (unsigned char*)hangul_wide;
	printf("wchar_t(%d) : L\"GA\" = ", sizeof(wchar_t));
	for (i = 0u; i < count; i++)
	{
		printf("%02x ", p[i] & 0xFFu);
	}
	printf("\r\n");
}

void bfe_debug_font_bitmap (bfe_font_bitmap_t* fb)
{
	static const bfe_byte_t mask[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

	bfe_uint_t x;
	bfe_uint_t y;


	for (y=0u; y<fb->font_bitmap_cy; y++)
	{
		for (x=0u; x<fb->font_bitmap_cx; x++)
		{
			if ( fb->font_bitmap_pointer[ y*fb->font_bitmap_cx_size + x/8u ] & mask[x % 8] )
			{
				printf ("*");
			}
			else
			{
				printf (".");
			}
		}
		printf ("\r\n");
	}
	printf ("\r\n");
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bfe_context_t _ctx;
bfe_font_bitmap_t _fb;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void bfe_debug_test_wchar(bfe_wchar_t s)
{
	bfe_get_wchar_font_bitmap(&_ctx, s, &_fb);bfe_debug_font_bitmap(&_fb);
}



//===========================================================================
void bfe_debug_test_char(bfe_char_t s)
{
	bfe_get_char_font_bitmap(&_ctx, s, &_fb);bfe_debug_font_bitmap(&_fb);
}

void bfe_debug_test_char_s(bfe_char_t* s)
{
	bfe_byte_t ch0;
	bfe_byte_t ch1;
	bfe_uchar16_t code;


	ch0 = *(s);
	ch1 = *(s+1);

	code = ch0 << 8u | ch1;

	bfe_get_char_font_bitmap(&_ctx, code, &_fb);bfe_debug_font_bitmap(&_fb);
}

void bfe_debug_test_char_2(bfe_uchar16_t s)
{
	bfe_get_char_font_bitmap(&_ctx, s, &_fb);bfe_debug_font_bitmap(&_fb);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int _tmain(int argc, TCHAR* argv[])
{
	bfe_debug_source_charset();
	bfe_default_font_initialize();

	bfe_initialize(&_ctx);


	//-----------------------------------------------------------------------
	// unicode font
	//-----------------------------------------------------------------------
#if 1
#if 1
	// ascii low
	bfe_debug_test_wchar(L'A');bfe_debug_test_wchar(L'a');
	bfe_debug_test_wchar(L'Z');bfe_debug_test_wchar(L'z');
	bfe_debug_test_wchar(L'0');bfe_debug_test_wchar(L'9');
	bfe_debug_test_wchar(0x00);bfe_debug_test_wchar(0x7f);
#endif


#if 1
	// hangul
	bfe_debug_test_wchar(L'가');bfe_debug_test_wchar(L'힣'); // 2350
	bfe_debug_test_wchar(L'갂');bfe_debug_test_wchar(L'좤'); // 8822
	bfe_debug_test_wchar(L'좥');bfe_debug_test_wchar(L'힋'); // 
	bfe_debug_test_wchar(L'힍');bfe_debug_test_wchar(L'힣'); // 
#endif


#if 1
	// hangul-jamo-jaeum/moeum
	bfe_debug_test_wchar(0x3131u);bfe_debug_test_wchar(0x314Eu); // jaeum
	bfe_debug_test_wchar(0x314Fu);bfe_debug_test_wchar(0x3163u); // moeum

	// hangul-jamo-choseong/jungseong/jongseong
	bfe_debug_test_wchar(0x1100u);bfe_debug_test_wchar(0x1112u); // choseong
	bfe_debug_test_wchar(0x1161u);bfe_debug_test_wchar(0x1175u); // jungseong
	bfe_debug_test_wchar(0x11A8u);bfe_debug_test_wchar(0x11C2u); // jongseong
#endif


#if 1
	// hanja
	// 0x4E00u '一' - 0x9F9Cu '龜'
	// 0xF900u '豈' - 0xF9FFu '刺'
	// 0xFA00u '切' - 0xFA0Bu '廓'
	bfe_debug_test_wchar(L'伽');bfe_debug_test_wchar(L'詰');
	bfe_debug_test_wchar(0x4E00u);bfe_debug_test_wchar(0x9F9Cu);
	bfe_debug_test_wchar(0xF900u);bfe_debug_test_wchar(0xF9FFu);
	bfe_debug_test_wchar(0xFA00u);bfe_debug_test_wchar(0xFA0Bu);
#endif


#if 1
	// special
	// 0x00A1u '¡' - 0x00FEu 'þ'
	// 0x0111u 'đ'  - 0x0451u 'ё'
	// 0x2015u '―' - 0x266Du '♭'
	// 0x3000u '　' - 0x33DDu '㏝'
	// 0xFF01u '！' - 0xFFE6u '￦'
	bfe_debug_test_wchar(L'。');bfe_debug_test_wchar(L'я');
	bfe_debug_test_wchar(0x00A1u);bfe_debug_test_wchar(0x00FEu);
	bfe_debug_test_wchar(0x0111u);bfe_debug_test_wchar(0x0451u);
	bfe_debug_test_wchar(0x2015u);bfe_debug_test_wchar(0x266Du);
	bfe_debug_test_wchar(0x3000u);bfe_debug_test_wchar(0x33DDu);
	bfe_debug_test_wchar(0xFF01u);bfe_debug_test_wchar(0xFFE6u);
#endif
#endif


	//-----------------------------------------------------------------------
	// cp949 font
	//-----------------------------------------------------------------------
#if 1
#if 1
	// ascii low
	bfe_debug_test_char('A');bfe_debug_test_char('a');
	bfe_debug_test_char('Z');bfe_debug_test_char('z');
	bfe_debug_test_char('0');bfe_debug_test_char('9');
	bfe_debug_test_char(0x00);bfe_debug_test_char(0x7f);
#endif


#if 1
	// hangul
	bfe_debug_test_char_s("가");bfe_debug_test_char_s("힣"); // 2350
	bfe_debug_test_char_s("갂");bfe_debug_test_char_s("좤"); // 8822
	bfe_debug_test_char_s("좥");bfe_debug_test_char_s("힋"); // 
	bfe_debug_test_char_s("힍");bfe_debug_test_char_s("힣"); // 
#endif


#if 1
	// hangul-jamo-jaeum/moeum
	bfe_debug_test_char_2(0xA4A1u);bfe_debug_test_char_2(0xA4BEu); // jaeum
	bfe_debug_test_char_2(0xA4BFu);bfe_debug_test_char_2(0xA4D3u); // moeum
#endif


#if 1
	// hanja
	bfe_debug_test_char_s("伽");bfe_debug_test_char_s("詰");
	bfe_debug_test_char_s("一");bfe_debug_test_char_s("龜");
	bfe_debug_test_char_s("豈");bfe_debug_test_char_s("刺");
	bfe_debug_test_char_s("切");bfe_debug_test_char_s("廓");
#endif


#if 1
	// special
	bfe_debug_test_char_s("。");bfe_debug_test_char_s("я");
#endif
#endif


	//-----------------------------------------------------------------------
	// cp949 <-> unicode
	//-----------------------------------------------------------------------
#if 1
	char    mbcs_string [] =  "AZaz09가힣갂좤좥힋힍힣ㄱㅎㅏㅣ伽詰一龜豈刺切廓。я"; // 28 글자 6+22*2바이트
	wchar_t wcs_string  [] = L"AZaz09가힣갂좤좥힋힍힣ㄱㅎㅏㅣ伽詰一龜豈刺切廓。я"; // 28 글자 36바이트

	char    mbcs[51];
	wchar_t wcs [51];
	int     mbcs_length;
	int     wcs_length;


	memset (mbcs, 0, sizeof(mbcs));
	memset (wcs , 0, sizeof(wcs ));

	wcs_length = bfe_mbcs_to_wcs(mbcs_string, strlen(mbcs_string), wcs, 1024);
	printf  ( "%d:%s", strlen(mbcs_string), mbcs_string);
	printf  ( "->");
	wprintf (L"%d:%s", wcs_length, wcs);
	printf  ( "\r\n");

	mbcs_length = bfe_wcs_to_mbcs(wcs_string, wcslen(wcs_string), mbcs, 1024);
	wprintf (L"%d:%s", wcslen(wcs_string), wcs_string);
	printf  ( "->");
	printf  ( "%d:%s", mbcs_length, mbcs);
	printf  ( "\r\n");


	memset (mbcs, 0, sizeof(mbcs));
	memset (wcs , 0, sizeof(wcs ));

	memset (mbcs, 0xFF, sizeof(mbcs)-1);
	memset (wcs , 0xFF, sizeof(wcs )-2);

	wcs_length = bfe_mbcs_to_wcs(mbcs_string, 0, wcs, 0);
	printf  ( "%d:%s", strlen(mbcs_string), mbcs_string);
	printf  ( "->");
	wprintf (L"%d:%s", wcs_length, wcs);
	printf  ( "\r\n");

	mbcs_length = bfe_wcs_to_mbcs(wcs_string, 0, mbcs, 0);
	wprintf (L"%d:%s", wcslen(wcs_string), wcs_string);
	printf  ( "->");
	printf  ( "%d:%s", mbcs_length, mbcs);
	printf  ( "\r\n");


#endif

	return 0;
}





#endif
#endif




