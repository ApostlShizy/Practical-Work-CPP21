#include<iostream>
#include<vector>
#include<string>
#include<fstream>

enum WINNER {PLAYER_WIN = 1,BOTS_WIN = 2};

int alive = 0;
int winner = 0;

struct Human {
	std::string name = "Enemy#";
	int health = rand() % 101 + 50;
	int armor = rand() % 51;
	int damage = rand() % 11 + 15;
	int pos[2] = { rand() % 20,rand() % 20 };
};

bool load(std::vector<Human>& npc, Human& player) {
	std::ifstream in_file("save.txt");
	if (in_file.is_open()) {
		int count_npc;
		in_file >> count_npc;
		npc.resize(count_npc);
		for (int i = 0; i < npc.size(); ++i) {
			in_file >> npc[i].name;
			in_file >> npc[i].health;
			in_file >> npc[i].armor;
			in_file >> npc[i].damage;
			in_file >> npc[i].pos[0];
			in_file >> npc[i].pos[1];
		}
		in_file >> player.name;
		in_file >> player.health;
		in_file >> player.armor;
		in_file >> player.damage;
		in_file >> player.pos[0];
		in_file >> player.pos[1];
		return true;
	}
	else {
		std::cerr << "\nNot found safe file!";
		return false;
	}
	in_file.close();
}

void take_damage(std::vector<Human>& npc, Human& player, int i) {
	npc[i].armor -= player.damage;
	if (npc[i].armor < 1) {
		npc[i].health += npc[i].armor;
		npc[i].armor = 0;
		if (npc[i].health < 1) {
			npc[i].pos[0] = -10;
			npc[i].pos[1] = -10;
			std::cout << "\n" << npc[i].name << " dead!" << std::endl;
			return;
		}
	}
	player.armor -= npc[i].damage;
	if (player.armor < 1) {
		player.health += player.armor;
		player.armor = 0;
		if (player.health < 1) {
			player.pos[0] = -10;
			player.pos[1] = -10;
			winner |= BOTS_WIN;
		}
	}
}

char check_pos(char map[][20],std::vector<Human> & npc, Human& player,int i ,int j) {
	if (player.pos[0] == i && player.pos[1] == j) {
		return 'P';
	}
	for (int k = 0; k < npc.size(); ++k) {
		if (npc[k].pos[0] == i && npc[k].pos[1] == j) {
			return 'E';
		}
	}
	return '.';
}

void display_map(char map[][20], std::vector<Human>& npc, Human& player) {
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {	
			map[i][j] = check_pos(map, npc, player, i, j);
			std::cout << map[i][j]<<" ";
		}
		std::cout << std::endl;
	}
}

void save(std::vector<Human>& npc, Human& player) {
	std::ofstream out_file("save.txt");	
	out_file << alive << " ";
	for (int i = 0; i < npc.size(); ++i) {
		if (npc[i].health > 0) {
			out_file << npc[i].name << " ";
			out_file << npc[i].health << " ";
			out_file << npc[i].armor << " ";
			out_file << npc[i].damage << " ";
			out_file << npc[i].pos[0] << " ";
			out_file << npc[i].pos[1] << " ";
		}
	}
	out_file << player.name << " ";
	out_file << player.health << " ";
	out_file << player.armor << " ";
	out_file << player.damage << " ";
	out_file << player.pos[0] << " ";
	out_file << player.pos[1] << " ";
	out_file.close();
}

void player_move(char map[][20],std::vector<Human>& npc, Human& player) {
	std::cout << "\nPlayer name: " << player.name;
	std::cout << "\nhealth: " << player.health;
	std::cout << "\narmor: " << player.armor;
	std::cout << "\ndamage: " << player.damage<<std::endl;
	while (true) {
		char move;
		std::cout << "\nMake move\nL\nR\nU\nD\n\n1 - Save 2 - Load\nEnter: ";
		std::cin >> move;
		if (move == '1') {
			save(npc,player);
		}
		else if (move == '2') {
			load(npc, player);
			display_map(map,npc,player);
		}
		else if (move == 'L') {			
			if (player.pos[1] - 1 >= 0 && map[player.pos[0]][player.pos[1]-1] != 'E') {
				player.pos[1] -= 1;
				map[player.pos[0]][player.pos[1]] = 'P';
				break;
			}
			else if (map[player.pos[0]][player.pos[1] - 1] == 'E') {
				for (int i = 0; i < npc.size(); ++i) {
					if (npc[i].pos[0] == player.pos[0] && npc[i].pos[1] == player.pos[1] - 1) {
						take_damage(npc, player,i);
					}
				}				
				break;
			}
			else {
				std::cout << "\nWrong input!!!";
			}
			
		}
		else if (move == 'R') {
			if (player.pos[1] + 1 < 20 && map[player.pos[0]][player.pos[1] + 1] != 'E') {
				player.pos[1] += 1;
				map[player.pos[0]][player.pos[1]] = 'P';
				break;
			}
			else if (map[player.pos[0]][player.pos[1] + 1] == 'E') {
				for (int i = 0; i < npc.size(); ++i) {
					if (npc[i].pos[0] == player.pos[0] && npc[i].pos[1] == player.pos[1] + 1) {
						take_damage(npc, player, i);
					}
				}
				break;
			}
			else {
				std::cout << "\nWrong input!!!";
			}
		}
		else if (move == 'U') {
			if (player.pos[0] - 1 >= 0 && map[player.pos[0] - 1][player.pos[1]] != 'E') {
				player.pos[0] -= 1;
				map[player.pos[0]][player.pos[1]] = 'P';
				break;
			}
			else if (map[player.pos[0] - 1][player.pos[1]] == 'E') {
				for (int i = 0; i < npc.size(); ++i) {
					if (npc[i].pos[0] == player.pos[0] - 1 && npc[i].pos[1] == player.pos[1]) {
						take_damage(npc, player, i);
					}
				}
				break;
			}
			else {
				std::cout << "\nWrong input!!!";
			}
		}
		else if (move == 'D') {
			if (player.pos[0] + 1 < 20 && map[player.pos[0] + 1][player.pos[1]] != 'E') {
				player.pos[0] += 1;
				map[player.pos[0]][player.pos[1]] = 'P';
				break;
			}
			else if (map[player.pos[0] + 1][player.pos[1]] == 'E') {
				for (int i = 0; i < npc.size(); ++i) {
					if (npc[i].pos[0] == player.pos[0] + 1 && npc[i].pos[1] == player.pos[1]) {
						take_damage(npc, player, i);
					}
				}
				break;
			}
			else {
				std::cout << "\nWrong input!!!";
			}
		}
	}
}

void move_AI(char map[][20],std::vector<Human>& npc, Human& player) {
	alive = 0;
	for (int i = 0; i < npc.size(); ++i) {
		if (winner & BOTS_WIN) {
			return;
		}
		if (npc[i].health > 0) {
			std::cout << "\nName: " << npc[i].name;
			std::cout << "\nhealth: " << npc[i].health;
			std::cout << "\narmor: " << npc[i].armor;
			std::cout << "\ndamage: " << npc[i].damage<<std::endl;
			int origin_y = npc[i].pos[0];
			int origin_x = npc[i].pos[1];
			int temp_y = npc[i].pos[0];
			int temp_x = npc[i].pos[1];		
			temp_y += (rand() % 3)-1;			
			if (temp_y < 0) {
				temp_y = 0;
			}
			else if (temp_y > 19) {
				temp_y = 19;
			}
			temp_x += (rand() % 3)-1;
			if (temp_x < 0) {
				temp_x = 0;
			}
			else if (temp_x > 19) {
				temp_x = 19;
			}
			if (map[temp_y][temp_x] == 'E') {
				temp_y = origin_y;
				temp_x = origin_x;
				npc[i].pos[0] = temp_y;
				npc[i].pos[1] = temp_x;
			}
			else if (map[temp_y][temp_x] == 'P') {
				temp_y = origin_y;
				temp_x = origin_x;
				npc[i].pos[0] = temp_y;
				npc[i].pos[1] = temp_x;
				take_damage(npc,player,i);
			}	
			else {
				npc[i].pos[0] = temp_y;
				npc[i].pos[1] = temp_x;
			}		
			if (npc[i].health > 0) {
				++alive;
			}
		}
	}
	if (!alive) {
		winner |= PLAYER_WIN;
	}
}

int input_num() {
	std::string num;
	std::cin >> num;
	for (int i = 0; i < num.size(); ++i) {
		if (num[i] < '0' || num[i] > '9') {
			std::cout << "\nEnter number!";
			return input_num();
		}
	}
	return std::stoi(num);
}


int main() {
	char map[20][20];
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			map[i][j] = '.';
		}		
	}
	Human player;
	std::vector<Human> npc(5);
	char choice;	
	do {
		std::cout << "New game - N\nLoad game - L\nEnter: ";
		std::cin >> choice;

	} while (choice != 'N' && choice != 'L');
	if (choice == 'N') {	
		std::cout << "\nEnter name: ";
		std::cin >> player.name;
		std::cout << "\nEnter health: ";
		player.health = input_num();
		std::cout << "\nEnter armor: ";
		player.armor = input_num();
		std::cout << "\nEnter damage: ";
		player.damage = input_num();
		for (int i = 0; i < npc.size(); ++i) {
			npc[i].name += std::to_string(i + 1);
		}
	}
	else {
		if (!load(npc, player)) {
			return 1;
		}
	}
	while (winner == 0) {	
		display_map(map, npc, player);
		player_move(map, npc, player);
		move_AI(map, npc, player);		
	}	
	if (winner & PLAYER_WIN) {
			std::cout << "\nPlayer win !!!";
	}
	else {
			std::cout << "\nBots win !!!";
	}
}