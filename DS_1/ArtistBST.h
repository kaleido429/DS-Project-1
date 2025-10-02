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

	void insert(const std::string& artist, const std::string& title, int runtime);
	ArtistBSTNode* search(const std::string& artist) const;
	void print(std::ostream& os) const;
	bool delete_node(const std::string& artist);
	bool empty() const { return root == nullptr; }

	// 단일 곡 삭제: 해당 아티스트 노드에서 title 제거, 노드가 비면 노드 삭제
	bool remove_song(const std::string& artist, const std::string& title);

};