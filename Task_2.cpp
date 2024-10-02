#include<iostream>
#include<vector>
#include<string>

enum BILDS_PLOT { HOUSE = 1, GARAGE = 2, BARN = 4, BATHHOUSE = 8, STOVE_GARAGE = 16 };


struct plot {
    int number_plot = 0;
    int plot_size = 0;
    int bilds = 0;
    std::vector<bool> stove_floor;
    std::vector<int> bilds_size{ 0,0,0,0 };
    std::vector<std::vector<std::string>> floor_rooms_s_t; /*size-type*/
    std::vector<int> floor_height;
};

int input_num() {
    std::string num;
    std::cin >> num;
    for (int i = 0; i < num.length(); ++i) {
        if (num[i] < '0' || num[i] > '9') {
            std::cout << "\nIncoorect value, enter number!\nEnter: ";
            return input_num();
        }
    }
    if (stoi(num) < 0) {
        std::cout << "\nValue can'not be negtive or zere";
        return input_num();
    }
    return stoi(num);
}

char y_or_n() {
    char choice;
    std::cout << "\nEnter (y/n): ";
    std::cin >> choice;
    if (choice != 'y' && choice != 'n') {
        std::cout << "\nWrong input!";
        return y_or_n();
    }
    return choice;
}

int space_bilds(std::vector<plot>& vec_plot, int i) {
    int size_house = 0;
    if (vec_plot[i].bilds & HOUSE) size_house += vec_plot[i].bilds_size[0];
    if (vec_plot[i].bilds & GARAGE) size_house += vec_plot[i].bilds_size[1];
    if (vec_plot[i].bilds & BARN) size_house += vec_plot[i].bilds_size[2];
    if (vec_plot[i].bilds & BATHHOUSE) size_house += vec_plot[i].bilds_size[3];
    return vec_plot[i].plot_size - size_house;
}

void floor_room_s_t(std::vector<plot>& vec_plot, int i, int j, int buffer) {
    int size_rooms = 0;
    {        
        std::cout << "\nOn floor be stove ?";
        char bake = y_or_n();
        if (bake == 'y') {
            vec_plot[i].stove_floor.push_back(true);
        }
        else {
            vec_plot[i].stove_floor.push_back(false);
        }
    }
    for (int k = 0; k < buffer; ++k) {
        int choice = 0;
        int size = 0;
        char type_room = ' ';
        std::cout << "\nSize of room " << k + 1 << " be on floor " << i + 1;
        std::cout << "\nHouse size left: " << vec_plot[i].bilds_size[0] - size_rooms << " M" << "\nEnter: ";
        size = input_num();
        while (size > vec_plot[i].bilds_size[0]) {
            std::cout << "\nWrong size,try again: ";
            size = input_num();
        }
        size_rooms += size;
        std::cout << "1-BEEDROOM\n2-KITCHEN\n3-BATHROOM\n4-CHILDREN\n5-LIVINGROOM\nEnter: ";
        choice = input_num();
        while (choice < 1 || choice > 5) {
            std::cout << "\nWrong num.Try again: ";
            choice = input_num();
        }
        switch (choice)
        {
        case 1:
            type_room = 'a';
            break;
        case 2:
            type_room = 'b';
            break;
        case 3:
            type_room = 'c';
            break;
        case 4:
            type_room = 'd';
            break;
        case 5:
            type_room = 'e';
            break;

        default:
            break;
        }
        vec_plot[i].floor_rooms_s_t[j].push_back(std::to_string(size) + type_room);
    }
    if (vec_plot[i].bilds_size[0] - size_rooms < 0) {
        std::cout << "\nRooms take more space that house haw try again !";
        floor_room_s_t(vec_plot, i, j, buffer);
    }
}

int main() {
    int vilage_size = 0;
    std::vector<plot> vec_plot;
    {
        int size;
        std::cout << "\nEnter size of vilage: ";
        std::cin >> size;
        vec_plot.resize(size);
    }
    for (int i = 0; i < vec_plot.size(); ++i) {       
        vec_plot[i].number_plot = i + 1;
        std::cout << "\nWe are workin on plot " << vec_plot[i].number_plot << std::endl;
        do {
            std::cout << "\nEnter size of plot,ecual 100M or more: ";
            vec_plot[i].plot_size = input_num();
        } while (vec_plot[i].plot_size < 100);
        do {    
            char choice;
            vec_plot[i].bilds_size[0] = 0;
            vec_plot[i].bilds_size[1] = 0;
            vec_plot[i].bilds_size[2] = 0;
            vec_plot[i].bilds_size[3] = 0;            
            std::cout << "\nSpace left: " << space_bilds(vec_plot, i);
            std::cout << "\nDo you want add House ?";
            choice = y_or_n();
            if (choice == 'y') {
                vec_plot[i].bilds |= HOUSE;
                std::cout << "\nSize of House: ";
                vec_plot[i].bilds_size[0] = input_num();
            }
            std::cout << "\nSpace left " << space_bilds(vec_plot, i);
            std::cout << "\nDo you want add garage ?";
            choice = y_or_n();
            if (choice == 'y') {
                vec_plot[i].bilds |= GARAGE;
                std::cout << "\nSize of garage: ";
                vec_plot[i].bilds_size[1] = input_num();
                std::cout << "\nAdd stove in garage ?";
                choice = y_or_n();
                if (choice == 'y') {
                    vec_plot[i].bilds |= STOVE_GARAGE;
                }
            }
            std::cout << "\nSpace left: " << space_bilds(vec_plot, i);
            std::cout << "\nDo you want add barn ?";
            choice = y_or_n();
            if (choice == 'y') {
                vec_plot[i].bilds |= BARN;
                std::cout << "\nSize of barn: ";
                vec_plot[i].bilds_size[2] = input_num();
            }
            std::cout << "\nSpace left: " << space_bilds(vec_plot, i);
            std::cout << "\nDo you want add bathhouse ?";
            choice = y_or_n();
            if (choice == 'y') {
                vec_plot[i].bilds |= BATHHOUSE;
                std::cout << "\nSize of bathhouse: ";
                vec_plot[i].bilds_size[3] = input_num();
            }              
        } while (space_bilds(vec_plot, i) < 0);
        vilage_size += vec_plot[i].plot_size;       
        if (vec_plot[i].bilds & HOUSE) {
            int buffer;
            std::cout << "\nEnter count of floors (1 - 3): ";
            buffer = input_num();
            while (buffer < 1 || buffer > 3) {
                std::cout << "\nUnacceptable count of floors!!!";
                buffer = input_num();                
            }
            vec_plot[i].floor_rooms_s_t.resize(buffer);
            for (int j = 0; j < vec_plot[i].floor_rooms_s_t.size(); ++j) {
                std::cout << "\nEnter count of rooms (2-4) on " << i + 1 << " floor: ";
                buffer = input_num();
                while (buffer < 2 || buffer > 4) {
                    std::cout << "\nUnacceptable count of rooms!!!\nEnter (2-4): ";
                    buffer = input_num();
                }
                floor_room_s_t(vec_plot, i, j, buffer);
            }
        }
    }
    for (int i = 0; i < vec_plot.size(); ++i) {        
        std::cout << '\n' + std::string(30, '-') + '\n';
        std::cout << "\nPlot " << vec_plot[i].number_plot << ": ";
        std::cout << "\nPlot size: " << vec_plot[i].plot_size << " M";
        std::cout << "\nIts " << vec_plot[i].plot_size / (vilage_size / 100) << "% of vilage.";
        std::cout << "\nThere is on the site: " << std::endl;
        if (vec_plot[i].bilds & HOUSE) std::cout << "House. Size: " << vec_plot[i].bilds_size[0] << std::endl;
        if (vec_plot[i].bilds & GARAGE) std::cout << "Garage. Size: " << vec_plot[i].bilds_size[1] << std::endl;
        if (vec_plot[i].bilds & STOVE_GARAGE) std::cout << "With stove." << std::endl;
        if (vec_plot[i].bilds & BARN) std::cout << "Barn. Size: " << vec_plot[i].bilds_size[2] << std::endl;
        if (vec_plot[i].bilds & BATHHOUSE) std::cout << "Bathhouse. Size: " << vec_plot[i].bilds_size[3] << std::endl;
        std::cout << "\nHouse has " << vec_plot[i].floor_rooms_s_t.size() << " floors"<<std::endl;
        for (int j = 0; j < vec_plot[i].floor_rooms_s_t.size(); ++j) {
            std::cout << "\n\tFloor " << j + 1 << ": "<<std::endl;
            if (vec_plot[i].stove_floor[j]) {
                std::cout << "\nThere is a stove on the floor" << std::endl;
            }
            for (int k = 0; k < vec_plot[i].floor_rooms_s_t[j].size(); ++k) {
                std::cout << stoi(vec_plot[i].floor_rooms_s_t[j][k]);
                if (vec_plot[i].floor_rooms_s_t[j][k].back() == 'a') {
                    std::cout << " Bedroom" << std::endl;
                }
                else if (vec_plot[i].floor_rooms_s_t[j][k].back() == 'b') {
                    std::cout << " Kitchen" << std::endl;
                }
                else if (vec_plot[i].floor_rooms_s_t[j][k].back() == 'c') {
                    std::cout << " Bathroom" << std::endl;
                }
                else if (vec_plot[i].floor_rooms_s_t[j][k].back() == 'd') {
                    std::cout << " Children" << std::endl;
                }
                else {
                    std::cout << " Livingroom" << std::endl;
                }
            }
        }
        std::cout << '\n' + std::string(30, '-') + '\n';
    }
}