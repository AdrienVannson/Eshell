#include <stdlib.h>
#include <string.h>

#include "env.h"

// The size of the environnement is limited
#define MAX_ENV_SIZE 1000

// The strings are allocated dynamically and must be freed
struct {
    char* key;
    char* value;
} env[MAX_ENV_SIZE];

void set_value_to_env(char* name, char *value)
{
    for (int i = 0; i < MAX_ENV_SIZE; i++) {
        if (env[i].key == NULL) {
            env[i].key = malloc((1 + strlen(name)) * sizeof(char));
            strcpy(env[i].key, name);

            env[i].value = malloc((1 + strlen(value)) * sizeof(char));
            strcpy(env[i].value, value);
        }
    }
}

char* get_value_from_env(char* name)
{
    for (int i = 0; i < MAX_ENV_SIZE; i++) {
        if (!strcmp(name, env[i].key)) {
            return env[i].value;
        }
    }
    return 0;
}

void free_env()
{
    for (int i = 0; i < MAX_ENV_SIZE; i++) {
        if (env[i].key != NULL) {
            free(env[i].key);
            free(env[i].value);
        }
    }
}
