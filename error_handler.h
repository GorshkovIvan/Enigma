#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

/*Error handler class contains functions that check for errors and invalid input.
  All functions except recognise parameter, output error codes.*/
class Error_handler{

public:

  /*Runs all tests below*/
  int error_testing(int argc, char **argv);
  
  /*Checks that there is enough parameters */
  int check_parameters(int argc, char** argv);

  /*Recognises parameter by two or three letter at the end of file name.
    return an integer (see Error_handler.cpp) that is later use to recognise a file.*/ 
  int recognise_parameter(const char* filename);

  /*Checks that input character that needs to be encrypted is valid*/
  int check_character(char &ch);

  /*Checks validity of plugboard input file*/
  int check_plugboard(const char* filename);

   /*Checks validity of reflector input file*/
  int check_reflector(const char* filename);

  /*Checks validity of rotor input files*/
  int check_rotor(const char* filename);

   /*Checks validity of rotoe starting positions input file*/
  int check_starting_positions(const char* filename, int number_of_rotors);
  
};


#endif


  

  
