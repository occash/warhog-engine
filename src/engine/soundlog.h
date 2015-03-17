#ifndef SOUNDLOG_H
#define SOUNDLOG_H
#include <fmod/fmod_errors.h>
#include <windows.h>
void err_check(FMOD_RESULT result, char *file, int line);
#define ERRCHECK(_result) err_check(_result, __FILE__, __LINE__)
#endif