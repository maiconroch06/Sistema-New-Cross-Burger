#ifndef _ORDER_
#define _ORDER_

#include <iostream>

class Order {
    private:
        int number;
        String client;
        String items[100];
        float total;
    public:
        Order(/* args */);
        ~Order();
        
        + insert()
        + insertEnd()
        + insertIndex()
        + removeValue()
        + search()
        + nextOrder()
        + previousOrder()

        + isEmpty()

};

#endif