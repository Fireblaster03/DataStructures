#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>


template <typename T> class flat_set {
    private:
    std::vector<T> vect;

    public:

    void insert(T data) {
        vect.insert(std::lower_bound(vect.begin(), vect.end(), data), data);
    }

    bool contains(T data) const {
        if(std::lower_bound(vect.begin(), vect.end(), data) != vect.end()) {
            return true;
        }
        return false;
    }

    size_t size() const {
        return vect.size();
    }

    void erase(T data) {
        if(contains(data)) {
            vect.erase(std::lower_bound(vect.begin(), vect.end(), data));
        }
    }

    void for_each(auto fn) {
        for(T data : vect) {
            fn(data);
        }
    }
  
};