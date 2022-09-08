#include "CSVLoader.h"

#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

// CSV���u���Ă���t�H���_
const string CSVLoader::directoryPath = "Resources/CSV/";
const string CSVLoader::extension = ".csv";
// �ÓI�񎟌��z��
std::vector<std::vector<int>> CSVLoader::csvVector(MAX_SQUARE_COUNT,std::vector<int>(MAX_SQUARE_COUNT));
// �c������
int CSVLoader::x = 0;
int CSVLoader::y = 0;

void CSVLoader::CSVLoad(const std::string& fileName, int newLine)
{
	std::string name = fileName;
	if (name == "")
	{
		std::string name = "test1";
	}
	
	// �t���p�X
	const string fullPath = directoryPath + fileName + extension;
	// �t�@�C���X�g���[��
	ifstream file;
	// �t�@�C�����J��
	file.open(fullPath);
	// �t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		assert(0);
	}
	// 1�s���i�[
	string line;
	// �Ō�̍s�܂Ń��[�v
	while (getline(file, line))
	{
		// �X�g���[���ɕϊ�
		istringstream streamLine(line);
		// 1�s�i�[�p
		string str;
		// ����������
		x = 0;
		// �J���}��؂��
		while (getline(streamLine, str, ','))
		{
			csvVector.at(y).at(x) = stoi(str);
			// �������Z
			++x;
		}
		// �c�����Z
		++y;
	}
	// �\���p
	printf("���f�[�^\n");
	Display(csvVector, newLine);
	file.close();
}

std::vector<std::string> CSVLoader::Split(std::string& line, char delimiter)
{
	// �X�g���[���ɕϊ�
	istringstream streamLine(line);
	// 1�s�i�[�p
	string str;
	// �z��i�[�p
	vector<string> strDate;
	// ����������
	x = 0;
	// �J���}��؂��
	while (getline(streamLine, str, delimiter))
	{
		csvVector.at(y).at(x) = stoi(str);
		strDate.push_back(str);
		// �������Z
		++x;
	}
	return strDate;
}

void CSVLoader::Display(std::vector<std::vector<int>>twoVec, int newLine)
{
	// ���s�p�J�E���g
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
	// CSV�t�@�C���̓ǂݍ���
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
				// (0,0)�����ォ�獶����
				int reverse = (MAX_SQUARE_COUNT - 1) - y;
				board.at(reverse).at(x) = csvVector.at(y).at(x);
			}
		}
		break;
	default:
		break;
	}

	// �\���p
	printf("�o�̓f�[�^\n");
	Display(board, newLine);
	return board;
}
