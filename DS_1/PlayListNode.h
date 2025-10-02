#pragma once
#include "PlayList.h"
#include <string>

class PlayListNode {
private:
	std::string artist;
	std::string title;
	int runtime_sec;

	PlayListNode* prev;
	PlayListNode* next;

public:
/*
원래 스켈레톤 코드
PlayList() {}
~PlayList(){}
*/
	PlayListNode(){
		artist = "";
		title = "";
		runtime_sec = 0;
		prev = nullptr;
		next = nullptr;
	}
	~PlayListNode(){
		
	}
	
	void set() {

	}
	//getter
	std::string get_artist() { return artist; }
	std::string get_title() { return title; }
	int get_runtime_sec() { return runtime_sec; }
	PlayListNode* get_prev() { return prev; }
	PlayListNode* get_next() { return next; }
	//setter
	void set_artist(std::string artist) { this->artist = artist; }
	void set_title(std::string title) { this->title = title; }
	void set_runtime_sec(int runtime_sec) { this->runtime_sec = runtime_sec; }
	void set_prev(PlayListNode* prev) { this->prev = prev; }
	void set_next(PlayListNode* next) { this->next = next; }
};