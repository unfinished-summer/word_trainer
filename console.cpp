#include "console.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
#include "word.h"
#include "wordbank.h"
#include "path_util.h"
#include "date_util.h"

int manageMode() {

    vector<Word> words;
    string csvPath = (fs::path(cppDir()) / "words.csv").string();

    loadWords(csvPath, words);

    while (true) {
        cout << "> ";
        string cmd;
        cin >> cmd;

        if (cmd == "list") {
            for (const Word& w : words) {
                cout << w.english << " " << w.chinese << " 对" << w.right
                    << " 错" << w.wrong << " 上次" << w.lastSeen << endl;
            }
        }
        else if (cmd == "quit") {
            break;
        }
        else if (cmd == "add") {
            Word w;
            cout << "英文：";
            cin >> w.english;

            // 闸门：先查重（输入完英文立刻查）
            bool exists = false;
            for (const Word& ww : words) {
                if (ww.english == w.english) {
                    exists = true;
                    break;              // 找到了就停，不用继续逛
                }
            }

            if (exists) {
                cout << "已存在 " << w.english << "，未添加" << endl;
            }
            else {
                cout << "中文：";
                cin >> w.chinese;
                w.right = 0;
                w.wrong = 0;
                w.lastSeen = today();              
                words.push_back(w);
                cout << "已添加: " << w.english << " / " << w.chinese << endl;

            }
        }
        else if (cmd == "remove") {
            cout << "要删除的英文：";
            string target;
            cin >> target;

            bool found = false;
            for (size_t i = 0;i < words.size();i++) {
                if (words[i].english == target) {
                    words.erase(words.begin() + i);
                    found = true;
                    cout << "已删除 " << target << endl;
                    break;                              // 划完立刻停手！（迭代器失效）
                }
            }
            if (!found) {
                cout << "没找到 " << target << endl;
            }
        }
        else if (cmd == "count") {
            cout << "数量为：" << words.size() << endl;
        }
        else {
            cout << "未知命令" << endl;
        }

    }

    saveWords(csvPath, words);
    return 0;
}