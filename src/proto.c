#include <stdio.h>
#include <../inc/proto.h>

//to remove extra whitespaces 
void str_trim_lf (char* arr, int length) 
{
    int i;
    for (i = 0; i < length; i++) 
    {
        if (arr[i] == '\n') 
        {
            arr[i] = '\0';
            break;
        }
    }
}  

