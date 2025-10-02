#include "TitleBST.h"
#include "TitleBSTNode.h"
#include <iostream>
#include <iomanip>

TitleBST::TitleBST()  {}

TitleBST::~TitleBST() { destroyRec(root); }

void TitleBST::destroyRec(TitleBSTNode* node) {
	if (!node) return;
	destroyRec(node->getLeft());
	destroyRec(node->getRight());
	delete node;
}

TitleBSTNode* TitleBST::insertRec(TitleBSTNode* node, const std::string& title,
								  const std::string& artist, int runtimeSec) {
	if (!node) {
		auto* n = new TitleBSTNode(title);
		n->addSong(artist, runtimeSec);
		return n;
	}
	if (title < node->getTitle()) {
		node->setLeft(insertRec(node->getLeft(), title, artist, runtimeSec));
	} else if (title > node->getTitle()) {
		node->setRight(insertRec(node->getRight(), title, artist, runtimeSec));
	} else {
		// 같은 제목 노드: (artist, runtime) 추가(중복 가수는 무시)
		node->addSong(artist, runtimeSec);
	}
	return node;
}

void TitleBST::insert(const std::string& title, const std::string& artist, int runtimeSec) {
	root = insertRec(root, title, artist, runtimeSec);
}

TitleBSTNode* TitleBST::searchRec(TitleBSTNode* node, const std::string& title) const {
	if (!node) return nullptr;
	if (title == node->getTitle()) return node;
	if (title < node->getTitle()) return searchRec(node->getLeft(), title);
	return searchRec(node->getRight(), title);
}

TitleBSTNode* TitleBST::search(const std::string& title) const {
	return searchRec(root, title);
}

TitleBSTNode* TitleBST::findMin(TitleBSTNode* node) const {
	while (node && node->getLeft()) node = node->getLeft();
	return node;
}

TitleBSTNode* TitleBST::removeRec(TitleBSTNode* node, const std::string& title) {
	if (!node) return nullptr;
	if (title < node->getTitle()) {
		node->setLeft(removeRec(node->getLeft(), title));
	} else if (title > node->getTitle()) {
		node->setRight(removeRec(node->getRight(), title));
	} else {
		// 삭제 대상 노드
		TitleBSTNode* L = node->getLeft();
		TitleBSTNode* R = node->getRight();
		if (!L && !R) {
			delete node;
			return nullptr;
		} else if (!L) {
			auto* tmp = R;
			delete node;
			return tmp;
		} else if (!R) {
			auto* tmp = L;
			delete node;
			return tmp;
		} else {
			// 오른쪽 서브트리에서 최소 제목 노드(succ) 찾기
			TitleBSTNode* succ = findMin(R);
			// 현재 노드의 데이터를 succ의 데이터로 교체
			node->replaceWith(succ);
			// succ 노드를 오른쪽 서브트리에서 제거
			node->setRight(removeRec(R, succ->getTitle()));
		}
	}
	return node;
}

bool TitleBST::delete_node(const std::string& title) {
	if (!search(title)) return false;
	root = removeRec(root, title);
	return true;
}

bool TitleBST::remove_song(const std::string& title, const std::string& artist) {
	TitleBSTNode* node = search(title);
	if (!node) return false;
	auto artists = node->getArtists();
	auto runtimes = node->getRuntimes();
	bool found = false;
	for (size_t i = 0; i < artists.size(); ++i) {
		if (artists[i] == artist) {
			artists.erase(artists.begin() + i);
			runtimes.erase(runtimes.begin() + i);
			found = true;
			break;
		}
	}
	if (!found) return false;
	// 노드 삭제 후 재삽입(간단 구현)
	root = removeRec(root, title);
	for (size_t i = 0; i < artists.size(); ++i) {
		insert(title, artists[i], runtimes[i]);
	}
	return true;
}

void TitleBST::inorderRec(TitleBSTNode* node, std::ostream& os) const {
	if (!node) return;
	inorderRec(node->getLeft(), os);
	const auto& artists = node->getArtists();
	const auto& runtimes = node->getRuntimes();
	for (size_t i = 0; i < artists.size(); ++i) {
		int sec = runtimes[i];
		int mm = sec / 60, ss = sec % 60;
		os << artists[i] << "/" << node->getTitle() << "/" << mm << ":" << std::setw(2) << std::setfill('0') << ss << '\n';
	}
	inorderRec(node->getRight(), os);
}

void TitleBST::print(std::ostream& os) const {
	inorderRec(root, os);
}