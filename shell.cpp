#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <unordered_set>
#include <bits/stdc++.h>
/*#include <stdio.h>*/
/*#include <stdlib.h>*/
using namespace std;

string get_path(string command, const string& path_env);

vector<string> tokenize(const string& input);

int main() {
  cout << unitbuf;
  cerr << unitbuf;
  unordered_set<string> DEFAULT_COMMANDS = { "echo", "exit", "type" };
  
  string user = getenv("USER");
  string path_env = getenv("PATH");
  while(true) {
    // basic shell sign
    char default_shell = '%';
    string shell_prompt = user + " " + default_shell + " ";
    cout << shell_prompt;
    
    // getting input
    string input;
    getline(cin, input);
    if (input.empty()) continue;

    vector<string> tokens = tokenize(input);   // Use a vector to store the tokens

    string command = tokens[0];

    // implementing exit
    if (command == "exit") break;

    // implementing echo
    else if (command == "echo") {
      /*cout << input << endl;*/
      /*cout << input.substr(0,1) << endl;*/
      if (input.length() < 5) cout << endl;
      string input_echo_string = input.substr(5); 
      if (input.substr(5,1) == "'") {
        string newStr = input.substr(6);
        int endQuote = newStr.find("'");
        cout << endQuote << endl;
        cout << newStr.substr(0, (endQuote)) << endl;
      }
      else cout << input_echo_string << endl;
    }

    // implementing type
    else if (command == "type") {
      if (tokens.size() < 2) { }
      else {
        bool found = false;
        string input = tokens[1];
        if (DEFAULT_COMMANDS.find(input) != DEFAULT_COMMANDS.end()) {
          found = true;
          cout << input << " is a shell builtin\n";
        }
        else {
          string path = get_path(input, path_env);
          if (path.empty()) cout << input << ": not found\n";
          else cout << input << " is " << path << endl;
        }
      }
    }
    
    // command not found
    /*else cout << command << ": command not found \n";*/
    else {
      string input = tokens[0];
      string path = get_path(input, path_env);
      if (path.empty()) { 
        cout << command << ": command not found \n";
      }
      else {
        string command = input;
        for (int i = 1; i < tokens.size(); i++) {
          command += " " + tokens[i];
        }
        const char* cmd = command.c_str();
        system(cmd);
      }
    }
  }


  return 0;
}

string get_path(string command, const string& path_env) {
  stringstream ss(path_env);

  string path;

  while(!ss.eof()) {
    getline(ss, path, ':');

    string abs_path = path + "/" + command;
    if (filesystem::exists(abs_path)) return abs_path;
  }
  return "";
}

vector<string> tokenize(const string& input) {
    vector<string> tokens;
    size_t pos = 0, found;
    while ((found = input.find_first_of(" \t", pos)) != string::npos) {
        if (found > pos) tokens.push_back(input.substr(pos, found - pos));
        pos = found + 1;
    }
    if (pos < input.length()) tokens.push_back(input.substr(pos));
    return tokens;
}

