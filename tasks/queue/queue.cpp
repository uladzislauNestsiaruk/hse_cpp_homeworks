#include "queue.h"

Node::Node(int32_t value, Node *next): value(value), next(next) {}

Queue::Queue(): front_(nullptr), tail_(nullptr), size_(0){}

Queue::~Queue(){
    Clear();
    delete front_;
}

void Queue::Push(int32_t value){
    if(!size_){
        front_ = tail_ = new Node(value, nullptr);
    }
    else{
        Node* next_tail = new Node(value, nullptr);
        tail_->next = next_tail;
        tail_ = next_tail;
    }
    ++size_;
}

void Queue::Pop() {
    if(size_){
        Node* temp = front_->next;
        delete front_;
        front_ = temp;
        --size_;
    }
}

void Queue::Clear() {
    while(size_){
        --size_;
        Pop();
    }
}

int32_t Queue::Size() const {
    return size_;
}

bool Queue::Empty() const {
    return size_ == 0;
}

int32_t Queue::Front() const {
    return front_->value;
}
