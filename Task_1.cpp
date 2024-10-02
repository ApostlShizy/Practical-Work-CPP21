#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<cstring>


struct statements {
    std::string first_name = "none";
    std::string last_name = "none";
    std::string date = "none";
    std::string sum = "none";
};

bool check_sum(const std::string & sum) {
    if(sum[0] == '0') {
        std::cout<<"\nCan't start from zero";
        return true;
    }
    for(int i = 0;i < sum.length();++i) {
        if(sum[i] < '0' || sum[i] > '9') {
            std::cout<<"\nWrong sum,enter number";
            return true;
        }
    }
    return false;
}

bool check_name(const std::string & name) {
    for(int i = 0;i < name.length();++i) {
        if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z')) {
            continue;
        }
        std::cout<<"\nInvalid name";
        return true;
    }
    return false;
}

bool check_date(const std::string& date) {
    int start = 0;
    bool feb = false;
    bool month = true;
    bool day = true;
    bool year = true;    
    for (int i = 0; i < date.length() && year; ++i) {
        if (date[i] == '.' && month) {
            int temp_m = stoi(date.substr(start, i));           
            if (temp_m < 1 || temp_m > 12) {
                std::cout << "\nWrong month !";
                return true;
            }
            if (temp_m == 2) {
                feb = true;
            }
            start = i + 1;
            month = false;
        }
        else if (date[i] == '.' && day) {
            int temp_d = stoi(date.substr(start, i));          
            if (feb && (temp_d > 28 || temp_d < 1)) {
                std::cout << "\nWrong day !";
                return true;
            }
            else if (!feb && (temp_d < 1 || temp_d > 31)) {
                std::cout << "\nWrong day !";
                return true;
            }
            start = i + 1;
            day = false;
        }
        else if (!day && year) {
            int temp_y = stoi(date.substr(start,date.length()-1));            
            if (temp_y < 1900 || temp_y > 2024) {
                std::cout << "\nWrong Year!";
                return true;
            }
            year = false;
        }
    }
    if (!(day && month && year)) {
        return false;
    }
    else {
        return true;
    }
}

void list() {
    std::ifstream in_file ("statements.txt");
    if(!in_file.is_open()) {
        std::cout<<"\nFail to open file!";
        return;
    }
    while(!in_file.eof()) {    
        std::cout<<'\n' + std::string(30,'-') +'\n';
        std::string buffer;
        std::getline(in_file,buffer);
        std::cout<<buffer;
    }
    in_file.close();
}

void add_state(std::vector<statements> & vec_state) {
    std::ofstream out_file("statements.txt",std::ios::app);
    int i = vec_state.size()-1;     
    out_file << vec_state[i].first_name << vec_state[i].last_name << vec_state[i].date << vec_state[i].sum;
    out_file.close();
}

statements form_state() {
    statements new_statement;
    std::string buffer;
    do {
        std::cout<<"\nEnter first name: ";
        std::cin >> buffer;        
    }while(check_name(buffer));
    new_statement.first_name = buffer + ' ';
    do {
        std::cout<<"\nEnter second name: ";
        std::cin>>buffer;
    }while(check_name(buffer));
    new_statement.last_name = buffer + ' ';
    do {
        std::cout<<"\nEnter date MM.DD.YYYY: ";
        std::cin>>buffer;
    }while(check_date(buffer));
    new_statement.date = buffer + ' ';
    do {
        std::cout<<"\nEnter sum: ";
        std::cin>>buffer;
    }while(check_sum(buffer));
    new_statement.sum = buffer + '\n';
    return new_statement;
}

int main () {
    std::vector<statements> vec_state;
    std::string command;
    do { 
        std::cout<<"\nChoice option:\nexit\nadd\nlist\nEnter: ";
        std::cin>>command;
        if(command == "add") {
            vec_state.push_back(form_state());
            add_state(vec_state);
        }
        else if (command == "list") {
            list();
        }
    }while(command != "exit");
}