#include <iostream>
#include <string>
#include <algorithm>

bool is_int(const std::string& str){

	std::string copy = str;

	//check if each char is an integer
    for(char c : copy){
        if(c < 48 || c > 57 ) return false;
    }

    //check for number duplicates
    std::sort(copy.begin(), copy.end());
    for(int i = 0; i < (copy.length() - 1); i++){
    	if(copy[i] == copy[i + 1]) return false;
    }

    return true;
}

std::string find_bulls_cows(const std::string& code, const std::string& guess){

	int cows = 0, bulls = 0;

	//finds the bulls
	for(int i = 0; i < guess.length(); i++){

		//stop checking once its the end of the secret_code 
		if(i > code.length()) break;

		if(code[i] == guess[i]) bulls++;
	}

	//find cows
	for(int i = 0; i < guess.length(); i++){
		for(int j = 0; j < code.length(); j++){

			if(code[i] == guess[j]){

				cows++;
				break; 
			} 

		}
	}

	return "There are " + std::to_string(bulls) + " bull(s) and " + std::to_string(cows - bulls) + " cow(s)";
}

int main(){

	int tries = 0;
	std::string secret_code, guess;
	
	std::cout << "     Bulls & Cows     \n";
	std::cout << "enter secret code to begin: ";
	std::cin >> secret_code;

	while(!(is_int(secret_code))){

		std::cout << "invalid code, try again: ";
		std::cin >> secret_code;

	}

	std::cout << "     Bulls & Cows    \n";
	std::cout << "      S T A R T      \n";

	while(!(guess == secret_code)){

		std::cout << ">> ";
		std::cin >> guess;	

		std::cout << find_bulls_cows(secret_code, guess) << "\n";
		tries++;

	}

	std::cout << "     G A M E O V E R \n";
	std::cout << "     # OF TRIES: " << tries << "\n";
	return 0;
}