#include "../models/Order.hpp"

using namespace std;

Order::Order() {
    this->number = 0;
    this->client = "";
    this->total = 0.0f;
}

Order::Order(int number, const string& client, const vector<string>& items, float total) {
    this->number = number;
    this->client = client;
    this->items = items;
    this->total = total;
}

Order::~Order() {

}

void Order::addItem(const string& item) {
    this->items.push_back(item);
}

void Order::removeItem() {
    if (!this->items.empty()) {
        this->items.pop_back();
    }
}

void Order::showOrder() const {
    cout << "   > Pedido: " << this->getNumber() << endl;
    cout << "   > Cliente: " << this->getClient() << endl;
    cout << "   > Itens:" << endl;
    for (const string& item : items) {
        cout << "      - " << item << endl;
    }
    cout << "   > Total: R$ " << this->getTotal() << endl;
}

int Order::getNumber() const {
    return number;
}

std::string Order::getClient() const {
    return client;
}

const std::vector<std::string>& Order::getItems() const {
    return items;
}

float Order::getTotal() const {
    return total;
}