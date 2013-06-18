// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include <cstdlib>
#include <iostream>
#include "XsqFile.hh"

using namespace std;
using namespace Xsq;


void no_more_memory() {
  cerr << "error: Memory allocation failed." << endl;
  exit(1);
}


int main(int argc, char **argv) {
	set_new_handler(no_more_memory);

  H5::Exception::dontPrint();

  try {
    XsqFile file(argv[1]);
    file.load_metadata();
    cout << "[xsqinfo v0.1] "; 
    cout << file;

  } catch (const H5::Exception& e) {
		cerr << e.getDetailMsg() << endl;
		exit(-1);

	} catch (const exception& e) {
		cerr << e.what() << endl;
		exit(-1);
	}

  return 0;
}
