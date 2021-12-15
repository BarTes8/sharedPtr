#include <iostream>

namespace bt{

template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr = nullptr) 
        : ptr_{ptr}
        , controlBlock_{new ControlBlock}
    {
        controlBlock_->sharedRefCount = 0;
        controlBlock_->weakRefCount = 0;
        if (ptr_) {
            ++controlBlock_->sharedRefCount;
        }
    }

    shared_ptr(const shared_ptr& sp)
        : ptr_(sp.ptr_)
        , controlBlock_(sp.controlBlock_)
    {
        ++controlBlock_->sharedRefCount;
    }

    shared_ptr(shared_ptr&& sp) 
        : ptr_(sp.ptr_)
        , controlBlock_(sp.controlBlock_)
    {
        sp.ptr_ = nullptr;
        sp.controlBlock_ = nullptr;
    }

    ~shared_ptr() {

    }

    shared_ptr& operator=(shared_ptr&& sp) {
        if (ptr_) {
            delete ptr_;
        }
        ptr_ = sp.ptr_;
        controlBlock_ = sp.controlBlock_;
        sp.ptr_ = nullptr;
        sp.controlBlock_ = nullptr;
        return *this;
    }

    shared_ptr& operator=(const shared_ptr& sp) {

    }

    T& operator*() {
        return *ptr_;
    }

    const T& operator*() const {
        return *ptr_;
    }

private:
    struct ControlBlock {
        int sharedRefCount{};
        int weakRefCount{};
    };

    T* ptr_{nullptr};
    ControlBlock* controlBlock_;
};

} // namespace bt

int main() {
    bt::shared_ptr<int> ptr{new int{5}};
    bt::shared_ptr<int> ptr2 = ptr;

    std::cout << *ptr << '\n';
    std::cout << *ptr2 << '\n';

    return 0;
}
