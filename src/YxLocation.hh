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

#ifndef YX_LOCATION_HH
#define YX_LOCATION_HH

#include <cstdint>
#include <utility>

namespace Xsq
{
	class YxLocation
	{
	private:
		uint16_t* m_data;
		unsigned m_nb_locations;

	public:
		YxLocation(const H5::DataSet& yxLocation_ds)
		{
			hsize_t yxLocation_ds_dims[2];
			yxLocation_ds.getSpace().getSimpleExtentDims(
				yxLocation_ds_dims, NULL);

			m_nb_locations = yxLocation_ds_dims[0];

			m_data = new uint16_t[m_nb_locations*2];
			yxLocation_ds.read(
				m_data, H5::PredType::NATIVE_UINT16);
		};

		~YxLocation()
		{
			delete [] m_data;
		}

		auto get_location(unsigned i) const -> std::pair<uint16_t, uint16_t>
		{
			return std::make_pair(m_data[i*2], m_data[i*2+1]);
		}

		auto get_nb_locations() const -> unsigned
		{
			return m_nb_locations;
		}
	};
}

#endif // YX_LOCATION_HH
