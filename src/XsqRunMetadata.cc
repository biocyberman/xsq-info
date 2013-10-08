// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include <cstdint>
#include <utility>
#include <iomanip>
#include <stdexcept>
#include "XsqRunMetadata.hh"


namespace Xsq {
	const std::vector<std::pair<std::string, XsqRunMetadata::Attr_t>> 
		XsqRunMetadata::s_attrs_names = {
			std::make_pair("AnalysisSoftware", STRING),
			std::make_pair("InstrumentVendor", STRING),
			std::make_pair("InstrumentModel", STRING),
			std::make_pair("InstrumentSerial", STRING),
			std::make_pair("InstrumentName", STRING),
			std::make_pair("LaneNumber", INTEGER),
			std::make_pair("RunName", STRING),
			std::make_pair("ProjectName", STRING),
			std::make_pair("SequencingSampleName", STRING),
			std::make_pair("SequencingSampleDescription", STRING),
			std::make_pair("LibraryType", STRING),
			std::make_pair("LibraryName", STRING),
			std::make_pair("RunStartTime", STRING),
			std::make_pair("RunEndTime", STRING),
			std::make_pair("Operator", STRING)
		};


	std::ostream& operator<<(std::ostream& o, const XsqRunMetadata& metadata) {
		o << "[RunMetaData]\n\n";
		for (const std::pair<std::string, XsqRunMetadata::Attr_t> &p: metadata.s_attrs_names)
			o << std::setw(28) << p.first << ": " << metadata.m_attrs_values.find(p.first)->second << std::endl;
		return o;
	}


	XsqRunMetadata::XsqRunMetadata(H5::H5File &file) {
		load(file);
	}


	/* function load
	 * It will load some metadata from the group of the file
	 * \param[in] path
	 */
	void XsqRunMetadata::load(H5::H5File& file) {
		H5::Group group = file.openGroup("RunMetadata");

		// load attributes
		for (const auto &a : s_attrs_names) { // <name, type>
			try {
				const H5::Attribute& attr = group.openAttribute(a.first);

				if (a.second == XsqRunMetadata::INTEGER) {
					std::uint8_t i;
					attr.read(attr.getDataType(), &i);
					m_attrs_values[a.first] = std::to_string((int) i);

				} else { // XsqRunMetadata::STRING
					std::string s;
					attr.read(attr.getDataType(), s);
					m_attrs_values[a.first] = s == "" || s == " " ? "None" : s;
				}

			} catch (const H5::Exception& e) {
				m_attrs_values[a.first] = "Unknown";
			}
		}

		group.close();
	}


	/* function get_attr
	 * \param[in] attr_name
	 * \return Return the value associated to the attribute
	 */
	std::string XsqRunMetadata::get_attr(const std::string& attr_name) const {
		std::map<std::string, std::string>::const_iterator it =
			m_attrs_values.find(attr_name);

		if (it == m_attrs_values.end())
			throw(std::invalid_argument(
						"Unkown or attribute '" + attr_name + "' not loaded"));

		return it->second;
	}

}
