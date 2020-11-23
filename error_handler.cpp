#include<iostream>
#include"error_handler.h"
#include"enigma.h"
#include"errors.h"
#include"data_handler.h"

using namespace std;

int Error_handler::check_parameters(int argc, char** argv){
  
  int plugboard_counter = 0;
  int rotor_counter = 0;
  int reflector_counter = 0;
  int positions_counter = 0;
  
  /*Adds one a variable above if the file was found*/
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

  /*Return NO_ERROR if plugboard, reflector and position files were found.*/
  if(plugboard_counter == 1 && reflector_counter == 1 && positions_counter == 1){
    
    return NO_ERROR;
    
  }else{

    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;

  }
  
}

int Error_handler::recognise_parameter(const char* filename){

  int char_count = 0;

  /*Checks file name endings to recognise files.*/
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

  /*Checks whether a character is a capital letter using ASCII code"*/
  if(ch < 65 || ch > 90){

    cerr << ch <<" is not a valid input character (input characters must be upper case letters A-Z)!";

    return INVALID_INPUT_CHARACTER;

  }

  return NO_ERROR;
  
}

/*Uses output of a function stored in count to catch errors in plugboard file. */
int Error_handler::check_plugboard(const char* filename){
  
  int plugboard[NUM_LETTERS];
  int count = load_data(filename, plugboard); // returns a negative number if an error was caught, returns a positive number equal to the number of gathered digits,
                                              // if there was no error. All other member functions in this class work in a similar fashion.  
  if(count == -11){                          
    
    cerr << "Can't open plugboard file " << filename;
    return ERROR_OPENING_CONFIGURATION_FILE;

  }
  
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
  
  return NO_ERROR;

}

/*Uses output of a function stored in count to catch errors in reflector file. */
int Error_handler::check_reflector(const char* filename){

  int reflector[NUM_LETTERS];
  int count = load_data(filename, reflector);

   if(count == -11){
     
    cerr << "Can't open reflector file " << filename;
    return ERROR_OPENING_CONFIGURATION_FILE;

   }
  
  if(count == -4){

    cerr << "Non-numeric character in reflector file " << filename;
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
 
  if(count != NUM_LETTERS || count == -610){
    
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

/*Uses output of a function stored in count to catch errors in rotor files. */
int Error_handler::check_rotor(const char* filename){

  int wiring_and_notches[NUM_LETTERS*2];
  int count = load_data_rotors(filename, wiring_and_notches);

   if(count == -11){
     
    cerr << "Can't open rotor file " << filename;
    return ERROR_OPENING_CONFIGURATION_FILE;

  }
 
  
  if(count == -4){

    cerr << "Non-numeric character in rotor file " << filename;
    return NON_NUMERIC_CHARACTER;
    
  }

  if(count == -3){

    cerr << "There is a number that is not between 0 and 25 in rotor file " << filename; 
    return INVALID_INDEX;
    
  }

  if(count == -7){

    return INVALID_ROTOR_MAPPING;

  }

  if(count > 0 && count < NUM_LETTERS){

    cerr << "Not all inputs mapped in rotor file " << filename;
    return INVALID_ROTOR_MAPPING;

  }

  return NO_ERROR;

}

/*Uses output of a function stored in count to catch errors in starting positions file. */
int Error_handler::check_starting_positions(const char* filename, int number_of_rotors){

  int positions[number_of_rotors];
  int count = load_data_starting_positions(filename, positions);

   if(count == -11){
     
    cerr << "Can't open rotor starting positions file " << filename;
    return ERROR_OPENING_CONFIGURATION_FILE;

  } 
  
  if(count == -4){

    cerr << "Non-numeric character in rotor positions file " << filename;
    return NON_NUMERIC_CHARACTER;
    
  }

  if(count == -3){

    cerr << "There is a number that is not between 0 and 25 in rotor position file " << filename; 
    return INVALID_INDEX;
    
  }

  if(count >= 0 && count < number_of_rotors){
    
    cerr << "No starting position for rotor ";
    
    for(int i = 0; i < (number_of_rotors - count); i++){

      cerr << i << ", "; 

      }
    
    cerr << "in rotor position file " << filename;
      
    return NO_ROTOR_STARTING_POSITION;

  }

  return NO_ERROR;
}

int Error_handler:: error_testing(int argc, char **argv){

  int error_code;

  error_code = check_parameters(argc, argv);

  if(error_code != 0){
    
    return error_code;
    
  }

  error_code = check_plugboard(argv[1]);

  if(error_code != 0){
    
    return error_code;
    
  }

  error_code = check_reflector(argv[2]);

  if(error_code != 0){
    
    return error_code;
    
  }
  
  int file_position = 3;

  while(recognise_parameter(argv[file_position]) == 2){

    error_code = check_rotor(argv[file_position]);

    if(error_code != 0)
      return error_code;

    file_position++;

  }

  error_code = check_starting_positions(argv[file_position], file_position - 3);
  if(error_code != 0){

    return error_code;

  }

  return NO_ERROR;

}
