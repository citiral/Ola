//
// Created by Citiral on 30/09/2015.
//

#ifndef OLA_STACKLIST_H
#define OLA_STACKLIST_H

#include <vector>
#include <map>

template <class K, class V>
class StackMap {
public:
    StackMap();
    virtual ~StackMap();

    void addValue(K key, V value);
    V getValue(K key);
    void removeValue(K key);
    bool hasValue(K key);

    void pushMap();
    void popMap();
private:
    V getValue(K key, int listIndex);
    bool hasValue(K key, int listIndex);

    std::vector<std::map<K, V>> _listMap;
};

template <class K, class V>
StackMap<K, V>::StackMap() {
    pushMap();
}

template <class K, class V>
StackMap<K, V>::~StackMap() {
}

template <class K, class V>
void StackMap<K, V>::addValue(K key, V value) {
    _listMap.back()[key] = std::move(value);
};

template <class K, class V>
V StackMap<K, V>::getValue(K key) {
    return getValue(key, _listMap.size()-1);
};

template <class K, class V>
V StackMap<K, V>::getValue(K key, int listIndex) {
    auto elemIndex = _listMap[listIndex].find(key);
    if (elemIndex == _listMap[listIndex].end()) {
        if (listIndex == 0)
            return nullptr;
        return getValue(key, listIndex-1);
    }
    return elemIndex->second;
};

template <class K, class V>
void StackMap<K, V>::removeValue(K key) {
    _listMap.back().erase(key);
};

template <class K, class V>
bool StackMap<K, V>::hasValue(K key) {
    return hasValue(key, _listMap.size()-1);
};

template <class K, class V>
bool StackMap<K, V>::hasValue(K key, int listIndex) {
    if (_listMap[listIndex].find(key) == _listMap[listIndex].end()) {
        if (listIndex == 0)
            return false;
        return hasValue(key, listIndex-1);
    }
    return true;
};

template <class K, class V>
void StackMap<K, V>::pushMap() {
    _listMap.push_back(std::map<K, V>());
};

template <class K, class V>
void StackMap<K, V>::popMap() {
    _listMap.erase(--_listMap.end());
};


#endif //OLA_STACKLIST_H
