#ifndef ORDER_HPP
#define ORDER_HPP

#include <iostream>
#include <string>
#include <vector>

class Order {
private:
    int number;
    std::string client;
    std::vector<std::string> items;
    float total;

public:
    Order(); // Construtor padrão
    Order(int number, const std::string& client, const std::vector<std::string>& items, float total);
    ~Order();

    void addItem(const std::string& item);
    void removeItem();
    void printOrder() const;

    int getNumber() const;
    std::string getClient() const;
    const std::vector<std::string>& getItems() const;
    float getTotal() const;
};

#endif