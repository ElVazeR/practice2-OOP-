#include <initializer_list>
#include <iostream>

template<typename key, typename value>
class map1 {
private:
    struct Pair {
        key first;
        value second;

        Pair() : first(), second() {}
        Pair(const key& key, const value& value) : first(key), second(value) {}
    };

    Pair* pairs;
    size_t capacity;
    size_t currentSize;

public:
   
    map1() : pairs(nullptr), capacity(0), currentSize(0) {}

    map1(const map1& other) : capacity(other.capacity), currentSize(other.currentSize) {
        pairs = new Pair[capacity];
        for (size_t i = 0; i < currentSize; ++i) {
            pairs[i] = other.pairs[i];
        }
    }

   
    map1(const std::initializer_list<std::pair<key, value>>& initList) : capacity(initList.size()), currentSize(0) {
        pairs = new Pair[capacity];
        for (auto& p : initList) {
            pairs[currentSize++] = Pair(p.first, p.second);
        }
    }

    
    ~map1() {
        delete[] pairs;
    }
    void resize() {
        capacity = capacity == 0 ? 1 : capacity * 2;
        Pair* newPairs = new Pair[capacity];
        for (size_t i = 0; i < currentSize; ++i) {
            newPairs[i] = pairs[i];
        }
        delete[] pairs;
        pairs = newPairs;
    }

  
    void setItem(const key& key, const value& value) {
        for (size_t i = 0; i < currentSize; ++i) {
            if (pairs[i].first == key) {
                pairs[i].second = value;
                return;
            }
        }
        if (currentSize >= capacity) {
            resize();
        }
        pairs[currentSize++] = Pair(key, value);
    }

  
    value& operator[](const key& key) {
        for (size_t i = 0; i < currentSize; ++i) {
            if (pairs[i].first == key) {
                return pairs[i].second;
            }
        }
  
        if (currentSize >= capacity) {
            resize();
        }
        pairs[currentSize] = Pair(key, value());
        return pairs[currentSize++].second;
    }

    void printAll() const {
        for (size_t i = 0; i < currentSize; ++i) {
            std::cout << "Key: " << pairs[i].first << ", Value: " << pairs[i].second << std::endl;
        }
    }

  
    void clear() {
        delete[] pairs;
        pairs = nullptr;
        capacity = 0;
        currentSize = 0;
    }
Практика по создани
    
    size_t size() const {
        return currentSize;
    }


};

int main() {
    setlocale(0, "Russian");
    map1<int, std::string> map1;
    map1.setItem(1, "Logan");
    map1.setItem(2, "Robert Downey Jr.");
    map1[3] = "Hugh Jackman";

    std::cout << map1[2] << std::endl;
    std::cout << "Current size is: " << map1.size() << std::endl;
    std::cout << "Тут добавил map1[5], но без value, для проверки увеличиться ли размер." << std::endl;
    std::cout << map1[5] << std::endl;
    std::cout << "Current size is: " << map1.size() << std::endl;
    map1[5] = "DeadPool";
    std::cout << map1[5] << std::endl;
    std::cout << "Current size is: " << map1.size() << std::endl;

    map1.printAll();

    map1.clear();
    std::cout << "Size after clear: " << map1.size() << std::endl;
    map1.printAll();

    return 0;
}