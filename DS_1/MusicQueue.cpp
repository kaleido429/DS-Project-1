#include "MusicQueue.h"

MusicQueue::MusicQueue() {
    // queue 초기화
    head = nullptr;
    rear = nullptr;
    size = 0;
}

MusicQueue::~MusicQueue() {
    // 모든 노드 메모리 해제
    while (!empty()) { // queue가 empty가 될 때까지, empty는 size가 0인지 확인 = node의 개수가 0
        MusicQueueNode* temp = pop(); // pop은 노드를 반환
        delete temp; // pop된 노드 메모리 해제
    }
}

bool MusicQueue::empty() {
    return this->size == 0; // size가 0이면 true, 아니면 false
}

// queue에 동일한 (artist, title) 곡이 존재하는지 확인
bool MusicQueue::exist(const std::string& artist, const std::string& title) {
    MusicQueueNode* current = this->head;// head부터 시작
    while (current != nullptr) {// queue 끝까지 탐색
        if (current->getArtist() == artist && current->getTitle() == title) {
            return true; // 중복 발견
        }
        current = current->getNext();
    }
    return false; // 중복 없음
}

void MusicQueue::push(const std::string& artist, const std::string& title, const std::string& runtime) {
    // PDF 요구사항에 따라 queue가 가득 차면 프로그램 종료
    if (this->size >= MAX_SIZE) {
        
        exit(EXIT_FAILURE);
    }
    
    // push할 새로운 node 생성(artist, title, runtime)
    MusicQueueNode* newNode = new MusicQueueNode(artist, title, runtime);

    if (empty()) { // queue가 비어있으면
        // 새로운 node가 head이자 rear 
        this->head = newNode; 
        this->rear = newNode;
    } else { // queue에 기존 노드가 있으면
        // rear -> new node 연결, new node를 rear로 갱신 
        this->rear->setNext(newNode); // rear의 next를 newNode로 설정
        newNode->setPrev(this->rear); // newNode의 prev를 기존 rear로 설정
        this->rear = newNode; // rear 갱신
    }
    this->size++; // size 증가(node 개수 증가)
}

MusicQueueNode* MusicQueue::pop(){
    // PDF 요구사항에 따라 queue가 비어있으면 프로그램 종료
    if (empty()) {
        exit(EXIT_FAILURE);
    }

    // head 노드 제거 후 반환, Queue는 FIFO 구조이므로 head 노드 반환(제거는 pop에서 하지 않고 Manager.cpp에서 함)
    MusicQueueNode* nodeToPop = this->head;
    
    this->head = this->head->getNext();// head를 다음 노드로 갱신
    
    if (this->head != nullptr) {// queue에 노드가 남아있으면
        this->head->setPrev(nullptr); // 새로운 head의 prev를 nullptr로 설정
    } else {
        // queue가 비게 되면 rear도 nullptr로 설정
        this->rear = nullptr;
    }

    this->size--; // size 감소(node 개수 감소)
    
    // pop된 노드를 리스트에서 완전히 분리
    nodeToPop->setNext(nullptr); 
    
    return nodeToPop;
}

// queue의 첫 node 반환
MusicQueueNode* MusicQueue::front() {
    return this->head;
}