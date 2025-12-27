#include "../headers/tablespoon_errors.h"

tablespoon_string tablespoon_errmessages[TABLESPOON_ERROR_COUNT] = {
    "tablespoon: successful",
    "tablespoon: failed",
    "tablespoon: memory error",
    "tablespoon: expected a non-null value",
    "tablespoon: did not expect stdin",
    "tablespoon: illogical input",
    "tablespoon: option object does not exist"

};

/*
    function
    what it does: print the err msg corresponding to a particular status code
                  to a specified destination
    inputs: tablespoon_status status (the code to print its cspng. err msg)
            FILE* destination (the file or stream to print to)
    returns: tablespoon_status (a status code indicating whether the fun ran
   successfully or not) fails on (handled, responsibility on user): null
   destination or stdin
*/
tablespoon_status_code tablespoon_printstatus(tablespoon_status *status,
                                              FILE *destination) {
  // check that destination is not null, and that it is not stdin
  if (!destination) {
    return TABLESPOON_INVALID_INPUT_NULL_VALUE;
  }
  if (destination == stdin) {
    return TABLESPOON_INVALID_INPUT_DESTINATION_STDIN;
  }

  // print the err msg corresponding to the status code
  // indicate function ran successfully
  printf("in %s, inside %s at line %u:\n\t\t%s\n", status->filename,
         status->funcname, status->linenum,
         tablespoon_errmessages[status->code]);
  return TABLESPOON_SUCCESSFUL;
}
