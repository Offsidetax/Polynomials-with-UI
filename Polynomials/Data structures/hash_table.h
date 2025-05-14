#include <iostream>
#include <vector>
#include <functional> // std::hash
#include <string>

using namespace std;

// Состояния ячейки таблицы
enum class CellState {
    EMPTY,
    OCCUPIED,
    DELETED
};

// Шаблонный класс хеш-таблицы
template<typename Key, typename Value>
class HashTable {
private:
    struct Cell {
        Key key;
        Value value;
        CellState state;

        Cell() : state(CellState::EMPTY) {}
    };

    static const int DEFAULT_SIZE = 11;
    vector<Cell> table;
    int currentSize;
    const double LOAD_FACTOR_THRESHOLD = 0.7;

    // Хеш-функция по std::hash
    int hashFunction(const Key& key) const {
        return hash<Key>{}(key) % table.size();
    }

    // Линейное пробирование
    int rehash(int hash, int attempt) const {
        return (hash + attempt) % table.size();
    }

    // Рехеширование таблицы
    void rehashTable() {
        vector<Cell> oldTable = table;
        table.clear();
        table.resize(oldTable.size() * 2);
        currentSize = 0;

        for (const auto& cell : oldTable) {
            if (cell.state == CellState::OCCUPIED) {
                insert(cell.key, cell.value);
            }
        }
    }

public:
    HashTable() : table(DEFAULT_SIZE), currentSize(0) {}

    bool insert(const Key& key, const Value& value) {
        if (static_cast<double>(currentSize) / table.size() >= LOAD_FACTOR_THRESHOLD) {
            rehashTable();
        }

        int index = hashFunction(key);
        int attempt = 1;
        int firstDeleted = -1;

        while (table[index].state != CellState::EMPTY) {
            if (table[index].state == CellState::OCCUPIED && table[index].key == key) {
                table[index].value = value;
                return true;
            }

            if (table[index].state == CellState::DELETED && firstDeleted == -1) {
                firstDeleted = index;
            }

            index = rehash(index, attempt++);
            if (attempt > table.size()) break;
        }

        int insertIndex = (firstDeleted != -1) ? firstDeleted : index;
        table[insertIndex].key = key;
        table[insertIndex].value = value;
        table[insertIndex].state = CellState::OCCUPIED;
        currentSize++;

        return true;
    }

    //bool find(const Key& key, Value& value) const {
    //    int index = hashFunction(key);
    //    int attempt = 1;

    //    while (table[index].state != CellState::EMPTY) {
    //        if (table[index].state == CellState::OCCUPIED && table[index].key == key) {
    //            value = table[index].value;
    //            return true;
    //        }
    //        index = rehash(index, attempt++);
    //        if (attempt > table.size()) break;
    //    }

    //    return false;
    //}

    Value* find(const Key& key) {
        int index = hashFunction(key);
        int attempt = 1;

        while (table[index].state != CellState::EMPTY) {
            if (table[index].state == CellState::OCCUPIED && table[index].key == key) {
                return &table[index].value;
            }
            index = rehash(index, attempt++);
            if (attempt > table.size()) break;
        }

        return nullptr;
    }

    bool remove(const Key& key) {
        int index = hashFunction(key);
        int attempt = 1;

        while (table[index].state != CellState::EMPTY) {
            if (table[index].state == CellState::OCCUPIED && table[index].key == key) {
                table[index].state = CellState::DELETED;
                currentSize--;
                return true;
            }
            index = rehash(index, attempt++);
            if (attempt > table.size()) break;
        }

        return false;
    }

    void print() const {
        for (int i = 0; i < table.size(); ++i) {
            cout << "[" << i << "]: ";
            if (table[i].state == CellState::OCCUPIED) {
                cout << "(" << table[i].key << " -> " << table[i].value << ")";
            }
            else if (table[i].state == CellState::DELETED) {
                cout << "DELETED";
            }
            else {
                cout << "EMPTY";
            }
            cout << endl;
        }
    }

    int size() const {
        return currentSize;
    }

    int capacity() const {
        return table.size();
    }
};
