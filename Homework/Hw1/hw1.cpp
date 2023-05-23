/*
This program reads a file, parses it and creates a box around all the words in according the the width of the box given.
There are three options the text can be ouputted, left_flush, right_flush, and full_justify.
The text and box will be outputted to a file
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void leftF(const vector<string>& allword, ostream& outfile, int length) {
    int dash_L = length + 4; // calculating the length of the dashes
    outfile << string(dash_L, 45) << endl; //45 is '-' on the ascii table

    string tempString = ""; 
    for (int i = 0; i < (int)allword.size(); i++) { // loops through every word in the file
        if (tempString == "") {  // if the string is empty (first line |)
            outfile << "| ";
        }

        // if the size of the tempString plus the word of the current loop is less than the width...
        if ((int)tempString.size() + (int)allword[i].size() <= length) { 
           if ((int)tempString.size() + (int)allword[i].size() == length) { // if the size of the tempString plus the word of the current loop is equal to the width
                tempString += allword[i];
           }
           
           else { // else add the word and a space
                tempString += allword[i];
                tempString += " ";
           }
        }
        else { // else when the current word will make the line in tempString go over the width...
            int extra_space = length - (int)tempString.size(); // calculate extra spaces
            outfile << tempString; 
            outfile << string(extra_space, 32); // 32 is ' ' on the ascii table
            tempString = allword[i] + " "; // reset tempString to the word that will make it go over and add a space
            outfile << " |\n| "; // add | and start new line with |
        }
        if (i == (int)allword.size()-1) { // if the word is the last word
            int extra_space = length - (int)tempString.size(); // recalculate spaces
            outfile << tempString;
            outfile << string(extra_space, 32); // 32 is ' ' on the ascii table         
        }
        
    }
    outfile << " |\n" << string(dash_L, 45) << endl; //45 is '-' on the ascii table
}

void rightF(const vector<string>& allword, ostream& outfile, int length) {
    int dash_L = length + 4; // calculating the length of the dashes
    outfile << string(dash_L, 45) << endl; //45 is '-' on the ascii table
    
    string tempString = ""; // initializing the String to be added to
    for (int i = 0; i < (int)allword.size(); i++) { // loops through every word in the file

        if (tempString == "") {  // if the string is empty (first line |)
            outfile << "| ";
        }

        // if the size of the tempString plus the word of the current loop is less than the width...
        if ((int)tempString.size() + (int)allword[i].size() <= length) { 
           if ((int)tempString.size() + (int)allword[i].size() == length) { // if the word will fit perfectly without any extra spaces
                tempString.erase(0, 1); // erase the extra space at the front
                tempString += " "; // add space to before the word
                tempString += allword[i]; // then add the word
           }
           
           else { // everything else...
                tempString += " ";
                tempString += allword[i];

           }
        }
        else { // when the word will go over to next line
            int extra_space = length - (int)tempString.size();  // calculate extra spaces
            outfile << string(extra_space, 32); // 32 is ' ' on the ascii table
            outfile << tempString;
            tempString = " " + allword[i]; // reset the string to the word that will be on the next line
            outfile << " |\n| ";
        }
        if (i == (int)allword.size()-1) { // if the word is the last word
            int extra_space = length - (int)tempString.size(); // calculate the amount of extra spaces again
            outfile << string(extra_space, 32); // 32 is ' ' on the ascii table   
            outfile << tempString;     
        }
    }
    outfile << " |\n" << string(dash_L, 45) << endl; //45 is '-' on the ascii table
}

void fullJ(const vector<string>& allword, ostream& outfile, int length) {

    int dash_L = length + 4;
    outfile << string(dash_L, 45) << endl; //45 is '-' on the ascii table
    
    string tempString = "";
    vector <string> line;
    int extra_space = 0;
    int len = 0; 

    //In this for loop tempString is building itself and resets when the word in the current loop is too long
    for (int i = 0; i < (int)allword.size(); i++) { // loops through all the words

        // (if the length of the string so far, plus the size of the word in the current loop) is less than width
        if (len + (int)allword[i].size() < length) { 
            // if the length of the string plus of the word plus 1 extra space is exactly the width
           if (len + (int)allword[i].size() + 1 == length) {
                tempString = " " + allword[i]; // add a space and the word to the string
                line.push_back(tempString); // appends the string to the vector
                len += tempString.size(); // add the size of the string
           }
           else if (i == 0) { // fixes the first word where there is an extra space at the beginning of the whole box
                tempString = allword[i];
                line.push_back(tempString);
                len += tempString.size();
           }
           else { // if it isn't going to perfectly fulfill the width
                tempString = allword[i]; // set the string equal to the word
                tempString = " " + tempString; // add the space before the word and add the word
                line.push_back(tempString); // add all of the edits to the vector
                len += tempString.size(); // add the size of the fixed string
           }
        }
        else if ((int)allword[i].size() > length) { // if the length of the word is greater than the size of the width
                outfile << "| "; // start a new line border
                outfile << allword[i].substr(0, length - 1) << "-" << " ";
            }
        
        else { // else if the word will make the line too long
            outfile << "| "; // start a new line border

            extra_space = length - (len - line.size() + 1); // calculate spaces
            int extra_space_r = extra_space % (line.size() - 1); // remaining spaces
            int extra_space_e = extra_space / (line.size() - 1) - 1; // extra spaces
            if (extra_space_e < 0){ // if it turns negative, set it equal to 0
                extra_space_e = 0;
            }
            for (int j = 0; j < (int)line.size(); j++) { // loops through the vector of strings
                outfile << line[j]; // output the word of the current iteration
                if (j != (int)line.size()-1) { // if the iteration is not the last
                    outfile << string(extra_space_e , 32); // output spaces
                    if (j < extra_space_r) { // if the remainder is greater than the iteration 
                        outfile << " "; // add a space
                    }
                }
            }
            
            outfile << " |\n";  // ending the line and starting a new one

            // resetting everything for the next iteration
            extra_space = 0;
            line.clear();
            tempString = allword[i];
            line.push_back(tempString);
            len = 0;
            len += tempString.size();
        }
        if (i == (int)allword.size()-1) { // if the word is the last word
            extra_space = length - (len);
            cout<<len<<endl;
            outfile << "| ";
            for (int j = 0; j < (int)line.size(); j++) {
                outfile << line[j];
            }
            outfile << string(extra_space , 32);
        }  
    }

    outfile << " |\n" << string(dash_L, 45) << endl; //45 is '-' on the ascii table
}
/*
boolean isdigits(char* argument) {
    for (int i = 0; i < argument.size(); i++) {
        if ()
    }
}
*/
int main(int argc, char*argv[]) {
    ifstream wordfile(argv[1]); // reading the given file
    ofstream outfile(argv[2]); // creating an output for the file

    if (!wordfile.good()) { // checks for file error
        cerr << "bad input file" << endl;
	}

    if (argc != 5) { // checks for correct number of arguments
        cerr << "incorrect number of arguments" << endl;
    }

    if (!outfile.good()) { // checks for output file error
        cerr << "bad output file" << endl;
    }
    /*
    if (isdigits(argv[3])) {
        cerr << "argument 3 is not a number" << endl;
    }
    */
    string n = ""; // initializes a tring for words to be put in
    vector <string> allwords;
	while (wordfile >> n) { // adds each word to an index in the vector
		allwords.push_back(n);
	}

    int length = stoi(argv[3]); // converting the width of the line to an integer 

    // RUNNING THE CORRECT FUNCTION
    if ((string)argv[4] == "flush_left") {
        leftF(allwords, outfile, length);

    }
    else if ((string)argv[4] == "flush_right") {
        rightF(allwords, outfile, length);
    }

    else if ((string)argv[4] == "full_justify") {
        fullJ(allwords, outfile, length);
    }
    else {
        cerr << "incorrect justification" << endl;
    }

return 0;
}