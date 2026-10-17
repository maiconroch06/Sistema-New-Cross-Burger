#ifndef ORDER_HPP
#define ORDER_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Order {
private:
    int number;
    string client;
    vector<string> items;       // ArrayList do C++
    vector<int> quantatyItems; 
    float total;

public:
    Order();
    Order(const string& client, const vector<string>& items);
    Order(const string& client, const vector<string>& items, const vector<int>& quantatyItems);
    Order(const int number, const string& client, const vector<string>& items, const float total);
    ~Order();

    // Esta variável estática funciona como o contador mestre do sistema
    inline static int globalCounter = 0; 

    void addItem(const std::string& item);
    void removeItem();
    void showOrder() const;

    void addItem(int itemCode);
    bool removeItem(int itemCode);

    float calcularTotal() const;

    int getNumber() const;
    void setNumber(int number);
    string getClient() const;
    const vector<string>& getItems() const;
    float getTotal() const;
    const vector<int>& getQuantatyItems() const;
};

#endif


// <vector>
// front(): Returns the value of the first element in the list.
// back(): Returns the value of the last element in the list.
// push_front(x): Adds a new element ‘x’ at the beginning of the list.
// push_back(x): Adds a new element ‘x’ at the end of the list.
// pop_front(): Removes the first element of the list, and reduces the size of the list by 1.
// pop_back(): Removes the last element of the list, and reduces the size of the list by 1.