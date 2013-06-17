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

#ifndef TILE_HH
#define TILE_HH

#include "H5Cpp.h"
#include "Tag.hh"
#include "YxLocation.hh"
#include <string>
#include <list>
#include <boost/algorithm/string/trim.hpp>


namespace Xsq
{
	class Tile
	{
	private:
		std::string m_name;
		H5::Group m_group;
		static const std::string s_reserved_name;

	public:
		Tile(const std::string& name, const H5::Group& group)
			: m_name(name), m_group(group)
		{
			boost::trim_left_if(m_name, boost::is_any_of("0"));
		};

		auto get_name() const -> const std::string&
		{
			return m_name;
		};

		auto get_tags() const -> std::list<Tag>;
    std::map<std::string, unsigned int> get_nb_reads() const;

		auto get_yxLocation() const -> YxLocation;
	};
}

#endif // TILE_HH
