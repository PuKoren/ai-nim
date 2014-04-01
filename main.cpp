#include <iostream>
#include <vector>

std::vector<int> rows;
int row_count = 4;

int xOr(){
	int value = 0;
	for(unsigned int i=0; i<rows.size(); i++){
		value ^= rows[i];
	}
	return value;
}

int sum(){
	int value = 0;
	for(unsigned int i=0; i<rows.size(); i++){
		value += rows[i];
	}
	return value;
}

void draw_game(){
	for(int i = 0; i < rows.size(); i++){
		std::cout << i+1 << ": ";
		for(int j = 0; j < rows[i]; j ++){
			std::cout << " | ";
		}
		std::cout << std::endl;
	}
}

void input(int &command, const char* command_name){
	std::cout << "Press " << command_name << ". Use 0 to exit." << std::endl;
	std::cin >> command;
}

bool remove_element(int row, int number){
	if(row < rows.size()){
		if(number <= rows[row]){
			rows[row] -= number;
			return true;
		}
	}
	std::cout << "Please check your input and try again." << std::endl;
	return false;
}

void add_element(int row, int number){
	rows[row] += number;
}

void computer(){
	std::cout << "Computer turn..." << std::endl;
	int sum = xOr();
	for(int i = 0; i < rows.size(); i++){
		if(rows[i] > 0){
			for(int j = 1; j <= rows[i]; j++){
				remove_element(i, j);
				int sum = xOr();
				if(sum != 0){
					add_element(i, j);
				}else{
					std::cout << "Removed " << j << " from row " << i+1 << std::endl;
					return;
				}
			}
		}
	}
	int i = 0;
	while(!remove_element(i, 1))
		i++;
}

int main(int argc, char** argv){
	for(int i = row_count-1; i >= 0; i--){
		rows.push_back(i*2 + 1);
	}
	std::cout << "Jeu de nim !" << std::endl;

	int command = -1;
	bool validated = false;
	while(command != 0 || !validated){
		draw_game();
		input(command, "row number");
		if(command != 0){
			int row = command;
			input(command, "how much you want to remove");
			if(command != 0){
				validated = remove_element(row-1, command);
				if(sum() == 0){
					std::cout << "You win." << std::endl;
					command = 0;
					break;
				}else{
					if(validated) computer();
					if(sum() == 0){
						std::cout << "You loose." << std::endl;
						command = 0;
					}
				}
			}
		}
	}

	return 0;
}