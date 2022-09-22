## Objectives
* Implemented **AVL** tree that is templated.  Provides the following *set* interface:
    * insert(T)
    * bool contains(T) const
    * size_t size() const
    * void erase(T)
    * for_each(Function fn)
* Implemented a **flat set** with the same interface as above, but with the internal storage using a sorted std::vector
