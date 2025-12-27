#include "../../headers/options/tablespoon_options.h"

/*
    function
    what it does: allocates memory for a new tablespoon_option struct on the heap
    inputs: key (name of the option)
            value_rules (regex to specifiy rules about which values are allowed for option)
            value_min_count (min number of values to be associated with option)
            value_max_count (max number of values to be assoicated with option)
            *status (a pointer to a status variable to specify whether func ran successfully or not)
    returns: a pointer to the newly created tablespoon_option struct
    fails on (handled, responsibilty on program): memory allocation errors
    fails on (handled, responsibilty on user): status = null,
                                               key = null,
                                               len(key) < 1,
                                               min_count > max_count
*/
tablespoon_option *tablespoon_createoption(tablespoon_string key,
                                           regex_t value_rules,
                                           size_t value_min_count,
                                           size_t value_max_count,
                                           tablespoon_status_code *code) {
  // check that code is not null
  if (!code) {
    // TODO: create a function to handle null codes
  }

  // check that key is not null and that its has a length of at least one
  if (!key || strlen(key) < 1) {
      *code = TABLESPOON_INVALID_INPUT_NULL_VALUE;
      return NULL;
  }

  //check that min_count is smaller than or equal to max_count
  if(value_min_count > value_max_count) {
      *code= TABLESPOON_INVALID_INPUT_INPUT_ILLOGICAL;
      return NULL;
  }

  //TODO: sanity check regex_t value_rules

  //alloc mem for the new option
  tablespoon_option* opt = malloc(sizeof(tablespoon_option));
  if(!opt) {
      *code = TABLESPOON_MEMORY_ERROR;
      return NULL;
  }

  //alloc a new status obj for new option
  tablespoon_status* nstatus = malloc(sizeof(tablespoon_status));
  nstatus -> code = TABLESPOON_SUCCESSFUL; //any new object status is successful by default
  if(!nstatus) {
      *code = TABLESPOON_MEMORY_ERROR;
      free(opt);
      return NULL;
  }

  //assign attributes
  opt -> key = key;
  opt -> value_rules = value_rules;
  opt -> value_min_count = value_min_count;
  opt -> value_max_count = value_max_count;
  opt -> status = nstatus;

  //indicate success, return the new option
  *code = TABLESPOON_SUCCESSFUL;
  return opt;
}

/*
    function
    what it does: deallocates mem for tablespoon_option struct
    inputs: *optionptr (ptr to tablespoon_option struct)
            *status (ptr to status variable to indicate whether func ran successfully)
    returns: nothing
    fails on (handled, responsibility on user): status = null, optionptr = null
*/
void tablespoon_deleteoption(tablespoon_option* optionptr, tablespoon_status_code* code) {
    //check that status is not null
    if(!code) {
        //TODO: handle case where status is null
    }

    //check that optionptr is not null
    if(!optionptr) {
        *code = TABLESPOON_OPTION_OBJ_DOES_NOT_EXIST;
        return;
    }

    if(!optionptr -> status) {
        //status inside optionptr is somehow already deleted
        //therefore, option object is considered corrupt
        //notify user of this
        *code = TABLESPOON_OPTION_OBJ_CORRUPT_NO_STATUS;
        free(optionptr);
        return;
    }

    //free program allocated memory for option obj
    //user may set values inside option obj to ptrs to heap memory,
    //but that is HER responsiblity to free.
    //this func ONLY frees mem THIS program is responsible for allocating
    free(optionptr -> status);
    free(optionptr);
    *code = TABLESPOON_SUCCESSFUL;
}
