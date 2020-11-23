#include<iostream>
#include"error_handler.h"
#include"enigma.h"
#include"errors.h"

using namespace std;

int Error_handler::check_parameters(int argc, char** argv){
  
  int plugboard_counter = 0;
  int rotor_counter = 0;
  int reflector_counter = 0;
  int positions_counter = 0;
  
  for(int file_position = 1; file_position < argc; file_position++){

    switch(recognise_parameter(argv[file_position])){

       case 0:
	 cerr <<  "INCOREECT FILENAME";
	 return 11;

       case 1:
	 plugboard_counter++;
	 break;

       case 2:
	 rotor_counter++;
	 break;

       case 3:
	 reflector_counter++;
	 break;

       case 4:
	 positions_counter++;
	 
    }
    
  }


  if(plugboard_counter == 1 && reflector_counter == 1 && positions_counter == 1){
    
    return NO_ERROR;
    
  }else{

    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;

  }
  
}

int Error_handler::recognise_parameter(const char* filename){

  int char_count = 0;

  while(filename[char_count] != '\0'){

    char_count++;

  }

  if(filename[char_count - 3] == '.' && filename[char_count - 2] == 'p' && filename[char_count - 1] == 'b')

    return 1;


  if(filename[char_count - 4] == '.' && filename[char_count - 3] == 'r' && filename[char_count - 2] == 'o' && filename[char_count - 1] == 't')

    return 2;


  if(filename[char_count - 3] == '.' && filename[char_count - 2] == 'r' && filename[char_count - 1] == 'f')

    return 3;


  if(filename[char_count - 4] == '.' && filename[char_count - 3] == 'p' && filename[char_count - 2] == 'o' && filename[char_count - 1] == 's')

    return 4;

  return NO_ERROR;

}

int Error_handler::check_character(char &ch){

  if(ch < 65 || ch > 90){

    if(ch > 47 && ch < 58)
      ch = ch + 17;
    
    
    if(ch > 96 && ch < 123)
      ch = ch - 32;
    
    
    cerr << ch << " is not a valid input character (input characters must be upper case letters A-Z)!";
    return INVALID_INPUT_CHARACTER;

  }

  return NO_ERROR;

}

int Error_handler::check_plugboard(const char* filename){

  int plugboard[NUM_LETTERS];
  int count = load_data(filename, plugboard);

  if(count == -4){

    cerr << "Non-numeric character in plugboard file " << filename;
    return NON_NUMERIC_CHARACTER;
  }
 
  if(count == -59){
    
    cerr << "Incorrect number of parameters in plugboard file " << filename;
    return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  } 

  
  if(count == -3){

    cerr << "There is a number that is not between 0 and 25 in plugboard file " << filename; 
    return INVALID_INDEX;

  }

  if(count % 2 != 0 || count == -610){
    
    cerr << "Incorrect number of parameters in plugboard file "<< filename  << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    
  }
  
  return 0;

}

int Error_handler::check_reflector(const char* filename){

  int reflector[NUM_LETTERS];
  int count = load_data(filename, reflector);
 
  if(count == -4){

    cerr << "Non-numeric character in reflector file: " << filename;
    return NON_NUMERIC_CHARACTER;
    
  }
  
  if(count == -59){
    
    cerr << "Incrorrect reflector mapping in file " << filename;
    return INVALID_REFLECTOR_MAPPING;
  }

  if(count == -3){

    cerr << "There is a number that is not between 0 and 25 in reflector file " << filename; 
    return INVALID_INDEX;

  }
 
  if(count  != NUM_LETTERS || count == -610){
    
    if((count < NUM_LETTERS) && ((count % 2) == 0) && count != -610){
      
      cerr << "Insufficient number of mappings in reflector file " << filename;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
      
    }
    
    if(count %2 != 0){
      
      cerr << "Incorrect (odd) number of parameters in reflector file " << filename;
      
    }else{

      cerr << "Incorrect number of parameters in reflector file " << filename;
      
    }
    
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    
  }
  


  
  return NO_ERROR;

}
