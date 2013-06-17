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

#ifndef LIBRARY_HH
#define LIBRARY_HH

#include "H5Cpp.h"
#include <string>
#include <vector>
#include "Tile.hh"
#include <map>

namespace Xsq 
{
	class Library
	{
	private:
		std::string m_complete_name;
		std::string m_sample_name;
		H5::Group m_group;

	public:
		Library(const std::string& name, const H5::Group& group);

		auto get_complete_name() const -> const std::string&
		{
			return m_complete_name;
		}

		auto get_sample_name() const -> const std::string&
		{
			return m_sample_name;
		}

		auto get_tiles() const -> std::vector<Tile>;

    std::map<std::string, unsigned int> get_nb_reads() const;
	};
}
#endif // LIBRARY_HH
