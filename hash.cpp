#include <iostream>
#include <string>

using namespace std;

template<typename K, typename V>
class HashTable {
private:
    struct Entry {
        K key;
        V value;
        bool isOccupied;  // 当前位置是否被占用
        bool neverUsed;   // 该位置是否从未被使用过
        
        Entry() : isOccupied(false), neverUsed(true) {}
    };
    
    Entry* table;
    int capacity;
    int size;
    
    int hash(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }
    

public:
    HashTable(int cap) : capacity(cap), size(0) {
        table = new Entry[capacity];
    }
    
    ~HashTable() {
        delete[] table;
    }
    
    bool insert(const K& key, const V& value) {
        int pos = hash(key);
        int originalPos = pos;
        
        do {
            if(table[pos].neverUsed || !table[pos].isOccupied) {
                table[pos].key = key;
                table[pos].value = value;
                table[pos].isOccupied = true;
                table[pos].neverUsed = false;
                size++;
                return true;
            }
            
            if(table[pos].key == key && table[pos].isOccupied) {//覆盖原有的value
                table[pos].value = value;
                return true;
            }
            
            pos = (pos + 1) % capacity;
        } while(pos != originalPos);
        
        return false;  // 表满
    }
    
    bool remove(const K& key) {
        int pos = find(key);
        if(pos != -1) {
            table[pos].isOccupied = false;
            // 不修改neverUsed
            size--;
            
            if(needReorganize()) {
                reorganize();
            }
            return true;
        }
        return false;
    }
    
    int find(const K& key) const {
        int pos = hash(key);
        int originalPos = pos;
        
        do {
            if(table[pos].neverUsed) {
                return -1;
            }
            if(table[pos].isOccupied && table[pos].key == key) {
                return pos;
            }
            pos = (pos + 1) % capacity;
        } while(pos != originalPos);
        
        return -1;
    }
    
    void print() {
        for(int i = 0; i < capacity; i++) {
            if(table[i].isOccupied) {
                cout << "[" << i << "]: " << table[i].key << " -> " 
                     << table[i].value << endl;
            }
        }
    }
    
    // 检查是否需要重组
    bool needReorganize() {
        int emptyBuckets = 0;
        int falseNeverUsed = 0;
        
        for(int i = 0; i < capacity; i++) {
            if(!table[i].isOccupied) {
                emptyBuckets++;
                if(!table[i].neverUsed) {
                    falseNeverUsed++;
                }
            }
        }
        
        if(emptyBuckets>0&&falseNeverUsed / (double)emptyBuckets >= 0.6)
        {
            return true;
        }
        else{
            return false;
        }
    }
    
    // 重组散列表
    void reorganize() {
        Entry* oldTable = table;
        table = new Entry[capacity];
        
        for(int i = 0; i < capacity; i++) {
            if(oldTable[i].isOccupied) {
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
        cout<<"重组了！"<<endl;
        delete[] oldTable;
    }
};

// 测试代码
int main() {
    HashTable<int, string> ht(7);
    
    // 测试插入
    ht.insert(1, "one");
    ht.insert(2, "two");
    ht.insert(8, "eight");  
    ht.insert(15, "fifteen");
    ht.insert(7,"seven");
    cout << "初始散列表:" << endl;
    ht.print();
    
    // 测试删除
    cout << "\n删除后:" << endl;
    ht.remove(2);
    ht.remove(1);
    ht.remove(8);

    ht.print();
    
    return 0;
}