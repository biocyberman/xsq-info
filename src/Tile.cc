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
  std::list<Tag> tags = get_tags();
  std::map<std::string, unsigned int> nb_reads;

  for (Tag t : tags)
    nb_reads[t.get_name()] = t.get_nb_reads();

  return nb_reads;
}

auto Tile::get_yxLocation() const -> YxLocation 
{
	const auto& fragments_group = m_group.openGroup("Fragments");
	const auto& yxLocation_ds = fragments_group.openDataSet("yxLocation");
	
	return YxLocation(yxLocation_ds);
}

const std::string Tile::s_reserved_name = "Fragments";
