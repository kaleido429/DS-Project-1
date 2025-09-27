#include "MusicQueue.h"

MusicQueue::MusicQueue() {

}

MusicQueue::~MusicQueue() {
    // 모든 노드 메모리 해제
    while (!empty()) {
        MusicQueueNode* temp = pop();
        delete temp;
    }
}

bool MusicQueue::empty() {
    return this->size == 0;
}

bool MusicQueue::exist(const std::string& artist, const std::string& title) {
    MusicQueueNode* current = this->head;
    while (current != nullptr) {
        if (current->getArtist() == artist && current->getTitle() == title) {
            return true; // 중복 발견
        }
        current = current->getNext();
    }
    return false; // 중복 없음
}

void MusicQueue::push(const std::string& artist, const std::string& title, const std::string& runtime) {
    // PDF 요구사항에 따라 큐가 가득 차면 프로그램 종료 [cite: 409]
    if (this->size >= MAX_SIZE) {
        
        exit(EXIT_FAILURE);
    }
    
    MusicQueueNode* newNode = new MusicQueueNode(artist, title, runtime);

    if (empty()) {
        this->head = newNode;
        this->rear = newNode;
    } else {
        this->rear->setNext(newNode);
        newNode->setPrev(this->rear);
        this->rear = newNode;
    }
    this->size++;
}

MusicQueueNode* MusicQueue::pop(){
    // PDF 요구사항에 따라 큐가 비어있으면 프로그램 종료 [cite: 409]
    if (empty()) {
        exit(EXIT_FAILURE);
    }

    MusicQueueNode* nodeToPop = this->head;
    
    this->head = this->head->getNext();
    
    if (this->head != nullptr) {
        this->head->setPrev(nullptr);
    } else {
        // 큐가 이제 비었음
        this->rear = nullptr;
    }

    this->size--;
    
    // pop된 노드를 리스트에서 완전히 분리
    nodeToPop->setNext(nullptr); 
    
    return nodeToPop;
}

MusicQueueNode* MusicQueue::front() {
    return this->head;
}