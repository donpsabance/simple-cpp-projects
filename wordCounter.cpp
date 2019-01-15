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
        cout << "   1) count total words in a file" << "\n";
        cout << "   2) count total of certain words in a file" << "\n";
        cout << "   3) find the most occuring word in a file" << "\n";
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
                        cin.ignore(INT_MAX, '\n');
                        break;
                    case 2:
                        repeated_words(get_file());
                        cin.ignore(INT_MAX, '\n');
                        break;
                    case 3:
                        most_occurance(get_file());
                        cin.ignore(INT_MAX, '\n');
                        break;
                    case 4:
                        find_typos(dictionary, get_file());
                        cin.ignore(INT_MAX, '\n');
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
        cin >> file_name;
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
    
    while(file >> temp) word_count ++;
    
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

void find_typos(vector<string>& dictionary, string file_name){

    unordered_map<string, string> location;
    ifstream file(file_name);

    string temp;
    string word;
    string ignore = "[](),.-&123456789"; 

    int count = 1;

    bool pass = false;
    bool flag = false;
    bool add = false;

    while(file >> temp){

        pass = false;
        flag = false;
        add = false;

        for(int i = 0; i < temp.length(); i++){
            for(int j = 0; j < ignore.length(); j++){

                if(temp[i] == ignore[j]){
                    flag = true;
                } 
            }

            if(!flag){

                //theres no invalid characters so we can continue
                word += tolower(temp[i]);
                add = true;

            }
            else{
                break;
            }
        }

        string format = "(" + to_string(count) + ") ";
        if(!(search_vector(dictionary, word)) && add)  location[word] += format;
        word = "";
        count ++;

    }
    
    (location.size() == 0) ? cout << "\n" << "no errors found." << "\n" : cout << "\n" << "potential typos or errors: " << "\n";
    for (auto i = location.begin(); i != location.end(); i++) cout << i->first << " - found @ " << i->second << "\n";
    cout << "\n";
    
}
