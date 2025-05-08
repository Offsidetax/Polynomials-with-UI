#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <iterator>

using namespace std;

template<typename Key, typename Value>
class ChainHashTable {
    int M;
    int totalCount = 0;
    double maxLoadFactor = 0.75;
    vector<vector<pair<Key, Value>>> chains;

    int hashFunction(const Key& key) const {
        return hash<Key>{}(key) % M;
    }

    void rehash() {
        int newM = M * 2;
        vector<vector<pair<Key, Value>>> newChains(newM);

        for (int i = 0; i < M; ++i) {
            for (const auto& kv : chains[i]) {
                int newIdx = hash<Key>{}(kv.first) % newM;
                newChains[newIdx].push_back(kv);
            }
        }

        chains = move(newChains);
        M = newM;
    }

public:
    ChainHashTable(int size = 10) : M(size), chains(size) {
        if (size < 0) throw "Size can't be lower, then 0!";
    }

    void insert(const Key& key, const Value& value) {
        //std::cout << "It works!" << std::endl;

        if ((double)(totalCount + 1) / M > maxLoadFactor) {
            rehash();
        }

        int idx = hashFunction(key);
        auto& bucket = chains[idx];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                it->second = value;
                return;
            }
        }

        bucket.emplace_back(key, value);  // новая пара
        totalCount++;
    }

    Value* find(const Key& key) {
        int idx = hashFunction(key);
        auto& bucket = chains[idx];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                return &it->second;
            }
        }

        return nullptr;
    }

    bool erase(const Key& key) {
        int idx = hashFunction(key);
        auto& bucket = chains[idx];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                totalCount--;
                return true;
            }
        }
        return false;
    }

    bool remove(const Key& key) { //для интерфейса
        return erase(key);
    }

    void debugPrint() const { //для отладки
        for (int i = 0; i < M; ++i) {
            cout << "[" << i << "]: ";
            for (const auto& kv : chains[i]) {
                cout << "(" << kv.first << ", " << kv.second << ") ";
            }
            cout << "\n";
        }
    }

    // ================= ИТЕРАТОР =================
    class Iterator {
        const ChainHashTable* table;
        int outerIndex;
        int innerIndex;

        void advanceToNextValid() {
            while (outerIndex < table->M && innerIndex >= (int)table->chains[outerIndex].size()) {
                ++outerIndex;
                innerIndex = 0;
            }
        }

    public:
        Iterator(const ChainHashTable* table, int outer, int inner): table(table), outerIndex(outer), innerIndex(inner) {
            advanceToNextValid();
        }

        Iterator& operator++() {
            ++innerIndex;
            advanceToNextValid();
            return *this;
        }

        const pair<Key, Value>& operator*() const {
            return table->chains[outerIndex][innerIndex];
        }

        bool operator!=(const Iterator& other) const {
            return outerIndex != other.outerIndex || innerIndex != other.innerIndex;
        }
    };

    Iterator begin() const { return Iterator(this, 0, 0); }
    Iterator end() const { return Iterator(this, M, 0); }
};
