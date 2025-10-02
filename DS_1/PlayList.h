#pragma once
#include "PlayListNode.h"
#include <string>
using namespace std;
class PlayListNode;
class PlayList {
private:
	PlayListNode* head;
	PlayListNode* cursor;
	int count;
	int time;
	std::string data;

public:
	PlayList();
	~PlayList();
	void insert_node(string artist, string title, int runtime_sec);
	void delete_node();
	bool delete_song(const std::string& artist, const std::string& title);
	bool empty();
	bool full();
	bool exist();
	std::string print();
	int run_time();
	int get_count() const { return count; }

	//내가 추가한 함수
	bool find_song(string artist, string title);
	PlayListNode* move_next(PlayListNode* current);
	PlayListNode* move_prev(PlayListNode* current);
};