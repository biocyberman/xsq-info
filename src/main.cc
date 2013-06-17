/**
 * The MIT License
 * 
 * (C) Copyright 2013 Florian Plaza Oñate
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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
