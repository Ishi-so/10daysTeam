#pragma once
#include <string>
#include <vector>

/// <summary>
/// CSV�̓ǂݍ���
/// </summary>
class CSVLoader
{
public:
	enum class BoardType
	{
		BOARD_2D, // xy���� ����(0,0)
		BOARD_3D, // xz���� ����(0,0)DirectX��������n
	};

private:
	// �}�X�̐�
	static const int MAX_SQUARE_COUNT = 640;

private: // �ÓI�����o�萔
	// CSV���u���Ă���t�H���_
	static const std::string directoryPath;
	// �g���q
	static const std::string extension;
	// �i�[�p
	static std::vector<std::string> stringMap;
	// 2�����z��
	static std::vector<std::vector<int>> csvVector;
	// �c������
	static int x, y;
	// �T�C�Y�ۑ�
	static int xSize, ySize;
private:
	// CSV�̓ǂݍ���
	static void CSVLoad(const std::string& fileName, int newLine);
	// �����񕪊�
	static std::vector<std::string> Split(std::string& line, char delimiter);
	// �\��
	static void Display(std::vector<std::vector<int>>twoVec, int newLine);
	// �T�C�Y�̐ݒ�
	static void SetSize(int x,int y);
public: // Getter
	static std::vector<std::vector<int>> GetCSVTwoVector(const std::string& fileName, BoardType type = BoardType::BOARD_2D, int newLine = 64);
	static int GetSize(std::string xy);
};