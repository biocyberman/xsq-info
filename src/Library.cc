// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include "Library.hh"

using namespace Xsq;

Library::Library(const std::string& name, const H5::Group& group)
	: m_complete_name(name), m_group(group)
{
	const auto& sample_name_attribute = m_group.openAttribute("LibraryName");
	const auto& sample_name_type = sample_name_attribute.getDataType();
	sample_name_attribute.read(sample_name_type, m_sample_name);
}

auto Library::get_tiles() const -> std::vector<Tile> 
{
	std::vector<Tile> tiles;

	unsigned nb_tiles = m_group.getNumObjs();
	tiles.reserve(nb_tiles);
		
	for (unsigned tile_id = 0; tile_id < nb_tiles; tile_id++)
	{
		const auto& tile_name = m_group.getObjnameByIdx(tile_id);
		tiles.push_back(Tile(tile_name, m_group.openGroup(tile_name)));
	}
		
	return tiles;
}

/**
 * Method wich return the nb of reads for each tag name
 * Joel Poudroux
 */
std::map<std::string, unsigned int> Library::get_nb_reads() const
{
  std::map<std::string, unsigned int> sum_nb_reads;

  // sum each nb_reads of each tiles
  for (const Tile& t : get_tiles())
  {
    // foreach tag name
    for (const std::pair<std::string, unsigned int>& tag : t.get_nb_reads())
      sum_nb_reads[tag.first] += tag.second;
  }
  
  return sum_nb_reads;
}
