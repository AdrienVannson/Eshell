#ifndef ENV_H
#define ENV_H

void set_value_to_env(char* name, char *value);
char* get_value_from_env(char* name);

void print_env();

// Free the environnement
void free_env();

#endif // ENV_H
