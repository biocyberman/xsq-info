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

#include "Tag.hh"
using namespace Xsq;

auto Tag::get_reads() const -> Reads
{
	H5::DataSet color_call_qv_ds = m_group.openDataSet("ColorCallQV");
	return Reads(color_call_qv_ds);
}

unsigned int Tag::get_nb_reads() const {
	H5::DataSet color_call_qv_ds = m_group.openDataSet("ColorCallQV");

  hsize_t color_call_qv_ds_dims[2];
  color_call_qv_ds.getSpace().getSimpleExtentDims(
    color_call_qv_ds_dims, NULL);

  return color_call_qv_ds_dims[0];
}

const std::map<std::string, char> Tag::s_tags_start =
	{{"F3", 'T'},{"F5-DNA", 'T'},{"R3", 'G'}};
