#include "wordbank.h"
#include "date_util.h"

bool parseLine(const string& line, Word& w)
{
	size_t pos = line.find(',');
	w.english = line.substr(0, pos-0);
	size_t start = pos + 1;
	pos = line.find(',',start);
	w.chinese = line.substr(start, pos-start);
	start = pos + 1;
	pos = line.find(',',start);
	w.right = stoi(line.substr(start, pos-start));
	start = pos + 1;
	pos = line.find(',',start);
	w.wrong = stoi(line.substr(start, pos-start));
	start = pos + 1;
	w.lastSeen = line.substr(start);

	return true;
}
bool loadWords(const string& path, vector<Word>& words)
{	
	// 打开 → 判断 → 循环读 → 关闭
	ifstream in(path);// ① 打开文件（读模式）
	if (!in.is_open()) return false;// ② 打开失败（文件不存在）→ 提前返回

	string line;
	while (getline(in, line)) {// ③ 逐行读；读到文件尾 getline 返回假，循环停
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