#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "word.h"

bool parseLine(const string& line, Word& w);
bool loadWords(const string& path, vector<Word>& words);
bool saveWords(const string& path, const vector<Word>& words);
bool shouldReview(const Word& w);   // 今天该不该背这个词