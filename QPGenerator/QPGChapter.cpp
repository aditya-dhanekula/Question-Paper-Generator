#include "QPGChapter.h"

int QPGChapter::counter;
QPGChapter::QPGChapter(std::string name) {
	chapterId = ++counter;
	strName = name;
}

int QPGChapter::getChapterId() {
	return chapterId;
}

string QPGChapter::getChapterName() {
	return strName;
}

void QPGChapter::setChapterName(std::string name) {
	strName = name;
}