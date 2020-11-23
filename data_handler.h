#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

/*Output of data extraction functions is used in enigma.cpp and error_handler.cpp 
 Error handler uses them to catch errors. They output a negative integer when an
 error was caught. This output is checked by an error_handler, when functions
 are called there. They return the number of extracted integers, if there was no error.  */

/*load_data is used to extract data for a plugboard and a reflector.  */
int load_data(const char* filename, int wiring[]);

/*load_data_rotors is used to extract data for rotors.  */
int load_data_rotors(const char* filename, int wiring[]);

/*load_data_rotors is used to extract data for rotor starting positions.  */
int load_data_starting_positions(const char* filename, int positions[]);
 
#endif 
