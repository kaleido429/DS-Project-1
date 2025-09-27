#pragma once
#include "MusicQueueNode.h"

class MusicQueue {
private:
	MusicQueueNode* head;
	MusicQueueNode* rear;
	int size = 0;
	static const int MAX_SIZE = 100; // 과제 요구 사항
public:
	MusicQueue();
	~MusicQueue();

	bool empty();
	bool exist(const std::string& artist, const std::string& title);
	void push(const std::string& artist, const std::string& title, const std::string& runtime);
	MusicQueueNode* pop();
	MusicQueueNode* front();
};