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

#ifndef READS_HH
#define READS_HH

#include <cstdint>

namespace Xsq
{
	class Reads
	{
	private:
		uint8_t* m_data;
		unsigned m_nb_reads;
		unsigned m_reads_length;

	public:
		Reads(const H5::DataSet& reads_ds)
		{
			hsize_t color_call_qv_ds_dims[2];
			reads_ds.getSpace().getSimpleExtentDims(
				color_call_qv_ds_dims, NULL);

			m_nb_reads = color_call_qv_ds_dims[0];
			m_reads_length = color_call_qv_ds_dims[1];

			m_data = new uint8_t[m_nb_reads*m_reads_length];
			reads_ds.read(
				 m_data, H5::PredType::NATIVE_UINT8);
		};

		~Reads()
		{
			delete [] m_data;
		}

		uint8_t* get_read(unsigned read_id) const
		{
			return m_data + read_id*m_reads_length;
		}

		unsigned get_nb_reads() const
		{
			return m_nb_reads;
		}

		unsigned get_reads_length() const
		{
			return m_reads_length;
		}
	};
}

#endif // READS_HH
