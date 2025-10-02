#pragma once
#include <vector>
#include <string>

class ArtistBSTNode {
private:
	std::string artist;
	std::vector<std::string> titles;
	std::string run_time; // optional aggregate representation
	std::vector<int> rt;  // runtimes per title (seconds)
	int count = 0;
	ArtistBSTNode* left = nullptr;
	ArtistBSTNode* right = nullptr;

public:
	ArtistBSTNode() = default;
	~ArtistBSTNode() = default;

	void set() {
		artist.clear();
		titles.clear();
		run_time.clear();
		rt.clear();
		count = 0;
		left = nullptr;
		right = nullptr;
	}

	void add_song(const std::string& title, int runtime) {
		for (const auto& t : titles) {
			if (t == title) return; // prevent duplicate titles per artist
		}
		titles.push_back(title);
		rt.push_back(runtime);
		++count;
	}

	// swap-in data from another node (keep tree links)
	void replaceWith(const ArtistBSTNode* other) {
		artist = other->artist;
		titles = other->titles;
		run_time = other->run_time;
		rt = other->rt;
		count = other->count;
	}

	// getters (const correctness)
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