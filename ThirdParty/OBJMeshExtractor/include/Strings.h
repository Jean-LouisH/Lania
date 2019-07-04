#ifndef String_h
#define String_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	char* data;
	uint64_t length;
	uint64_t capacity;
}ecString;

ecString ecNewString(const char* initialString);
void ecAppendCharToString(ecString* string, char character); 
uint64_t ecCountSubstrings(ecString* string, const char* text);
bool ecIsStringAndCharArrayTheSame(ecString* string, const char* text);
void ecClearString(ecString* string);
void ecFreeString(ecString* string);

#ifdef __cplusplus
}
#endif

#endif /*String_h*/
