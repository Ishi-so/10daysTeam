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
int CSVLoader::xSize = 0, CSVLoader::ySize = 0;

void CSVLoader::CSVLoad(const std::string& fileName, int newLine)
{
	// �T�C�Y�̏�����
	xSize = 0;
	ySize = 0;

	// ���O
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
		// �T�C�Y�̐ݒ�
		SetSize(x,y);
		// �c�����Z
		++y;
	}
	// �T�C�Y�̐ݒ�
	SetSize(x,y);
	// �\���p
	printf("���f�[�^\n");
	//Display(csvVector, newLine);
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

	for (int y = 0; y < ySize; ++y)
	{
		for (int x = 0; x < xSize; ++x)
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

void CSVLoader::SetSize(int x, int y)
{
	if (xSize <= x) { xSize = x; }
	if (ySize <= y) { ySize = y; }
}

int CSVLoader::GetSize(std::string xy)
{
	if (xy == "x")return xSize;
	if (xy == "y")return ySize;
	return 0;
}

std::vector<std::vector<int>> CSVLoader::GetCSVTwoVector(const std::string& fileName, BoardType type, int newLine)
{
	// CSV�t�@�C���̓ǂݍ���
	CSVLoad(fileName,newLine);
	std::vector<std::vector<int>>board(ySize, std::vector<int>(xSize));
	switch (type)
	{
	case BoardType::BOARD_2D:
		for (int y = 0; y < ySize; ++y)
		{
			for (int x = 0; x < xSize; ++x)
			{
				board.at(y).at(x) = csvVector.at(y).at(x);
			}
		}
		break;
	case BoardType::BOARD_3D:
		for (int y = 0; y < ySize; ++y)
		{
			for (int x = 0; x < xSize; ++x)
			{
				// (0,0)�����ォ�獶����
				int reverse = (ySize - 1) - y;
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
