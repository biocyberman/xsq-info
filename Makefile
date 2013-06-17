#
# The MIT License
# 
# (C) Copyright 2013 Florian Plaza Oñate
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

EXEC = xsqinfo

CC = g++
CFLAGS = --std=c++0x -Wextra -O3 -march=native
BOOST_LIBS= -lboost_filesystem -lboost_system -lboost_program_options
HDF5_LIBS = -lhdf5_hl_cpp -lhdf5_cpp -lhdf5
LDFLAGS = $(BOOST_LIBS) $(HDF5_LIBS)

SRC_DIR = src
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJECTS = $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SRC))

.PHONY : clean

all: $(BUILD_DIR) $(EXEC) 

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS)  $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(EXEC) $(BUILD_DIR)

