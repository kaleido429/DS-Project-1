#pragma once
#include "PlayListNode.h"
#include <string>
using namespace std;
class PlayListNode;
class PlayList {
private:
	PlayListNode* head; // PlayList의 첫 노드
	PlayListNode* cursor; // 현재 노드(커서)
	int count; // PlayList의 노드 개수
	int time; // PlayList의 전체 재생 시간
	std::string data; // PlayList의 노드 데이터

public:
	PlayList(); // 기본 생성자
	~PlayList(); // 소멸자

	// 기능 요구사항
	// insert_node : (artist, title, runtime_sec)를 받아 PlayList에 새 노드 추가
	void insert_node(string artist, string title, int runtime_sec);
	// delete_node : 현재 커서가 가리키는 노드 삭제
	void delete_node();
	// delete_song : (artist, title)로 노드 삭제
	bool delete_song(const std::string& artist, const std::string& title);
	// empty : PlayList가 비었는지 확인
	bool empty();
	// full : PlayList가 꽉 찼는지 확인
	bool full();
	// exist : PlayList에 노드가 존재하는지 확인
	bool exist();
	// print : PlayList 내용을 문자열로 반환
	std::string print();
	// run_time : PlayList의 전체 재생 시간 반환
	int run_time();
	// get_count : PlayList의 노드 개수 반환
	int get_count() const { return count; }

	//내가 추가한 함수
	bool find_song(string artist, string title); // 특정 (artist, title) 노드가 PlayList에 존재하는지 확인
	PlayListNode* move_next(PlayListNode* current); // 다음 노드로 이동
	PlayListNode* move_prev(PlayListNode* current); // 이전 노드로 이동
};