#pragma once
#include <string>
class ArtistBSTNode; // forward declaration
class ArtistBST {
private:
	ArtistBSTNode* root = nullptr;


	//helper functions
	ArtistBSTNode* insertRec(ArtistBSTNode* node, const std::string& artist,const std::string& title, int runtime);
    ArtistBSTNode* searchRec(ArtistBSTNode* node, const std::string& artist) const;
    ArtistBSTNode* removeRec(ArtistBSTNode* node, const std::string& artist);
    ArtistBSTNode* findMin(ArtistBSTNode* node) const;
	void inorderRec(ArtistBSTNode* node, std::ostream& os) const;
    void destroyRec(ArtistBSTNode* node);
public:
	ArtistBST();
	~ArtistBST();

	// 기능 요구사항
	// insert : 아티스트, 제목, 재생 시간을 받아 ArtistBST에 곡 추가
	void insert(const std::string& artist, const std::string& title, int runtime);
	// search : 아티스트를 받아 해당 노드 반환(없으면 nullptr)
	ArtistBSTNode* search(const std::string& artist) const;
	// print : 트리 출력
	void print(std::ostream& os) const; // 중위 순회 출력
	// delete_node : 아티스트를 받아 해당 노드 삭제(성공 시 true, 실패 시 false)
	bool delete_node(const std::string& artist);
	// empty : 트리가 비었는지 확인
	bool empty() const { return root == nullptr; }

	// 단일 곡 삭제: 해당 아티스트 노드에서 title 제거, 노드가 비면 노드 삭제
	bool remove_song(const std::string& artist, const std::string& title);

};