#include "mem_utils.h"
#include <stdio.h>
#include <string.h>

void print_stats(struct Stats *stats)
{
	printf("Allocator: %s\nBlocks: %ld\nAvarage Allocation Time: %.2f "
	       "μs\nAvarage Free Time: %.2f μs\nPeak Memory Usage: %.2f MB\n",
	       stats->allocator_type, stats->nr_allocations,
	       stats->avg_alloc_time*1e6, stats->avg_free_time*1e6,
	       stats->mem_usage_mb);
}

double avg(double *values, int size)
{
	double sum = 0.0;
	for (int i = 0; i < size; i++) {
		sum += *(values + i);
	}
	return size > 0 ? sum / size : 0.0;
}

double get_mem_usage()
{
	FILE *fp = fopen("/proc/self/status", "r");
	if (!fp) {
		perror("fopen");
		return 1;
	}

  int found = 0;
	char line[256];
	while (fgets(line, sizeof(line), fp)) {
		if (strncmp(line, "VmRSS:", 6) == 0) {
      found = 1;
			break;
		}
	}
	fclose(fp);

  if (!found) {
    fprintf(stderr, "VmRSS not found in /proc/self/status\n");
    return 0.0;
  }

	return strtod(line + 6, NULL) / 1024.0;
}
