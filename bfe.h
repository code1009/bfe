#ifndef __bfe_h__
#define __bfe_h__

/****************************************************************************
**
** File: bfe.h
**
** Created by MOON, Eui-kwon.
** Created on Nov-14th, 2019.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
/****************************************************************************

# 한글 Bitmap Font 8x4x4 폰트 정보

- 초성8벌
  1벌: 종성==X && 중성=="ㅏㅐㅑㅒㅣㅓㅔㅕㅖ"
  2벌: 종성==X && 중성=="ㅗㅛㅡ"
  3벌: 종성==X && 중성=="ㅜㅠ"
  4벌: 종성==X && 중성=="ㅘㅙㅚㅢ"
  5벌: 종성==X && 중성=="ㅝㅞㅟ"
  6벌: 종성==O && 중성=="ㅏㅐㅑㅒㅣㅓㅔㅕㅖ"
  7벌: 종성==O && 중성=="ㅗㅛㅡㅜㅠ"
  8벌: 종성==O && 중성=="ㅘㅙㅚㅢㅝㅞㅟ"

- 중성4벌
  1벌: 종성==X && 초성=="ㄱㅋ"
  2벌: 종성==X && 초성!="ㄱㅋ"
  3벌: 종성==O && 초성=="ㄱㅋ"
  4벌: 종성==O && 초성!="ㄱㅋ"

- 종성4벌
  1벌: 중성=="ㅏㅑㅘㅣ"
  2벌: 중성=="ㅓㅕㅚㅝㅟㅢ"
  3벌: 중성=="ㅐㅒㅔㅖㅙㅞ"
  4벌: 중성=="ㅗㅛㅜㅠㅡ"



# 유니코드 한글 자소 분리
- 초성:  (n-0xAC00)/(21*28)
- 중성: ((n-0xAC00)%(21*28))/28
- 종성:  (n-0xAC00)%28

- 자소분리 Index 번호
  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |번호| 0| 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|
  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |초성|ㄱ|ㄲ|ㄴ|ㄷ|ㄸ|ㄹ|ㅁ|ㅂ|ㅃ|ㅅ|ㅆ|ㅇ|ㅈ|ㅉ|ㅊ|ㅋ|ㅌ|ㅍ|ㅎ|##|##|##|##|##|##|##|##|##|
  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |중성|ㅏ|ㅐ|ㅑ|ㅒ|ㅓ|ㅔ|ㅕ|ㅖ|ㅗ|ㅘ|ㅙ|ㅚ|ㅛ|ㅜ|ㅝ|ㅞ|ㅟ|ㅠ|ㅡ|ㅢ|ㅣ|##|##|##|##|##|##|##|
  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |종성|  |ㄱ|ㄲ|ㄳ|ㄴ|ㄵ|ㄶ|ㄷ|ㄹ|ㄺ|ㄻ|ㄼ|ㄽ|ㄾ|ㄿ|ㅀ|ㅁ|ㅂ|ㅄ|ㅅ|ㅆ|ㅇ|ㅈ|ㅊ|ㅋ|ㅌ|ㅍ|ㅎ|
  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+



# 완성형한글.특수문자의 한글 낱글자
  - 유니코드 한글 낱글자 51자: 0x3131 'ㄱ' - 0x3163 'ㅣ'
  - 완성형   한글 낱글자 51자: 0xA4A1 'ㄱ' - 0xA4D3 'ㅣ'
  ㄱㄲㄳㄴㄵㄶㄷㄸㄹㄺㄻㄼㄽㄾㄿㅀㅁㅂㅃㅄㅅㅆㅇㅈㅉㅊㅋㅌㅍㅎ(30자) : 종성에서ㄸ,ㅃ,ㅉ추가
  ㅏㅐㅑㅒㅓㅔㅕㅖㅗㅘㅙㅚㅛㅜㅝㅞㅟㅠㅡㅢㅣ(21자) : 중성과 동일

  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |번호| 0| 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|
  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |자음|ㄱ|ㄲ|ㄳ|ㄴ|ㄵ|ㄶ|ㄷ|ㄸ|ㄹ|ㄺ|ㄻ|ㄼ|ㄽ|ㄾ|ㄿ|ㅀ|ㅁ|ㅂ|ㅃ|ㅄ|ㅅ|ㅆ|ㅇ|ㅈ|ㅉ|ㅊ|ㅋ|ㅌ|ㅍ|ㅎ|
  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
       | 0| 1|  | 2|  |  | 3| 4| 5|  |  |  |  |  |  |  | 6| 7| 8|  | 9|10|11|12|13|14|15|16|17|18| 초성번호
       |  |  | 3|  | 5| 6|  |  |  | 9|10|11|12|13|14|15|  |  |  |18|  |  |  |  |  |  |  |  |  |  | 종성번호
       | 1| 2|  | 4|  |  | 7|  | 8|  |  |  |  |  |  |  |16|17|  |  |19|20|21|22|  |23|24|25|26|27| 종성번호
       +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |번호| 0| 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|19|20|
  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |모음|ㅏ|ㅐ|ㅑ|ㅒ|ㅓ|ㅔ|ㅕ|ㅖ|ㅗ|ㅘ|ㅙ|ㅚ|ㅛ|ㅜ|ㅝ|ㅞ|ㅟ|ㅠ|ㅡ|ㅢ|ㅣ|
  +----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+



# 유니코드 한글 자모 코드표(자음/모음)
  +------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
  | U+   |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  A |  B |  C |  D |  E |  F |
  +------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
  | 3130 |    | ㄱ | ㄲ | ㄳ | ㄴ | ㄵ | ㄶ | ㄷ | ㄸ | ㄹ | ㄺ | ㄻ | ㄼ | ㄽ | ㄾ | ㄿ |
  | 3140 | ㅀ | ㅁ | ㅂ | ㅃ | ㅄ | ㅅ | ㅆ | ㅇ | ㅈ | ㅉ | ㅊ | ㅋ | ㅌ | ㅍ | ㅎ | ㅏ |
  | 3150 | ㅐ | ㅑ | ㅒ | ㅓ | ㅔ | ㅕ | ㅖ | ㅗ | ㅘ | ㅙ | ㅚ | ㅛ | ㅜ | ㅝ | ㅞ | ㅟ |
  | 3160 | ㅠ | ㅡ | ㅢ | ㅣ | ㅤ | ㅥ | ㅦ | ㅧ | ㅨ | ㅩ | ㅪ | ㅫ | ㅬ | ㅭ | ㅮ | ㅯ |
  | 3170 | ㅰ | ㅱ | ㅲ | ㅳ | ㅴ | ㅵ | ㅶ | ㅷ | ㅸ | ㅹ | ㅺ | ㅻ | ㅼ | ㅽ | ㅾ | ㅿ |
  | 3180 | ㆀ | ㆁ | ㆂ | ㆃ | ㆄ | ㆅ | ㆆ | ㆇ | ㆈ | ㆉ | ㆊ | ㆋ | ㆌ | ㆍ | ㆎ |    |
  +------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+



# 유니코드 한글 자모 코드표(초성/중성/중성)
  +------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
  | U+   |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  A |  B |  C |  D |  E |  F |
  +------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
  | 1100 | ᄀ | ᄁ | ᄂ | ᄃ | ᄄ | ᄅ | ᄆ | ᄇ | ᄈ | ᄉ | ᄊ | ᄋ | ᄌ | ᄍ | ᄎ | ᄏ |
  | 1110 | ᄐ | ᄑ | ᄒ | ᄓ | ᄔ | ᄕ | ᄖ | ᄗ | ᄘ | ᄙ | ᄚ | ᄛ | ᄜ | ᄝ | ᄞ | ᄟ |
  | 1120 | ᄠ | ᄡ | ᄢ | ᄣ | ᄤ | ᄥ | ᄦ | ᄧ | ᄨ | ᄩ | ᄪ | ᄫ | ᄬ | ᄭ | ᄮ | ᄯ |
  | 1130 | ᄰ | ᄱ | ᄲ | ᄳ | ᄴ | ᄵ | ᄶ | ᄷ | ᄸ | ᄹ | ᄺ | ᄻ | ᄼ | ᄽ | ᄾ | ᄿ |
  | 1140 | ᅀ | ᅁ | ᅂ | ᅃ | ᅄ | ᅅ | ᅆ | ᅇ | ᅈ | ᅉ | ᅊ | ᅋ | ᅌ | ᅍ | ᅎ | ᅏ |
  | 1150 | ᅐ | ᅑ | ᅒ | ᅓ | ᅔ | ᅕ | ᅖ | ᅗ | ᅘ | ᅙ | ᅚ | ᅛ | ᅜ | ᅝ | ᅞ | ᅟ |
  | 1160 | ᅠ | ᅡ | ᅢ | ᅣ | ᅤ | ᅥ | ᅦ | ᅧ | ᅨ | ᅩ | ᅪ | ᅫ | ᅬ | ᅭ | ᅮ | ᅯ |
  | 1170 | ᅰ | ᅱ | ᅲ | ᅳ | ᅴ | ᅵ | ᅶ | ᅷ | ᅸ | ᅹ | ᅺ | ᅻ | ᅼ | ᅽ | ᅾ | ᅿ |
  | 1180 | ᆀ | ᆁ | ᆂ | ᆃ | ᆄ | ᆅ | ᆆ | ᆇ | ᆈ | ᆉ | ᆊ | ᆋ | ᆌ | ᆍ | ᆎ | ᆏ |
  | 1190 | ᆐ | ᆑ | ᆒ | ᆓ | ᆔ | ᆕ | ᆖ | ᆗ | ᆘ | ᆙ | ᆚ | ᆛ | ᆜ | ᆝ | ᆞ | ᆟ |
  | 11A0 | ᆠ | ᆡ | ᆢ | ᆣ | ᆤ | ᆥ | ᆦ | ᆧ | ᆨ | ᆩ | ᆪ | ᆫ | ᆬ | ᆭ | ᆮ | ᆯ |
  | 11B0 | ᆰ | ᆱ | ᆲ | ᆳ | ᆴ | ᆵ | ᆶ | ᆷ | ᆸ | ᆹ | ᆺ | ᆻ | ᆼ | ᆽ | ᆾ | ᆿ |
  | 11C0 | ᇀ | ᇁ | ᇂ | ᇃ | ᇄ | ᇅ | ᇆ | ᇇ | ᇈ | ᇉ | ᇊ | ᇋ | ᇌ | ᇍ | ᇎ | ᇏ |
  | 11D0 | ᇐ | ᇑ | ᇒ | ᇓ | ᇔ | ᇕ | ᇖ | ᇗ | ᇘ | ᇙ | ᇚ | ᇛ | ᇜ | ᇝ | ᇞ | ᇟ |
  | 11E0 | ᇠ | ᇡ | ᇢ | ᇣ | ᇤ | ᇥ | ᇦ | ᇧ | ᇨ | ᇩ | ᇪ | ᇫ | ᇬ | ᇭ | ᇮ | ᇯ |
  | 11F0 | ᇰ | ᇱ | ᇲ | ᇳ | ᇴ | ᇵ | ᇶ | ᇷ | ᇸ | ᇹ | ᇺ | ᇻ | ᇼ | ᇽ | ᇾ | ᇿ |
  +------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+

****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef signed   int       bfe_int_t    ; 
typedef unsigned int       bfe_uint_t   ;
//===========================================================================
typedef unsigned int       bfe_bool_t   ;
typedef unsigned char      bfe_byte_t   ;
//===========================================================================
typedef unsigned short int bfe_wchar_t  ;
typedef char               bfe_char_t   ;
typedef unsigned short int bfe_uchar16_t;




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define BFE_TRUE  1u
#define BFE_FALSE 0u
#define BFE_NULL_POINTER 0u





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if defined ( __cplusplus )
#	define BFE_API extern "C"
#else
#	define BFE_API extern
#endif




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define BFE_CONFIG_UNICODE_HANGUL  1
#define BFE_CONFIG_UNICODE_SPECIAL 1
#define BFE_CONFIG_UNICODE_HANJA   1

#define BFE_CONFIG_CP949_HANGUL    1
#define BFE_CONFIG_CP949_HANJA     1
#define BFE_CONFIG_CP949_SPECIAL   1

#define BFE_CONFIG_CODE_CONVERSION 1





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define BFE_FONT_TYPE_UNKNOWN             0
#define BFE_FONT_TYPE_ASCII_LOW           1
#define BFE_FONT_TYPE_HANGUL_JOHAB844     2
#define BFE_FONT_TYPE_CP949_SPECIAL_1128  3
#define BFE_FONT_TYPE_CP949_HANJA_4888    4

#define BFE_CHAR_TYPE_UNKNOWN                0
#define BFE_CHAR_TYPE_ASCII_LOW              1
#define BFE_CHAR_TYPE_ASCII_HIGH             2
#define BFE_CHAR_TYPE_HANGUL                 3
#define BFE_CHAR_TYPE_HANGUL_JAMO_CHOSEONG   4
#define BFE_CHAR_TYPE_HANGUL_JAMO_JUNGSEONG  5
#define BFE_CHAR_TYPE_HANGUL_JAMO_JONGSEONG  6
#define BFE_CHAR_TYPE_HANGUL_JAMO_JAEUM      7
#define BFE_CHAR_TYPE_HANGUL_JAMO_MOEUM      8
#define BFE_CHAR_TYPE_CP949_HANJA_4888       9
#define BFE_CHAR_TYPE_CP949_SPECIAL_1128    10




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define BFE_UNICODE_HANGUL_CHOSEONG(ch)   ((ch-0xAC00u)/(21*28))
#define BFE_UNICODE_HANGUL_JUNGSEONG(ch) (((ch-0xAC00u)%(21*28))/28)
#define BFE_UNICODE_HANGUL_JONGSEONG(ch)  ((ch-0xAC00u)%28)





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _bfe_font_t
{
	bfe_byte_t* font_data_pointer;
	bfe_uint_t  font_data_size;
	bfe_uint_t  font_type;
	bfe_uint_t  font_count;
	bfe_uint_t  font_size;
	bfe_uint_t  font_cx;
	bfe_uint_t  font_cy;
	bfe_uint_t  font_cx_size;
	bfe_uint_t  font_cy_size;
}
bfe_font_t;

typedef struct _bfe_font_hangul_johab844_t
{
	bfe_byte_t* font_data_pointer;
	bfe_uint_t  font_data_size;
	bfe_uint_t  font_type;
	bfe_uint_t  font_count;
	bfe_uint_t  font_size;
	bfe_uint_t  font_cx;
	bfe_uint_t  font_cy;
	bfe_uint_t  font_cx_size;
	bfe_uint_t  font_cy_size;

	bfe_byte_t* choseong [8];
	bfe_byte_t* jungseong[4];
	bfe_byte_t* jongseong[4];
}
bfe_font_hangul_johab844_t;

typedef struct _bfe_font_bitmap_t
{
	bfe_byte_t* font_bitmap_pointer;
	bfe_uint_t  font_bitmap_size;
	bfe_uint_t  font_bitmap_cx;
	bfe_uint_t  font_bitmap_cy;
	bfe_uint_t  font_bitmap_cx_size;
	bfe_uint_t  font_bitmap_cy_size;
}
bfe_font_bitmap_t;

typedef struct _bfe_context_t
{
	bfe_font_t*                 font_unknown           ;
	bfe_font_t*                 font_ascii_low         ;

#if (1==BFE_CONFIG_UNICODE_HANGUL) || (1==BFE_CONFIG_CP949_HANGUL)
	bfe_font_hangul_johab844_t* font_hangul_johab844;
#endif

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
	bfe_font_t*                 font_cp949_special_1128;
#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)
	bfe_font_t*                 font_cp949_hanja_4888;
#endif

#if (1==BFE_CONFIG_UNICODE_HANGUL) || (1==BFE_CONFIG_CP949_HANGUL)
	bfe_byte_t union_font_bitmap_buffer[32]; // 16x16
#endif
}
bfe_context_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bfe_int_t bfe_cp949_hangul_11172_index (bfe_uchar16_t ch);
bfe_int_t bfe_cp949_special_1128_index (bfe_uchar16_t ch);
bfe_int_t bfe_cp949_hanja_4888_index   (bfe_uchar16_t ch);

bfe_int_t bfe_hangul_johab844_choseong_set  (bfe_uint_t choseong, bfe_uint_t jungseong, bfe_uint_t jongseong);
bfe_int_t bfe_hangul_johab844_jungseong_set (bfe_uint_t choseong, bfe_uint_t jungseong, bfe_uint_t jongseong);
bfe_int_t bfe_hangul_johab844_jongseong_set (bfe_uint_t choseong, bfe_uint_t jungseong, bfe_uint_t jongseong);

void bfe_get_font_bitmap_hangul_johab844_jamo_choseong  (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb);
void bfe_get_font_bitmap_hangul_johab844_jamo_jungseong (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb);
void bfe_get_font_bitmap_hangul_johab844_jamo_jongseong (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb);
void bfe_get_font_bitmap_hangul_johab844_jamo_moeum     (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb);
void bfe_get_font_bitmap_hangul_johab844_jamo_jaeum     (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t index, bfe_font_bitmap_t* fb);
void bfe_get_font_bitmap_hangul_johab844                (bfe_context_t* ctx, bfe_font_hangul_johab844_t* f, bfe_uint_t choseong, bfe_uint_t jungseong, bfe_uint_t jongseong, bfe_font_bitmap_t* fb);

bfe_uint_t bfe_get_wchar_type        (bfe_context_t* ctx, bfe_wchar_t ch);
void       bfe_get_wchar_font_bitmap (bfe_context_t* ctx, bfe_wchar_t ch, bfe_font_bitmap_t* fb);

bfe_uint_t bfe_get_char_type        (bfe_context_t* ctx, bfe_uchar16_t ch);
void       bfe_get_char_font_bitmap (bfe_context_t* ctx, bfe_uchar16_t ch, bfe_font_bitmap_t* fb);

void bfe_default_font_initialize (void);

void bfe_initialize (bfe_context_t* ctx);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if (1==BFE_CONFIG_CODE_CONVERSION)

bfe_bool_t bfe_cp949_hangul_to_unicode  (bfe_uchar16_t cp949, bfe_wchar_t* unicode);

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
bfe_bool_t bfe_cp949_special_to_unicode (bfe_uchar16_t cp949, bfe_wchar_t* unicode);
#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)
bfe_bool_t bfe_cp949_hanja_to_unicode   (bfe_uchar16_t cp949, bfe_wchar_t* unicode);
#endif

bfe_int_t bfe_mbcs_to_wcs (bfe_char_t* mbcs_string, bfe_int_t mbcs_length, bfe_wchar_t* wcs_string, bfe_int_t wcs_length);

//===========================================================================
bfe_bool_t bfe_unicode_to_cp949_hangul  (bfe_wchar_t unicode, bfe_uchar16_t* cp949);

#if (1==BFE_CONFIG_UNICODE_SPECIAL) || (1==BFE_CONFIG_CP949_SPECIAL)
bfe_bool_t bfe_unicode_to_cp949_special (bfe_wchar_t unicode, bfe_uchar16_t* cp949);
#endif

#if (1==BFE_CONFIG_UNICODE_HANJA) || (1==BFE_CONFIG_CP949_HANJA)
bfe_bool_t bfe_unicode_to_cp949_hanja   (bfe_wchar_t unicode, bfe_uchar16_t* cp949);
#endif

bfe_int_t bfe_wcs_to_mbsc (bfe_wchar_t* wcs_string, bfe_int_t wcs_length, bfe_char_t* mbcs_string, bfe_int_t mbcs_length);

#endif





/////////////////////////////////////////////////////////////////////////////
//===========================================================================




#endif




