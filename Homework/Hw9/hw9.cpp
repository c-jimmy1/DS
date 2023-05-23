#include <iostream>
#include <fstream>

#include "hashtable.h"

// Hash function from lab 11
class hash_string_obj {
public:
    unsigned int operator() (const std::string& key) const {
        //  This implementation comes from
        //  http://www.partow.net/programming/hashfunctions/
        unsigned int hash = 1315423911;
        for (unsigned int i = 0; i < key.size(); ++i)
            hash ^= ((hash << 5) + key[i] + (hash >> 2));
        return hash;
    }
};


typedef HashTable<hash_string_obj> HashTable_type;

// Function that handles the queries in the CIN
void query(HashTable_type &hashtable, const std::string &allgenome, unsigned int kmer, 
            unsigned int mismatches, const std::string &query_string) {
    
    // Get the vector of indexes where the query exists using the .getIndex function in the class
    std::pair<std::string, std::vector<int> > pair = hashtable.getIndex(query_string, kmer);
    std::vector<int> listIndex = pair.second;

    // match is a bool that handles the No matches even after checking the future hashes
    bool match = false;
    bool isPrinted = false;
    
    // Iterating through the list of indexes to print out the number of matches
    for(unsigned int i = 0; i < listIndex.size(); i++) {
        
        // Counter for mismatches and the current index of the first for loop
        unsigned int count_mis = 0;
        unsigned int curr = 0; 
        for (unsigned int j = listIndex[i]; j < query_string.size() + listIndex[i]; j++) {
            if (allgenome[j] != query_string[curr]) {
                count_mis++;
            }
            curr++;
        }

        // If the mismatches is less than the limit print the part of the genome and the query
        if (count_mis <= mismatches) {
            match = true;
            unsigned query_size = query_string.size();
            std::string matched = allgenome.substr(listIndex[i], query_size);
            
            // Prevents Query title from printing multiple times
            if (!isPrinted) {
                std::cout << "Query: " << query_string << std::endl;
                isPrinted = true;
            }
            
            std::cout << listIndex[i] << " " << count_mis << " " << matched << std::endl;
        }
    }

    // Otherwise there is no match at all
    if (!match) {
        std::cout << "Query: " << query_string << std::endl;
        std::cout << "No Match" << std::endl;
    }

}

int main() {
    std::string command, second, query_string;
    std::string allgenome, single_base; 
    unsigned int table_size = 100;
    float occupancy = 0.5;
    unsigned int kmer, mismatches;
    HashTable_type hashtable(table_size, occupancy);

    while (std::cin >> command >> second) {
        // ERROR CHECKING AND THEN READING THE ENTIRE GENOME INTO A STRING
        if (command == "genome") {
            // Set default values for table_size and occupanc
            // parse through the genome file to put the entire genome in one string
            std::ifstream genome_file(second);
            if (!genome_file.good()) {
                std::cerr << "Could not open file: " << second << std::endl; 
            }

            while (genome_file >> single_base) {
                allgenome += single_base;
            }
        }
        else if (command == "table_size") {
            table_size = stoi(second);
            hashtable.setSize(table_size);
        }
        else if (command == "occupancy") {
            occupancy = (float)stof(second);
            hashtable.setOccupancy(occupancy);
        }
        else if (command == "kmer") {
            kmer = stoi(second);
            // Looping through the entire genome to insert the kmer size key to the hashtable
            for (unsigned int i = 0; i <= allgenome.size() - kmer; ++i) {
                std::string key = allgenome.substr(i, kmer);
                hashtable.insert(key, i);
            }
            hashtable.print();
        }
        else if (command == "query") {
            mismatches = stoi(second);
            std::cin >> query_string;
            query(hashtable, allgenome, kmer, mismatches, query_string);
        }
        else if (command == "quit") {
            break;
        }
    }
}