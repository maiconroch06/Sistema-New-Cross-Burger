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
    float total;

public:
    Order(); // Construtor padrão
    Order(const string& client, const vector<string>& items);
    Order(const int number, const string& client, const vector<string>& items, const int total);
    ~Order();

    void addItem(const std::string& item);
    void removeItem();
    void showOrder() const;

    float calcularTotal() const;

    int getNumber() const;
    void setNumber(int number);
    std::string getClient() const;
    const std::vector<std::string>& getItems() const;
    float getTotal() const;
};

#endif