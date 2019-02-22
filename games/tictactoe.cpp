#include <iostream>
#include <string>
#include <vector>

void run_game();
bool check_game(std::vector<char> vec);
bool valid_input(std::vector<char> vec, std::string str);
void draw_board(std::vector<char> vec);
void clear_screen();

int main(){

	run_game();
	return 0;
}

void run_game(){

	std::vector<char> table(9, '~');
	std::string location = "0";
	char player_turn = 'X'; //first player to start

	clear_screen();
  	draw_board(table);
  	while(!check_game(table)){
  		while(!valid_input(table, location)){
  			std::cout << "enter location (1-9) for player (" << player_turn << "): ";
  			std::cin >> location;
  		}

  		table[std::stoi(location) - 1] = player_turn;
  		clear_screen();
  		draw_board(table);
  		// clear_screen();

  		std::cout << "\nprevious move: " << location << "\n";
  		if(check_game(table)){ std::cout << "player " << player_turn << " has won \n";}
  		(player_turn == 'X') ? player_turn = 'O' : player_turn = 'X';

  	}
}

bool check_game(std::vector<char> vec){

	bool result = false;
	bool draw = true;

	// //horizontal
	if((vec[0] == vec[1] && vec[1] == vec[2]) && vec[0] != '~') { result = true;}
	else if((vec[3] == vec[4] && vec[4] == vec[5]) && vec[3] != '~') {result = true;}
	else if((vec[6] == vec[7] && vec[7] == vec[8]) && vec[6] != '~') {result = true;}
	else if((vec[0] == vec[3] && vec[3] == vec[6]) && vec[0] != '~') {result = true;}//vertical
	else if((vec[1] == vec[4] && vec[4] == vec[7]) && vec[1] != '~') {result = true;}
	else if((vec[2] == vec[5] && vec[5] == vec[8]) && vec[2] != '~') {result = true;}
	else if((vec[0] == vec[4] && vec[4] == vec[8]) && vec[0] != '~') {result = true;}//diagon
	else if((vec[2] == vec[4] && vec[4] == vec[6]) && vec[2] != '~') {result = true;}
	else{
		//check for draw
		for(int i = 0; i < vec.size(); i++){
			if(vec[i] == '~'){ 
				draw = false; 
				break; 
			}
			if(i == vec.size() - 1){
				if(draw){ std::cout << "game ended in a draw \n"; exit(0); }
			}
		}
	}
	return result;
}

bool valid_input(std::vector<char> vec, std::string str){

	bool result = false;
	try{ 
		int x = stoi(str);
		if(x > 0 && x <= 9){  (vec[x - 1] == '~') ? result = true : result = false; }
		return result;
	}catch(...){ result = false;}
	return result;
}

void draw_board(std::vector<char> vec){

	std::cout << "       |       |		 \n"; 
	std::cout << "   " << vec[0] << "   |   " << vec[1] << "   |   " << vec[2] << "	 \n"; 
	std::cout << "       |       |		 \n"; 
	std::cout << " - - - + - - - + - - -	 \n"; 
	std::cout << "       |       |		 \n"; 
	std::cout << "   " << vec[3] << "   |   " << vec[4] << "   |   " << vec[5] << "	 \n"; 
	std::cout << "       |       |		 \n"; 
	std::cout << " - - - + - - - + - - -	 \n"; 
	std::cout << "       |       |		 \n"; 
	std::cout << "   " << vec[6] << "   |   " << vec[7] << "   |   " << vec[8] << "	 \n"; 
	std::cout << "       |       |		 \n"; 

}

void clear_screen(){ 
	std::cout << "\033[2J\033[1;1H"; 
	// std::cout << std::string( 10, '\n' );
}