#include <stdlib.h>

/**
 * getenv - Retrieve the value of an environment variable
 *
 * @name: The name of the environment variable to retrieve.
 *
 * Description:
 * The `getenv` function searches for an environment variable with the name
 * specified by `name` and returns its value as a string. If the variable
 * is found, the function returns a pointer to its value. If the variable
 * is not found, the function returns NULL.
 *
 * Return:
 * A pointer to the value of the environment variable, or NULL if the
 * variable does not exist.
 *
 * Example:
 * char *path;
 * path = getenv("PATH");
 * if (path != NULL) {
 *     printf("PATH: %s\n", path);
 * } else {
 *     printf("PATH environment variable not found.\n");
 * }
 *
 * Include:
 * #include <stdlib.h>
 */
char *getenv(const char *name);
