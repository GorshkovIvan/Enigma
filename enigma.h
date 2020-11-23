#ifndef ENIGMA_H
#define ENIGMA_H

#include<vector>
#include"error_handler.h"

constexpr int NUM_LETTERS = 26;

int load_data(const char* filename, int wiring[]);
int load_data_rotors(const char* filename, int wiring[]);

/*Plugboard class replicates the functionality of Enigma plugboard. */

class Plug_board{
  int wiring[NUM_LETTERS]; // wiring array index represents the input letter and values represent letters to which the input is matched.
  
public:
  /*Plugboard() is a constructor that initialises a plugboard where each letter is wired to itself.*/
  Plug_board();
  
  /*setup_plug_board loads wiring data to wiring array from the input file*/
  void setup_plug_board(const char* filename);

  /*encrypt function takes a digit and returns a value that wiring array stores in index equl to digit*/
  int encrypt(int digit);
  
  void print_plug_board();
    
};


/*Reflector class replicates the functionality of Enigma reflector. */
class Reflector{
  int wiring[NUM_LETTERS];  // wiring array index represents the input letter and values represent letters to which the input is matched.
  int number_of_wirings;    
  
public:
   /*Reflector() is a constructor that initialises a reflector where each letter is wired to itself.*/
  Reflector();

   /*setup_reflector loads wiring data to wiring array from the input file*/
  void setup_reflector(const char* filename);

   /*encrypt function takes a digit and returns a value that wiring array stores in index equal to digit*/
  int encrypt(int digit);
  
  void print_reflector();
    
};

/*Rotor class replicates the functionality of Enigma rotor. It stores the wiring, notch positions and the number of rotations.*/
class Rotor{
  
  /*wiring[][0] and wiring[][1] store values that represent letters to which the input letters represented by array indecies are mapped.
    wiring[][1] is used when a letter is being passed from right to left between components and wiring[][0] from left to right.
    For example, when moving right to left, if a letter enters a rotor at position 2, it leaves at position stored in wiring[2][1] */
  
  int wiring[NUM_LETTERS][2]; 
  std::vector<int> notches; 
  int number_of_rotations;
  
public:

  /*Rotor function is a constructor, that uploads wiring, notches and a strating position from the iput file. 
    Starting position file is being read in the Enigma class. */ 
  Rotor(const char* filename, int starting_position);

  /*Ecrypts a letter when it is being passed from right to left.*/
  int encrypt_forwards(int digit);

  /*Ecrypts a letter when it is being passed from left to right.*/
  int encrypt_backwards(int digit);

  /*Outputs the number of rotations made.*/
  int get_rotations_num();

  /*Rotates a rotor by one position.*/
  void rotate();

  /*Outputs an array of notch positions*/
  int get_notches(int notches_array[]);

  void print_rotor();
  
};

/*Enigma class contains all components of Enigma and functions that encrypt the message.*/
class Enigma{
  
  Error_handler error_handler; 
  bool rotor_exists = false;  //false if rotor files were not provided
  std::vector<Rotor> rotors;  //Stores all rotors in a vector
  Reflector reflector;
  Plug_board plug_board;
 
  
public:
  
  /*Constructor that calls the constructors of all Enigma components and uploads data to them.*/
  Enigma(int number_of_files, char **files);

  /*Takes one character as an input and encrypts it.*/
  int encrypt_character(int char_number);

  /*Takes two neighboor rotors as argumaets and rotates one that locates on the left if the notch 
    of the right hand side rotor is reaches A position. Outputs True if the LHS rotor rotated.*/
  bool rotate_one_rotor(int right_rotor_position, int left_rotor_position);

  /*Rotates the first rotor on the right and uses rotate_one_rotor to rotate other rotors*/ 
  void rotate_rotors();

  /*Takes a message in a vector as input (passed by reference) and encrypts it character by character.*/
  void encrypt_message(std::vector<char> &message);
  
};
#endif
