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

    
    return 0;
}
