#pragma once
#include "MusicQueueNode.h"

class MusicQueue {
private:
	MusicQueueNode* head; //Queue의 첫 node
	MusicQueueNode* rear; //Queue의 마지막 node
	int size = 0; // 현재 Queue의 크기 (노드 수)
	static const int MAX_SIZE = 100; // 과제 요구 사항
public:
	MusicQueue(); // 생성자
	~MusicQueue();// 소멸자

	// queue가 비었는지 확인
	bool empty();
	// queue에 동일한 (artist, title) 곡이 존재하는지 확인
	bool exist(const std::string& artist, const std::string& title);
	// queue에 새 노드 추가
	void push(const std::string& artist, const std::string& title, const std::string& runtime);
	MusicQueueNode* pop(); // queue에서 제거할 노드 반환
	MusicQueueNode* front(); // queue의 첫 노드 반환
};