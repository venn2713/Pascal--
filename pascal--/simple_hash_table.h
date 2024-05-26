#pragma once
#include <vector>
#include <utility>
#include <string>
#include <functional>

using namespace std;

// Простая хэш-таблица с открытой адресацией
template <typename Key, typename Value>
class SimpleHashTable {
public:
    SimpleHashTable(size_t size = 101) : table(size), filled(0) {}

    bool insert(const Key& key, const Value& value) {
        size_t hash = hashFunction(key);
        size_t index = hash % table.size();
        size_t original_index = index;
        while (table[index].first != "" && table[index].first != key) {
            index = (index + 1) % table.size();
            if (index == original_index) return false; // Таблица заполнена
        }
        if (table[index].first == "") filled++;
        table[index] = { key, value };
        return true;
    }

    bool get(const Key& key, Value& value) const {
        size_t hash = hashFunction(key);
        size_t index = hash % table.size();
        size_t original_index = index;
        while (table[index].first != "") {
            if (table[index].first == key) {
                value = table[index].second;
                return true;
            }
            index = (index + 1) % table.size();
            if (index == original_index) break; // Прошли весь круг, элемент не найден
        }
        return false;
    }

    bool exists(const Key& key) const {
        Value temp;
        return get(key, temp);
    }

private:
    vector<pair<Key, Value>> table;
    size_t filled;

    size_t hashFunction(const Key& key) const {
        hash<string> hash_fn;
        return hash_fn(key);
    }
};
