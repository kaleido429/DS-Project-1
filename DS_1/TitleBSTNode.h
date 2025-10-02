#pragma once
#include <string>
#include <vector>

class TitleBSTNode {
private:
	// 노드 키: 노래 제목
	std::string title;
	// 동일 제목의 가수 목록과 각 재생시간(초)
	std::vector<std::string> artists;
	std::vector<int> runtimes;

	TitleBSTNode* left = nullptr;
	TitleBSTNode* right = nullptr;

public:
	TitleBSTNode() = default;
	explicit TitleBSTNode(const std::string& t) : title(t) {}

	~TitleBSTNode() = default;

	// 곡(가수, 재생시간) 추가: 동일 가수-제목 중복은 무시
	void addSong(const std::string& artist, int runtimeSec) {
		for (size_t i = 0; i < artists.size(); ++i) {
			if (artists[i] == artist) return; // 동일 가수는 중복 추가 안 함
		}
		artists.push_back(artist);
		runtimes.push_back(runtimeSec);
	}

	// getters
	const std::string& getTitle() const { return title; }
	const std::vector<std::string>& getArtists() const { return artists; }
	const std::vector<int>& getRuntimes() const { return runtimes; }
	TitleBSTNode* getLeft() const { return left; }
	TitleBSTNode* getRight() const { return right; }

	// setters
	void setTitle(const std::string& t) { title = t; }
	void setLeft(TitleBSTNode* n) { left = n; }
	void setRight(TitleBSTNode* n) { right = n; }

	// 현재 노드의 데이터(title, artists, runtimes)만 other의 것으로 교체 (포인터 구조는 유지)
	void replaceWith(const TitleBSTNode* other) {
		title = other->title;
		artists = other->artists;
		runtimes = other->runtimes;
	}
};