#ifndef _HUGEIC_SDK_VER_H_
#define _HUGEIC_SDK_VER_H_
#include "svn_version.h"
#include "app_version.h"

#define SDK_MVER 1  /*sdk main version*/
#define SDK_BVER 6  /*sdk branch version*/
#define SDK_PVER 4  /*sdk patch version*/

#define SDK_VERSION (SDK_MVER<<24|SDK_BVER<<16|SDK_PVER<<8|PROJECT_TYPE)

#define __STR1__(R) #R
#define __STR2__(R) __STR1__(R)

//#define SVN_VERSION "xxxxxxx"
#ifndef SVN_VERSION
#error "SVN_VERSION not defined"
#endif
//#define APP_VERSION "xxxxxxx"
#ifndef APP_VERSION
#error "APP_VERSION not defined"
#endif

#define VERSION_SHOW() do{\
        printf("\r\n** hgSDK-v"__STR2__(SDK_MVER)"."__STR2__(SDK_BVER)"."__STR2__(SDK_PVER)"."__STR2__(PROJECT_TYPE)\
                "-"__STR2__(SVN_VERSION)", app-"__STR2__(APP_VERSION)", build time:"__DATE__" "__TIME__" **\n\r");\
    }while(0)
#endif
