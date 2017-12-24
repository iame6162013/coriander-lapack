
#include "coriander-lapack/clLapack_source_code.h"
#include <fstream>





std::string getFloatPotrfSourceCode(){
	std::ifstream floatPotrfSourceCode("~/coriander/kernels/floatPotrfSourceCode.cl");
	std::string src(std::istreambuf_iterator<char>(floatPotrfSourceCode), std::istreambuf_iterator<char>);

	return src;
}
