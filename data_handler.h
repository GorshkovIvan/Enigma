#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

int load_data(const char* filename, int wiring[]);

int load_data_rotors(const char* filename, int wiring[]);

int load_data_starting_positions(const char* filename, int positions[]);
 
#endif 
