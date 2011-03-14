#ifndef _NULLPO_H_
#define _NULLPO_H_

#define NULLPO_CHECK 1
        // 全体のスイッチを宣言しているヘッダがあれば
        // そこに移動していただけると

#if __STDC_VERSION__ < 199901L
# if __GNUC__ >= 2
#  define __func__ __FUNCTION__
# else
#  define __func__ ""
# endif
#endif

#ifdef LCCWIN32
#define __attribute__(x)        /* nothing */
#endif

#define NLP_MARK __FILE__, __LINE__, __func__

/*----------------------------------------------------------------------------
 * Macros
 *----------------------------------------------------------------------------
 */
/*======================================
 * Nullチェック 及び 情報出力後 return
 *・展開するとifとかreturn等が出るので
 *  一行単体で使ってください。
 *・nullpo_ret(x = func());
 *  のような使用法も想定しています。
 *--------------------------------------
 * nullpo_ret(t)
 *   戻り値 0固定
 * [引数]
 *  t       チェック対象
 *--------------------------------------
 * nullpo_retv(t)
 *   戻り値 なし
 * [引数]
 *  t       チェック対象
 *--------------------------------------
 * nullpo_retr(ret, t)
 *   戻り値 指定
 * [引数]
 *  ret     return(ret);
 *  t       チェック対象
 *--------------------------------------
 * nullpo_ret_f(t, fmt, ...)
 *   詳細情報出力用
 *   戻り値 0
 * [引数]
 *  t       チェック対象
 *  fmt ... vprintfに渡される
 *    備考や関係変数の書き出しなどに
 *--------------------------------------
 * nullpo_retv_f(t, fmt, ...)
 *   詳細情報出力用
 *   戻り値 なし
 * [引数]
 *  t       チェック対象
 *  fmt ... vprintfに渡される
 *    備考や関係変数の書き出しなどに
 *--------------------------------------
 * nullpo_retr_f(ret, t, fmt, ...)
 *   詳細情報出力用
 *   戻り値 指定
 * [引数]
 *  ret     return(ret);
 *  t       チェック対象
 *  fmt ... vprintfに渡される
 *    備考や関係変数の書き出しなどに
 *--------------------------------------
 */

#if NULLPO_CHECK

#define nullpo_ret(t) \
	if (nullpo_chk(NLP_MARK, (void *)(t))) {return(0);}

#define nullpo_retv(t) \
	if (nullpo_chk(NLP_MARK, (void *)(t))) {return;}

#define nullpo_retr(ret, t) \
	if (nullpo_chk(NLP_MARK, (void *)(t))) {return(ret);}

// 可変引数マクロに関する条件コンパイル
#if __STDC_VERSION__ >= 199901L
/* C99に対応 */
#define nullpo_ret_f(t, fmt, ...) \
	if (nullpo_chk_f(NLP_MARK, (void *)(t), (fmt), __VA_ARGS__)) {return(0);}

#define nullpo_retv_f(t, fmt, ...) \
	if (nullpo_chk_f(NLP_MARK, (void *)(t), (fmt), __VA_ARGS__)) {return;}

#define nullpo_retr_f(ret, t, fmt, ...) \
	if (nullpo_chk_f(NLP_MARK, (void *)(t), (fmt), __VA_ARGS__)) {return(ret);}

#elif __GNUC__ >= 2
/* GCC用 */
#define nullpo_ret_f(t, fmt, args...) \
	if (nullpo_chk_f(NLP_MARK, (void *)(t), (fmt), ## args)) {return(0);}

#define nullpo_retv_f(t, fmt, args...) \
	if (nullpo_chk_f(NLP_MARK, (void *)(t), (fmt), ## args)) {return;}

#define nullpo_retr_f(ret, t, fmt, args...) \
	if (nullpo_chk_f(NLP_MARK, (void *)(t), (fmt), ## args)) {return(ret);}

#else

/* その他の場合・・・ orz */

#endif

#else /* NULLPO_CHECK */
/* No Nullpo check */

// if((t)){;}
// 良い方法が思いつかなかったので・・・苦肉の策です。
// 一応ワーニングは出ないはず

#define nullpo_ret(t) if((t)){;}
#define nullpo_retv(t) if((t)){;}
#define nullpo_retr(ret, t) if((t)){;}

// 可変引数マクロに関する条件コンパイル
#if __STDC_VERSION__ >= 199901L
/* C99に対応 */
#define nullpo_ret_f(t, fmt, ...) if((t)){;}
#define nullpo_retv_f(t, fmt, ...) if((t)){;}
#define nullpo_retr_f(ret, t, fmt, ...) if((t)){;}

#elif __GNUC__ >= 2
/* GCC用 */
#define nullpo_ret_f(t, fmt, args...) if((t)){;}
#define nullpo_retv_f(t, fmt, args...) if((t)){;}
#define nullpo_retr_f(ret, t, fmt, args...) if((t)){;}

#else
/* その他の場合・・・ orz */
#endif

#endif /* NULLPO_CHECK */

/*----------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------
 */
/*======================================
 * nullpo_chk
 *   Nullチェック 及び 情報出力
 * [引数]
 *  file    __FILE__
 *  line    __LINE__
 *  func    __func__ (関数名)
 *    これらには NLP_MARK を使うとよい
 *  target  チェック対象
 * [返り値]
 *  0 OK
 *  1 NULL
 *--------------------------------------
 */
int  nullpo_chk (const char *file, int line, const char *func,
                 const void *target);

/*======================================
 * nullpo_chk_f
 *   Nullチェック 及び 詳細な情報出力
 * [引数]
 *  file    __FILE__
 *  line    __LINE__
 *  func    __func__ (関数名)
 *    これらには NLP_MARK を使うとよい
 *  target  チェック対象
 *  fmt ... vprintfに渡される
 *    備考や関係変数の書き出しなどに
 * [返り値]
 *  0 OK
 *  1 NULL
 *--------------------------------------
 */
int  nullpo_chk_f (const char *file, int line, const char *func,
                   const void *target, const char *fmt, ...)
    __attribute__ ((format (printf, 5, 6)));

/*======================================
 * nullpo_info
 *   nullpo情報出力
 * [引数]
 *  file    __FILE__
 *  line    __LINE__
 *  func    __func__ (関数名)
 *    これらには NLP_MARK を使うとよい
 *--------------------------------------
 */
void nullpo_info (const char *file, int line, const char *func);

/*======================================
 * nullpo_info_f
 *   nullpo詳細情報出力
 * [引数]
 *  file    __FILE__
 *  line    __LINE__
 *  func    __func__ (関数名)
 *    これらには NLP_MARK を使うとよい
 *  fmt ... vprintfに渡される
 *    備考や関係変数の書き出しなどに
 *--------------------------------------
 */
void nullpo_info_f (const char *file, int line, const char *func,
                    const char *fmt, ...)
    __attribute__ ((format (printf, 4, 5)));

#endif
