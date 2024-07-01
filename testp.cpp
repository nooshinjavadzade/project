#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;
struct log{
    string username;
    string password;
    string first_name;
    string last_name;
    string total_rank;
};
struct q{
    string question;
    string option_1;
    string option_2;
    string option_3;
    string option_4;
    char answer;
    string designer;
};
struct category{
    string name;
    q x[100];
};
struct scr{
    string username;
    int score;
};
bool emptyy(string x[] , int size){
    for (int i = 0; i < 9; ++i) {
        if (x[i].empty()){
            return true;
        }
    }
    return false;
}

bool search_in_file(const string& filename , const string& word){
    ifstream file(filename);
    string line;
    while (getline(file , line)){
        if (line.find(word) != string::npos){
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
int index_for_soal(q x[]){
    for (int i = 0; i < 100; ++i) {
        if (x[i].question.empty())
            return i;
    }
}
string* split(const string& input) {
    string* tokens = new string[10];
    string token;
    istringstream tokenStream(input);
    int count = 0;
    while (tokenStream >> token) {
        tokens[count++] = token;
    }
    return tokens;
}
bool word_count(const string& word, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower); // تبدیل همه حروف به حروف کوچک
        size_t pos = 0;
        while ((pos = line.find(word, pos)) != string::npos) {
            count++;
            pos += word.length();
        }
    }

    file.close();

    return count >= 5;
}
int countWordsInFile(const string& filename, const string& word) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "error" << endl;
        return -1;
    }

    string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    file.close();

    int count = 0;
    size_t pos = 0;
    while ((pos = content.find(word, pos)) != string::npos) {
        count++;
        pos += word.length();
    }

    return count;
}
string summ(const string& strNumber, int num) {
    int number = stoi(strNumber); // تبدیل رشته به عدد
    int result = number + num; // جمع دو عدد

    // تبدیل عدد حاصل به رشته
    stringstream ss;
    ss << result;
    string resultStr = ss.str();

    return resultStr;
}
int string_to_int(const string& input) {
    stringstream ss(input);
    int number;
    ss >> number;
    return number;
}
bool scoree(const scr &a, const scr &b) {
    if(a.score != b.score){
        return a.score > b.score;
    }
    else{
        return a.username < b.username;
    }
}
int search_my_rank(scr x[] , string name){
    int i;
    for (i = 0; !x[i].username.empty(); ++i) {
        if (x[i].username == name)
            return (i+1);
    }
    return -1;
}
int digit(string x){
    string num_str;
    for(char c : x){
        if (isdigit(c))
        {
            num_str += c;
        }
    }
    int y;
    stringstream(num_str) >> y;
    return y;
}
void printFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

int main() {
    log loggins[100];
    int num_logs = 0;
    category cat[100];
    int num_cat = 0;
    string logged;
    while (1){
        bool admin = false;
        cout << "hi , welcome to Quiz Of Kings" << endl;
        cout << "Enter order commands to login or register" << endl;
        cout << "Remember that the password should only be 4 characters long" << endl;
        cout << "Please enter a space before the command where there are cin.ignore commands, otherwise you will encounter an error" << endl;
        while(1){
            string in1;
            cin.ignore();
            getline(cin, in1);
            if (in1.find("register") != string::npos) {
                string login[9];
                string word;
                stringstream ss(in1);
                int count = 0;
                while (ss >> word) {
                    login[count++] = word;
                }
                if (emptyy(login, 9) || login[0] != "register" || login[1] != "-u" || login[3] != "-p" ||
                    login[5] != "-f" || login[7] != "-l" || login[2] == "admin") {
                    cout << "There was a problem. Please enter all commands and information correctly" << endl;
                    continue;
                } else if (login[4].length() != 4) {
                    cout << "the password should only be 4 characters long" << endl;
                    continue;
                } else {
                    bool find;
                    fstream file;
                    file.open("users_information.txt", ios::in);
                    string line;
                    while (getline(file, line)) {
                        if (line.find(login[2]) != string::npos) {
                            cout << "This username already exists. Please enter another username" << endl;
                            find = true;
                            break;
                        }
                        if (file.eof()) {
                            find = false;
                        }
                    }
                    file.close();
                    if (!find) {
                        loggins[num_logs].username = login[2];
                        loggins[num_logs].password = login[4];
                        loggins[num_logs].first_name = login[6];
                        loggins[num_logs].last_name = login[8];
                        loggins[num_logs].total_rank = "0";
                        logged = loggins[num_logs].username;
                        fstream filee;
                        filee.open("users_information.txt", ios::app);
                        filee << loggins[num_logs].username << endl << loggins[num_logs].password << endl
                              << loggins[num_logs].first_name << endl << loggins[num_logs].last_name << endl
                              << loggins[num_logs].total_rank << endl;
                        num_logs++;
                        filee.close();
                        cout << "You have successfully registered" << endl;
                        break;
                    } else
                        continue;
                }
            } else if (in1.find("login") != string::npos) {
                string login[5];
                string word;
                stringstream ss(in1);
                int count = 0;
                while (ss >> word) {
                    login[count++] = word;
                }
                if (login[0] != "login" || login[1] != "-u" || login[3] != "-p") {
                    cout << "Please enter the commands correctly" << endl;
                    continue;
                } else if (login[2] == "admin" && login[4] == "admin") {
                    admin = true;
                    cout << "You have successfully logged in" << endl;
                    break;
                } else {
                    bool find = false;
                    bool pasword = false;
                    fstream file;
                    file.open("users_information.txt", ios::in);
                    string line;
                    while (getline(file, line)) {
                        if (line.find(login[2]) != string::npos) {
                            find = true;
                            break;
                        }
                    }
                    if (file.eof()) {
                        find = false;
                    }
                    file.close();
                    file.open("users_information.txt", ios::in);
                    while (getline(file, line)) {
                        if (line.find(login[2]) != string::npos) {
                            getline(file, line);
                            if (line.find(login[4]) != string::npos) {
                                pasword = true;
                                break;
                            } else {
                                pasword = false;
                                break;
                            }
                        }
                    }
                    file.close();
                    if (!find) {
                        cout << "This username does not exist." << endl;
                        continue;
                    } else if (!pasword) {
                        cout << "The password is incorrect" << endl;
                        continue;
                    } else {
                        logged = login[2];
                        cout << "You have successfully logged in" << endl;
                        loggins[0].username = logged;
                        break;
                    }
                }

            } else {
                cout << "Please enter the commands correctly" << endl;
                continue;
            }
        }
        while(!admin){
            cout << "Users main menu:" << endl;
            cout << "If you want to start a game, enter <start game>" << endl;
            cout << "If you want to add a question, enter <add question>" << endl;
            cout << "If you want to see the scoreboard, enter <scoreboard>" << endl;
            cout << "If you want to return to the registration and login menu, please enter <Exit>" << endl;
            string in;
            getline(cin , in);
            if (in.find("add question") != string::npos){
                cout << "Enter the name of the category you want to add a question" << endl;
                cout << "If you want to see the available categories, enter from the admin menu." << endl;
                cout << "Whenever you want to return to the main menu of users, enter <back>" << endl;
                string input;
                string in[3];
                cin.ignore();
                getline(cin , input);
                string word;
                stringstream ss(input);
                int count=0;
                while (ss >> word){
                    in[count++] = word;
                }
                if (search_in_file("cat.txt", in[2])){
                    cout << "Enter <add question> to add a question" << endl;
                    string mewo;
                    cin.ignore();
                    getline(cin , mewo);
                    if (mewo == "add question"){
                        int index = 0;
                        cat[index].name = in[2];
                        string soal;
                        cout << "Please enter the question" << endl;
                        string k;
                        cin.ignore();
                        getline(cin , k);
                        cout << "Enter option 1" << endl;
                        cin.ignore();
                        getline(cin , soal);
                        cat[index].x[index_for_soal(cat[index].x)].option_1= soal;
                        cout << "Enter option 2" << endl;
                        cin.ignore();
                        getline(cin , soal);
                        cat[index].x[index_for_soal(cat[index].x)].option_2 = soal;
                        cout << "Enter option 3" << endl;
                        cin.ignore();
                        getline(cin , soal);
                        cat[index].x[index_for_soal(cat[index].x)].option_3 = soal;
                        cout << "Enter option 4" << endl;
                        cin.ignore();
                        getline(cin , soal);
                        cat[index].x[index_for_soal(cat[index].x)].option_4 = soal;
                        cout << "Enter the answer" << endl;
                        char x;
                        cin >>x;
                        cat[index].x[index_for_soal(cat[index].x)].answer = x;
                        cat[index].x[index_for_soal(cat[index].x)].designer = logged;
                        fstream file;
                        file.open("Unconfirmed-questions.txt" , ios::app);
                        file << cat[index].name << ":" << endl;
                        file << k << endl;
                        file << cat[index].x[index_for_soal(cat[index].x)].option_1 << endl;
                        file << cat[index].x[index_for_soal(cat[index].x)].option_2 << endl;
                        file << cat[index].x[index_for_soal(cat[index].x)].option_3 << endl;
                        file << cat[index].x[index_for_soal(cat[index].x)].option_4 << endl;
                        file << cat[index].x[index_for_soal(cat[index].x)].answer << endl;
                        file << cat[index].x[index_for_soal(cat[index].x)].designer << endl;
                        cout << "The question has been successfully entered and is awaiting approval" << endl;
                        cout << "Enter the word <back> to return to the main user menu" << endl;
                        file.close();
                        index++;
                        string back;
                        cin.ignore();
                        getline(cin , back);
                        if (back == "back")
                            continue;
                    }
                    else{
                        cout << "Enter <add question> to add a question" << endl;
                        continue;
                    }
                }
                else{
                    cout << "The category you were looking for did not exist. If you want to see the available categories, enter from the admin menu."<< endl;
                    continue;
                }

            }
            else if (in.find("start game") != string::npos){
                int count = 1;
                cout << "Enter <show categories> to see categories" << endl;
                string in;
                cin.ignore();
                getline(cin, in);
                if (in == "show categories") {
                    fstream file;
                    string line;
                    file.open("cat.txt", ios::in);
                    while (getline(file, line)) {
                        if (word_count(line, "qestion.txt")) {
                            cout << count << ": " << line << endl;
                        }
                    }
                    file.close();
                }
                else{
                    cout << "Please enter the commands correctly" << endl;
                    continue;
                }
                cout << "Now please enter the category you want" << endl;
                string input[3];
                for (int i = 0; i < 3; ++i) {
                    cin >> input[i];
                }
                if (search_in_file("cat.txt", input[2]) && word_count(input[2] , "qestion.txt")) {
                    cout << "Enter <start quiz> if you want to start the game" << endl;
                    string in;
                    cin.ignore();
                    getline(cin , in);
                    if (in.find("start quiz") != string::npos){
                        int mark=0;
                        srand(time(0));
                        for(int k =0; k<5 ;k++){
                            int q = rand() % countWordsInFile("qestion.txt", input[2]) + 1;
                            fstream filee;
                            string in;
                            filee.open("qestion.txt", ios::in);
                            int num = 1;
                            while (getline(filee, in)) {
                                if (in.find(input[2]) != string::npos) {
                                    if (num == q) {
                                        string qestion[6];
                                        for (int o = 0; o < 6; ++o) {
                                            getline(filee, qestion[o]);
                                        }
                                        for (int l = 0; l < 5; ++l) {
                                            cout << qestion[l] << endl;
                                        }
                                        char user;
                                        cin >> user;
                                        if (user == qestion[5][0]) {
                                            mark++;
                                            break;
                                        }
                                    } else {
                                        num++;
                                    }
                                }
                            }
                            cout << "soal: " <<k<< endl;
                        }
                        cout << "The quiz is over. Your score: " << mark << endl;
                        fstream file;
                        fstream temp;
                        file.open("users_information.txt", ios::in);
                        temp.open("temp.txt", ios::out);
                        string in;
                        while (getline(file, in)) {
                            if (in.find(logged) != string::npos) {
                                temp << in << endl;
                                for (int i = 0; i < 3; ++i) {
                                    getline(file, in);
                                    temp << in << endl;
                                }
                                getline(file, in);
                                in = summ(in, mark);
                                temp << in << endl;
                            } else {
                                temp << in << endl;
                            }
                        }
                        file.close();
                        temp.close();
                        string filename = "users_information.txt";
                        remove(filename.c_str());
                        rename("temp.txt", filename.c_str());
                        cout << "Enter <back> to return to the main user menu" << endl;
                        string enter;
                        cin.ignore();
                        getline(cin , enter);
                        if (enter == "back")
                            continue;
                    }
                    else{
                        cout << "Please enter the commands correctly" << endl;
                        continue;
                    }
                }
                else {
                    cout << "The category you are looking for either does not exist or does not have enough questions" << endl;
                    continue;
                }
            }
            else if (in.find("scoreboard") != string::npos){
                scr people[100];
                fstream file;
                string input;
                file.open("users_information.txt" , ios::in);
                int i =0;
                while (getline(file , input)){
                    people[i].username = input;
                    for (int j = 0; j < 4; ++j) {
                        getline(file , input);
                    }
                    people[i].score = string_to_int(input);
                    i++;
                }
                file.close();
                sort(people , people+i , scoree);
                string back;
                cout << "Enter the command you want and I will give you information about the ranks or enter <back>"<< endl;
                string user;
                cin.ignore();
                getline(cin, user);
                if (user.find("show scoreboard -c all") != string::npos) {
                    for (int j = 0; j<i; ++j) {
                        cout << "username: " << people[j].username << " score: " << people[j].score << endl;
                    }
                    cout << "Enter <back> to return to the main user menu" << endl;
                    cin.ignore();
                    getline(cin , back);
                    if (back == "back")
                        continue;
                }
                else if (user == "show my rank -c all"){
                    cout << "your rank: " << search_my_rank(people , logged) << endl;
                    cout << "Enter <back> to return to the main user menu" << endl;
                    cin.ignore();
                    getline(cin , back);
                    if (back == "back")
                        continue;
                }
                else if (user == "back"){
                    continue;
                }
                else if (user.find("-h") != string::npos){
                    for (int j = 0; j < digit(user); ++j) {
                        cout << people[j].username << endl;

                    }
                    cout << "Enter <back> to return to the main user menu" << endl;
                    cin.ignore();
                    getline(cin , back);
                    if (back == "back")
                        continue;
                }

            }
            else if (in.find("Exit") != string::npos)
                break;
        }
        while (admin){
            cout << "welcome, dear admin." << endl;
            cout << "To go to the categories menu, please enter <categories>" << endl;
            cout <<"Enter <questions> to go to the questions menu"<< endl;
            cout <<"Enter <users> to go to the users menu" << endl;
            cout << "Enter <exit> to return to the registration and login menu" << endl;
            string inn;
            cin.ignore();
            getline(cin , inn);
            if (inn == "categories"){
                while (1){
                    cout << "Enter the relevant commands to see categories or create and delete them" << endl;
                    string input;
                    cin.ignore();
                    getline(cin, input);
                    string in_put[3];
                    string word;
                    stringstream ss(input);
                    int count = 0;
                    while (ss >> word) {
                        in_put[count++] = word;
                    }
                    if (input.find("show categories") != string::npos ) {
                        fstream y;
                        y.open("cat.txt" , ios::in);
                        string line;
                        while (getline(y , line)){
                            cout << line << endl;
                        }
                        continue;
                    }
                    else if (in_put[0] == "add" && in_put[1] == "-c") {
                        if (search_in_file("cat.txt", in_put[2])) {
                            cout << "This category exists." << endl;
                        }
                        else{
                            fstream file;
                            file.open("cat.txt" , ios::app);
                            file << in_put[2] << endl;
                            file.close();
                            cout << "Category added successfully" << endl;
                            continue;
                        }
                    }
                    else if (in_put[0] == "remove" || in_put[1] == "-c"){
                        fstream file;
                        fstream temp;
                        string line;
                        file.open("cat.txt" , ios::in);
                        temp.open("temp.txt" , ios::out);
                        string filename = "cat.txt";
                        while (getline(file , line)){
                            if (line.find(in_put[2]) != string::npos)
                                continue;
                            else
                                temp << line << endl;
                        }
                        file.close();
                        temp.close();
                        remove(filename.c_str());
                        rename("temp.txt" , filename.c_str());
                        cout << "category secsesfully deleted";
                        file.open("qestion.txt" , ios::in);
                        temp.open("temp.txt" , ios::out);
                        while (getline(file , line)){
                           if( line.find(in_put[2]) != string::npos){
                               for (int i = 0; i < 6; ++i) {
                                   getline(file , line);
                               }
                           }
                           else{
                               temp << line << endl;
                           }
                        }
                        filename = "qestion.txt";
                        file.close();
                        temp.close();
                        remove(filename.c_str());
                        rename("temp.txt" , filename.c_str());
                        continue;
                    }
                    else if (input == "back")
                        break;
                }
            }
            else if (inn == "questions"){
                cout << "If you want to see more information about the question, such as the designer's information and the category related to the question, enter the number of question" << endl;
                cout << "Enter <delete> to delete the question and <ok> to confirm the question" << endl;
                fstream file;
                file.open("Unconfirmed-questions.txt" , ios::in);
                string x[100][8];
                string line;
                int i = 0;
                while (getline(file , line)){
                    x[i][0] = line;
                    for (int j = 1; j < 8; ++j) {
                        getline(file , line);
                        x[i][j] = line;
                    }
                    i++;
                }
                file.close();
                for (int j = 0; !x[j][0].empty(); ++j) {
                    cout << j+1 << ". " << x[j][1] << endl;
                    cout << x[j][2] << endl;
                    cout << x[j][3] << endl;
                    cout << x[j][4] << endl;
                    cout << x[j][5] << endl;
                    cout << x[j][6] << endl;
                }
                while (1){
                    cout << "Enter the question number to see more information about the question" << endl;
                    cout <<"Enter 0 to return to the question section" << endl;
                    int num;
                    cin >> num;
                    if (num == 0)
                        break;
                    else{
                        string rank;
                        fstream file;
                        file.open("users_information.txt" , ios::in);
                        string line;
                        while (getline(file , line)){
                            if (line.find(x[num-1][7]) != string::npos){
                                for (int j = 0; j < 4; ++j) {
                                    getline(file , line);
                                }
                                rank = line;
                            }
                        }
                        file.close();
                        cout <<"category: " << x[num-1][0] << " username of designer: " << x[num-1][7] << " score: " << rank << endl;
                        string put;
                        cin.ignore();
                        getline(cin , put);
                        if (put == "back")
                            continue;
                        else if (put == "ok"){
                            fstream f;
                            f.open("qestion.txt" , ios::app);
                            f << x[num-1][0] << endl;
                            f<< x[num-1][1] << endl;
                            f<< x[num-1][2] << endl;
                            f << x[num-1][3] << endl;
                            f << x[num-1][4] << endl;
                            f << x[num-1][5] << endl;
                            f << x[num-1][6] << endl;
                            f.close();
                            fstream file;
                            fstream temp;
                            string line;
                            string filename = "Unconfirmed-questions.txt";
                            file.open("Unconfirmed-questions.txt" , ios::in);
                            temp.open("temp.txt" , ios::out);
                            int line_num =1;
                            while (getline(file , line)){
                                if (line_num == num){
                                    for (int j = 0; j < 7; ++j) {
                                        getline(file , line);
                                    }
                                }
                                else{
                                    temp << line << endl;
                                }
                                line_num++;
                            }
                            file.close();
                            temp.close();
                            remove(filename.c_str());
                            rename("temp.txt" , filename.c_str());
                            cout <<"Question successfully added" << endl;
                        }
                        else if (put == "delete"){
                            fstream file;
                            fstream temp;
                            string line;
                            string filename = "Unconfirmed-questions.txt";
                            file.open("Unconfirmed-questions.txt" , ios::in);
                            temp.open("temp.txt" , ios::out);
                            int line_num =1;
                            while (getline(file , line)){
                                if (line_num == num){
                                    for (int j = 0; j < 7; ++j) {
                                        getline(file , line);
                                    }
                                }
                                else{
                                    temp << line << endl;
                                    for (int j = 0; j < 7; ++j) {
                                        getline(file , line);
                                        temp << line << endl;
                                    }
                                }
                                line_num++;
                            }
                            file.close();
                            temp.close();
                            remove(filename.c_str());
                            rename("temp.txt" , filename.c_str());
                            cout <<"Question successfully deleted. " << endl;
                        }
                    }
                }
            }
            else if (inn.find("users") != string::npos){
                cout << "To see users or delete and add them, enter the relevant command" << endl;
                string y;
                string line;
                string x[100][5];
                fstream file;
                file.open("users_information.txt" , ios::in);
                int i = 0;
                while (getline(file , line)){
                    x[i][0] = line;
                    for (int j = 1; j < 5; ++j) {
                        getline(file , line);
                        x[i][j] = line;
                    }
                    i++;
                }
                file.close();
                cin.ignore();
                getline(cin , y);
                if (y.find("show users") != string::npos){
                    for (int j = 0; !x[j][0].empty(); ++j) {
                        cout << j+1 << ". username: " << x[j][0] << " score: " << x[j][4] << endl;
                    }
                }
                else if (y.find("remove") != string::npos){
                    string input[3];
                    string word;
                    stringstream ss(y);
                    int count = 0;
                    while (ss >> word) {
                        input[count++] = word;
                    }
                    if (!search_in_file("users_information.txt" , input[2])){
                        cout << "There is no such user" << endl;
                        continue;
                    }
                    else{
                        string line;
                        fstream file;
                        fstream temp;
                        string filename = "users_information.txt";
                        file.open("users_information.txt" , ios::in);
                        temp.open("temp.txt" , ios::out);
                        while(getline(file , line)){
                            if (line.find(input[2]) != string::npos){
                                for (int j = 0; j < 4; ++j) {
                                    getline(file , line);
                                }
                            }
                            else
                                temp << line << endl;
                        }
                        file.close();
                        temp.close();
                        remove(filename.c_str());
                        rename("temp.txt" , filename.c_str());
                        cout << "The desired user was successfully deleted" << endl;
                        continue;
                    }

                }
                else if (y == "back")
                    continue;
            }
            else if (inn.find("exit") != string::npos)
                break;

        }
    }
    return 0;
}
