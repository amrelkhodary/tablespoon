#ifndef H_TABLESPOON_ERRORS
    #define H_TABLESPOON_ERRORS
    #define TABLESPOON_ERROR_COUNT 7

    #include "./tablespoon_structures.h" //for tablespoon_string and tablespoon_bool
    #include <stdio.h>
    //define an error type as an enum of possible error codes
    typedef enum tablespoon_status_code {
        TABLESPOON_SUCCESSFUL,
        TABLESPOON_FAILED, //generic failed code, avoid using it unless absolutely necessary
        TABLESPOON_MEMORY_ERROR,
        TABLESPOON_INVALID_INPUT_NULL_VALUE, //passing an NULL to a func which expects non-NULL values
        TABLESPOON_INVALID_INPUT_DESTINATION_STDIN, //passing stdin to a func that does not expect stdin
        TABLESPOON_INVALID_INPUT_INPUT_ILLOGICAL, //passing args that dont make sense, e.g. having arg min_val > max_val
        TABLESPOON_OPTION_OBJ_DOES_NOT_EXIST, //passing NULL where func expects a pointer to tablespoon_option
        TABLESPOON_OPTION_OBJ_CORRUPT_NO_STATUS, //tablespoon option does not have a status obj inside it
    } tablespoon_status_code;

    //define status type
    typedef struct tablespoon_status {
        tablespoon_status_code code;
        tablespoon_string filename; //file where err occured
        tablespoon_string funcname; //func where err occured
        unsigned int linenum; //line where err occured
    } tablespoon_status;

    //pair every status code with a message
   extern tablespoon_string tablespoon_errmessages[TABLESPOON_ERROR_COUNT];

   //func declarations
   tablespoon_status_code tablespoon_printstatus(tablespoon_status* status, FILE* destination);
#endif
