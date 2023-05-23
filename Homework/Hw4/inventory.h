#ifndef __inventory_h__
#define __inventory_h__
#include <iostream>
#include <list>
#include "waitlist.h"

class Inventory {
    public:
    // CONSTRUCTORS
    Inventory();
    Inventory(const std::string& ids, const unsigned int& quantities, const std::string& name);

    // ACCESSORS
    std::string get_itemID() const;
    unsigned int get_itemQuantity() const;
    std::string get_itemName() const;
    std::list <std::string> get_custRenting() const;
    std::list<Waitlist> get_Waitlist() const;

    // MODIFIERS
    void return_quantity(unsigned int amount);
    void rent_quantity(unsigned int amount);
    void add_cust(std::string cust_ID);
    void add_waitlist(Waitlist waitlist_object);

    private: // REPRESENTATION
    std::string item_id, item_name;
    unsigned int quantity;
    std::list <Waitlist> waitlist;
    std::list <std::string> cust_timestamp;
    std::list <std::string> cust_renting;
};

#endif