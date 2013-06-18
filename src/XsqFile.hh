#ifndef XSQ_FILE_HH
#define XSQ_FILE_HH

// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

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
#include "XsqRunMetadata.hh"


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

			friend std::ostream& operator<<(std::ostream&, const XsqFile&);
	};
}

#endif // XSQ_FILE_HH
