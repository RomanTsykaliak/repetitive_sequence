# makefile
# Copyright 2024 Roman Tsykaliak
#   This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#   This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#   You should have received a copy of the GNU General Public License
# along with this program.  If not, see
# <https://www.gnu.org/licenses/>. 
LIBS:= #atomic boost_locale boost_thread
INCLUDE:= #lib
override CXXFLAGS+=-Og -gdwarf-4 -DDEBUG -m64 \
-time -pipe -std=c++23 \
-Werror -Wall -Wextra -Wpointer-arith \
-Wstrict-overflow=3 -pedantic \
# -pthread #-fsanitize=thread -fcoroutines -fmodules-ts \
# -pg # gprof code.cpp gmon.out > gprof_analysis.out
LDLIBS+=$(LIBS:%=-l%)
LDFLAGS!=echo -n ${INCLUDE} | \
sed 's@\([[:alnum:]./_]\+\)@-L\1 -Wl,-rpath=\1@g';
TARGETS:=$(patsubst %.cpp,%,$(wildcard *.cpp))
.PHONY:all
ifneq "$(strip ${TARGETS})" ""
all:${TARGETS}
else
all:;@echo "Nothing to make!"
endif
.PHONY:clean
clean:
	-rm -f ${TARGETS}
