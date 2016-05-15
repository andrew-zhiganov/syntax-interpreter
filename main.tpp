#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int Proceed(string file){
    void PrepareLine(string & line);
    void ParseVar(string & line, int & event, int & state);
    void ParseIdent(string & line, int & event, int & state, vector<string> & idents);
    void ParseInt(string & line, int & event, int & state);
    void ParseBegin(string & line, int & event, int & state);
    void ParseAssignment(string & line, int & event, int & state, vector<string> & idents);

    ifstream input;
    input.open(file);
    int event = 0;
    int state = 0;
    vector<string> idents;
    string line;

    while(!input.eof() && event == 0){
        getline(input, line);
        PrepareLine(line);
//        cout << line << " <-- newline  ";
        while(event == 0 && line.length() != 0 && state != 6){
            switch(state){
                case 0: {ParseVar(line, event, state); break;}
                case 1: {ParseIdent(line, event, state, idents); break;}
                case 2: {ParseInt(line, event, state); break;}
                case 3: {ParseBegin(line, event, state); break;}
                case 4: {ParseAssignment(line, event, state, idents); break;}
                case 5: {ParseAssignment(line, event, state, idents); break;}
            }
//            cout << line << " , " << state << " , " << event << " !!! ";
        };

    }
    if(state != 6 && event == 0){
        event = 14;
    }
    if(state == 6 && !input.eof()){
        event = 16;
    }
    input.close();
    return event;
}

void PrepareLine(string & line){
    for(uint i = 0; i < line.length(); i++){
        bool modified = false;
        if(line[i] == ' '){
            line.erase(i, 1);
            modified = true;
        }
        if(int(line[i]) >= int('A') && int(line[i]) <= int('Z')){
            line[i] = char(int(line[i]) - int('A') + int('a'));
            modified = true;
        }
        if(modified){i--;}
    }
    return;
}

void ParseVar(string & line, int & event, int & state){
    if(line.length() >= 3 && line[0] == 'v' && line[1] == 'a' && line[2] == 'r'){
        state = 1;
        line.erase(0, 3);
    }
    else{
        event = 1;
    }
    return;
}

void ParseIdent(string & line, int & event, int & state, vector<string> & idents){
    string spec[4] = {"var", "begin", "end", "integer"};
    uint i = 0;

    while(int(line[i]) >= int('a') && int(line[i]) <= int('z') || int(line[i]) >= int('0') && int(line[i]) <= int('9')){
        i++;
    }
    if(i == 0){
        event = 2;
        return;
    }
    else if(i > 11){
        event = 4;
        return;
    }
    else{
        char buffer[11] = "";
        line.copy(buffer, i, 0);
        line.erase(0, i);

        string word = buffer;
        bool correct = true;
        for(int q = 0; q < word.length(); q++){
            if(int(word[q]) < 'a' || int(word[q]) > 'z'){
                correct = false;
            }
        }
        if(!correct){
            event = 5;
            return;
        }
        if(word == spec[0] || word == spec[1] || word == spec[2] || word == spec[3]){
            event = 5;
            return;
        }
        bool equal = false;
        for(uint j = 0; j < idents.size(); j++){
            if(word == idents[j]){
                event = 3;
                equal = true;
                break;
            }
        }
        if(!equal){
            idents.push_back(word);
            if(line[0] == ':'){
                state = 2;
                line.erase(0, 1);
            }
            else if(line[0] == ','){
                line.erase(0, 1);
            }
            else{
                event = 6;
            }
        }
    }
    return;
}

void ParseInt(string & line, int & event, int & state){
    uint i = 0;
    while(int(line[i]) >= 'a' && int(line[i]) <= 'z'){
        i++;
    }
    if(i != 7){
        event = 7;
        return;
    }
    else{
        char buffer[7] = "";
        line.copy(buffer, i, 0);
        line.erase(0, i);
        string word = buffer;
        if(word != "integer"){
            event = 7;
            return;
        }
        if(line[0] != ';'){
            event = 8;
            return;
        }
        else{
            line.erase(0, 1);
            state = 3;
        }
    }
    return;
}

void ParseBegin(string & line, int & event, int & state){
    uint i = 0;
    while(int(line[i]) >= 'a' && int(line[i]) <= 'z'){
        i++;
    }
    if(i != 5){
        event = 9;
        return;
    }
    else{
        char buffer[5] = "";
        line.copy(buffer, i, 0);
        line.erase(0, i);
        string word = buffer;
        if(word != "begin"){
            event = 9;
            return;
        }
        state = 4;
    }
    return;
}

void ParseAssignment(string & line, int & event, int & state, vector<string> & idents){
    void ParseExpression(string & line, int & event, int & state, vector<string> & idents);

    uint i = 0;
    while(int(line[i]) >= 'a' && int(line[i]) <= 'z' && i < line.length()){
        i++;
    }
    char buffer[255] = "";
    line.copy(buffer, i, 0);
    line.erase(0, i);
    string word = buffer;
    if(state == 5 && word == "end"){
        state = 6;
        return;
    }
    else{
        bool correct = false;
        for(int j = 0; j < idents.size(); j++){
            if(idents[j] == word){
                correct = true;
            }
        }
        if(!correct){
            event = 10;
            return;
        }
        if(line[0] != '='){
            event = 11;
            return;
        }
        else{
            line.erase(0, 1);
        }
        if(line[line.length() - 1] != ';'){
            event = 8;
            return;
        }
        else{
            line.erase(line.length() - 1, 1);
            if(line.length() == 0){
                event = 15;
            }
            else{
                ParseExpression(line, event, state, idents);
            }
            state = 5;
        }
    }
    return;
}

void ParseExpression(string & line, int & event, int & state, vector<string> & idents){
//    cout << "EXR |" << line << "| ";
    void ParseSubExpression(string & line, int & event, int & state, vector<string> & idents);
    if(event != 0){return;}
    if(line[0] != '-' && line[0] != '(' && (int(line[0]) < 'a' || int(line[0]) > 'z') && (int(line[0]) < '0' || int(line[0]) > '9')){
        event = 12;
        return;
    }
    if(line[0] == '-'){
        line.erase(0, 1);
    }
    if(line.length() == 0){
        event = 15;
    }
    else{
        ParseSubExpression(line, event, state, idents);
    }
    return;
}

void ParseSubExpression(string & line, int & event, int & state, vector<string> & idents){
//    cout << "SUBEXR |" << line << "| ";
    if(event != 0){return;}
    int skob = 0;
    for(uint i = 0; i < line.length(); i++){
        if(!((int(line[i]) >= int('a') && int(line[i]) <= int('z')) || (int(line[i]) >= int('0') && int(line[i]) <= int('9')) || line[i] == '(' || line[i] == ')' || line[i] == '-' || line[i] == '+' || line[i] == '/')){
            event = 12;
            return;
        }
        else if(line[i] == '('){
            skob++;
        }
        else if(line[i] == ')'){
            skob--;
        }
    }
    if(event != 0){return;}
    if(skob != 0){
        event = 13;
        return;
    }
    uint q = 0;
    int skob2 = 0;
    bool binFound = false;
    while(q < line.length()){
        if(line[q] == '('){
            skob2++;
        }
        if(line[q] == ')'){
            skob2--;
        }
        if((line[q] == '+' || line[q] == '-' || line[q] == '/') && skob2 == 0){
            binFound = true;
            break;
        }
        q++;
    }
    if(binFound){
        char buffer[255] = "";
        line.copy(buffer, q, 0);
        line.erase(0, q);
        string word = buffer;
        if(word.length() == 0){
            event = 15;
        }
        else{
            ParseSubExpression(word, event, state, idents);
        }
        line.erase(0, 1);
        if(line.length() == 0){
            event = 15;
        }
        else{
            ParseSubExpression(line, event, state, idents);
        }
        return;
    }
    else if(line[0] == '(' && line[line.length() - 1] == ')'){
        line.erase(line.length() - 1, 1);
        line.erase(0, 1);
        if(line.length() == 0){
            event = 15;
        }
        else{
            ParseExpression(line, event, state, idents);
        }
        return;
    }
    uint i = 0;
    while(int(line[i]) >= 'a' && int(line[i]) <= 'z' && i < line.length()){
        i++;
    }
    if(i == line.length()){
        char buffer[255] = "";
        line.copy(buffer, i, 0);
        line.erase(0, i);
        string word = buffer;
        bool correct = false;
        for(int j = 0; j < idents.size(); j++){
            if(idents[j] == word){
                correct = true;
            }
        }
        if(!correct){
            event = 10;
            return;
        }
        return;
    }
    uint j = 0;
    while(int(line[j]) >= '0' && int(line[j]) <= '9' && j < line.length()){
        j++;
    }
    if(j == line.length()){
        line.erase(0, j);
        return;
    }
    event = 15;
    return;
}