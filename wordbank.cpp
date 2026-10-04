#include "wordbank.h"
#include "date_util.h"

bool parseLine(const string& line, Word& w)
{
	// ① 拆第 1 段：english —— 连一个逗号都没有 → 坏行
	size_t pos = line.find(',');
	if (pos == string::npos) return false;
	w.english = line.substr(0, pos);
	size_t start = pos + 1;

	// ② 拆第 2 段：chinese —— 后面没逗号 → 缺字段
	pos = line.find(',', start);
	if (pos == string::npos) return false;
	w.chinese = line.substr(start, pos - start);
	start = pos + 1;

	// ③ 拆第 3 段：right（数字）—— 非数字会让 stoi 抛异常，必须拦
	pos = line.find(',', start);
	if (pos == string::npos) return false;
	try { w.right = stoi(line.substr(start, pos - start)); }
	catch (...) { return false; }   // 空串/乱码 → 这一行整个不要
	start = pos + 1;

	// ④ 拆第 4 段：wrong（数字）
	pos = line.find(',', start);
	if (pos == string::npos) return false;
	try { w.wrong = stoi(line.substr(start, pos - start)); }
	catch (...) { return false; }
	start = pos + 1;

	// ⑤ 拆第 5 段：lastSeen（到行尾）
	w.lastSeen = line.substr(start);

	// ⑥ 最后把关：关键字段为空（如 ",,0,0,2026-01-01"）也是脏数据
	if (w.english.empty() || w.chinese.empty() || w.lastSeen.empty()) return false;

	return true;
}
bool loadWords(const string& path, vector<Word>& words)
{	
	// 打开 → 判断 → 循环读 → 关闭
	ifstream in(path);// ① 打开文件（读模式）
	if (!in.is_open()) return false;// ② 打开失败（文件不存在）→ 提前返回

	string line;
	while (getline(in, line)) {// ③ 逐行读；读到文件尾 getline 返回假，循环停

		// 记事本/Windows 保存的 csv 是 CRLF：先把结尾 \r 剥掉
		if (!line.empty() && line.back() == '\r') line.pop_back();
		if (line.empty()) continue;		// 空行直接跳过，不喂给 parseLine

		Word w;					//    每一行 = 一个新单词 → 新建一个格子
		if (parseLine(line, w)) {
			words.push_back(w);
		}
	}
	in.close();

	return true;
}
bool saveWords(const string& path, const vector<Word>& words)
{
	//打开（写模式）→ 遍历 words → 逐行写 → 关闭
	ofstream out(path);
	if (!out.is_open()) return false;

	for (const Word& w : words) {
		out << w.english << "," << w.chinese << "," << w.right << "," << w.wrong << "," << w.lastSeen << "\n";
	}

	out.close();

	return true;
}

bool shouldReview(const Word& w) {
	int need = 1 + w.right;                 // 间隔 = right + 1
	return daysSince(w.lastSeen) >= need;   // 过了足够久才出现
}