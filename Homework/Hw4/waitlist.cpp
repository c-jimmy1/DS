#include "waitlist.h"

// CONSTRUCTOR
Waitlist::Waitlist() {
    cust_ID = "";
    item_ID = "";
    quantity = 0;
    timestamp = 0;
}

Waitlist::Waitlist(std::string custIDS, std::string itemIDs, unsigned int quantities, unsigned int timestamps) {
    cust_ID = custIDS;
    item_ID = itemIDs;
    quantity = quantities;
    timestamp = timestamps;
}

// ACCESSORS
std::string Waitlist::getcustID() const{
    return cust_ID;
}
std::string Waitlist::getitemID() const{
    return item_ID;
}
unsigned int Waitlist::getQuantity() const{
    return quantity;
}
unsigned int Waitlist::getTimestamp() const{
    return timestamp;
}

// MODIFIERS
