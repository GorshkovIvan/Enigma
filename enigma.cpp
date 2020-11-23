#include<iostream>
#include<fstream>
#include<vector>
#include"enigma.h"
#include"error_handler.h"
#include"errors.h"
#include<string>
#include<sstream>

using namespace std;

int load_data(const char* filename, int wiring[]){
    
  ifstream in_stream;
  string input;
  int count = 0;
  
  
  in_stream.open(filename);
  if(!in_stream){
    cout << "Failed!" << '\n';
   }
  
  while(in_stream >> input){
    
    for(auto i = 0u; i < input.length(); i++){
      
      if(!(isdigit(input[i]))){
	in_stream.close();
	return -4;
   
     }
    }

    stringstream ss(input);
    ss >> wiring[count];
    if(wiring[count] > 25 || wiring[count] < 0){
      in_stream.close();
      return -3;
    }
    
    ss.str("");
    
    if(count ==  NUM_LETTERS){
      
      in_stream.close();
      return -610;
      
    }
   
    count++;
    if(count > 1){
      for(int i = 0; i < count-1; i++){
	for(int j = 1; j < count - i; j++){
	  if(wiring[i] == wiring[i+j]){
	    in_stream.close();
	    return -59;
	    
	  }
	}
      }
    }
  }

  in_stream.close();
  cout << endl << count << endl;
  return count;
  
}

int load_data_rotors(const char* filename, int wiring[]){
    
  ifstream in_stream;
  string input;
  int count = 0;
  
  
  in_stream.open(filename);
  if(!in_stream){
    cout << "Failed!" << '\n';
   }
  
  while(in_stream >> input){
    
    for(auto i = 0u; i < input.length(); i++){
      
      if(!(isdigit(input[i]))){
	in_stream.close();
	return -4;
   
     }
    }

    stringstream ss(input);
    ss >> wiring[count];
    if(wiring[count] > 25 || wiring[count] < 0){
      in_stream.close();
      return -3;
    }
    
    ss.str("");
    count++;
    
  }

  in_stream.close();

  return count;
  
}

void read_message(const char* filename, char message[]){
  
  ifstream in_stream;

  in_stream.open(filename);
  if(!in_stream){
    cout << "Failed!" << '\n';
   }
  
  int count = 0;
  char ch;
  while(!in_stream.eof()){
    in_stream.get(ch);
    if(ch > 64 && ch <91){
      message[count] = ch;
      count++;
    }
   }
  
  message[count] = '\0';
  in_stream.close();
  
}

Plug_board::Plug_board(){
   
    for(int i = 0; i < NUM_LETTERS; i++){
      wiring[i] = i;
    }
}
  
void Plug_board::setup_plug_board(const char* filename){
    
  int plugs[NUM_LETTERS];
  int number_of_plugs = 0;
  
  number_of_plugs = load_data(filename, plugs);
  
  for(int i = 0; i < number_of_plugs; i = i + 2){
    wiring[plugs[i]] = plugs[i+1];
    wiring[plugs[i+1]] = plugs[i];
    }
  }
  
int Plug_board::encrypt(int digit){
    return wiring[digit];
  }
  
void Plug_board::print_plug_board(){
   for(int i = 0; i < NUM_LETTERS; i++){
     cout << wiring[i] <<" ";
    }
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
  
void Reflector::print_reflector(){
   for(int i = 0; i < NUM_LETTERS; i++){
     cout << wiring[i] <<" ";
    }
}
    

Rotor::Rotor(const char* filename, int starting_position){
    
    int wiring_and_notches[NUM_LETTERS*2];
    int number_of_data_elements;
    
    number_of_data_elements = load_data_rotors(filename, wiring_and_notches);
    
    for(int i = 0; i < NUM_LETTERS; i++){
      
      wiring[i][1] = wiring_and_notches[i];
      wiring[wiring_and_notches[i]][0] = i;
      
    }
    
    for(int i = NUM_LETTERS; i < number_of_data_elements; i++){
      
      notches.push_back(wiring_and_notches[i]);

    }

    number_of_rotations = starting_position; 
  
  }

int Rotor::encrypt_forwards(int digit){
    
    digit =  (digit + number_of_rotations) % NUM_LETTERS;
    digit = (NUM_LETTERS + (wiring[digit][1] - (number_of_rotations % NUM_LETTERS))) % NUM_LETTERS;
    return digit;
    
  }

int Rotor::encrypt_backwards(int digit){
    
    digit =  (digit + number_of_rotations) % NUM_LETTERS;
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

  
void Rotor::print_rotor(){
  
    for(int i = 0; i < NUM_LETTERS; i++){
      cout << endl;
      for(int j = 0; j < 2; j++){
	cout << wiring[i][j] << "  ";
      }
      
    }
    /*
    cout << endl;
    cout << "rotations " << number_of_rotations;
    cout << endl;
    */
}

Enigma::Enigma(int number_of_files, char **files){
   
    plug_board.setup_plug_board(files[1]);
    reflector.setup_reflector(files[2]);

    if(error_handler.recognise_parameter(files[3]) == 2){
      
      int rotor_count = number_of_files - 4;
      int rotor_starting_positions[rotor_count];
    
      load_data(files[number_of_files - 1], rotor_starting_positions);
    
      for(int i = number_of_files - 2; i > 2; i--){
      
	rotors.push_back(Rotor(files[i], rotor_starting_positions[rotor_count - 1]));
	rotor_count --;

	rotor_exists = true;
    }

    }
}
int Enigma::encrypt_character(int char_number){

  if(rotor_exists){
  
    rotate_rotors();

  }
   
  //  cout << "pb output" << endl;
  int encrypted_char_number = plug_board.encrypt(char_number);
  /* 
      cout << endl;
      cout << encrypted_char_number;
      cout << endl;
      cout << "rotors output";
      cout << endl;
  */
  if(rotor_exists){
    
      for(auto rotor_number = 0u; rotor_number < rotors.size(); rotor_number++){
	
	encrypted_char_number = rotors[rotor_number].encrypt_forwards(encrypted_char_number);
	/*
	cout << endl;
	cout << encrypted_char_number;
	cout << endl;
	*/  
      }

  }
      /*
      cout << "reflector output" << endl;
      */
      encrypted_char_number = reflector.encrypt(encrypted_char_number);
      /*
      cout << encrypted_char_number;
      cout << endl;
      cout << "rotors output";
      cout << endl;
      */

      if(rotor_exists){
	for(int rotor_number = rotors.size()-1; rotor_number >= 0; rotor_number--){
	
	  encrypted_char_number = rotors[rotor_number].encrypt_backwards(encrypted_char_number);
	/*
	cout << endl;
	cout << encrypted_char_number;
	cout << endl;
	*/  
	}
      }
      return plug_board.encrypt(encrypted_char_number);
     
}
  
bool Enigma::rotate_one_rotor(int right_rotor_position, int left_rotor_position){
  
    int right_rotor_notches[NUM_LETTERS];
    int right_rotor_rotations = rotors[right_rotor_position].get_rotations_num();
    int notches_num = rotors[right_rotor_position].get_notches(right_rotor_notches);

    
    for(int notch_index = 0; notch_index < notches_num; notch_index++){
      
      if(((right_rotor_notches[notch_index] + right_rotor_rotations) % NUM_LETTERS) == 0){
	
	rotors[left_rotor_position].rotate();
	
	return true;
	
      }
    }
    return false;
  }

void Enigma::rotate_rotors(){
    
    auto right_rotor_position = 0u;
    bool rotation_happened = true;
    
    rotors[0].rotate();
    
    while(rotation_happened && (right_rotor_position < rotors.size() - 1)){
      
      rotation_happened = rotate_one_rotor(right_rotor_position, right_rotor_position + 1);
      right_rotor_position++;
      
    }
  }

void Enigma::encrypt_message(vector<char> &message){
  
 
  
  for(auto char_index = 0u; char_index < message.size(); char_index++){

    message[char_index] =  encrypt_character(message[char_index] - 65) + 65;
    
  }
  
  
    
}
  
 
