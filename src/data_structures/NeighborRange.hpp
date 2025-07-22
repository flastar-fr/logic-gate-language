#pragma once

template<typename T>
struct NeighborRange {
    explicit NeighborRange(const T* i_begin, const T* i_end): i_begin(i_begin), i_end(i_end) {}

    const T* i_begin;
    const T* i_end;
};
