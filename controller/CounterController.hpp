#ifndef COUNTER_CONTROLLER_HPP
#define COUNTER_CONTROLLER_HPP

#include <vector>
#include <string>
#include "../models/KitchenLinkedQueue.hpp"

using namespace std;

class CounterController {
private:
    KitchenLinkedQueue& fila;
    vector<string> menuNames;

public:
    CounterController(KitchenLinkedQueue& queue);

    void runMenuCounter();
    void menuRegisterOrder();
    void menuRemoveOrder();
    void menuSearchOrder();
    void menuManageOrder();
    
    void menuAddItem(NodeQueue* node);
    void menuRemoveItem(NodeQueue* node);
};

#endif