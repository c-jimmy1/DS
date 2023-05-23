#include "customer.h"

// CONSTRUCTORS
Customer::Customer() {
    cust_id = "";
    actions = "";
    time = 0;
    quantity = 0;
    part_id = "";
    cust_name = "";
}

Customer::Customer(const std::string& ids, const std::string& action, const unsigned int& times, const unsigned int& quantities, const std::string& part, const std::string& name) {
    cust_id = ids;
    actions = action;
    time = times;
    quantity = quantities;
    part_id = part;
    cust_name = name;
}

// ACCESSORS
std::string Customer::get_customerID() const{
    return cust_id;
}

std::string Customer::get_action() const{
    return actions;
}

unsigned int Customer::get_time() const{
    return time;
}

unsigned int Customer::get_reqQuantity() const{
    return quantity;
}

std::string Customer::get_partID() const{
    return part_id;
}

std::string Customer::get_customerName() const{
    return cust_name;
}

std::list <std::string> Customer::get_rentedItems() const{
    return rented_items;
}

std::list <std::string> Customer::get_pendingItems() const{
    return pending_items;
}

//MODIFIERS
void Customer::add_rents(std::string item_id) {
    rented_items.push_back(item_id);
}

void Customer::pending_rents(std::string item_id) {
    pending_items.push_back(item_id);
}

