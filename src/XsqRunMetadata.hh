#ifndef XSQ_RUNMETADATA_HH
#define XSQ_RUNMETADATA_HH

// (C) Copyright 2013 Florian Plaza Onate & Joel Poudroux
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include <H5Cpp.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>

namespace Xsq {
	
	class XsqRunMetadata {
		private:

			enum Attr_t {
				STRING, INTEGER
			};

			static const std::vector<std::pair<std::string, Attr_t>> s_attrs_names;
			std::map<std::string, std::string> m_attrs_values;

		public:
			XsqRunMetadata() {}
			XsqRunMetadata(H5::H5File&);
			~XsqRunMetadata() {}

			void load(H5::H5File&);
			std::string get_attr(const std::string&) const;

			friend std::ostream& operator<<(std::ostream&, const XsqRunMetadata&);
	};

}

#endif
