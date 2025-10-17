#pragma once

#include "CSTRpredefines.h"

#ifdef __CSTR_OK
# 	undef __CSTR_OK
#endif // defined(__CSTR_OK)

#if __STDC_VERSION__ >= CSTR_DEFAULT_C_STD

#include <stdbool.h>
#include <stdlib.h>

#define CSTR_NPOS 					-1
#define CSTR_SUCCESS				0
#define CSTR_FAIL					1
#define CSTR_FORCECAP_LIMIT			2

#ifdef CSTR_RECOMMENDED
# 	define CSTR_DYNAMIC_CAPACITY
# 	define CSTR_ENABLE_GET_RETURN
#   define CSTR_ENABLE_GET_CONST_RETURN
#endif // CSTR_RECOMMENDED

#define __CSTR_ALL_TYPES_CMP 

typedef struct
{
	/* PRIVILEGED INITIALIZERS ONLY */
	bool initialized; // Should not be touched except for inner functions, such as:
					  // cstr_init()
	
	/* OTHERS CAN GO HERE BELOW */

	char *data;

	bool forceCap;

	size_t len;
	size_t cap;
} CSTR;

CSTR cstr_init(void);

int cstr_initCopy(CSTR *_dest, const char *_src);
int cstr_destroy(CSTR *_str);
int cstr_set(CSTR *_str, const char *_data);
int cstr_add(CSTR *_str, const char *_suffix);
int cstr_substr(CSTR *_str, size_t _start, size_t _len);
int cstr_clear(CSTR *_str);
int cstr_upper(CSTR *_str);
int cstr_lower(CSTR *_str);
int cstr_insert(CSTR *_str, const char *_data, size_t _pos);
int cstr_reverse(CSTR *_str);
int cstr_replace(CSTR *_str, const char *_old, const char *_new);
int cstr_replaceAll(CSTR *_str, const char *_old, const char *_new);
int cstr_erase(CSTR *_str, int _pos, size_t _len);
int cstr_shrink(CSTR *_str, const size_t _len);
int cstr_fromInt(CSTR *_str, int _val);
int cstr_fromLong(CSTR *_str, long _val);
int cstr_fromFloat(CSTR *_str, float _val);
int cstr_fromDouble(CSTR *_str, double _val);
int cstr_fromHex(CSTR *_str, unsigned int _val);

size_t cstr_find(const CSTR *_str, const char *_find);
size_t cstr_findFrom(const CSTR *_str, const char *_find, size_t pos);

bool cstr_startsWith(CSTR _str, const char *_prefix);
bool cstr_endsWith(const CSTR _str, const char *_suffix);
bool cstr_comp(const CSTR _s1, const CSTR _s2);

const char *cstr_bool(const bool _bool);

#define __CSTR_OK

#ifdef __CSTR_OK
# 	ifdef CSTR_ENABLE_GET_RETURN
# 		define CSTR_GET_RETURN(_cstr, _call, ...) ((_call(&_cstr,  __VA_ARGS__)), _cstr)
# 	else
# 		define CSTR_GET_RETURN(_cstr, _call, ...)
# 	endif // defined(CSTR_ENABLE_GET_RETURN)

# 	ifdef CSTR_CONST_RETURN_USE_PTR_METHOD
# 		define CSTR_CONST_RETURN_PTR_METHOD ->
# 	else
# 		define CSTR_CONST_RETURN_PTR_METHOD .
# 	endif

# 	ifdef CSTR_ENABLE_GET_CONST_RETURN
#       define CSTR_GET_CONST_RETURN(_str, _call, ...) \
        ({ \
            CSTR tmpS; \
            cstr_initCopy(&tmpS, _str CSTR_CONST_RETURN_PTR_METHOD data); \
            _call(&tmpS, __VA_ARGS__); \
            tmpS; \
        })
# 	else
# 		define CSTR_GET_CONST_RETURN(_str, _call, ...)
# 	endif // defined(CSTR_ENABLE_GET_CONST_RETURN)
#endif // __CSTR_OK

#else
# 	error "Must use C11 as the minimum standard"
#endif // __STDC_VERSION__

