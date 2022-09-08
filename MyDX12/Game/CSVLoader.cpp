#include "CSVLoader.h"

#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

// CSVが置いてあるフォルダ
const string CSVLoader::directoryPath = "Resources/CSV/";
const string CSVLoader::extension = ".csv";
// 静的二次元配列
std::vector<std::vector<int>> CSVLoader::csvVector(MAX_SQUARE_COUNT,std::vector<int>(MAX_SQUARE_COUNT));
// 縦軸横軸
int CSVLoader::x = 0;
int CSVLoader::y = 0;

void CSVLoader::CSVLoad(const std::string& fileName, int newLine)
{
	std::string name = fileName;
	if (name == "")
	{
		std::string name = "test1";
	}
	
	// フルパス
	const string fullPath = directoryPath + fileName + extension;
	// ファイルストリーム
	ifstream file;
	// ファイルを開く
	file.open(fullPath);
	// ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}
	// 1行を格納
	string line;
	// 最後の行までループ
	while (getline(file, line))
	{
		// ストリームに変換
		istringstream streamLine(line);
		// 1行格納用
		string str;
		// 横軸初期化
		x = 0;
		// カンマ区切りで
		while (getline(streamLine, str, ','))
		{
			csvVector.at(y).at(x) = stoi(str);
			// 横軸加算
			++x;
		}
		// 縦軸加算
		++y;
	}
	// 表示用
	printf("元データ\n");
	Display(csvVector, newLine);
	file.close();
}

std::vector<std::string> CSVLoader::Split(std::string& line, char delimiter)
{
	// ストリームに変換
	istringstream streamLine(line);
	// 1行格納用
	string str;
	// 配列格納用
	vector<string> strDate;
	// 横軸初期化
	x = 0;
	// カンマ区切りで
	while (getline(streamLine, str, delimiter))
	{
		csvVector.at(y).at(x) = stoi(str);
		strDate.push_back(str);
		// 横軸加算
		++x;
	}
	return strDate;
}

void CSVLoader::Display(std::vector<std::vector<int>>twoVec, int newLine)
{
	// 改行用カウント
	int count = 0;

	for (int y = 0; y < MAX_SQUARE_COUNT; ++y)
	{
		for (int x = 0; x < MAX_SQUARE_COUNT; ++x)
		{
			printf("%d", twoVec.at(y).at(x));
			printf(",");
			count++;
			if (count >= newLine)
			{
				printf("\n");
				count = 0;
			}
		}
	}
	printf("\n");
}

std::vector<std::vector<int>> CSVLoader::GetCSVTwoVector(const std::string& fileName, BoardType type, int newLine)
{
	// CSVファイルの読み込み
	CSVLoad(fileName,newLine);
	std::vector<std::vector<int>>board(MAX_SQUARE_COUNT, std::vector<int>(MAX_SQUARE_COUNT));
	switch (type)
	{
	case BoardType::BOARD_2D:
		for (int y = 0; y < MAX_SQUARE_COUNT; ++y)
		{
			for (int x = 0; x < MAX_SQUARE_COUNT; ++x)
			{
				board.at(y).at(x) = csvVector.at(y).at(x);
			}
		}
		break;
	case BoardType::BOARD_3D:
		for (int y = 0; y < MAX_SQUARE_COUNT; ++y)
		{
			for (int x = 0; x < MAX_SQUARE_COUNT; ++x)
			{
				// (0,0)を左上から左下に
				int reverse = (MAX_SQUARE_COUNT - 1) - y;
				board.at(reverse).at(x) = csvVector.at(y).at(x);
			}
		}
		break;
	default:
		break;
	}

	// 表示用
	printf("出力データ\n");
	Display(board, newLine);
	return board;
}
