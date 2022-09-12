#pragma once
#include <string>
#include <vector>

/// <summary>
/// CSVの読み込み
/// </summary>
class CSVLoader
{
public:
	enum class BoardType
	{
		BOARD_2D, // xy平面 左上(0,0)
		BOARD_3D, // xz平面 左下(0,0)DirectX準拠左手系
	};

private:
	// マスの数
	static const int MAX_SQUARE_COUNT = 640;

private: // 静的メンバ定数
	// CSVが置いてあるフォルダ
	static const std::string directoryPath;
	// 拡張子
	static const std::string extension;
	// 格納用
	static std::vector<std::string> stringMap;
	// 2次元配列
	static std::vector<std::vector<int>> csvVector;
	// 縦軸横軸
	static int x, y;
	// サイズ保存
	static int xSize, ySize;
private:
	// CSVの読み込み
	static void CSVLoad(const std::string& fileName, int newLine);
	// 文字列分割
	static std::vector<std::string> Split(std::string& line, char delimiter);
	// 表示
	static void Display(std::vector<std::vector<int>>twoVec, int newLine);
	// サイズの設定
	static void SetSize(int x,int y);
public: // Getter
	static std::vector<std::vector<int>> GetCSVTwoVector(const std::string& fileName, BoardType type = BoardType::BOARD_2D, int newLine = 64);
	static int GetSize(std::string xy);
};