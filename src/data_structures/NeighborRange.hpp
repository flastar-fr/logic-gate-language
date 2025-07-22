#pragma once

template<typename T>
struct NeighborRange {
    explicit NeighborRange(T* i_begin, T* i_end): i_begin(i_begin), i_end(i_end) {}

    [[nodiscard]] T* begin() const { return i_begin; }
    [[nodiscard]] T* end() const { return i_end; }

    T* i_begin;
    T* i_end;
};
