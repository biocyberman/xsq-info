#ifndef XSQ_RUNMETADATA
#define XSQ_RUNMETADATA

// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

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
