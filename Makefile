#
# Copyright (C) 2009-2020 Canonical, Ltd.
# Copyright (C) 2020-2025 Colin Ian King
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#

BINDIR=/usr/bin

LDFLAGS += -static
CFLAGS += -O3

readtsc: readtsc.o
	$(CC) readtsc.o -o readtsc
	strip readtsc

clean:
	rm -f readtsc readtsc.o readtsc*snap

install: readtsc
	mkdir -p ${DESTDIR}${BINDIR}
	cp readtsc ${DESTDIR}${BINDIR}

