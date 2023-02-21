#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define _WIN32_WINNT 0x0A00
#define MAXSIZE 1024
#define MAX_SHADOW_LEN 100
#define ITER_SIZE 255/(MAX_SHADOW_LEN*1.0)

#include "Windows.h"
#include "functions.h"