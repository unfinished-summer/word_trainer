#include "ui.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
#include "raylib.h"
#include "word.h"
#include "wordbank.h"
#include "path_util.h"
#include "date_util.h"

int playMode() {
	vector<Word> words;
	string csvPath = (fs::path(cppDir()) / "words.csv").string();

	if (!loadWords(csvPath, words)) {            // ← 读取失败要拦！
		cout << "词库文件读取失败：" << csvPath << endl;
		return 1;                                 // 打不开就别开窗口
	}

	vector<int> due;                     // 今天该背的【下标清单】
	for (int i = 0; i < (int)words.size(); i++) {
		if (shouldReview(words[i])) {
			due.push_back(i);            // 存编号，不存词
		}
	}
	if (due.empty()) {
		cout << "今天没有要背的词，休息一下" << endl;
		return 0;                          // 不弹窗口
	}

	int total = due.size();

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);   // 必须在 InitWindow 之前
	InitWindow(1280, 720, "背单词");
	SetTargetFPS(60);

	char* buf = LoadFileText("C:\\Users\\36779\\OneDrive\\Desktop\\common_chars.txt");
	int cpCount = 0;
	int* cps = LoadCodepoints(buf, &cpCount);
	Font zh = LoadFontEx("C:/Windows/Fonts/simhei.ttf", 64, cps, cpCount);
	UnloadCodepoints(cps);
	UnloadFileText(buf);

	int index = 0;                  // 当前第几张卡（更新阶段的"状态"）
	bool showBack = false;

	while (!WindowShouldClose()) {

		if (IsKeyPressed(KEY_SPACE)) {
			showBack = !showBack;
		}
		if (IsKeyPressed(KEY_RIGHT)) {
			index = (index + 1) % due.size();
			showBack = false;   // 新卡从正面开始
		}
		if (IsKeyPressed(KEY_LEFT)) {
			index = (index - 1 + due.size()) % due.size();
			showBack = false;
		}
		if (IsKeyPressed(KEY_Y)) {
			words[due[index]].right++;                    // Q1：认识 → 答对计数 +1
			words[due[index]].lastSeen = today();   // ← 记下"今天背过了"
			showBack = false;
			due.erase(due.begin() + index);
			if (due.empty()) break;                                   // ① 先查空
			if (index >= (int)due.size()) index = (int)due.size() - 1; // ② 删了末尾 → 回退到最后一张
		}
		if (IsKeyPressed(KEY_N)) {
			words[due[index]].wrong++;                    // 不认识 → 答错计数 +1
			words[due[index]].right = 0;            // ← 答错重置：从头积累
			words[due[index]].lastSeen = today();   // ← 同样记今天
			showBack = false;
			due.erase(due.begin() + index);
			if (due.empty()) break;                                   // ① 先查空
			if (index >= (int)due.size()) index = (int)due.size() - 1; // ② 删了末尾 → 回退到最后一张
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		int sw = GetScreenWidth();    // 窗口当前宽（每帧实时）
		int sh = GetScreenHeight();

		const char* text = showBack ? words[due[index]].chinese.c_str() : words[due[index]].english.c_str();
		float fontSize = 60.0f;
		Vector2 sz = MeasureTextEx(zh, text, fontSize, 1);  // 量文本尺寸
		float x = (sw - sz.x) / 2;     // 水平居中
		float y = (sh - sz.y) / 2;      // 垂直居中
		DrawTextEx(zh, text, Vector2{ x, y }, fontSize, 1, DARKGRAY);
		string tip = "按 Y(认识)/ N(不认识)";
		float tipSize = 24.0f;                                  // 小字号
		Vector2 tipSz = MeasureTextEx(zh, tip.c_str(), tipSize, 1);
		float tipX = (sw - tipSz.x) / 2;
		float tipY = (sh - tipSz.y) / 2 + 120;
		DrawTextEx(zh, tip.c_str(), Vector2{ tipX, tipY }, tipSize, 1, GRAY);
		float ratio = 1.0f - (float)due.size() / total;   // 1 - 剩余/总数 = 已背比例
		float totalW = sw*0.8;                 // 进度条全长
		DrawRectangle(sw*0.1, sh-60, totalW, 30, LIGHTGRAY);          // 背景：灰，全长
		DrawRectangle(sw*0.1, sh-60, totalW * ratio, 30, BLUE);       // 前景：蓝，比例宽

		EndDrawing();
	}
	if (due.empty()) {
		cout << "今天的词全部背完，明天见" << endl;
	}

	if (!saveWords(csvPath, words)) {
		cout << "保存失败（磁盘满或文件只读）" << endl;
		return 1;
	}

	CloseWindow();
	return 0;
}