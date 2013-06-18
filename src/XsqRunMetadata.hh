#ifndef XSQ_RUNMETADATA
#define XSQ_RUNMETADATA

// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include <H5Cpp.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>

namespace Xsq {
	
	class Xsq_RunMetaData {
		public:

			enum data_type {
				STRING, INTEGER
			};

			static const std::vector<std::pair<std::string, data_type>> s_attrs_names;
			std::map<std::string, std::string> m_attrs_values;

		public:
			Xsq_RunMetaData() {}
			Xsq_RunMetaData(H5::H5File&);
			~Xsq_RunMetaData() {}

			void load(H5::H5File&);
			std::string get_attr(const std::string&) const;

			friend std::ostream& operator<<(std::ostream&, const Xsq_RunMetaData&);
	};

}

#endif
