#pragma once
#include <string>

using namespace std;
class QPGChapter
{
private:
	static int counter;
	int chapterId;
	string strName;
public:
	QPGChapter(string name);
	int getChapterId();
	string getChapterName();
	void setChapterName(string name);
};

