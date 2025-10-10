#pragma once
#include <vector>
#include <string>

class ArtistBSTNode {
private:
	std::string artist; // 가수
	std::vector<std::string> titles; // 곡 제목
	std::string run_time; // 전체 재생 시간(분:초)
	std::vector<int> rt;  // 곡 제목별 재생 시간 (초)
	int count = 0; // 곡 개수
	ArtistBSTNode* left = nullptr; // 왼쪽 자식 노드
	ArtistBSTNode* right = nullptr; // 오른쪽 자식 노드

public:

	ArtistBSTNode() = default; // 기본 생성자, 모든 멤버 변수를 기본값으로 초기화
	~ArtistBSTNode() = default; // 기본 소멸자

	// 모든 멤버 변수를 초기 상태로 재설정
	void set() {
		artist.clear();
		titles.clear();
		run_time.clear();
		rt.clear();
		count = 0;
		left = nullptr;
		right = nullptr;
	}

	// 곡(제목, 재생시간) 추가: 동일 제목 중복은 무시
	void add_song(const std::string& title, int runtime) {
		for (const auto& t : titles) { // 곡 제목 중복 검사
			if (t == title) return; // 중복 제목인 경우 추가하지 않음
		}
		titles.push_back(title); // 제목 추가
		rt.push_back(runtime); // 재생시간 추가
		++count; // 곡 개수 증가
	}

	// 다른 노드(other)의 데이터를 현재 노드에 복사
	void replaceWith(const ArtistBSTNode* other) {
		artist = other->artist;
		titles = other->titles;
		run_time = other->run_time;
		rt = other->rt;
		count = other->count;
	}

	// getters 
	const std::string& get_artist() const { return artist; }
	const std::vector<std::string>& get_title() const { return titles; }
	const std::string& get_run_time() const { return run_time; }
	const std::vector<int>& get_rt() const { return rt; }
	int get_count() const { return count; }
	ArtistBSTNode* get_left() const { return left; }
	ArtistBSTNode* get_right() const { return right; }

	// setters
	void set_artist(const std::string& a) { artist = a; }
	void set_title(const std::string& title) { titles.push_back(title); ++count; }
	void set_run_time(const std::string& rt_str) { run_time = rt_str; }
	void set_rt(int runtime) { rt.push_back(runtime); ++count; }
	void set_count(int c) { count = c; }
	void set_left(ArtistBSTNode* l) { left = l; }
	void set_right(ArtistBSTNode* r) { right = r; }
};