#ifndef File_h
#define File_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include "Strings.h"

ecString ecExtractFileExtension(const char* filepath);

#ifdef __cplusplus
}
#endif

#endif /*File_h*/