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
    
    return 0;
    
  }else{

    cerr << "INSUFFICENT_NUMBER_OF_PARAMETERS (1)" << endl;
    return 1;

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

  return 0;

}

int Error_handler::check_character(char ch){

  if(ch < 65 || ch > 90){

    cerr << "INVALID_INPUT_CHARACTER (2)" << endl;
    return 2;

  }

  return 0;

}

int Error_handler::check_plugboard(const char* filename){

  int plugboard[NUM_LETTERS / 2];
  int count = load_data(filename, plugboard);

  if(count % 2 != 0){

    cerr << "INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS (6)" << endl;
    return 6;
    
  }

  for(int i = 0; i < count; i = i + 2){

    if(plugboard[i] == plugboard[i+1]){

      cerr << "IMPOSSIBLE_PLUGBOARD_CONFIGURATION (5)";
      return 5;

    }

    if((plugboard[i] < 0 || plugboard[i] > 25) || (plugboard[i+1] < 0 || plugboard[i+1] > 25)){

      cerr << "INVALID_INDEX (3)" << endl;
      return 3;
      
    }

  }

  for(int i = 0; i < count - 1; i++){

    for(int j = i + 1; j < count; j++){

      if(plugboard[i] == plugboard[j]){
	
      cerr << "IMPOSSIBLE_PLUGBOARD_CONFIGURATION (5)";
      return 5;

      } 
    }
  }
  
  return 0;

}

int Error_handler::check_reflector(const char* filename){

  int reflector[NUM_LETTERS];
  int count = load_data(filename, reflector);

  if(count  != NUM_LETTERS ){

    cerr << "INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS (10)" << endl;
    return 10;
    
  }

  for(int i = 0; i < count; i = i + 2){

    if(reflector[i] == reflector[i+1]){

      cerr << "INVALID_REFLECTOR_MAPPING (9)";
      return 9;

    }

    if((reflector[i] < 0 || reflector[i] > 25) || (reflector[i+1] < 0 || reflector[i+1] > 25)){

      cerr << "INVALID_INDEX (3)" << endl;
      return 3;
      
    }

  }

  for(int i = 0; i < count - 1; i++){

    for(int j = i + 1; j < count; j++){

      if(reflector[i] == reflector[j]){
	
	cerr << "IMPOSSIBLE_REFLECTOR_CONFIGURATION (5)";
	return 5;

      } 
    }
  }
  
  return 0;

}
