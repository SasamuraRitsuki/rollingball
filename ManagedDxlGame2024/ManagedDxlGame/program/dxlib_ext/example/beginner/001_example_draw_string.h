/*

//---------------------------------------------------------------------------------------------------------------
//
//
// [ 入門 ] 文字列描画
//
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"

// 描画される整数型変数( int 型 )
int draw_value_int = 10;

// 描画される浮動小数型変数( float 型 )
float draw_value_float = 1.23456f;

// 描画される文字列型変数( std::string 型 )
std::string draw_string = "hello world";

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));
}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	// 描画する文字列のサイズを設定
	SetFontSize(20);

	// 通常の文字描画
	DrawStringEx(0, 0, -1, "通常の文字列描画");

	// 緑色で文字描画
	// GetColor に指定した色は 0 〜 255 で左から 赤, 緑, 青 成分です
	DrawStringEx(0, 20, GetColor(0, 255, 0), "色を付けた文字列描画");

	// 変数の値を描画するには " で囲った中で %d や %f キーワードを使用します
	// int 型の場合は 数値を描画したい場所に %d を設定し
	// 終わりの " 後に対象の変数を指定します
	DrawStringEx(0, 40, -1, "変数の内容を描画 (int 型) %d", draw_value_int);

	// float 型の場合は %f を使用します
	DrawStringEx(0, 60, -1, "変数の内容を描画 (float 型) %f", draw_value_float);

	// std::string 型の場合は %s を使用します
	// string 型を指定する場合、変数に対して .c_str() を付ける
	DrawStringEx(0, 80, -1, "変数の内容を描画 (std::string 型) %s", draw_string.c_str());


	// tips... %** キーワードはこれ意外にも存在するので『 書式指定子 』で調べてみましょう


	// 描画する文字列のサイズを設定
	SetFontSize(50);

	DrawStringEx(0, 120, -1, "サイズが変更された文字列描画");



	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}


//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
}


*/