/*


//---------------------------------------------------------------------------------------------------------------
//
//
// [ 入門 ] キーボード入力を検知する基本的サンプル
// 
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"

// キーを押しっぱなしでカウントアップし続ける変数
int on_keep_count_up_value = 0;

// キーが押された瞬間だけカウントアップする変数
int on_trigger_count_up_value = 0;


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));

	// 描画される文字列のサイズを変更
	SetFontSize(50);
}



//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	// 押しっぱなしを検知
	if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		on_keep_count_up_value++;
	}

	// 押した瞬間を検知
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
		on_trigger_count_up_value++;
	}

	DrawStringEx(0, 0, -1, "押しっぱなし(Z) %d", on_keep_count_up_value);

	DrawStringEx(0, 50, -1, "押した瞬間(X) %d", on_trigger_count_up_value);



	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}


//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
}


*/