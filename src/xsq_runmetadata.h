/**
 * The MIT License
 * 
 * (C) Copyright 2013 Joel Poudroux
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

#ifndef XSQ_RUNMETADATA
#define XSQ_RUNMETADATA

#include <string>
#include <iostream>
#include <H5Cpp.h>
#include <map>
#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;

namespace Xsq {

class Xsq_RunMetaData {

  public:

    enum data_type {
      STRING, INTEGER
    };

    static const vector<pair<string, data_type>> m_attrs;
    map<string, string> m_values;

  public:
    Xsq_RunMetaData() {}
    Xsq_RunMetaData(H5::H5File &);
    ~Xsq_RunMetaData() {}

    void load(H5::H5File &);
    string get_attr(const string &) const;

    friend ostream & operator<<(ostream &, const Xsq_RunMetaData &);
};

}

#endif
