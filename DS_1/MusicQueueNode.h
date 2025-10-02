#pragma once
//#include "MusicQueue.h"
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

class MusicQueueNode {
private:
	string artist; //가수 이름
	string title; //곡 제목
	string run_time; //재생 시간

	MusicQueueNode* next; //다음 노드 포인터
	MusicQueueNode* prev; //이전 노드 포인터

public:
/*
생성자: artist, title, run_time 초기화, next, prev는 nullptr로 설정
소멸자: next, prev를 nullptr로 설정(Queue에서 pop할 때 메모리 delete하기 때문에 빈 소멸자여도 무방)
*/
	MusicQueueNode(const std::string& artist_val, const std::string& title_val, const std::string& runtime_val)
		: artist(artist_val), title(title_val), run_time(runtime_val), next(nullptr), prev(nullptr) {}
	~MusicQueueNode() {
		next = nullptr;
		prev = nullptr;
	}
	/*
	void insert() {

	}

	bool exist() {

	}
	*/
	// Getters
	std::string getArtist() const { return artist; }
	std::string getTitle() const { return title; }
	std::string getRuntime() const { return run_time; }
	MusicQueueNode* getNext() const { return next; }
	MusicQueueNode* getPrev() const { return prev; }

	// Setters
	void setNext(MusicQueueNode* node) { next = node; }
	void setPrev(MusicQueueNode* node) { prev = node; }
};