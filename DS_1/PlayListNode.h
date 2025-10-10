#pragma once
#include "PlayList.h"
#include <string>

class PlayListNode {
private:
	std::string artist; // 가수 이름
	std::string title; // 곡 제목
	int runtime_sec; // 재생 시간(초)

	PlayListNode* prev; // 이전 노드 포인터
	PlayListNode* next; // 다음 노드 포인터

public:
/*
원래 스켈레톤 코드
PlayList() {}
~PlayList(){}
*/
	PlayListNode(){ // 기본 생성자: 모든 멤버 변수를 기본값으로 초기화
		set();
	}
	~PlayListNode(){
		
	}
	
	void set() {
		artist.clear();
		title.clear();
		runtime_sec = 0;
		prev = nullptr;
		next = nullptr;
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