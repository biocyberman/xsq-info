// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include "Tile.hh"
using namespace Xsq;

auto Tile::get_tags() const -> std::list<Tag>
{
	std::list<Tag> tags;

	for (unsigned tag_id = 0; tag_id < m_group.getNumObjs(); tag_id++)
	{
		const auto& tile_name = m_group.getObjnameByIdx(tag_id);

		if (tile_name != s_reserved_name)
			tags.push_back(Tag(tile_name, m_group.openGroup(tile_name)));
	}
	
	return tags;
}

/**
 * Method wich return the nb of reads for each tag name
 */
std::map<std::string, unsigned int> Tile::get_nb_reads() const {
	std::map<std::string, unsigned int> nb_reads;

	for (const Tag& t : get_tags())
		nb_reads[t.get_name()] = t.get_nb_reads();

	return nb_reads;
}

const std::string Tile::s_reserved_name = "Fragments";
