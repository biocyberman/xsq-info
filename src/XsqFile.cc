// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include "XsqFile.hh"
#include <iomanip>

namespace Xsq {

/**
 * Print RunMetaData information and the number of reads
 */
std::ostream& operator<<(std::ostream& o, const XsqFile& file)
{
	o << basename(file.m_path.c_str()) << "\n\n";
	o << file.m_metadata << '\n';

	o << "[Read size]\n";

	std::map<std::string, unsigned> read_size = file.get_used_tags_length();
	for (std::pair<std::string, unsigned> t : read_size)
		o << t.first << ": " << t.second << '\n';

	o << "\n[Number of reads]\n";

	std::map<std::string, unsigned> nb_reads = file.get_nb_reads();
	for (std::pair<std::string, unsigned> l : nb_reads)
		o << l.first << ": " << l.second << '\n';
}

/**
 * Method wich return the number of reads by libraries
 * The library name is prefixed by the tag name
 * Joel Poudroux
 */
std::map<std::string, unsigned int> XsqFile::get_nb_reads() const {
	std::map<std::string, unsigned int> sum_nb_reads;

	for (const Library& l: get_libraries()) {
		// foreach tag name
		for (const std::pair<std::string, unsigned>& t : l.get_nb_reads())
			sum_nb_reads[t.first + '_' + l.get_complete_name()] = t.second;
	}

	return sum_nb_reads;
}

/**
 * Method wich loads metadata in the XsqRunMetadata class
 */
void XsqFile::load_metadata() {
	m_metadata.load(m_file);
}

/**
 * Method which returns a list of all the libraries in this XsqFile
 * except those which are unclassified or unassigned.
 */
auto XsqFile::get_libraries() const -> std::vector<Library>
{
	std::vector<Library> libraries;

	for (unsigned library_id = 0; library_id < m_file.getNumObjs(); library_id++)
	{
		const auto& library_name = m_file.getObjnameByIdx(library_id);

		if (std::find_if(s_reserved_names.begin(), s_reserved_names.end(), StringPrefixComparator(library_name)) == s_reserved_names.end())
			libraries.push_back(Library(library_name, m_file.openGroup(library_name)));
	}

	return libraries;
}

/**
 * Method which returns a list of all the libraries in this XsqFile
 * whose name is prefixed by one of the elements in the prefixes_wanted list.
 */
auto XsqFile::get_libraries_by_prefix(const std::vector<std::string>& prefixes_wanted) const -> std::vector<Library>
{
	std::vector<Library> libraries;

	for (unsigned library_id = 0; library_id < m_file.getNumObjs(); library_id++)
	{
		const auto& library_name = m_file.getObjnameByIdx(library_id);

		if (std::find_if(prefixes_wanted.begin(), prefixes_wanted.end(), StringPrefixComparator(library_name)) != prefixes_wanted.end())
		{
			libraries.push_back(Library(library_name, m_file.openGroup(library_name)));
		}
	}

	return libraries;
}


/**
 * Method which returns a vector of all the tags used in this XsqFile.
 * e.g: 'F3', 'R3'
 */
auto XsqFile::get_used_tags_names() const -> std::vector<std::string> 
{
	const auto& run_metadata_group = m_file.openGroup("RunMetadata");
	const auto& tag_details_group = run_metadata_group.openGroup("TagDetails");

	hsize_t nb_tags = tag_details_group.getNumObjs(); 
	std::vector<std::string> used_tags_names(nb_tags);

	for (unsigned tag_id = 0; tag_id < nb_tags; tag_id++)
	{
		std::string tag_name = tag_details_group.getObjnameByIdx(tag_id);
		used_tags_names[tag_id] = tag_name;
	}

	return used_tags_names;
}

/**
 * Method which returns a map of all the tags used in this XSQ file and their respective read length.
 * e.g: 'F3', 'R3'
 */
std::map<std::string, unsigned> XsqFile::get_used_tags_length() const
{
	const auto& run_metadata_group = m_file.openGroup("RunMetadata");
	const auto& tag_details_group = run_metadata_group.openGroup("TagDetails");

	hsize_t nb_tags = tag_details_group.getNumObjs();
	std::map<std::string, unsigned> used_tags;

	for (unsigned tag_id = 0; tag_id < nb_tags; tag_id++)
	{
		// Get fragment name
		const auto tag_name = tag_details_group.getObjnameByIdx(tag_id);


		// Get fragment size
		// This is a NIGHTMARE!!
		const auto& tag_group = tag_details_group.openGroup(tag_name);
		const auto& ds_color_encoding = tag_group.openDataSet("DatasetColorEncoding");

		const H5::CompType ds_color_encoding_comp_type(ds_color_encoding);
		std::vector<unsigned char> ds_color_encoding_vector(ds_color_encoding.getStorageSize());
		ds_color_encoding.read(ds_color_encoding_vector.data(), ds_color_encoding_comp_type);

		unsigned num_color_calls_index = ds_color_encoding_comp_type.getMemberIndex("NumColorCalls");
		unsigned num_color_calls_offset = ds_color_encoding_comp_type.getMemberOffset(num_color_calls_index);
		unsigned num_color_calls = ds_color_encoding_vector[ num_color_calls_offset];


		used_tags[tag_name] = num_color_calls;
	}

	return used_tags;
}

/**
 * Groups which are not libraries or libraries which should not be extracted
 */
const std::vector<std::string> XsqFile::s_reserved_names =
{"RunMetadata","TagDetails","Indexing","Unassigned","Unclassified"};

}
