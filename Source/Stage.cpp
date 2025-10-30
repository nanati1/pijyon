#include "Stage.h"
#include <assert.h>
#include <vector>
#include "Player.h"
#include "CsvReader.h"
#include "Screen.h"
#include "Enemy.h"


Stage::Stage()
{
	// �X�e�[�W�f�[�^�̓ǂݍ���
	CsvReader* csv = new CsvReader("data/map/stage1.csv");
	for (int line = 0; line < csv->GetLines(); line++) {
		std::vector<int> mapLine;
		for (int column = 0; column < csv->GetColumns(line); column++) {
			int c = csv->GetInt(line, column);
			mapLine.push_back(c);
		}
		map.push_back(mapLine);
	}
	delete csv;

	bImage = LoadGraph("data/image/Sora2.jpg");
	assert(bImage > 0);
	hImage = LoadGraph("data/image/parts.png");
	assert(hImage > 0);
	imageSize = VECTOR2(64, 64);
	anim = 3;
	animY = 1;

	scrollX = 0;

	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			int c = map[y][x];
			if (c == 9) {
				int px = x * imageSize.x + imageSize.x / 2.0f;
				int py = y * imageSize.y + imageSize.y / 2.0f;
				// �}�b�v�̃Y���␳�i��E����2�}�X����΍�j
				/*px += 2 * imageSize.x;
				py += 2 * imageSize.y;*/
				new Player(VECTOR2(px, py));
			}
			if (c == 8) {
				int ex = x * imageSize.x + imageSize.x / 2.0f;
				int ey = y * imageSize.y + imageSize.y / 2.0f;
				new Enemy(VECTOR2(ex, ey));
			}
			
		}
	}

}

Stage::~Stage()
{
}

void Stage::Draw()
{

	
	DrawExtendGraph(Screen::startX, Screen::startY, Screen::endX, Screen::endY, bImage, 0);


	int w = imageSize.x;
	int h = imageSize.y;
	
	
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			int c = map[y][x];
			int drawX = x * w - scrollX + Screen::startX; // �����ォ��`��
			int drawY = y * h + Screen::startY;


			// ��ʊO�Ȃ�`���Ȃ�
			if (drawX < Screen::startX - w || drawX > Screen::endX   ) {
				continue;
			}
			// ��ʊO�Ȃ�`���Ȃ�
			if (drawY < Screen::startY - h || drawY > Screen::endY - h ) {
				continue;
			}
			if (c == 1) {
				DrawRectGraph(drawX , drawY, 3 * w, 1 * h, w, h, hImage, TRUE);
			}
			else if (c == 2) {
				DrawRectGraph(drawX , drawY, 0 * w, 1 * h, w, h, hImage, TRUE);
			}
			else if (c == 3) {
				DrawRectGraph(drawX , drawY, 3 * w, 0 * h, w, h, hImage, TRUE);
			}
		}
	}

}

int Stage::CheckRight(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	// �`�b�v�ɂǂꂮ�炢�߂荞��ł��邩��Ԃ�
	int x = pos.x / imageSize.x;
	int dx = pos.x - x * imageSize.x; // �`�b�v�̒��̍��W
	return dx + 1;
}

int Stage::CheckLeft(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	// �`�b�v�ɂǂꂮ�炢�߂荞��ł��邩��Ԃ�
	int x = pos.x / imageSize.x;
	int dx = pos.x - x * imageSize.x; // �`�b�v�̒��̍��W
	return imageSize.x - dx;
}

int Stage::CheckDown(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	// �`�b�v�ɂǂꂮ�炢�߂荞��ł��邩��Ԃ�
	int y = pos.y / imageSize.y;
	int dy = pos.y - y * imageSize.y; // �`�b�v�̒��̍��W
	return dy + 1;
	
}

int Stage::CheckUp(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	// �`�b�v�ɂǂꂮ�炢�߂荞��ł��邩��Ԃ�
	int y = pos.y / imageSize.y;
	int dy = pos.y - y * imageSize.y; // �`�b�v�̒��̍��W
	return imageSize.y - dy;
}

bool Stage::IsWall(VECTOR2 pos)
{
	// �`�b�v�̏ꏊ����肷��
	int x = pos.x / imageSize.x;
	int y = pos.y / imageSize.y;
	if (y < 0 || y >= map.size()) {
		return false;
	}
	if (x < 0 || x >= map[y].size()) {
		return false;
	}


	// �`�b�v�̔ԍ������āA�ǂ��ǂ����m�肷��
	switch (map[y][x]) {
	case 0:
	case 9:
	case 8:
		return false;
	}
	return true;
}
