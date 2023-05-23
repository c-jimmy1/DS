#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <iostream>
#include <cassert>
#include <utility>

typedef std::vector<std::pair<std::string, std::vector<int> > > table_def;
template <typename HashFunc> 
class HashTable {
    public:
    // ===========CONSTRUCTORS===========
    HashTable(unsigned int init_size, float init_occupancy) : m_table(init_size), m_size(0), m_occupancy(init_occupancy) {}

    // ===========ACCESSORS==============
    
    // This function returns the pair of the requested query string that is passed in
    std::pair<std::string, std::vector<int> > getIndex(const std::string&query_string, const unsigned int&kmer) const{
        
        // First the program needs the get the kmer size of the key
        std::string query_string_key = query_string.substr(0, kmer);

        // Calculate the index
        unsigned int index = m_hash(query_string_key) % m_table.size();

        // Check if the given key is at the index calcuated
        if (m_table[index].first == query_string_key) {
            return m_table[index];
        }

        // If there is a collision, use linear probe to search the rest of the hash table for the correct key
        else if (m_table[index].first != query_string_key) {
            while (m_table[index].first != query_string_key) {
                index++;
                if (index == m_table.size()) {
                    index = 0;
                }
            }
            return m_table[index];
        }

        // Else return a pair with an empty vector (meaning nothing was found)
        else {
            return std::pair<std::string, std::vector<int > > ();
        }
    }

    void print() {
    for (unsigned int i=0; i < m_table.size(); ++i) {
      if (m_table[i].first.size() > 0) { 
        std::cout << i << ": " << m_table[i].first << " Genome Indexes: ";
       } else {
        std::cout << i << ": ";
       }
    //   for (unsigned int j=0; j < m_table[i].second.size(); ++j) {
    //     std::cout << m_table[i].second[j] << " ";
    //   }
      std::cout << std::endl;
    }
   }

    // ===========MODIFIERS==============
    void setOccupancy(float new_occupancy) {
        m_occupancy = new_occupancy;
    }

    // The table is initialized with 100 size so when setting a new size the table has to be resized to the new table
    void setSize(unsigned int new_size) {
        resize_table(new_size);
    }

    // Helper function for insert to caculate Occupancy and resize of the occupancy after inserting goes over the allowed
    void calcOccupancy() {
        float curr_occupancy = (float) m_size/(float) m_table.size();

        if (curr_occupancy > m_occupancy) {
            unsigned int new_size = 2*m_table.size();
            resize_table(new_size);
        }
    }

    // Insert function that inserts the key and the starting positon of the key in the entire genome string
    void insert(const std::string& key, const int start_pos) {
        calcOccupancy();

        // Calculate the index
        unsigned int index = m_hash(key) % m_table.size();

        // If the table has no existing key and value make a pair, with the key and an empty vector and then push back the starting positon to the vector
        if (m_table[index].first.empty()) {
            m_table[index] = std::make_pair(key, std::vector<int>());
            m_table[index].second.push_back(start_pos);
            m_size += 1;
        }
        else {
            // If the table has an existing key and the current index key is equal to the key you want to insert, push back the next index it appears to the vector
            if (!m_table[index].first.empty() && m_table[index].first == key) {
                m_table[index].second.push_back(start_pos);
            }
            // Use Linear probe to find the next place you can put the key
            else {
                // If the key is different and there is something already at the current index, move to the next index to find an empty spot
                while (!m_table[index].first.empty() && m_table[index].first != key) {
                    index++;
                    if (index == m_table.size()) {
                        index = 0;
                    }
                }
                // If the next spot's key is the same, add it to the vector of indexes
                if (m_table[index].first == key) {
                    m_table[index].second.push_back(start_pos);
                }

                // Else create a new pair and push back the starting positon index
                else {
                    m_table[index] = std::make_pair(key, std::vector<int>());
                    m_table[index].second.push_back(start_pos);
                    m_size += 1;
                }
            }
        }
    }

    // }
    // ==========REPRESENTATION==========
    private:  
    table_def m_table; // actual table
    HashFunc m_hash; // Used to return the index in the table
    unsigned int m_size; // Total number of actual values
    float m_occupancy;

    // =========PRIVATE FUNCTIONS========
    void resize_table(unsigned int new_size) {
        table_def temp_new_table (new_size);
        
        // Iterate through each pair the old table
        for (unsigned int i = 0; i < m_table.size(); ++i) {
          
            // Get the hash key of each pair to calculate the index
            std::string key = m_table[i].first;
            unsigned int index = m_hash(key) % new_size;

            // Constraint to make sure that it is inserting into an empty positon of the new hash table
            while (!key.empty() && !temp_new_table[index].first.empty()) {
                index++;
                if (index == temp_new_table.size()) {
                    index = 0;  
                }
                
            }
            temp_new_table[index] = m_table[i];
        }
        m_table = temp_new_table;
    }

};

#endif