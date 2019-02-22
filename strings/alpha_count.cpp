#include <iostream>
#include <vector>
#include <map>
#include <string>

int main(){

	std::string temp;
	std::string longest_word;

	std::vector<std::string> vec;
	std::vector<int> alpha(26, 0);
	std::map<char, int> occurance;

	int longest_length = 0;

	while(std::cin >> temp){

		//add the word to the vector
		vec.push_back(temp);

	}

	for(int i = 0; i < vec.size(); i++){
		for(int j = 0; j < vec[i].length(); j++){

			//lowercase all letters in the vector
			vec[i][j] = std::tolower(vec[i][j]);

		}

		if(vec[i].length() > longest_length){

			longest_length = vec[i].length();
			longest_word = vec[i];
		}
	}


	for(int i = 0; i < vec.size(); i++){
		for(int j = 0; j < vec[i].length(); j++){

			(occurance.find((char)vec[i][j]) == occurance.end()) ? occurance[(char)vec[i][j]] = 1 : occurance[(char)vec[i][j]] += 1;

		}

		for(std::map<char, int>::iterator it = occurance.begin(); it != occurance.end(); it++) {
	  		if(it->second > alpha[(char)it->first - 'a']){
	  			alpha[it->first - 'a'] = it->second;
	  		}
		}
		occurance.clear();
	}

	std::cout << "needed letters: \n";

	for(int k = 0; k < alpha.size(); k++){
		if(alpha[k] > 0){

			std::cout << "   " << (char) (k + 'a') << " - " << alpha[k] << "\n";
		}
	}

	std::cout << "longest word: " << longest_word << "\n";
	std::cout << "word length: " << longest_length << "\n";

}