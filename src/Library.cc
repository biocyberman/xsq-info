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
std::map<std::string, unsigned int> Library::get_nb_reads() const {
  std::map<std::string, unsigned int> sum_nb_reads;
  std::vector<Tile> tiles = get_tiles();
  std::map<std::string, unsigned int> one_tile;

  // sum each nb_reads of each tiles
  for (Tile t : tiles) {
    one_tile = t.get_nb_reads();

    // foreach tag name
    for (std::pair<std::string, unsigned int> tag : one_tile)
      sum_nb_reads[tag.first] += tag.second;
  }
  
  return sum_nb_reads;
}
