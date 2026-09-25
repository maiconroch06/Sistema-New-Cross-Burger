#ifndef _ORDER_
#define _ORDER_

#include <iostream>

class Order {
    private:
        int number;
        std::string client;
        std::string items[100];
        float total;
    public:
        Order(/* args */);
        ~Order();

};

#endif