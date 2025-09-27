#pragma once
#include "PlayList.h"

class PlayListNode {
private:
	string artist;
	string title;
	int runtime_sec;

	PlayListNode* prev;
	PlayListNode* next;

public:
/*
원래 스켈레톤 코드
PlayList() {}
~PlayList(){}
*/
	PlayListNode();
	~PlayListNode();
	
	void set() {

	}
	
};