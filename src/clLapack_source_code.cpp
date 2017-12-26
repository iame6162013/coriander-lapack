
#include "coriander-lapack/clLapack_source_code.h"
#include <fstream>





std::string getFloatPotrfSourceCode(){
	std::string source_location = std::string(getenv("HOME")) + "/coriander/kernels/floatPotrfSourceCode.cl";
	std::ifstream floatPotrfSourceCode(source_location, std::ifstream::in);
	if(floatPotrfSourceCode){
		std::string src;
		floatPotrfSourceCode.seekg(0, std::ios::end);
		src.resize(floatPotrfSourceCode.tellg());
		floatPotrfSourceCode.seekg(0, std::ios::beg);

		floatPotrfSourceCode.read(&src[0], src.size());
		floatPotrfSourceCode.close();
		return src;
	}
	throw("floatPotrfSourceCode not found!");
}
