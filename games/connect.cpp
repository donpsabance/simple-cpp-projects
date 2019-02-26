#include <iostream>
#include <vector>
#include <string>
#include <cstring>

void display_game(const std::vector<std::vector<std::string> >& vec){

	std::cout << "\033[2J\033[1;1H"; 
	std::cout << "\n\n               \033[1;3;31mC O N N E C T ~ \033[1;3;34mF O U R\033[0m\n\n";
	for(int i = 5; i >= 0; i--){

		std::cout << "          ";
		for(int j = 0; j < 7; j++){


			if(vec[j][i] == "R"){
				std::cout << "[ \033[1;31m" << vec[j][i] << "\033[0m ]";
			}
			else if(vec[j][i] == "B"){
				std::cout << "[ \033[1;34m" << vec[j][i] << "\033[0m ]";
			}
			else{
				std::cout << "[ \033[1;90m" << vec[j][i] << "\033[0m ]";
			}
		} 
		std::cout << "\n\n";

	}
	std::cout << "\n\n";
}

bool add_slot(std::vector<std::vector<std::string> >& vec, int column, std::string color){

	int count = std::stoi(vec[column][6]);

	//column already full
	if(count >= 6) return false;

	vec[column][count] = color;
	vec[column][6] = std::to_string(count + 1);
	return true;

}

bool check_win(const std::vector<std::vector<std::string> >& vec){

	//vertical
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 3; j++){

			// std::cout << vec[i][j] << vec[i][j+1] << vec[i][j+2] << vec[i][j+3] << "\n";
			if(vec[i][j] == vec[i][j+1] && vec[i][j+1] == vec[i][j+2] && vec[i][j+2] == vec[i][j+3] &&
			   vec[i][j] != "0" && vec[i][j+1] != "0" && vec[i][j+2] != "0" && vec[i][j+3] != "0"){

				std::cout << vec[i][j] << " has won @ COL: " << 1 + i << " ROWS: " << 1 + j  << "-" << 1 + (j+1) << "-" << 1 + (j+2) << "-" << 1 + (j+3) << "\n";
				return true;
			} 

		}
	}

	//horizontal
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 4; j++){

			if(vec[j][i] == vec[j+1][i] && vec[j+1][i] == vec[j+2][i] && vec[j+2][i] == vec[j+3][i] &&
			   vec[j][i] != "0" && vec[j+1][i] != "0" && vec[j+2][i] != "0" && vec[j+3][i] != "0"){

				std::cout << vec[i][j] << " has won @ ROW: " << 1 + j << " COLS: " << 1 + i << "-" << 1 + (i+1) << "-" << 1 + (i+2) << "-" << 1 + (i+3) << "\n";
				return true;
			} 

		}
	}

	//diagonal 
	for(int i = 0; i < 3; i++){

		if(vec[i][i]== vec[i+1][i+1] && vec[i+1][i+1] == vec[i+2][i+2] && vec[i+2][i+2] == vec[i+3][i+3] &&
		   vec[i][i]!= "0" && vec[i+1][i+1] != "0" && vec[i+2][i+2] != "0" && vec[i+3][i+3] != "0"){

			std::cout << vec[i][i] << " has won @ " << 1 + i << ":" << 1 + i << " " <<
													   1 + (i + 1) << ":" << 1 + (i + 1) << " " <<
													   1 + (i + 2) << ":" << 1 + (i + 2) << " " <<
													   1 + (i + 2) << ":" << 1 + (i + 2) << "\n";
		   	return true;
		}

		if(vec[i+1][i] == vec[i+2][i+1] && vec[i+2][i+1] == vec[i+3][i+2] && vec[i+3][i+2] == vec[i+4][i+3] &&
		   vec[i+1][i] != "0" && vec[i+2][i+1] != "0" && vec[i+3][i+2] != "0" && vec[i+4][i+3] != "0"){

			std::cout << vec[i+1][i] << " has won @ " << 1 + (i+1) << ":" << 1 + (i) << " " <<
										   1 + (i + 2) << ":" << 1 + (i + 1) << " " <<
										   1 + (i + 3) << ":" << 1 + (i + 2) << " " <<
										   1 + (i + 4) << ":" << 1 + (i + 3) << "\n";
			
		   	return true;
		}
	}

	for(int i = 0; i < 2; i++){

		if(vec[i][i+1] == vec[i+1][i+2] && vec[i+1][i+2] == vec[i+2][i+3] && vec[i+2][i+3] == vec[i+3][i+4] &&
		   vec[i][i+1] != "0" && vec[i][i+1] != "0" && vec[i][i+1] != "0" && vec[i][i+1] != "0"){

			std::cout << vec[i][i+1] << " has won @ " << 1 + (i) << ":" << 1 + (i + 1) << " " <<
						   1 + (i + 1) << ":" << 1 + (i + 2) << " " <<
						   1 + (i + 2) << ":" << 1 + (i + 3) << " " <<
						   1 + (i + 3) << ":" << 1 + (i + 4) << "\n";

			return true;
		}

		if(vec[i+2][i] == vec[i+3][i+1] && vec[i+3][i+1] == vec[i+4][i+2] && vec[i+4][i+2] == vec[i+5][i+3] &&
		   vec[i+2][i] != "0" && vec[i+3][i+1] != "0" && vec[i+4][i+2] != "0" && vec[i+5][i+3] != "0"){

			std::cout << vec[i+2][i] << " has won @ " << 1 + (i + 2) << ":" << 1 + (i) << " " <<
						   1 + (i + 3) << ":" << 1 + (i + 1) << " " <<
						   1 + (i + 4) << ":" << 1 + (i + 2) << " " <<
						   1 + (i + 5) << ":" << 1 + (i + 3) << "\n";

			return true;
		}
	}

	if(vec[3][0] == vec[4][1] && vec[4][1] == vec[5][2] && vec[5][2] == vec[6][3] &&
		vec[3][0] != "0"){

		std::cout << vec[3][0] << " has won @ 4:1 5:2 6:3 7:4 \n";
		return true;
	}

	if(vec[0][2] == vec[1][3] && vec[1][3] == vec[2][4] && vec[2][4] == vec[3][5] &&
		vec[0][2] != "0"){

		std::cout << vec[3][0] << " has won @ 1:3 1:4 3:5 4:6 \n";
		return true;
	}

	return false;
}	

bool is_valid_int(std::string str){

	for(char c : str){
		if(c < 48 || c > 57) return false;
	}

	int temp = std::stoi(str);
	if(temp >= 0 && temp <= 7) return true;

	return false;

}

void run_game(){

	std::vector<std::vector<std::string> > vec(7, std::vector<std::string> (7, "0"));

	std::string input = "-1";
	int turn = 0;

	display_game(vec);
	while(!check_win(vec)){

		if(turn == 0){

			while(!is_valid_int(input)){

				std::cout << "enter column for player B: ";
				std::cin >> input;

			}

			if(!add_slot(vec, std::stoi(input) - 1, "B")){

					std::cout << "column already full, try again: ";
					input = "-1";
					
			} 

			display_game(vec);

			input = "-1";
			turn = 1;
		}
		else if(turn == 1){

			while(!is_valid_int(input)){

				std::cout << "enter column for player R: ";
				std::cin >> input;

			}

			if(!add_slot(vec, std::stoi(input) - 1, "R")){

				std::cout << "column already full, try again: ";
				input = "-1";
					
			} 

			display_game(vec);

			input = "-1";
			turn = 0;
		}
	}
}

int main(){


	run_game();

	return	0;

}