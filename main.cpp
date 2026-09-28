#include <iostream>
#include "models/Order.hpp"
#include "models/DoublyLinkedList.hpp"

using namespace std;

int main() {
    DoublyLinkedList listOrders;

    Order order1(1, "Maicon", {"Hamburguer", "Batata Frita"}, 25.50f);
    Order order2(2, "Estudante", {"Pizza GG", "Coca Zero", "Sobremesa"}, 68.50f);
    Order order3(3, "Rocha", {"Milk Shake", "Batata Frita"}, 25.50f);

    listOrders.insert(order1);
    listOrders.insert(order2);
    listOrders.insertEnd(order3);

    listOrders.printList();

    return 0;
}