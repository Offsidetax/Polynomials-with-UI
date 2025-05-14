#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

template <class TKey, class TValue>
class SortedTable 
{
    std::vector<std::pair<TKey, TValue>> data;

public:
    TValue& operator[](const TKey& key) 
    {
        auto it = std::lower_bound(data.begin(), data.end(), key, [](const auto& pair, const TKey& key) { return pair.first < key; });
        if (it != data.end() && it->first == key) 
        {
            return it->second;
        }
        it = data.insert(it, std::make_pair(key, TValue{}));
        return it->second;
    }

    void print() const 
    {
        for (const auto& pair : data) 
        {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    class Iterator 
    {
        typename std::vector<std::pair<TKey, TValue>>::iterator iter;
    public:
        Iterator(typename std::vector<std::pair<TKey, TValue>>::iterator it) : iter(it) {}
        std::pair<TKey, TValue>& operator*() { return *iter; }
        Iterator& operator++() { ++iter; return *this; }
        bool operator!=(const Iterator& other) const { return iter != other.iter; }
        bool operator==(const Iterator& other) const { return iter == other.iter; }
        std::pair<TKey, TValue>* operator->() { return &(*iter); }
    };

    Iterator begin() { return Iterator(data.begin()); }
    Iterator end() { return Iterator(data.end()); }

    Iterator insert(const TKey& key, const TValue& value) 
    {
        auto it = std::lower_bound(data.begin(), data.end(), key,
            [](const auto& pair, const TKey& key) { return pair.first < key; });
        if (it != data.end() && it->first == key) 
        {
            it->second = value;
            return Iterator(it);
        }
        it = data.insert(it, std::make_pair(key, value));
        return Iterator(it);
    }

    Iterator erase(const TKey& key) 
    {
        auto it = std::lower_bound(data.begin(), data.end(), key,
            [](const auto& pair, const TKey& key) { return pair.first < key; });
        if (it != data.end() && it->first == key) 
        {
            return Iterator(data.erase(it));
        }
        return end();
    }

    //Iterator find(const TKey& key) 
    //{
    //    auto it = std::lower_bound(data.begin(), data.end(), key,
    //        [](const auto& pair, const TKey& key) { return pair.first < key; });
    //    if (it != data.end() && it->first == key)
    //    {
    //        return Iterator(it);
    //    }
    //    return end();
    //}

    //Для интерфейса
    TValue* find(const TKey& key)
    {
        auto it = std::lower_bound(data.begin(), data.end(), key,
            [](const auto& pair, const TKey& key) { return pair.first < key; });
        if (it != data.end() && it->first == key)
        {
            return &(it->second);  // Возвращаем указатель на значение
        }
        return nullptr; // Не найдено
    }


    void remove(const TKey& key)
    {
        erase(key);
    }
};
