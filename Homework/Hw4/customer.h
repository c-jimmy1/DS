#ifndef __customer_h__
#define __customer_h__
#include <iostream>
#include <list>
class Customer {
    public:
    
    // CONSTRUCTORS
    Customer();
    Customer(const std::string& ids, const std::string& action, const unsigned int& times, const unsigned int& quantities, const std::string& part, const std::string& name);
    
    // ACCESSORS
    std::string get_customerID() const;
    std::string get_action() const;
    unsigned int get_time() const;
    unsigned int get_reqQuantity() const;
    std::string get_partID() const;
    std::string get_customerName() const;
    std::list <std::string> get_rentedItems() const;
    std::list <std::string> get_pendingItems() const;

    // MODIFIERS
    void add_rents(std::string item_id);
    void pending_rents(std::string item_id);

    private:
    std::string cust_id, actions, part_id, cust_name;
    unsigned int time, quantity;
    std::list <std::string> rented_items;
    std::list <std::string> pending_items;
}; 

#endif