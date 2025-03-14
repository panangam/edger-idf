#pragma once

#include <vector>
#include <cstddef>
#include <iterator>

template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity)
        : capacity(capacity), buffer(capacity), head(0), size(0) {}

    void push(const T& item) {
        buffer[(head + size) % capacity] = item;
        if (size < capacity) {
            size++;
        } else {  // Overwrite oldest item
            head = (head + 1) % capacity;
        }
    }
    std::size_t getSize() const { return size; }
    std::size_t getCapacity() const { return capacity; }

    class Iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(const RingBuffer<T>& ringBuffer, std::size_t index)
            : ringBuffer(ringBuffer), index(index) {}

        bool operator!=(const Iterator& other) const { return index != other.index; }
        const T& operator*() const { return ringBuffer.buffer[index % ringBuffer.capacity]; }
        Iterator& operator++() {
            index++;
            return *this;
        }
        size_t getIndex() const { return index; }

    private:
        const RingBuffer<T>& ringBuffer;
        size_t index;
    };

    Iterator begin() const { return Iterator(*this, head); }
    Iterator end() const { return Iterator(*this, head + size); }

private:
    std::size_t capacity;
    std::vector<T> buffer;
    std::size_t head;
    std::size_t size;
};
