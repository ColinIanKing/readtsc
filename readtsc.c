/*
 * Copyright (C) 2009-2020 Canonical
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *  Author Colin Ian King,  colin.king@canonical.com
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>
#include <sched.h>
#include <sys/types.h>

#define NAME "readtsc"

#if defined(__x86_64__) || defined(__x86_64) || \
    defined(__i386__)   || defined(__i386)
static inline uint64_t rdtsc(void)
{
	if (sizeof(long) == sizeof(uint64_t)) {
		uint32_t lo, hi;
        	asm volatile("rdtsc" : "=a" (lo), "=d" (hi));
		return ((uint64_t)(hi) << 32) | lo;
	} else {
		uint64_t tsc;
        	asm volatile("rdtsc" : "=A" (tsc));
		return tsc;
	}
}

int main(int argc, char **argv)
{
	uint64_t tsc;
	cpu_set_t set;
	long cpu = 0;
	long cpus = sysconf(_SC_NPROCESSORS_ONLN);

	if (argc > 1) {
		if (sscanf(argv[1], "%ld", &cpu) != 1)
			cpu = -1;

		if (cpu < 0 || cpu >= cpus) {
			fprintf(stderr, NAME ": cpu number was '%s', should be 0..%ld\n", argv[1], cpus - 1);
			exit(EXIT_FAILURE);
		}
		CPU_ZERO(&set);
		CPU_SET(cpu, &set);
		if (sched_setaffinity(getpid(), sizeof(set), &set) < 0) {
			fprintf(stderr, NAME ": sched_setaffinity failed: errno=%d (%s)\n",
				errno, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	cpu = sched_getcpu();
 	tsc = rdtsc();
	printf("0x%" PRIx64 " %" PRIu64 " (on cpu %ld)\n",tsc, tsc, cpu);

	exit(EXIT_SUCCESS);
}
#else
int main(int argc, char **argv)
{
	fprintf(stderr, "failed: only supported for x86 platforms\n");
	exit(EXIT_FAILURE);
}

#endif
