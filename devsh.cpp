#include <bits/stdc++.h>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;


unordered_set<string> DEFAULT_COMMANDS = {"echo", "exit", "type"};
string USER = getenv("USER");
string PATH_ENV = getenv("PATH");

string get_path(string command, const string &path_env);

void type_cmd(vector<string>);

vector<string> tokenize(const string &input);

void exec_command(vector<string>);

void echo_cmd(vector<string>);

int main() {
  cout << unitbuf;
  cerr << unitbuf;

    while (true) {
    // basic shell sign
    char default_shell = '%';
    /*system("hostname");*/
    string shell_prompt = USER + " " + default_shell + " ";
    cout << shell_prompt;

    // getting input
    string input;
    getline(cin, input);
    if (input.empty())
      continue;

    vector<string> tokens = tokenize(input); // Use a vector to store the tokens

    string command = tokens[0];

    // implementing exit
    if (command == "exit")
      break;

    // implementing echo
    else if (command == "echo") {
      if (tokens.size() < 2) {
        cout << endl;
      } else
        echo_cmd(tokens);
    }

    // implementing type
    else if (command == "type") {
      if (tokens.size() < 2) {
      } else {
        type_cmd(tokens);
      }
    }

    // command not found
    else {
      string input = tokens[0];
      string path = get_path(input, PATH_ENV);
      if (path.empty()) {
        cout << command << ": command not found \n";
      } else {
        exec_command(tokens);
      }
    }
  }

  return 0;
}

string get_path(string command, const string &path_env) {
  stringstream ss(path_env);

  string path;

  while (!ss.eof()) {
    getline(ss, path, ':');

    string abs_path = path + "/" + command;
    if (filesystem::exists(abs_path))
      return abs_path;
  }
  return "";
}

vector<string> tokenize(const string &input) {
  vector<string> tokens;
  size_t pos = 0, found;
  while ((found = input.find_first_of(" \t", pos)) != string::npos) {
    if (found > pos)
      tokens.push_back(input.substr(pos, found - pos));
    pos = found + 1;

  }
  if (pos < input.length())
    tokens.push_back(input.substr(pos));
  return tokens;
}

void exec_command(vector<string> tokens) {
  if (tokens.empty())
    return;

  vector<char *> args;
  for (string &token : tokens) {
    args.push_back(&token[0]);
  }
  args.push_back(nullptr);

  pid_t pid = fork();
  if (pid == 0) {
    execvp(args[0], args.data());
    perror("execvp");
    exit(EXIT_FAILURE);
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
  } else {
    perror("fork");
  }
}

void echo_cmd(vector<string> tokens) {

  string echo_output;
  bool in_quotes = false;
  char quote_char = '\0';

  for (size_t i = 1; i < tokens.size(); i++) {
    string word = tokens[i];
    char front = word.front();
    char back = word.back();
    char singleQuote = '\'';
    char doubleQuote = '\"';

    if (!in_quotes && (front == singleQuote || front == doubleQuote)) {
      in_quotes = true;
      quote_char = word.front();
      word = word.substr(1);
    }

    if (in_quotes && (back == quote_char)) {
      in_quotes = false;
      word.pop_back();
    }

    if (!echo_output.empty())
      echo_output += " ";
    echo_output += word;
  }
  cout << echo_output << endl;
}

void type_cmd(vector<string> tokens) {
  bool found = false;
  string input = tokens[1];
  if (DEFAULT_COMMANDS.find(input) != DEFAULT_COMMANDS.end()) {
    found = true;
    cout << input << " is a shell builtin\n";
  } else {
    string path = get_path(input, PATH_ENV);
    if (path.empty())
      cout << input << ": not found\n";
    else
      cout << input << " is " << path << endl;
  }
}
