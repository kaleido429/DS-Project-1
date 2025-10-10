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
        PlayListNode* tmp = cur; // temp가 cur를 가리킴
        cur = cur->get_next(); // cur를 다음 노드로 이동
        delete tmp; // temp가 가리키던 노드 삭제
    }
    delete head; // head 노드 삭제
    // 변수 초기화
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

    PlayListNode* newNode = new PlayListNode; // 새 노드 생성
    newNode->set_artist(artist); // 가수 이름 설정
    newNode->set_title(title); // 곡 제목 설정
    newNode->set_runtime_sec(runtime_sec); // 재생 시간 설정

    if(empty()) {
        //리스트가 비어있는 경우, head와 cursor가 새 노드를 가리킴
        head = newNode;
        cursor = newNode;
        newNode->set_next(newNode);
        newNode->set_prev(newNode);
        count = 1;
        time = runtime_sec;
    } else {
        // newNode를 cursor 뒤에 삽입
        newNode->set_next(cursor->get_next());
        newNode->set_prev(cursor);
        cursor->get_next()->set_prev(newNode);
        cursor->set_next(newNode);
        cursor = newNode; // cursor를 새로 삽입한 노드로 이동
        count++;
        time += runtime_sec;
    }
}

// 현재 커서가 가리키는 노드 삭제
void PlayList::delete_node() {
    if (empty()) return;

    PlayListNode* toDelete = cursor;
    if (toDelete == head && toDelete->get_next() == head) {
        // 리스트에 노드가 하나만 있는 경우
        head = cursor = nullptr;
    } else {
        // 리스트에 노드가 여러 개 있는 경우
        toDelete->get_prev()->set_next(toDelete->get_next());
        toDelete->get_next()->set_prev(toDelete->get_prev());
        if (toDelete == head) head = toDelete->get_next();
        cursor = toDelete->get_next();
    }
    delete toDelete;
}

// (artist, title)로 노드 삭제
bool PlayList::delete_song(const std::string& artist, const std::string& title) {
    if (empty()) return false;
    PlayListNode* cur = head; // head부터 시작
    do {
        // (artist, title) 일치하는 노드 찾기
        if (cur->get_artist() == artist && cur->get_title() == title) {
            int sec = cur->get_runtime_sec();
            if (cur == head && cur->get_next() == head) {// 리스트에 노드가 하나만 있는 경우
                delete cur; // cur 노드 삭제
                head = cursor = nullptr;
                count = 0;
                time = 0;
                return true;
            }
            // unlink
            cur->get_prev()->set_next(cur->get_next()); // cur의 이전 노드가 cur의 다음 노드를 가리키도록
            cur->get_next()->set_prev(cur->get_prev()); // cur의 다음 노드가 cur의 이전 노드를 가리키도록
            if (cur == head) head = cur->get_next(); // head가 삭제되는 노드인 경우 head 갱신
            if (cur == cursor) cursor = cur->get_next(); // cursor가 삭제되는 노드인 경우 cursor 갱신
            delete cur;
            --count; // 노드 개수 감소
            time -= sec; // 재생 시간 감소
            return true;
        }
        cur = cur->get_next(); // 다음 노드로 이동
    } while (cur != head); // 원형 리스트를 한 바퀴 돌았으면 종료
    return false;
}

// PlayList가 비었는지 확인
bool PlayList::empty() {
    return head == nullptr;
}

// PlayList가 꽉 찼는지 확인
bool PlayList::full() {
    return count >= 10; // PDF기준 PlayList의 최대 노드 수는 10
}

// PlayList에 노드가 존재하는지 확인
bool PlayList::exist() {
    return !empty();
}

// PlayList 출력, 각 노드의 (artist/title/mm:ss) 형식
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

// PlayList의 전체 재생 시간 반환
int PlayList::run_time() {
    return time;
}

// 추가 구현
// 특정 (artist, title) 노드가 PlayList에 존재하는지 확인
bool PlayList::find_song(string artist, string title) {
    if (empty()) return false;
    PlayListNode* cur = head;
    // (artist, title) 노드 탐색
    do {
        if (cur->get_artist() == artist && cur->get_title() == title) return true;
        cur = cur->get_next();
    } while (cur != head);
    return false;
}

// 다음 노드로 이동
PlayListNode* PlayList::move_next(PlayListNode* current) {
    return current ? current->get_next() : nullptr;
}

// 이전 노드로 이동
PlayListNode* PlayList::move_prev(PlayListNode* current) {
    return current ? current->get_prev() : nullptr;
}