#include <iostream>
#include <string>
#include <vector>

using namespace std;

void game();
bool check_game(vector<char> vec);
bool valid_input(vector<char> vec, string str);
void draw_board(vector<char> vec);
void clear_screen();

int main(){

	game();
	return 0;
}

void game(){

	vector<char> table(9, '~');
	string location = "0";
	char player_turn = 'X'; //first player to start

  	clear_screen();
  	draw_board(table);
  	while(!check_game(table)){

  		cout << "enter location for player (" << player_turn << "): ";
  		cin >> location;

  		while(!valid_input(table, location)){
  			cout << "invalid location, please enter again: (" << player_turn << "): ";
  			cin >> location;
  		}

  		table[stoi(location) - 1] = player_turn;
  		clear_screen();
  		draw_board(table);

  		if(check_game(table)){ cout << "player " << player_turn << " has won" << endl;}
  		(player_turn == 'X') ? player_turn = 'O' : player_turn = 'X';

  	}
}

bool check_game(vector<char> vec){

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

	//check for draw
	for(int i = 0; i < vec.size(); i++){
		if(vec[i] == '~'){
			draw = false;
			break;
		}

		if(i == vec.size() - 1){
			if(draw){
				cout << "game ended in a draw \n";
				exit(0);
			}
		}
	}

	return result;
}

bool valid_input(vector<char> vec, string str){

	bool result = false;
	try{ 

		int x = stoi(str);
		if(x > 0 && x <= 9){  (vec[x - 1] == '~') ? result = true : result = false; }
		return result;

	}catch(...){ result = false;}
	return result;
}

void draw_board(vector<char> vec){

	cout << "       |       |		 " << endl; 
	cout << "   " << vec[0] << "   |   " << vec[1] << "   |   " << vec[2] << "	 " << endl; 
	cout << "       |       |		 " << endl; 
	cout << " - - - + - - - + - - -	 " << endl; 
	cout << "       |       |		 " << endl; 
	cout << "   " << vec[3] << "   |   " << vec[4] << "   |   " << vec[5] << "	 " << endl; 
	cout << "       |       |		 " << endl; 
	cout << " - - - + - - - + - - -	 " << endl; 
	cout << "       |       |		 " << endl; 
	cout << "   " << vec[6] << "   |   " << vec[7] << "   |   " << vec[8] << "	 " << endl; 
	cout << "       |       |		 " << endl; 

}

void clear_screen(){ cout << "\033[2J\033[1;1H"; }