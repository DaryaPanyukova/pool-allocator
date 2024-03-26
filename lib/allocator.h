#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>

template<typename Type>
class Allocator {
public:
    using value_type = Type;
    using reference = Type&;
    using size_type = size_t;
    using pointer = Type*;


    struct Pool {
        value_type* first_free = nullptr; // первый свободный чанк
        value_type* first = nullptr; // начало памяти (может быть != first_free)
        size_type chunk_size;
        size_type chunk_number;

        bool isFree() {
            return first_free != nullptr;
        }

        Pool() = default;

        Pool(const Pool& other) {
            first_free = other.first_free;
            first = other.first;
            chunk_size = other.chunk_size;
            chunk_number = other.chunk_number;
        }

        Pool(size_type chunk_size1, size_type chunk_number1) {
            chunk_size = chunk_size1;
            chunk_number = chunk_number1;

            size_type size = std::max(sizeof(value_type), 8ULL) * chunk_size *
                             chunk_number;
            first_free = first = static_cast<value_type*>(malloc(size));

            value_type** prev = reinterpret_cast<value_type**> (first);
            value_type** next = prev;
            for (size_t i = 1; i < chunk_number1; ++i) {
                size_type shift = (std::max(sizeof(value_type), 8ULL) /
                                   sizeof(value_type)) * chunk_size;
                next = reinterpret_cast<value_type**>
                (reinterpret_cast<value_type*>(next) + shift);
                *prev = reinterpret_cast<value_type*> (next);
                prev = next;

            }
            *prev = nullptr;
        }

        ~Pool() {
            if (first != nullptr) {
                free(first);
            }
        }

        bool ContainsChunk(const value_type* chunk) const {
            return (chunk >= first &&
                    chunk <= first + chunk_size * chunk_number);
        }
    };


    Allocator() = default;

    Allocator(
            const std::initializer_list<std::pair<size_type, size_type>>& pools) {
        for (const auto& pool_data: pools) {
            size_type chunk_size = pool_data.first;
            size_type chunk_number = pool_data.second;

            auto ptr = std::shared_ptr<Pool>(new Pool(chunk_size, chunk_number));
            pools_.insert({chunk_size, ptr});
        }
    }

    template<class W> friend
    class Allocator;

    template<typename W>
    Allocator(const Allocator<W>& other) {
        for (auto& elem: other.pools_) {
            auto ptr = std::shared_ptr<Allocator<Type>::Pool>(new Allocator<Type>::Pool(elem.second->chunk_size, elem.second->chunk_number));
            pools_.insert({elem.first, ptr});
        }
    }

    ~Allocator() =
    default;

    value_type* allocate(size_type size) {
        auto pool = pools_.lower_bound(size);
        for (; pool != pools_.end(); ++pool) {
            if (pool->second->isFree()) {  // если пул свободный
                break;
            }
        }

        if (pool == pools_.end()) {
            throw std::bad_alloc();
        }

        value_type* tmp = pool->second->first_free;
        pool->second->first_free = *reinterpret_cast<value_type**>(tmp);
        return tmp;
    }

    void deallocate(value_type* chunk, size_type size) {
        std::shared_ptr <Pool> pool;
        for (auto& elem: pools_) {
            if (elem.second->ContainsChunk(chunk)) {
                pool = elem.second;
                break;
            }
        }

        if (pool != nullptr) {
            value_type** ptr = reinterpret_cast<value_type**> (chunk);
            *ptr = pool->first_free;
            pool->first_free = chunk;
        }
    }

    bool operator==(const Allocator<value_type>& other) const {
        return this->pools_ == other.pools_;
    }

    bool operator!=(const Allocator<value_type>& other) const {
        return !(*this == other);
    }

    template<class Y>
    struct rebind {
        using other = Allocator<Y>;
    };


private:
    std::multimap<size_type, std::shared_ptr<Pool>> pools_;
};

