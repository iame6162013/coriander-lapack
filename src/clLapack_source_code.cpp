
#include "coriander-lapack/clLapack_source_code.h"
#include <fstream>





std::string getFloatPotrfSourceCode(){
	std::cout << "a" << std::endl;
	std::ifstream floatPotrfSourceCode("~/coriander/kernels/floatPotrfSourceCode.cl", std::ios::in);
	if(floatPotrfSourceCode){
		std::cout << "b" << std::endl;
		std::string src;
		floatPotrfSourceCode.seekg(0, std::ios::end);
		std::cout << "x" << std::endl;
		src.resize(floatPotrfSourceCode.tellg());
		std::cout << "g" << std::endl;
		floatPotrfSourceCode.seekg(0, std::ios::beg);

		std::cout << "t" << std::endl;
		floatPotrfSourceCode.read(&src[0], src.size());
		std::cout << "y" << std::endl;
		floatPotrfSourceCode.close();
		std::cout << "z" << std::endl;
		return src;
	}
	throw("floatPotrfSourceCode not found!");
}
