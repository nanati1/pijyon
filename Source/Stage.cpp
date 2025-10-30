#include "Stage.h"
#include <assert.h>
#include <vector>
#include "Player.h"
#include "CsvReader.h"
#include "Screen.h"
#include "Enemy.h"


Stage::Stage()
{
	// ステージデータの読み込み
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
				// マップのズレ補正（上・左に2マスずれ対策）
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
			int drawX = x * w - scrollX + Screen::startX; // ←左上から描く
			int drawY = y * h + Screen::startY;


			// 画面外なら描かない
			if (drawX < Screen::startX - w || drawX > Screen::endX   ) {
				continue;
			}
			// 画面外なら描かない
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
	// チップにどれぐらいめり込んでいるかを返す
	int x = pos.x / imageSize.x;
	int dx = pos.x - x * imageSize.x; // チップの中の座標
	return dx + 1;
}

int Stage::CheckLeft(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	// チップにどれぐらいめり込んでいるかを返す
	int x = pos.x / imageSize.x;
	int dx = pos.x - x * imageSize.x; // チップの中の座標
	return imageSize.x - dx;
}

int Stage::CheckDown(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	// チップにどれぐらいめり込んでいるかを返す
	int y = pos.y / imageSize.y;
	int dy = pos.y - y * imageSize.y; // チップの中の座標
	return dy + 1;
	
}

int Stage::CheckUp(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	// チップにどれぐらいめり込んでいるかを返す
	int y = pos.y / imageSize.y;
	int dy = pos.y - y * imageSize.y; // チップの中の座標
	return imageSize.y - dy;
}

bool Stage::IsWall(VECTOR2 pos)
{
	// チップの場所を特定する
	int x = pos.x / imageSize.x;
	int y = pos.y / imageSize.y;
	if (y < 0 || y >= map.size()) {
		return false;
	}
	if (x < 0 || x >= map[y].size()) {
		return false;
	}


	// チップの番号を見て、壁かどうか確定する
	switch (map[y][x]) {
	case 0:
	case 9:
	case 8:
		return false;
	}
	return true;
}
