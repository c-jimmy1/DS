/* 
THIS IS THE MAIN FILE THAT UTLILIZES BOTH A CUSTOMER CLASS AND INVENTORY CLASS
TO MANAGE THE CUSTOMERS AND THE TOOLS INVENTORY OF THE ACME TOOL RENTAL COMPANY
*/

#include <iostream>
#include <fstream>
#include <list>
#include "inventory.h"
#include "customer.h"
#include "waitlist.h"

// PARSING GOES THROUGH THE CUSTOMER AND INVENTORY FILES TO GATHER INFO TO CREATE CLASS OBJECTS FOR EACH ITEM AND CUSTOMER
void parsing(std::ifstream& inventory_file, std::ifstream& customer_file, std::list <Inventory>& inventory_objects, std::list <Customer>& customer_objects) {
    // INV IS SHORT FOR INVENTORY
    std::string inv_id, inv_name;
    int inv_quantity;
	while (inventory_file >> inv_id >> inv_quantity >> inv_name) {
        if (inv_id[0] != 'T' || inv_quantity < 0) {
            std::cerr << "Invalid inventory ID " << inv_id << " found in the inventory file." << std::endl;
        }
        else {
		    inventory_objects.emplace_back(Inventory(inv_id, inv_quantity, inv_name));
        }
    }

    // CUST IS SHORT FOR CUSTOMER
    std::string cust_id, cust_action, part_num, cust_name;
    int cust_time, cust_quantity;
	while (customer_file >> cust_id >> cust_action >> cust_time >> cust_quantity >> part_num >> cust_name) {
        if (cust_id[0] != 'C' || cust_quantity < 0 || part_num[0] != 'T') {
            std::cerr << "Invalid customer information found for ID " << cust_id << " in the customer file." << std::endl;
        }
        else {
		    customer_objects.emplace_back(Customer(cust_id, cust_action, cust_time, cust_quantity, part_num, cust_name));
        }
    }
}


void rent_return(std::list <Inventory>& inventory_objects, std::list <Customer>& customer_objects) {
    std::list<Customer>::iterator cust_iterator;
    std::list<Inventory>::iterator inv_iterator;
    // LOOPS THROUGH THE CUSTOMER OBJECTS
    for (cust_iterator = customer_objects.begin(); cust_iterator != customer_objects.end(); ++cust_iterator){ 

        //INITIALIZE ALL THE VARIABLE COMPONENT OF CUSTOMER CLASS  
        bool found = false;
        std::string cust_id = cust_iterator->get_customerID();
        std::string action = cust_iterator->get_action();
        unsigned int time = cust_iterator->get_time();
        std::string part_id = cust_iterator->get_partID();
        unsigned int req_quantity = cust_iterator->get_reqQuantity();
        
        // LOOPS THROUGH THE INVENTORY OBJECTS
        for (inv_iterator = inventory_objects.begin(); inv_iterator != inventory_objects.end(); ++inv_iterator) {

            // INITIALIZING ALL THE ITEMS OF THE INVENTORY OBJECTS
            std::string item_id = inv_iterator->get_itemID();
            unsigned int item_quantity = inv_iterator->get_itemQuantity();
            std::list <Waitlist> waitlist = inv_iterator->get_Waitlist();
            
            // MAKING THE RENTING PART, SUBTRACTING THE QUANTITIES, ADDING CUSTOMERS TO THE INVENTORY OBJECT
            // ALSO ADDING WHAT EACH CUSTOMER IS RENTING
            if (action == "rent" && part_id == item_id) {
                found = true;
                if (req_quantity <= item_quantity) {
                    (*inv_iterator).rent_quantity(req_quantity);
                    (*inv_iterator).add_cust(cust_id);
                    (*cust_iterator).add_rents(item_id);
                    // how many quantities each customer has for that object
                }
                else {
                    // IF THE QUANTITY REQUESTED IS OVER THE AMOUNT THE ITEM HAS, ADD THEM TO THE WAITLIST AND PENDING REQUESTS
                    (*inv_iterator).add_waitlist(Waitlist(cust_id, item_id, req_quantity, time));
                    (*cust_iterator).pending_rents(item_id);
                }
                
            }
            // NOW ONTO THE RETURN PART OF THE PROGRAM
            if (action == "return" && part_id == item_id) {

                // ADD THE QUANTITY GIVEN BACK
                (*inv_iterator).return_quantity(req_quantity);
                // found = true;
                std::list<Waitlist>::iterator wl_itr;
                // IF THE WAITLIST HAS SOMEONE
                if (waitlist.size() > 0) {
                    // LOOPS THROUGH THE WAITLIST TO SEE IF THE ITEM CAN BE RENTED OUT TO THE CUSTOMER ON THE WAITLIST
                    for (wl_itr = waitlist.begin(); wl_itr != waitlist.end(); ++wl_itr) {
                        std::string waitlist_itemID = wl_itr->getitemID();
                        unsigned int waitlist_quantity = wl_itr->getQuantity();
                        if (waitlist_itemID == item_id && waitlist_quantity <= item_quantity) {
                            (*inv_iterator).rent_quantity(waitlist_quantity);
                        }
                        
                    }
                }
            }
        }
        if (found == false) {
        std::cerr << "Customer " << cust_id << " requested item " << part_id << " which is not in the inventory." << std::endl;
        }
    }
}

int main(int argc, char*argv[]) {
    // INTIALIZING READING/WRITING FILES
    std::ifstream inventory_file(argv[1]);
    std::ifstream customer_file(argv[2]);
    std::ofstream inventory_out(argv[3]);
    std::ofstream customer_out(argv[4]);

    // COMMAND LINE ARGUEMENTS ERROR CHECKING
    if (!inventory_file.good()) {
        std::cerr << "Bad inventory input file" << std::endl;
	}
    if (!customer_file.good()) {
        std::cerr << "Bad customer input file" << std::endl;
	}
    if (!inventory_out.good()) {
        std::cerr << "bad inventory output file" << std::endl;
    }
    if (!customer_out.good()) {
        std::cerr << "bad customer output file" << std::endl;
    }
    if (argc != 5) {
        std::cerr << "incorrect number of arguments" << std::endl;
    }
    
    std::list <Inventory> inventory_objects;
    std::list <Customer> customer_objects;
    parsing(inventory_file, customer_file, inventory_objects, customer_objects);
    rent_return(inventory_objects, customer_objects);

    // THIS IS FOR PRINTING WAITLIST
    std::list<Inventory>::iterator it;
    std::list<std::string>::iterator s_it;
    for (it = inventory_objects.begin(); it != inventory_objects.end(); ++it){
        std::list<std::string> custRenting = it->get_custRenting();
        for (s_it = custRenting.begin(); s_it != custRenting.end(); ++s_it) {
            std::cout << *s_it << std::endl;
        }
    }
    return 0;
}