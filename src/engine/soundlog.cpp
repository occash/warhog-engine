#include "soundlog.h"
#include <stdio.h>
void err_check(FMOD_RESULT result, char *file, int line)
{
    if (result != FMOD_OK)
        printf("FMOD error! file:%s line:%d  %s\n", file, line, FMOD_ErrorString(result));
}
