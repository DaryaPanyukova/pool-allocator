#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <fstream>
#include "../lib/allocator.h"

std::ofstream output("D:\\ITMOlabs\\basics_c++\\labwork-9-DaryaPanyukova\\out.txt");

auto TestVectorStd(int size) {
    std::vector<int> vec1;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        vec1.emplace_back(i);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(
            stop - start);

    return dur;
}

auto TestVectorPool(int size) {
    Allocator<int> alloc({{ {16384 + 1, 2}}});
    std::vector<int, Allocator<int>> vec2(alloc);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        vec2.emplace_back(i);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(
            stop - start);

    return dur;
}

auto TestVector() {
    for (int i = 10000; i <= 500000; i += 10000) {
        output << '\n';
        // std, pool
        output << i << ' ' << TestVectorStd(i).count() << " " << TestVectorPool(i).count();
    }
}



auto TestListStd(int size) {
    std::list<double> data;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        data.push_back(i);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(
            stop - start);

    return dur;
}

auto TestListPool(int size) {
    Allocator<double> alloc({{10, size}});

    std::list<double, Allocator<double>> data(alloc);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        data.push_back(i);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(
            stop - start);

    return dur;
}

void TestList() {
    for (int i = 10000; i <= 500000; i += 10000) {
        output << '\n';
        // std, pool
        output << i << ' ' << TestListStd(i).count() << " " << TestListPool(i).count();
    }
}



int main() {
   // TestList();
    for (auto i = 0; i < 10; i++) {
        std::cout << TestVectorPool(10000).count() << ' '
                  << TestVectorStd(10000).count()
                  << std::endl;
    }
    return 0;
}