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

#ifndef XSQ_FILE_HH
#define XSQ_FILE_HH

#include "H5Cpp.h"
#include <iomanip>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#include <vector>
#include <list>
#include <map>
#include <string>
#include "Library.hh"
#include "StringPrefixComparator.hh"
#include "xsq_runmetadata.h"


namespace Xsq
{
	class XsqFile
	{
	private:
		H5::H5File m_file;
		fs::path m_path;
		static const std::vector<std::string> s_reserved_names;

    Xsq_RunMetaData m_metadata;

	public:
		XsqFile(const std::string& path)
			: m_file(path, H5F_ACC_RDONLY), m_path(path){};

		XsqFile()
		{}

		~XsqFile()
		{
			m_file.close();
		};

		auto get_path() const-> fs::path
		{
			return m_path;
		}

		auto get_libraries() const -> std::vector<Library>;
		auto get_libraries_by_prefix(const std::vector<std::string>&) const -> std::vector<Library>;
		auto get_used_tags_names() const -> std::vector<std::string>;
    std::map<std::string, unsigned> get_used_tags_length() const;
    void load_metadata();
    std::map<std::string, unsigned int> get_nb_reads() const;

    friend ostream & operator<<(ostream &, const XsqFile &);
	};
}

#endif // XSQ_FILE_HH
