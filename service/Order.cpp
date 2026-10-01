#include "../models/Order.hpp"

using namespace std;

Order::Order() {
    this->number = 0;
    this->client = "";
    this->items = {NULL};
    this->total = 0.0f;
}

Order::Order(const string& client, const vector<string>& items) {
    //this->number = number; // Será definido na classe KitchenLikedQueue
    this->client = client;
    this->items = items;
    this->total = calcularTotal();
}

Order::Order(const int number, const string& client, const vector<string>& items, const int total) {
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

float Order::calcularTotal() const {
    float total = 0;

    for (const string& item : this->items) {
        if (item == "Cachorro Quente") {
            total += 8.0;
        } else if (item == "Batata Frita") {
            total += 6.0;
        } else if (item == "Hambuger") {
            total += 20.0;
        } else if (item == "Pizza") {
            total += 46.0;
        } else {
            total += 12.0;
        }
    }

    return total;
}

int Order::getNumber() const {
    return number;
}

void Order::setNumber(int number) {
    this->number = number;
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