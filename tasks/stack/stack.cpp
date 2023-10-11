#include "stack.h"

Node::Node(int32_t value, Node* previous) : value(value), previous(previous){};

Stack::Stack() : head_(nullptr), size_(0){};

Stack::~Stack() {
    delete head_;
}

void Stack::Push(int32_t value) {
    head_ = new Node(value, head_);
    ++size_;
}

void Stack::Pop() {
    if (size_) {
        Node* temp = head_;
        --size_;
        head_ = temp->previous;
        delete temp;
    }
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    while (size_) {
        Pop();
        --size_;
    }
}

bool Stack::Empty() const {
    return size_ == 0;
}