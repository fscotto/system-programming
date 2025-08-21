#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include <stdlib.h>

/* Block number under testing */
#define BLOCK_NUM 5

struct Stats {
	const char *allocator_type;
	size_t nr_allocations;
	double avg_alloc_time;
	double avg_free_time;
	double mem_usage_mb;
};

/* Print on STDOUT the memory stats collected */
void print_stats(struct Stats *);

/* Calculate arithmetic average */
double avg(double *, int size);

/* Read in the a Linux system at /proc/self/status file the RSS field */
double get_mem_usage();

#endif