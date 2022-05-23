
#include <memory> 
#include <iostream>

using namespace std;

template<typename T>
class unique_pointer
{
private:
    T* obj;

public:
    unique_pointer() : obj(nullptr) {}
    unique_pointer(const unique_pointer& sp) = delete;
    unique_pointer(T* p) {
        obj = p;
    }

    ~unique_pointer() {
        delete obj;
    }

    T& operator* () {
        return *obj;
    }

    T* get() {
        return obj;
    }

    void reset() {
        delete obj;
        obj = nullptr;
    }

    void realese() {
        obj = nullptr;
    }

    void swap(unique_pointer<T>& up) {
        std::swap(obj, up.obj);
    }
};

template<class T>
class shared_pointer {
    T* obj = nullptr;
    size_t* count = nullptr;
public:
    shared_pointer() : obj(nullptr), count(nullptr) {}
    shared_pointer(const shared_pointer& sp) {
        obj = sp.obj;
        count = sp.count;
        (*count)++;
    };

    shared_pointer(T* p) {
        obj = p;
        count = new size_t(1);
    }

    ~shared_pointer() {
        if ((*count) > 0) {
            (*count)--;
        }
        else
        {
            delete obj;
            delete count;
        }
    }

    T& operator* () {
        return *obj;
    }

    T* operator->() {
        return obj;
    }

    void operator= (shared_pointer<T>& up) {
        this->obj = up.obj;
        count = up.count;
        (*count)++;
    }

    T* get() {
        return obj;
    }

    void reset() {
        delete obj;
        obj = nullptr;
    }

    void swap(shared_pointer<T>& up) {
        std::swap(obj, up.obj);
    }

    size_t use_count() {
        return *count;
    }
};

int main()
{
    shared_pointer<int> p(new int(5));
    shared_pointer<int> p2;
    cout << p.use_count() << endl;
    p2 = p;
    cout << p.use_count() << endl;

    shared_pointer<int> y;
    y = p2;
    cout << p.use_count() << endl;

    cout << "---------------------\n";
    shared_pointer<int> p3(new int(5));
    shared_pointer<int> p4;
    cout << p3.use_count() << endl;
    p4 = p3;
    cout << p3.use_count() << endl;

    shared_pointer<int> x;
    x = p4;
    cout << p3.use_count() << endl;

    return 0;
}