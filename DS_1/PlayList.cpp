#include "PlayList.h"
#include "PlayListNode.h"
#include <sstream>
#include <iomanip>
using namespace std;
PlayList::PlayList() {
    // playlist의 private 멤버 변수 초기화
    head = nullptr;
    cursor = nullptr;
    count = 0;
    time = 0;
    data = "";
}

PlayList::~PlayList() {
    if(head == nullptr) return; // 빈 리스트인 경우
    // Circular Linked List의 모든 노드 삭제
    PlayListNode* cur = head->get_next();
    while (cur != head) {
        PlayListNode* tmp = cur;
        cur = cur->get_next();
        delete tmp;
    }
    delete head;
    head = cursor = nullptr;
    count = 0;
    time = 0;
}

void PlayList::insert_node(string artist, string title, int runtime_sec) {
    if(full()) {
        //리스트가 꽉 찬 경우
        return;
    }
    if(find_song(artist, title)) {
        //이미 존재하는 노드인 경우
        return;
    }

    PlayListNode* newNode = new PlayListNode;
    newNode->set_artist(artist);
    newNode->set_title(title);
    newNode->set_runtime_sec(runtime_sec);

    if(empty()) {
        //리스트가 비어있는 경우
        head = newNode;
        cursor = newNode;
        newNode->set_next(newNode);
        newNode->set_prev(newNode);
        count = 1;
        time = runtime_sec;
    } else {
        //newNode를 cursor 뒤에 삽입
        newNode->set_next(cursor->get_next());
        newNode->set_prev(cursor);
        cursor->get_next()->set_prev(newNode);
        cursor->set_next(newNode);
        cursor = newNode; //cursor를 새로 삽입한 노드로 이동
        count++;
        time += runtime_sec;
    }
}

void PlayList::delete_node() {

}

bool PlayList::delete_song(const std::string& artist, const std::string& title) {
    if (empty()) return false;
    PlayListNode* cur = head;
    do {
        if (cur->get_artist() == artist && cur->get_title() == title) {
            int sec = cur->get_runtime_sec();
            if (cur == head && cur->get_next() == head) {
                delete cur;
                head = cursor = nullptr;
                count = 0;
                time = 0;
                return true;
            }
            // unlink
            cur->get_prev()->set_next(cur->get_next());
            cur->get_next()->set_prev(cur->get_prev());
            if (cur == head) head = cur->get_next();
            if (cur == cursor) cursor = cur->get_next();
            delete cur;
            --count;
            time -= sec;
            return true;
        }
        cur = cur->get_next();
    } while (cur != head);
    return false;
}

bool PlayList::empty() {
    return head == nullptr;
}

bool PlayList::full() {
    return count >= 10; // PDF기준 PlayList의 최대 노드 수는 10
}

bool PlayList::exist() {
    return !empty();
}

std::string PlayList::print() {
    data.clear();
    if (empty()) return data;
    std::ostringstream oss;
    PlayListNode* cur = head;
    do {
        int sec = cur->get_runtime_sec();
        int mm = sec / 60, ss = sec % 60;
        oss << cur->get_artist() << "/" << cur->get_title() << "/" << mm << ":" << std::setw(2) << std::setfill('0') << ss << "\n";
        cur = cur->get_next();
    } while (cur != head);
    data = oss.str();
    return data;
}

int PlayList::run_time() {
    //구현필요
    return time;
}

// 추가 구현
bool PlayList::find_song(string artist, string title) {
    if (empty()) return false;
    PlayListNode* cur = head;
    do {
        if (cur->get_artist() == artist && cur->get_title() == title) return true;
        cur = cur->get_next();
    } while (cur != head);
    return false;
}

PlayListNode* PlayList::move_next(PlayListNode* current) {
    return current ? current->get_next() : nullptr;
}

PlayListNode* PlayList::move_prev(PlayListNode* current) {
    return current ? current->get_prev() : nullptr;
}