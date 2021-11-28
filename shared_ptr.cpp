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
    return 0;
}
