//
//  paper_check.cpp
//  
//
//  Created by Don Abance on 2019-01-14.
//

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

string get_file();
vector<string> load_dictionary(string file_name);
bool search_vector(const vector<string> &vec, string to_find);
void total_words(string file_name);
void repeated_words(string file_name);
void most_occurance(string file_name);
void find_typos(vector<string>& dictionary, string file_name);

int main(){

    vector<string> dictionary = load_dictionary("english3.txt");

    bool empty_dictionary;

    if(dictionary.empty()) empty_dictionary = true;
    
    string fail_code = "q";
    string temp;
    string input = "";
    
    while(input != fail_code){
        
        cout << "options: (enter q to quit) " << "\n";
        cout << "   1) count total words & characters in a file" << "\n";
        cout << "   2) count total of certain words in a file" << "\n";
        cout << "   3) find the (10) most occuring words in a file" << "\n";
        (empty_dictionary) ? cout << "" : cout << "   4) find potential typos in a file" << "\n";
        cout << "please enter an option: ";

        input = "";
        getline(cin, temp);

        //force lower case all inputs so all options can be case insensitive 
        for(int i = 0; i < temp.length(); i++) input += ::tolower(temp[i]);
        
        if(!temp.empty()){
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
                        break;
                    case 4:
                        find_typos(dictionary, get_file());
                        break;
                    default:
                        cout << "invalid option" << "\n";
                        break;
                }
            } catch (...) { /*failed so output everything again*/ }
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
        getline(cin, file_name);
        file.open(file_name);       
        
    }
    return file_name;
}

vector<string> load_dictionary(string file_name){

    ifstream inputFile(file_name);
    string temp_read;
    string lowercase_read = "";

    vector<string> dictionary;

    if(!inputFile.fail()){
        while(inputFile >> temp_read){

            for(int i = 0; i < temp_read.length(); i++) lowercase_read += tolower(temp_read[i]);
            dictionary.push_back(lowercase_read);
            lowercase_read = "";

        }
        cout << "loaded successfully..." << "\n";
    }
    else cout << "no dictionary loaded, option 4 disabled" << "\n";
    return dictionary;
}

bool search_vector(const vector<string> &vec, string to_find){

    int vec_start = 0;
    int vec_end = vec.size() - 1;
    int counter = 0;

    //check until either it found or it reached the end of search
    while(vec_start <= vec_end){

        int vec_middle = ((vec_end + vec_start)  / 2) ;
        if(vec[vec_middle] == to_find){

            return true;
        }
        else{

            (vec[vec_middle] > to_find) ? vec_end = vec_middle - 1 : vec_start = vec_middle + 1;
            counter ++;
        }
    }
    return false;
}

void total_words(string file_name){
    
    ifstream file(file_name);
    string temp;
    int word_count = 0;
    int char_count = 0;
    
    while(file >> temp){
        for(int i = 0; i < temp.length(); i++){
            char_count ++;
        }
        word_count ++;
    }
    
    cout << "\n";
    cout << "total words found: " << word_count << "\n";
    cout << "total characters found: " << char_count << "\n";
    cout << "\n";
}

void repeated_words(string file_name){
    
    ifstream file(file_name);
    
    string temp = "";
    string word = "";
    string word_temp = "";
    string word_to_find = "";
    string case_sensitive = "";

    bool valid = false;

    int word_count = 0;

    while(word_temp.empty()){
        cout << "enter word to find: ";
        getline(cin, word_temp);
    }

    while(case_sensitive.empty() || !valid){
        cout << "case sensitive? (y/n): ";
        getline(cin, case_sensitive);
        
        if(case_sensitive == "y" || case_sensitive == "Y"){
            while (file >> temp) {
                if(temp.compare(word_temp) == 0){
                    word_count ++;
                } 
            }
            cout  << "\n" << "total number of \"" << word_temp << " \" found: " << word_count << "\n"  << "\n";
            valid = true;
        }
        else if(case_sensitive == "n" || case_sensitive == "N"){
            
            for(char c : word_temp){
                word_to_find += tolower(c);
            }
            while (file >> temp) {
                for(char c : temp){
                    word += tolower(c);
                }
                if(word.compare(word_to_find) == 0){
                    word_count ++;
                } 
                word = "";
            }
            cout  << "\n" << "total number of \"" << word_to_find << " \" found: " << word_count << "\n"  << "\n";
            valid = true;
        }
    }
}

void most_occurance(string file_name){
    
    ifstream file(file_name);
    
    map<string, int> occurance;
    map<string, int> most_occurance;
    vector<int> amnt_occ;
    vector<string> words;
    
    string temp;
    string word = "";
    string ignore = "![]().,-&1234567890{}'? " ; 
    string choice = "";
    
    while (file >> temp) {
        
        for(int i = 0; i < temp.length(); i++) temp.erase(std::remove(temp.begin(), temp.end(), ignore[i]), temp.end());
        for(char c : temp) word += tolower(c);
        
        //if the word has not yet been seen, add to map, otherwise, increment its previous value
        (occurance.find(word) == occurance.end()) ? occurance[word] = 1 : occurance[word] += + 1;
        word = "";
    }
    
    //add the occurance in a vector
    for (auto i = occurance.begin(); i != occurance.end(); i++) amnt_occ.push_back(i->second);
    
    //sort to get the highest ones
    sort(amnt_occ.rbegin(), amnt_occ.rend());


    for(int i = 0; i < 10; i++){
        for (auto j = occurance.begin(); j != occurance.end(); j++) {
            if(amnt_occ[i] == j->second && most_occurance.find(j->first) == most_occurance.end()){

                most_occurance[j->first] = amnt_occ[i]; 
                words.push_back(j->first);
                break;

            }
        }
    }

    cout << "\n" << "most occurances: " << "\n" << "ignored characters: " << ignore << "\n" << "\n";
    for(int i = 0; i < 10; i++){
        for (auto j = occurance.begin(); j != occurance.end(); j++) {
            if(words[i] == j->first && j->second == amnt_occ[i]){

                 cout << j->first << " |  amount of occurances: " << j->second << "\n";
                 break;
            }
        }
    }
    cout << "\n";
}

void find_typos(vector<string>& dictionary, string file_name){

    unordered_map<string, string> location;
    ifstream file(file_name);

    string temp;
    string word;
    string ignore = "![]().,-&1234567890{}?:/ "; 

    int count = 1;

    while(file >> temp){

        for(int i = 0; i < temp.length(); i++){
            for(int j = 0; j < ignore.length(); j++){

                temp.erase(std::remove(temp.begin(), temp.end(), ignore[j]), temp.end());

            }
        }

        if(temp.length() > 0){

            for(char c : temp) word += tolower(c);

            string format = "(" + to_string(count) + ") ";
            if(!(search_vector(dictionary, word)))  location[word] += format;
            word = "";
            count ++;

        }   
    }
    
    (location.size() == 0) ? cout << "\n" << "no potential errors found." << "\n" : cout << "\n" << "potential typos or errors: " << "\n";
    cout << "ignored characters: " << ignore << "\n" << "\n";
    for (auto i = location.begin(); i != location.end(); i++) cout << i->first << " - found @ " << i->second << "\n";
    (location.size() == 0) ? cout << "" : cout << "\n";
    
}

