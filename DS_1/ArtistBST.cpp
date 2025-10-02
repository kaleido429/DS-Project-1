#include "ArtistBST.h"
#include "ArtistBSTNode.h"
#include <iostream>
#include <iomanip>

ArtistBST::ArtistBST() {}
ArtistBST::~ArtistBST() { destroyRec(root); }

void ArtistBST::destroyRec(ArtistBSTNode* node) {
    if (!node) return;
    destroyRec(node->get_left());
    destroyRec(node->get_right());
    delete node;
}

ArtistBSTNode* ArtistBST::insertRec(ArtistBSTNode* node, const std::string& artist,
                                    const std::string& title, int runtime) {
    if (!node) {
        auto* n = new ArtistBSTNode();
        n->set_artist(artist);
        n->add_song(title, runtime);
        return n;
    }
    if (artist < node->get_artist()) {
        node->set_left(insertRec(node->get_left(), artist, title, runtime));
    } else if (artist > node->get_artist()) {
        node->set_right(insertRec(node->get_right(), artist, title, runtime));
    } else {
        // 같은 아티스트: 곡만 추가
        node->add_song(title, runtime);
    }
    return node;
}

void ArtistBST::insert(const std::string& artist, const std::string& title, int runtime) {
    root = insertRec(root, artist, title, runtime);
}

ArtistBSTNode* ArtistBST::searchRec(ArtistBSTNode* node, const std::string& artist) const {
    if (!node) return nullptr;
    if (artist == node->get_artist()) return node;
    if (artist < node->get_artist()) return searchRec(node->get_left(), artist);
    return searchRec(node->get_right(), artist);
}

ArtistBSTNode* ArtistBST::search(const std::string& artist) const { return searchRec(root, artist); }

ArtistBSTNode* ArtistBST::findMin(ArtistBSTNode* node) const {
    while (node && node->get_left()) node = node->get_left();
    return node;
}

ArtistBSTNode* ArtistBST::removeRec(ArtistBSTNode* node, const std::string& artist) {
    if (!node) return nullptr;

    if (artist < node->get_artist()) {
        node->set_left(removeRec(node->get_left(), artist));
    } else if (artist > node->get_artist()) {
        node->set_right(removeRec(node->get_right(), artist));
    } else {
        // 삭제 대상
        ArtistBSTNode* L = node->get_left();
        ArtistBSTNode* R = node->get_right();
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
            // 오른쪽 서브트리의 최소(사전순 가장 작은) 노드로 대체
            ArtistBSTNode* succ = findMin(R);
            node->replaceWith(succ);
            node->set_right(removeRec(R, succ->get_artist()));
            return node;
        }
    }
    return node;
}

bool ArtistBST::delete_node(const std::string& artist) {
    if (!search(artist)) return false;
    root = removeRec(root, artist);
    return true;
}

bool ArtistBST::remove_song(const std::string& artist, const std::string& title) {
    ArtistBSTNode* node = search(artist);
    if (!node) return false;
    // remove title in node
    auto titles = node->get_title();
    auto times = node->get_rt();
    bool found = false;
    for (size_t i = 0; i < titles.size(); ++i) {
        if (titles[i] == title) {
            titles.erase(titles.begin() + i);
            times.erase(times.begin() + i);
            found = true;
            break;
        }
    }
    if (!found) return false;
    // 재설정: 간단히 node를 초기화 후 재삽입 대신, 교체 세터가 없어 직접 갱신 불가
    // 간단 해결: node 내용을 대체하기 위한 setter 추가가 필요하지만 스켈레톤을 크게 바꾸지 않기 위해
    // 임시로: 노드 삭제 후 나머지 곡을 재삽입
    std::string artistName = node->get_artist();
    // 노드 제거
    root = removeRec(root, artistName);
    // 남은 곡 재삽입
    for (size_t i = 0; i < titles.size(); ++i) {
        insert(artistName, titles[i], times[i]);
    }
    return true;
}

void ArtistBST::inorderRec(ArtistBSTNode* node, std::ostream& os) const {
    if (!node) return;
    inorderRec(node->get_left(), os);
    const auto& titles = node->get_title();
    const auto& times = node->get_rt();
    for (size_t i = 0; i < titles.size(); ++i) {
        int sec = times[i];
        int mm = sec / 60, ss = sec % 60;
        os << node->get_artist() << "/" << titles[i] << "/" << mm << ":" << std::setw(2) << std::setfill('0') << ss << "\n";
    }
    inorderRec(node->get_right(), os);
}

void ArtistBST::print(std::ostream& os) const { inorderRec(root, os); }