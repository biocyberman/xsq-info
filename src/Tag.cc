// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include "Tag.hh"
using namespace Xsq;

unsigned int Tag::get_nb_reads() const {
	const H5::DataSet& color_call_qv_ds = m_group.openDataSet("ColorCallQV");

	hsize_t color_call_qv_ds_dims[2];
	color_call_qv_ds.getSpace().getSimpleExtentDims(
			color_call_qv_ds_dims, NULL);

	return color_call_qv_ds_dims[0];
}

const std::map<std::string, char> Tag::s_tags_start =
{{"F3", 'T'},{"F5-DNA", 'T'},{"R3", 'G'}};
