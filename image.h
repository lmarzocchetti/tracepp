#ifndef TRACEPP_IMAGE_H
#define TRACEPP_IMAGE_H

#include <vector>

#include "math.h"
#include "types.h"

namespace trace {

// Image data as array of float or byte pixels. Images can be stored in linear
// or non linear color space.
template<typename T>
struct Image {
    Vec2i _size = {0, 0};
    std::vector<T> _data = {};

    // iterators and references
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reference = typename std::vector<T>::reference;
    using const_reference = typename std::vector<T>::const_reference;

    // image api similar to vector
    Image() : _size{0, 0}, _data{} {};

    Image(Vec2i size, const T &value = T{})
            : _size{size}, _data((size_t) size.x * (size_t) size.y, value) {};

    Image(Vec2i size, const T *values)
            : _size{size}, _data{values, values + size.x * size.y} {};

    // size
    bool empty() const {
        return _size == zero2i;
    };

    Vec2i size() const {
        return this->_size;
    };

    // iterator access
    iterator begin() {
        return _data.begin();
    };

    iterator end() {
        return _data.end();
    };

    const_iterator begin() const {
        return _data.begin();
    };

    const_iterator end() const {
        return _data.end();
    };

    // pixel access
    T &operator[](Vec2i ij) {
        return _data[ij.y * _size.x + ij.x];
    };

    const T &operator[](Vec2i ij) const {
        return _data[ij.y * _size.x + ij.x];
    };

    // data access
    T *data() {
        return _data.data();
    };

    const T *data() const {
        return _data.data();
    };

    std::vector<T> &pixels() {
        return _data;
    };

    const std::vector<T> &pixels() const {
        return _data;
    };
};
}

#endif //TRACEPP_IMAGE_H
