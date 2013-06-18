// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include <iostream>
#include "XsqFile.hh"

void no_more_memory() {
	std::cerr << "error: Memory allocation failed." << std::endl;
	std::exit(1);
}

int main(int argc, char **argv) {
	std::set_new_handler(no_more_memory);

	H5::Exception::dontPrint();

	try {
		Xsq::XsqFile file(argv[1]);
		file.load_metadata();
		std::cout << "[xsqinfo v0.1] "; 
		std::cout << file;

	} catch (const H5::Exception& e) {
		std::cerr << e.getDetailMsg() << std::endl;
		std::exit(-1);

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::exit(-1);
	}

	return 0;
}
