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
    vector<string> items;
    vector<int> quantatyItems;
    float total;

public:
    Order();
    Order(const string& client, const vector<string>& items);
    Order(const string& client, const vector<string>& items, const vector<int>& quantatyItems);
    Order(const int number, const string& client, const vector<string>& items, const float total);
    ~Order();

    void addItem(const std::string& item);
    void removeItem();
    void showOrder() const;

    float calcularTotal() const;

    int getNumber() const;
    void setNumber(int number);
    string getClient() const;
    const vector<string>& getItems() const;
    float getTotal() const;
    const vector<int>& getQuantatyItems() const;
};

#endif