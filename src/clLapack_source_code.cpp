
#include "coriander-solver/clLapack_source_code.h"


//TODO: put in actual source code -.-
std::string getFloatPotrfSourceCode(){
	return 	"void kernel simple_add(global const int* A, global const int* B, global int* C){"
            	"	C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];"
            	"}";
}
