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

#include <iostream>
#include <string>
#include <string.h>
#include <cstdint>
#include <vector>
#include <map>
#include <utility>
#include <iomanip>

#include "xsq_runmetadata.h"

using namespace std;

namespace Xsq {

const vector<pair<string, Xsq_RunMetaData::data_type>> 
      Xsq_RunMetaData::m_attrs = {

  make_pair("AnalysisSoftware", STRING),
  make_pair("InstrumentVendor", STRING),
  make_pair("InstrumentModel", STRING),
  make_pair("InstrumentSerial", STRING),
  make_pair("InstrumentName", STRING),
  make_pair("LaneNumber", INTEGER),
  make_pair("RunName", STRING),
  make_pair("ProjectName", STRING),
  make_pair("SequencingSampleName", STRING),
  make_pair("SequencingSampleDescription", STRING),
  make_pair("LibraryType", STRING),
  make_pair("LibraryName", STRING),
  make_pair("RunStartTime", STRING),
  make_pair("RunEndTime", STRING),
  make_pair("Operator", STRING)
};


ostream& operator<<(ostream &o, const Xsq_RunMetaData &metadata) {
  o << "[RunMetaData]" << endl << endl;
  for (const pair<string, Xsq_RunMetaData::data_type> &p: metadata.m_attrs)
    o << setw(28) << p.first << ": " << metadata.m_values.find(p.first)->second << endl;
}


Xsq_RunMetaData::Xsq_RunMetaData(H5::H5File &file) {
  load(file);
}


/* function load
 * It will load some metadata from the group of the file
 * \param[in] path
 */
void Xsq_RunMetaData::load(H5::H5File &file) {
  H5::Group group = file.openGroup("RunMetadata");

  // load attributes
  for (const auto &a : m_attrs) { // <name, type>
    try {
      H5::Attribute attr = group.openAttribute(a.first);

      if (a.second == Xsq_RunMetaData::INTEGER) {
        std::uint8_t i;
        attr.read(attr.getDataType(), &i);
        m_values[a.first] = std::to_string((int) i);

      } else { // Xsq_RunMetaData::STRING
        string s;
        attr.read(attr.getDataType(), s);
        m_values[a.first] = s == "" || s == " " ? "None" : s;
      }

    } catch (const H5::Exception& e) {
      m_values[a.first] = "Unknown";
    }
  }

  group.close();
}


/* function get_attr
 * \param[in] attr_name
 * \return Return the value associated to the attribute
 */
string Xsq_RunMetaData::get_attr(const string &attr_name) const {
  map<string, string>::const_iterator it;
  it = m_values.find(attr_name);

  if (it == m_values.end())
    throw(invalid_argument(
          "Unkown or attribute '" + attr_name + "' not loaded"));

  return it->second;
}

}
