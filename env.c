#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
        if (env[i].key == NULL || !strcmp(env[i].key, name)) {
            env[i].key = strdup(name);
            env[i].value = strdup(value);
            return;
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

void print_env()
{
    for (int i = 0; i < MAX_ENV_SIZE; i++) {
        if (env[i].key) {
            printf("%s=%s\n", env[i].key, env[i].value);
        }
    }
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
