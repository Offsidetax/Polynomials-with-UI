#pragma once
#include <vector>
#include <utility>

template <class TKey, class TValue>
class UnsortedTable {
	std::vector<std::pair<TKey, TValue>> data;

public:
   /* void insert(const TKey& key, const TValue& value) {// Вставка новой пары ключ-значение
        for (auto& pair : data) {
            if (pair.first == key) {  // Если ключ уже есть, обновляем значение
                pair.second = value;
                return;
            }
        }
        data.emplace_back(key, value);  // Добавляем новую пару в конец
    }

    TValue find(const TKey& key) const {
        for (const auto& pair : data) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw "There is no such object in table!";
    }


    void remove(const TKey& key) { // Удаление элемента по ключу
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].first == key) {
                data[i] = data.back();  // Заменяем найденный элемент последним
                data.pop_back();        // Удаляем последний элемент
                return;
            }
        }
        throw "There is no such object in table!";
    }*/

    TValue& operator[](const TKey& key) { // Перегруженный оператор [] для доступа по ключу
        for (auto& pair : data) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        data.emplace_back(key, TValue{}); // Если ключ не найден, добавляется новая пара
        return data.back().second;
    }

    // Вывод всех элементов (для отладки)
    void print() const {
        for (const auto& pair : data) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    class Iterator {
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

    Iterator insert(const TKey& key, const TValue& value) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->first == key) {
                it->second = value;
                return Iterator(it);
            }
        }
        data.emplace_back(key, value);
        return Iterator(data.end() - 1);
    }

    Iterator erase(const TKey& key) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->first == key) {
                auto nextIt = data.erase(it);
                return Iterator(nextIt);
            }
        }
        return end();
    }

    /*Iterator find(const TKey& key) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->first == key) {
                return Iterator(it);
            }
        }
        return end();
    }*/

    ///ДЛЯ ИНТЕРФЕЙСА////
    TValue* find(const TKey& key) {
        for (auto& pair : data) {
            if (pair.first == key) {
                return &pair.second;
            }
        }
        return nullptr;
    }

    const TValue* find(const TKey& key) const {
        for (const auto& pair : data) {
            if (pair.first == key) {
                return &pair.second;
            }
        }
        return nullptr;
    }

    bool remove(const TKey& key) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].first == key) {
                data[i] = data.back();
                data.pop_back();        
                return true;
            }
        }
        return false;  
    }

};