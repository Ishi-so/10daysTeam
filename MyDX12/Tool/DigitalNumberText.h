#pragma once
//DigitalNumberText
#include <iostream>
class Sprite;

enum DrawTimeType {
	HMS = 0,
	HM,
	MS
};

class DigitalNumberText
{
public:
	// デバッグテキスト用のテクスチャ番号を指定
	static const int maxCharCount = 100;	// 最大文字数
	static const int fontWidth = 32;	// フォント画像内1文字分の横幅
	static const int fontHeight = 64;	// フォント画像内1文字分の縦幅
	static const int fontLineCount = 12;	// フォント画像内1行分の文字数
	const int fontCode = -127;

public:// 静的メンバ関数
	static DigitalNumberText* GetInstance();

public:// メンバ関数

	void Initialize(unsigned int texnumber);

	void Print(int score, float x, float y, float scale = 1.0f);

	// 時間表示のためだけの関数(type : 表示タイプ,h : 時、m : 分、 s : 秒、x : X座標,y : Y座標,scale : 拡大率)
	// sを0としh,mに別の値があれば特殊表記(H : M)
	// hを0としm,sに別の値があれば特殊表記(M : S)
	void TimePrintHMS(const DrawTimeType& type ,int h, int m, float s, float x, float y, float scale = 1.0f);

	void SetColor(float r, float g, float b, float a);

	void DrawAll();

private:

	DigitalNumberText();
	DigitalNumberText(const DigitalNumberText&) = delete;
	~DigitalNumberText();
	DigitalNumberText& operator=(const DigitalNumberText&) = delete;

private:
	// スプライトデータの配列
	Sprite* spriteDatas[maxCharCount] = {};
	// スプライトデータ配列の添え字番号
	int spriteIndex = 0;
	float cr = 1.0f;
	float cg = 1.0f;
	float cb = 1.0f;
};