/*****************************************************************************************/
/*                                                                                       */
/*[システム名]    ロード2語関数                                                          */
/*                                                                                       */
/*[機能概要]      OPCode副OPが0x10有効アドレスの中身をＲに設定する関数                   */
/*                                                                                       */
/*[記述形式]      int fnc_ld2(Ttracetbl  *pk_trace, unsigned short *puh_1st_adr )        */
/*                                                                                       */
/*[パラメータ]    Ttracetbl       *pk_trace     (I/O)トレースリスト用構造体              */
/*                unsigned short  *puh_1st_adr  (I)仮想メモリの先頭アドレス              */
/*                                                                                       */
/*[戻り値]        RESULT_OK         正常終了                                             */
/*                                                                                       */
/*[特記事項]      なし                                                                   */
/*                                                                                       */
/*[改版履歴]      作成    2021.12.21  **********                                         */
/*                                                                                       */
/*****************************************************************************************/
#include "fnc_ld2.h"

int fnc_ld2(Ttracetbl *pk_trace, unsigned short *puh_1st_adr)
{
	/*ヌルポインタチェック*/
    if(puh_1st_adr == NULL) {
        return ERROR_NULL;
    }
	
	/*ロード処理*/
	pk_trace->auh_ogr[pk_trace->uh_g] = *(puh_1st_adr + pk_trace->uh_ea);

	/*フラグの初期化*/
	pk_trace->uh_fr = 0x0000;
	
	/*ゼロフラグ判定*/

	if((short)pk_trace->auh_ogr[pk_trace->uh_g] == 0) {
		pk_trace->uh_fr |= FR_ZERO_FRAG;
	}
	
	/*サインフラグ判定*/
	if((short)(pk_trace->auh_ogr[pk_trace->uh_g]) < 0) {
		pk_trace->uh_fr |= FR_SIGN_FRAG;
	}

	/*プログラムレジスタ更新*/
	pk_trace->uh_pr += 2;
	
	/*正常終了*/
	return RESULT_OK;
}
