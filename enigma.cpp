#include<iostream>
#include<fstream>
#include<vector>
#include"enigma.h"
#include"error_handler.h"
#include"errors.h"
#include<string>
#include<sstream>
#include"data_handler.h"

using namespace std;


Plug_board::Plug_board(){                                
   
  for(int i = 0; i < NUM_LETTERS; i++){
    wiring[i] = i;
  }
}
  
void Plug_board::setup_plug_board(const char* filename){
  
  int plugs[NUM_LETTERS];
  int number_of_plugs = 0;
  
  number_of_plugs = load_data(filename, plugs);
  
  for(int i = 0; i < number_of_plugs; i = i + 2){    // setups plugboard mapping
    
    wiring[plugs[i]] = plugs[i+1];                     
    wiring[plugs[i+1]] = plugs[i];
    
  }
}
  
int Plug_board::encrypt(int digit){
  
  return wiring[digit];
    
}
    

Reflector::Reflector(){
   
  for(int i = 0; i < NUM_LETTERS; i++){
    wiring[i] = i;
  }
   
}
  
void Reflector::setup_reflector(const char* filename){
    
  int plugs[NUM_LETTERS];
  int number_of_plugs = 0;
  
  number_of_plugs = load_data(filename, plugs);
  
  for(int i = 0; i < number_of_plugs; i = i + 2){
    
    wiring[plugs[i]] = plugs[i+1];
    wiring[plugs[i+1]] = plugs[i];
      
  }
}
  
int Reflector::encrypt(int digit){
  
  return wiring[digit];
    
}
  

    

Rotor::Rotor(const char* filename, int starting_position){
    
  int wiring_and_notches[NUM_LETTERS*2];
  int number_of_data_elements;
    
  number_of_data_elements = load_data_rotors(filename, wiring_and_notches); // loads wiring and notches data.
    
  for(int i = 0; i < NUM_LETTERS; i++){
      
    wiring[i][1] = wiring_and_notches[i];         //A letter enters wiring[i][1] when it comes from the right hand side. It contains a value to which the letter is mapped to. 
    wiring[wiring_and_notches[i]][0] = i;         //A letter enters wiring[i][0] when it comes from the left hand side. It contains a value to which the letter is mapped to. 
      
  }
    
  for(int i = NUM_LETTERS; i < number_of_data_elements; i++){
      
    notches.push_back(wiring_and_notches[i]);

  }

  number_of_rotations = starting_position;        //initial number of rotations is equal to the starting position.
  
}

int Rotor::encrypt_forwards(int digit){
  
  digit =  (digit + number_of_rotations) % NUM_LETTERS;      //Adjusts the  position at which the letter enters the rotor to the number of rotations.
  digit = (NUM_LETTERS + (wiring[digit][1] - (number_of_rotations % NUM_LETTERS))) % NUM_LETTERS; //Adjusts the postion at which the letter enters the next component 
  return digit;                                                                                   //to the number of rotations.
  
}

int Rotor::encrypt_backwards(int digit){
  
  digit = (digit + number_of_rotations) % NUM_LETTERS;
  digit = (NUM_LETTERS + (wiring[digit][0] - (number_of_rotations % NUM_LETTERS))) % NUM_LETTERS;
  
  return digit;
    
}

int Rotor::get_rotations_num(){
    
  return number_of_rotations;
    
}

void Rotor::rotate(){
    
  number_of_rotations++;
    
}

int Rotor::get_notches(int notches_array[]){

  for(auto notch_index = 0u; notch_index < notches.size(); notch_index++){
    
    notches_array[notch_index] = notches[notch_index];

  }
    
  return notches.size();
    
}



Enigma::Enigma(int number_of_files, char **files){    //constructor
   
  plug_board.setup_plug_board(files[1]);              
  reflector.setup_reflector(files[2]);
  
  if(error_handler.recognise_parameter(files[3]) == 2){     //Checks whether there is a least one rotor.
    
    int rotor_count = number_of_files - 4;
    int rotor_starting_positions[rotor_count];
    
    load_data_starting_positions(files[number_of_files - 1], rotor_starting_positions);
    
    for(int i = number_of_files - 2; i > 2; i--){
      
      rotors.push_back(Rotor(files[i], rotor_starting_positions[rotor_count - 1]));
      rotor_count --;

      rotor_exists = true; 
    }
    
  }
}

int Enigma::encrypt_character(int char_number){

  if(rotor_exists){                                                                        //rotors can only rotate if they exist.
  
    rotate_rotors();

  }
   
 
  int encrypted_char_number = plug_board.encrypt(char_number);                             //Letter ecnters a plugboard.

  if(rotor_exists){
    
    for(auto rotor_number = 0u; rotor_number < rotors.size(); rotor_number++){             //Encrypts by passing a letter from right to left if rotors exists.
	
      encrypted_char_number = rotors[rotor_number].encrypt_forwards(encrypted_char_number);
	
    }

  }

  encrypted_char_number = reflector.encrypt(encrypted_char_number);                         //Letter goes through the reflector.

  if(rotor_exists){
    
    for(int rotor_number = rotors.size()-1; rotor_number >= 0; rotor_number--){             //Encrypts by passing a letter from left to right if rotors exists.
	
      encrypted_char_number = rotors[rotor_number].encrypt_backwards(encrypted_char_number);
      
    }
  }
  
  return plug_board.encrypt(encrypted_char_number);                                          //Letter exits through the plugboard. 
     
}
  
bool Enigma::rotate_one_rotor(int right_rotor_position, int left_rotor_position){
  
  int right_rotor_notches[NUM_LETTERS];
  int right_rotor_rotations = rotors[right_rotor_position].get_rotations_num();
  int notches_num = rotors[right_rotor_position].get_notches(right_rotor_notches);

    
  for(int notch_index = 0; notch_index < notches_num; notch_index++){                        //Goes through notches of the rotor to the right and rotates rotor to its left if
                                                                                             //the notch is at the top position. 
    if(((right_rotor_notches[notch_index] + right_rotor_rotations) % NUM_LETTERS) == 0){
	
      rotors[left_rotor_position].rotate();
      
      return true;                                                                          //Returns true if rotor to the left rotates and false otherwise.
      
    }
  }
  return false;
}

void Enigma::rotate_rotors(){
    
  auto right_rotor_position = 0u;
  bool rotation_happened = true;
    
  rotors[0].rotate();                                                                        //The first rotor on the right, rotates every time the letter is passed.
    
  while(rotation_happened && (right_rotor_position < rotors.size() - 1)){                    //Goes through rotors from right to left. The function that check whether 
                                                                                               //a rotor should rotate only executes when a rotor on its right rotates.
    rotation_happened = rotate_one_rotor(right_rotor_position, right_rotor_position + 1);
    right_rotor_position++;
      
  }
}

void Enigma::encrypt_message(vector<char> &message){
  
 
  
  for(auto char_index = 0u; char_index < message.size(); char_index++){

    message[char_index] =  encrypt_character(message[char_index] - 65) + 65;                    //Converts a character to an integer when passed into the machine and  
                                                                                                //and back after the encryption using ASCII code.
  }
  
  
  
}
  
 
