/*******************************************************************************
*
*  File Name : ft_errors.c
*
*  Purpose :
*
*  Creation Date : 22-10-13 16:28:16
*
*  Last Modified : 22-10-13 16:36:09
*
*  Created By :
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ft_errors.h"

void ft_print_error(const char *func, int line, char *msg)
{
    printf("%s:%d > error %s\n", func, line, msg);
    exit(EXIT_FAILURE);
}


