#pragma once
#include <string>
#include <iosfwd>

class TitleBSTNode; // forward declaration

class TitleBST {
private:
	TitleBSTNode* root = nullptr;

	// helpers
	TitleBSTNode* insertRec(TitleBSTNode* node, const std::string& title,
							const std::string& artist, int runtimeSec);
	TitleBSTNode* searchRec(TitleBSTNode* node, const std::string& title) const;
	TitleBSTNode* removeRec(TitleBSTNode* node, const std::string& title);
	TitleBSTNode* findMin(TitleBSTNode* node) const;
	void inorderRec(TitleBSTNode* node, std::ostream& os) const;
	void destroyRec(TitleBSTNode* node);

public:
	TitleBST();
	~TitleBST();

	// 기능 요구사항

	// insert : 제목, 아티스트, 재생 시간을 받아 TitleBST에 곡 추가
	void insert(const std::string& title, const std::string& artist, int runtimeSec);
	// search : 제목을 받아 해당 노드 반환(없으면 nullptr)
	TitleBSTNode* search(const std::string& title) const;
	// delete_node : 제목을 받아 해당 노드 삭제(성공 시 true, 실패 시 false)
	bool delete_node(const std::string& title);
	// print : 트리 출력
	void print(std::ostream& os) const; // 중위 순회 출력
	// empty : 트리가 비었는지 확인
	bool empty() const { return root == nullptr; }

	// 단일 곡 삭제: 특정 제목 노드에서 artist 제거, 노드 비면 삭제
	bool remove_song(const std::string& title, const std::string& artist);

	/* 기존 무인자 함수
	void insert() {}
	void search() {}
	void print() {}
	void delete_node() {}
	*/
};