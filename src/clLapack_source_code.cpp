
#include "coriander-lapack/clLapack_source_code.h"
#include <fstream>





std::string getFloatPotrfSourceCode(){
	std::ifstream floatPotrfSourceCode("~/coriander/kernels/floatPotrfSourceCode.cl");
	if(floatPotrfSourceCode){
		std::string src;
		floatPotrfSourceCode.seekg(0, td::ios::end);
		src.resize(floatPotrfSourceCode.tellg());
		floatPotrfSourceCode.seekg(0, std::ios::beg);

		floatPotrfSourceCode.read(&src[0], src.size());
		return src;
	}
	throw("floatPotrfSourceCode not found!");
}
