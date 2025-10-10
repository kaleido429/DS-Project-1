#include "TitleBST.h"
#include "TitleBSTNode.h"
#include <iostream>
#include <iomanip>

TitleBST::TitleBST()  {} // 기본 생성자

TitleBST::~TitleBST() { destroyRec(root); } // 소멸자

void TitleBST::destroyRec(TitleBSTNode* node) {
	if (!node) return; // node 없는 경우, 종료
	destroyRec(node->getLeft()); // 왼쪽 서브트리 파괴
	destroyRec(node->getRight()); // 오른쪽 서브트리 파괴
	delete node; // 현재 노드 삭제
}

// insertRec: TitleBST에 (title, artist, runtimeSec) 삽입, 재귀 함수
TitleBSTNode* TitleBST::insertRec(TitleBSTNode* node, const std::string& title, const std::string& artist, int runtimeSec) {
	if (!node) { // node 없는 경우, 새 노드 생성 후 반환
		auto* n = new TitleBSTNode(title);
		n->addSong(artist, runtimeSec);
		return n;
	}
	if (title < node->getTitle()) { // title 기준으로 왼쪽/오른쪽 서브트리 탐색
		node->setLeft(insertRec(node->getLeft(), title, artist, runtimeSec));
	} else if (title > node->getTitle()) { // 오른쪽 서브트리 탐색
		node->setRight(insertRec(node->getRight(), title, artist, runtimeSec));
	} else { // 같은 제목 노드: (artist, runtime) 추가(중복 가수는 무시)
		node->addSong(artist, runtimeSec);
	}
	return node;
}

// insert: TitleBST에 (title, artist, runtimeSec) 삽입
void TitleBST::insert(const std::string& title, const std::string& artist, int runtimeSec) {
	// 재귀 함수 호출
	root = insertRec(root, title, artist, runtimeSec);
}

// searchRec: title로 TitleBST에서 node 탐색(재귀)
TitleBSTNode* TitleBST::searchRec(TitleBSTNode* node, const std::string& title) const {
	if (!node) return nullptr; // node 없는 경우, nullptr 반환
	if (title == node->getTitle()) return node; // 제목이 일치하는 경우, 현재 노드 반환
	if (title < node->getTitle()) return searchRec(node->getLeft(), title); // 왼쪽 서브트리 탐색
	return searchRec(node->getRight(), title); // 오른쪽 서브트리 탐색
}

// search: title로 TitleBST에서 node 탐색
TitleBSTNode* TitleBST::search(const std::string& title) const {
	return searchRec(root, title);
}

// findMin: sub tree에서 최소 제목 node 탐색
TitleBSTNode* TitleBST::findMin(TitleBSTNode* node) const {
	// 왼쪽 서브트리로 계속 이동
	while (node && node->getLeft()) node = node->getLeft();
	return node;
}

// removeRec: title로 TitleBST에서 node 삭제(재귀)
TitleBSTNode* TitleBST::removeRec(TitleBSTNode* node, const std::string& title) {
	if (!node) return nullptr; // node 없는 경우, nullptr 반환
	if (title < node->getTitle()) { // 왼쪽 서브트리 탐색
		node->setLeft(removeRec(node->getLeft(), title)); // 왼쪽 서브트리에서 재귀 삭제
	} else if (title > node->getTitle()) { // 오른쪽 서브트리 탐색
		node->setRight(removeRec(node->getRight(), title)); // 오른쪽 서브트리에서 재귀 삭제
	} else {
		// 삭제 대상 노드
		TitleBSTNode* L = node->getLeft();
		TitleBSTNode* R = node->getRight();
		if (!L && !R) { // 자식 노드 없는 경우, 현재 노드 삭제
			delete node;
			return nullptr;
		} else if (!L) { // 왼쪽 자식 없는 경우, 오른쪽 자식으로 대체
			auto* tmp = R;
			delete node;
			return tmp;
		} else if (!R) { // 오른쪽 자식 없는 경우, 왼쪽 자식으로 대체
			auto* tmp = L;
			delete node;
			return tmp;
		} else { // 자식 노드 둘 다 있는 경우, 오른쪽 서브트리에서 최소 제목 노드(succ) 찾아서 대체
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

// delete_node: title로 TitleBST에서 node 삭제
bool TitleBST::delete_node(const std::string& title) {
	if (!search(title)) return false; // 제목 없는 경우, false 반환
	root = removeRec(root, title);
	return true;
}

// remove_song: title로 TitleBST에서 artist 제거, 노드 비면 삭제
bool TitleBST::remove_song(const std::string& title, const std::string& artist) {
	TitleBSTNode* node = search(title); // 제목으로 노드 탐색
	if (!node) return false; // 노드 없는 경우, false 반환
	auto artists = node->getArtists();
	auto runtimes = node->getRuntimes();
	bool found = false;
	for (size_t i = 0; i < artists.size(); ++i) { // artist 탐색
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

// inorderRec: 중위 순회로 TitleBST 출력(재귀)
void TitleBST::inorderRec(TitleBSTNode* node, std::ostream& os) const {
	if (!node) return;
	inorderRec(node->getLeft(), os); // 왼쪽 서브트리 먼저 출력
	const auto& artists = node->getArtists();
	const auto& runtimes = node->getRuntimes();
	for (size_t i = 0; i < artists.size(); ++i) { // 각 (artist, title, runtime) 출력
		int sec = runtimes[i];
		int mm = sec / 60, ss = sec % 60;
		os << artists[i] << "/" << node->getTitle() << "/" << mm << ":" << std::setw(2) << std::setfill('0') << ss << '\n';
	}
	inorderRec(node->getRight(), os); // 오른쪽 서브트리 출력
}

// print: TitleBST 출력
void TitleBST::print(std::ostream& os) const {
	inorderRec(root, os); // 중위 순회 출력
}