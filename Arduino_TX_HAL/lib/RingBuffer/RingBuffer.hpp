//
// Created by senyaa on 4/21/25.
//

#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <array>
#include <cstdio>

template<typename T, std::size_t N>
class RingBuffer : public std::array<T,N>{
public:
    /**
     *
     * @param items buffer of items to insert
     * @param amount Amount to insert
     * @return New write_index
     */
    size_t insert(const T items[], size_t amount);
    /**
     * Reads data from the ringbuffer. The amount says how many items you want to read.
     * @param items Buffer of items to read into
     * @param amount amount to read
     * @return new read_index
     */
    size_t retrieve(T *items, size_t amount);
    size_t space_free();
    size_t space_used();
private:
    // The values below are for keeping track where exactly we can write to. If these collide then there is something wrong and we overfilled the buffer
    // Keeps track what the last data index was when data was written
    size_t write_index = 0;
    // Keeps track what the last data index was when data was read
    size_t read_index = 0;
    bool overflown = false;
};

template <typename T, std::size_t N>
size_t RingBuffer<T, N>::insert(const T items[], size_t amount) {
    if (write_index + amount > this->size()) {
        size_t fill_from_begin = (write_index + amount) - this->size();
        size_t fill_to_end = amount - fill_from_begin;
        std::copy(items, items + fill_to_end, &this->at(write_index));
        write_index = 0;
        std::copy(items + fill_to_end, items + amount, &this->at(write_index));
        write_index = fill_from_begin;
        overflown = true;
        // char buf[255];
        // sprintf(buf, "write_index:%d, amount:%d, FillToEnd:%d, FillFromBegin:%d\n",write_index, amount, fill_to_end, fill_from_begin);
        // HAL_UART_Transmit(&huart4, reinterpret_cast<const uint8_t*>(buf), strlen(buf), 100);
    } else {
        overflown = false;
        std::copy(items, items + amount, &this->at(write_index));
        write_index += amount;
    }
    return write_index;
}

template <typename T, std::size_t N>
size_t RingBuffer<T, N>::retrieve(T* items, size_t amount) {
    if (read_index + amount > this->size()) {
        size_t read_from_begin = (read_index + amount) - this->size();
        size_t read_to_end = amount - read_from_begin;
        std::copy(&this->at(read_index), &this->at(read_index) + read_to_end, items);
        std::memset(&this->at(read_index), 0, read_to_end);
        read_index = 0;
        std::copy(&this->at(read_index), &this->at(read_index) + read_from_begin, items + read_to_end);
        std::memset(&this->at(read_index), 0, read_from_begin);
        read_index = read_from_begin;
    } else {
        std::copy(&this->at(read_index), &this->at(read_index) + amount, items);
        read_index += amount;
    }
    return read_index;
}
template <typename T, std::size_t N>
size_t RingBuffer<T, N>::space_free() {
    size_t free_space = this->size();
    if (read_index > write_index && overflown) {
        free_space = read_index - write_index;
    }
    else {
        free_space = this->size() - (write_index - read_index);
    }
    return free_space;
}
template <typename T, std::size_t N>
size_t RingBuffer<T, N>::space_used() {

    size_t used_space = this->size();
    if (read_index > write_index && overflown) {
        used_space = this->size() - read_index + write_index;
    }
    else {
        used_space = write_index - read_index;
    }
    return used_space;
}

#endif //RINGBUFFER_H
