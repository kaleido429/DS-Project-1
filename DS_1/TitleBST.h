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

	// 기능 요구사항 API
	void insert(const std::string& title, const std::string& artist, int runtimeSec);
	TitleBSTNode* search(const std::string& title) const;
	bool delete_node(const std::string& title);
	void print(std::ostream& os) const; // 중위 순회 출력
	bool empty() const { return root == nullptr; }

	// 단일 곡 삭제: 특정 제목 노드에서 artist 제거, 노드 비면 삭제
	bool remove_song(const std::string& title, const std::string& artist);

	// 기존 무인자 함수는 남겨두되 내부에서 아무것도 하지 않음(호환용)
	void insert() {}
	void search() {}
	void print() {}
	void delete_node() {}
};