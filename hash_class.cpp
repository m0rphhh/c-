#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
 
#define N 1000003
 
using namespace std;
 
typedef vector<list<int>> table_t;
 
class HashTable {
public:
    HashTable();
 
    void change_table(int key);
 
    vector<int> get_result();
 
private:
    table_t hash_table;
 
    unsigned h(unsigned key);
};
 
HashTable::HashTable() {
    hash_table.resize(N);
}
 
vector<int> HashTable::get_result() {
    vector<int> result;
    for (const auto &i: hash_table) {
        for (auto it = i.begin(); it != i.end(); advance(it, 1)) {
            result.push_back(*it);
        }
    }
 
    sort(result.begin(), result.end());
    return result;
}
 
void HashTable::change_table(int key) {
    list<int> *lst = &hash_table[h(abs(key))];
    auto it = find(lst->begin(), lst->end(), abs(key));
    if (key > 0 && it == lst->end()) {
        lst->push_front(key);
    } else if (key < 0 && it != lst->end()) {
        lst->erase(it);
    }
}
 
unsigned HashTable::h(unsigned int key) {
    double a = (sqrt(5) - 1) / 2;
    return floor(N * (key * a - floor(key * a)));
}
 
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
 
    HashTable hash_table = HashTable();
 
    int key;
    do {
        fin >> key;
        hash_table.change_table(key);
    } while (key != 0);
 
    vector<int> result = hash_table.get_result();
 
    for (int i : result) {
        fout << i << " ";
    }
 
    fin.close();
    fout.close();
    return 0;
}