#include "inventory.h"

// CONSTRUCTORS
Inventory::Inventory() {
    item_id = "";
    quantity = 0;
    item_name = "";
}

Inventory::Inventory(const std::string& ids, const unsigned int& quantities, const std::string& name) {
    item_id = ids;
    quantity = quantities;
    item_name = name;
}
// ACCESSORS
std::string Inventory::get_itemID() const{
    return item_id;
}

unsigned int Inventory::get_itemQuantity() const{
    return quantity;
}

std::string Inventory::get_itemName() const{
    return item_name;
}

std::list <std::string> Inventory::get_custRenting() const{
    return cust_renting;
}

std::list<Waitlist> Inventory::get_Waitlist() const{
    return waitlist;
}

// MODIFIERS
void Inventory::return_quantity(unsigned int amount) {
    quantity += amount;
}
void Inventory::rent_quantity(unsigned int amount) {
    quantity -= amount;
}

void Inventory::add_cust(std::string cust_ID) {
    cust_renting.push_back(cust_ID);
}

void Inventory::add_waitlist(Waitlist waitlist_object){
    waitlist.emplace_back(waitlist_object);
}