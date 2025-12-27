#ifndef H_TABLESPOON_OPTION
#define H_TABLESPOON_OPTION

#include "../tablespoon_errors.h"
#include "../tablespoon_structures.h" //for tablespoon_string type
#include <regex.h>                    //for regex_t type
#include <stdlib.h>                   //for size_t type
#include <string.h> //used in tablespoon_createoption() //used in tablespoon_createoption() //used in tablespoon_createoption() //used in tablespoon_createoption()

// define option type
typedef struct tablespoon_option {
  tablespoon_string key;
  regex_t value_rules; // regex to determine if the passed option is valid
  size_t value_min_count;
  size_t value_max_count;
  tablespoon_status* status;
} tablespoon_option;

// functions to allocate/deallocate mem for options on the heap
tablespoon_option *tablespoon_createoption(tablespoon_string key,
                                           regex_t value_rules,
                                           size_t value_min_count,
                                           size_t value_max_count,
                                           tablespoon_status_code *code);

void tablespoon_deleteoption(tablespoon_option *optionptr,
                             tablespoon_status_code *code);
#endif
