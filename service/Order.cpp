#include "../models/Order.hpp"

using namespace std;

Order::Order() {
    this->number = 0;
    this->client = "";
    this->items = {};
    this->total = 0.0f;
    this->quantatyItems = {0, 0, 0, 0, 0};
}

// Será definido na classe KitchenLikedQueue
Order::Order(const string& client, const vector<string>& items, const vector<int>& quantatyItems) {
    this->client = client;
    this->items = items;
    this->quantatyItems = quantatyItems;
    this->total = calcularTotal();
}

Order::Order(const int number, const string& client, const vector<string>& items, const float total) {
    this->number = number;
    this->client = client;
    this->items = items;
    this->quantatyItems = {0, 0, 0, 0, 0};
    this->total = total;
}

Order::~Order() {}

void Order::addItem(const string& item) {
    this->items.push_back(item);
    this->total = calcularTotal();
}

void Order::removeItem() {
    if (!this->items.empty()) {
        this->items.pop_back();
        this->total = calcularTotal();
    }
}

void Order::showOrder() const {
    cout << "   > Pedido: " << this->getNumber() << endl;
    cout << "   > Cliente: " << this->getClient() << endl;
    cout << "   > Itens:" << endl;

    vector<string> menuNames = {"Cachorro Quente", "Batata Frita", "Hamburguer", "Pizza", "Coca Zero"};

    // Verifica se ha quantidades registradas no vetor
    bool isQuantaty = false;
    for (int qtd : quantatyItems) {
        if (qtd > 0) {
            isQuantaty = true;
            break;
        }
    }

    if (isQuantaty) {
        // Exibicao para pedidos cadastrados pelo menu
        for (size_t i = 0; i < menuNames.size() && i < quantatyItems.size(); ++i) {
            if (quantatyItems[i] > 0) {
                cout << "      - " << menuNames[i] << " x" << quantatyItems[i] << endl;
            }
        }
    } else {
        // Exibicao para pedidos de exemplo (do main.cpp)
        for (const string& item : items) {
            cout << "      - " << item << endl;
        }
    }

    cout << "   > Total: R$ " << this->getTotal() << endl;
}

void Order::addItem(int itemCode) {
    if (itemCode >= 0 && itemCode < 5) {
        quantatyItems[itemCode]++;
        this->total = calcularTotal();
    }
}

bool Order::removeItem(int itemCode) {
    if (itemCode >= 0 && itemCode < 5 && quantatyItems[itemCode] > 0) {
        quantatyItems[itemCode]--;
        this->total = calcularTotal();
        return true;
    }
    return false;
}

float Order::calcularTotal() const {
    // Tabela de preços na mesma ordem das opções (0 a 4)
    float prices[] = {8.0f, 6.0f, 20.0f, 46.0f, 12.0f};
    float totalCalculated = 0.0f;

    for (int i = 0; i < 5; i++) {
        totalCalculated += quantatyItems[i] * prices[i];
    }
    return totalCalculated;
}

// metodos acessores

int Order::getNumber() const {
    return number;
}

void Order::setNumber(int number) {
    this->number = number;
}

string Order::getClient() const {
    return client;
}

const vector<string>& Order::getItems() const {
    return items;
}

float Order::getTotal() const {
    return total;
}

const vector<int>& Order::getQuantatyItems() const {
    return quantatyItems;
}