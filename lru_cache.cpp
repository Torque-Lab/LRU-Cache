#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;
class LRUCache
{
private:
    int capacity;

    list<pair<int, int>> cacheList; // {key, value}

    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;
    void moveToFront(int key, int value)
    {
        cacheList.erase(cacheMap[key]);
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin(); // Update map
    }

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key)
    {
        if (cacheMap.find(key) == cacheMap.end())
        {
            return -1;
        }
        int value = cacheMap[key]->second;
        moveToFront(key, value);
        return value;
    }

    void put(int key, int value)
    {
        if (cacheMap.find(key) != cacheMap.end())
        {
            moveToFront(key, value); // Key exists, update position
        }
        else
        {
            if (cacheList.size() == capacity)
            {
                // Remove least recently used (last element)
                int lruKey = cacheList.back().first;
                cacheMap.erase(lruKey);
                cacheList.pop_back();
            }
            // Insert new key-value pair
            cacheList.push_front({key, value});
            cacheMap[key] = cacheList.begin();
        }
    }

    void display()
    {
        for (const auto &pair : cacheList)
        {
            cout << "[" << pair.first << ":" << pair.second << "] ";
        }
        cout << endl;
    }
};

int main()
{
    LRUCache cache(3);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.display();

    cache.get(1);
    cache.display();

    cache.put(4, 40);
    cache.display();

    cout << "Get 2: " << cache.get(2) << endl;

    return 0;
}
