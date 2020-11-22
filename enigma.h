#ifndef ENIGMA_H
#define ENIGMA_H

#include<vector>
#include"error_handler.h"

constexpr int NUM_LETTERS = 26;
constexpr int MAX_FILE_NUMBER = 80;
constexpr int MAX_WORD_LENGTH = 80;

int load_data(const char* filename, int wiring[]);

void read_message(const char* filename, char message[]);

class Plug_board{
  int wiring[NUM_LETTERS];
  
public:
    
  Plug_board();
 
  void setup_plug_board(const char* filename);
  
  int encrypt(int digit);
  
  void print_plug_board();
    
};

class Reflector{
  int wiring[NUM_LETTERS];
  int number_of_wirings;
  
public:
  
  Reflector();
  
  void setup_reflector(const char* filename);
  
  int encrypt(int digit);
  
  void print_reflector();
    
};

class Rotor{
  
  int wiring[NUM_LETTERS][2];
  std::vector<int> notches;
  int number_of_rotations;
  
public:
 
  Rotor(const char* filename, int starting_position);

  int encrypt_forwards(int digit);

  int encrypt_backwards(int digit);

  int get_rotations_num();

  void rotate();

  int get_notches(int notches_array[]);

  void print_rotor();
  
};

class Enigma{
  Error_handler error_handler;
  bool rotor_exists = false;
  
  
public:
  
  std::vector<Rotor> rotors;
  Reflector reflector;
  Plug_board plug_board;
  
  Enigma(int number_of_files, char **files);
  
  int encrypt_character(int char_number);
  
  bool rotate_one_rotor(int right_rotor_position, int left_rotor_position);

  void rotate_rotors();

  void encrypt_message(std::vector<char> &message);
  
};
#endif
