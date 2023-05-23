#ifndef __waitlist_h__
#define __waitlist_h__
#include <iostream>
#include <list>

class Waitlist{
public:
    // CONSTRUCTOR
    Waitlist();
    Waitlist(std::string custIDS, std::string itemIDS, unsigned int quantities, unsigned int timestamps);

    // ACCESSORS
    std::string getcustID() const;
    std::string getitemID() const;
    unsigned int getQuantity() const;
    unsigned int getTimestamp() const;

    // MODIFIERS
private:
    std::string cust_ID, item_ID;
    unsigned int quantity, timestamp;
};

#endif