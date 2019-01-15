//
//  wordCounter.cpp
//  
//
//  Created by Don Abance on 2019-01-14.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <unordered_map>

using namespace std;

string get_file();
void total_words(string file_name);
void repeated_words(string file_name);
void most_occurance(string file_name);

int main(){
    
    string fail_code = "q";
    string input;
    
    while(input != fail_code){
        
        cout << "options: (enter q to quit) " << "\n";
        cout << "   1) count total words in a file" << "\n";
        cout << "   2) count total of certain words in a file" << "\n";
        cout << "   3) find the most occuring word in a file" << "\n";
        cout << "please enter an option: ";
        
        cin >> input;
        
        try {
            switch (stoi(input)){
                case 1:
                    total_words(get_file());
                    break;
                case 2:
                    repeated_words(get_file());
                    break;
                case 3:
                    most_occurance(get_file());
                default:
                    break;
            }
        } catch (...) {
            
            //failed so output everything again
            
        }
    }
    return 0;
}

string get_file(){
    
    string file_name = "";
    ifstream file;
    
    file.open(file_name);
    
    while(file.fail()){
        
        cout << "please enter the file name: ";
        cin >> file_name;
        file.open(file_name);
        
    }
    return file_name;
}

void total_words(string file_name){
    
    ifstream file(file_name);

    string temp;
    int word_count = 0;
    
    while(file >> temp){
        word_count ++;
    }
    
    cout << "\n";
    cout << "total words found: " << word_count << "\n";
    cout << "\n";
}

void repeated_words(string file_name){
    
    ifstream file(file_name);
    
    string temp;
    string word_to_find;
    int word_count = 0;
    
    cout << "enter word to find: ";
    cin >> word_to_find;
    
    while (file >> temp) {
        if(temp.compare(word_to_find) == 0) word_count ++;
    }
    
    cout  << "\n" << "total number of \"" << word_to_find << " \" found: " << word_count << "\n"  << "\n";
}

void most_occurance(string file_name){
    
    ifstream file(file_name);
    
    unordered_map<string, int> occurance;
    unordered_map<string, int> most_occurance;
    
    string temp;
    string word = "";
    int counter = 0;
    
    while (file >> temp) {
        
        for(int i = 0; i < temp.length(); i++) word += tolower(temp[i]);
        
        //if the word has not yet been seen, add to map, otherwise, increment its previous value
        (occurance.find(word) == occurance.end()) ? occurance[word] = 1 : occurance[word] += + 1;
        word = "";
    }
    
    //count the most occurance
    for (auto i = occurance.begin(); i != occurance.end(); i++) if(i->second > counter) counter = i->second;
    
    //save all the most occurance
    for (auto i = occurance.begin(); i != occurance.end(); i++) {
        if(i->second == counter) most_occurance[i->first] = counter;
    }

    cout << "\n" << "most occurances: " << "\n";
    for (auto i = most_occurance.begin(); i != most_occurance.end(); i++) cout << i->first << " |  amount of occurances: " << i->second << "\n";
    cout << "\n";
    
}
