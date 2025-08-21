#include "mem_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>

/* Run allocation benchmark using malloc */
struct Stats *bench_malloc();

/* Run allocation benchmark using calloc */
struct Stats *bench_calloc();

/* Run allocation benchmark using mmap */
struct Stats *bench_mmap();

typedef struct Stats *(*StatsFn)(void);

/* Memory blocks size to allocate for testing */
static size_t size_blocks[BLOCK_NUM] = {1024, 2048, 4096, 100000, 8192};

int main(int argc, char const *argv[])
{
	const StatsFn benchmarks[] = {bench_malloc, bench_calloc, bench_mmap};
	for (int i = 0; i < 3; i++) {
		StatsFn benchmark = benchmarks[i];
		struct Stats *result = benchmark();
		print_stats(result);
		free(result);
		printf("-------------------------------------------\n");
	}
	return 0;
}

struct Stats *bench_malloc()
{
	// Benchmark malloc function
	double peak_mem = 0.0;
	double m_elapsed_times[BLOCK_NUM] = {0};
	double f_elapsed_times[BLOCK_NUM] = {0};
	for (int i = 0; i < BLOCK_NUM; i++) {
		size_t size = size_blocks[i];
		struct timespec m_start, f_start, m_end, f_end;

		// malloc
		clock_gettime(CLOCK_MONOTONIC, &m_start);
		void *ptr = malloc(size);
		clock_gettime(CLOCK_MONOTONIC, &m_end);
		m_elapsed_times[i] = ((m_end.tv_sec - m_start.tv_sec) +
				      (m_end.tv_nsec - m_start.tv_nsec)) /
		    1e9;

		double curr_mem_usage = get_mem_usage();
		if (peak_mem <= curr_mem_usage) {
			peak_mem = curr_mem_usage;
		}

		// free
		clock_gettime(CLOCK_MONOTONIC, &f_start);
		free(ptr);
		clock_gettime(CLOCK_MONOTONIC, &f_end);
		f_elapsed_times[i] = ((f_end.tv_sec - f_start.tv_sec) +
				      (f_end.tv_nsec - f_start.tv_nsec)) /
		    1e9;
	}

	struct Stats *stats = (struct Stats *)malloc(sizeof(struct Stats));
	if (!stats) {
		perror("malloc");
		exit(1);
	}
	stats->allocator_type = "malloc";
	stats->nr_allocations = BLOCK_NUM;
	stats->avg_alloc_time = avg(m_elapsed_times, BLOCK_NUM);
	stats->avg_free_time = avg(f_elapsed_times, BLOCK_NUM);
	stats->mem_usage_mb = peak_mem;
	return stats;
}

struct Stats *bench_calloc()
{
	// Benchmark malloc function
	double peak_mem = 0.0;
	double m_elapsed_times[BLOCK_NUM] = {0};
	double f_elapsed_times[BLOCK_NUM] = {0};
	for (int i = 0; i < BLOCK_NUM; i++) {
		size_t size = size_blocks[i];
		struct timespec m_start, f_start, m_end, f_end;

		// malloc
		clock_gettime(CLOCK_MONOTONIC, &m_start);
		void *ptr = calloc(1, size);
		clock_gettime(CLOCK_MONOTONIC, &m_end);
		m_elapsed_times[i] = ((m_end.tv_sec - m_start.tv_sec) +
				      (m_end.tv_nsec - m_start.tv_nsec)) /
		    1e9;

		double curr_mem_usage = get_mem_usage();
		if (peak_mem <= curr_mem_usage) {
			peak_mem = curr_mem_usage;
		}

		// free
		clock_gettime(CLOCK_MONOTONIC, &f_start);
		free(ptr);
		clock_gettime(CLOCK_MONOTONIC, &f_end);
		f_elapsed_times[i] = ((f_end.tv_sec - f_start.tv_sec) +
				      (f_end.tv_nsec - f_start.tv_nsec)) /
		    1e9;
	}

	struct Stats *stats = (struct Stats *)malloc(sizeof(struct Stats));
	if (!stats) {
		perror("malloc");
		exit(1);
	}
	stats->allocator_type = "calloc";
	stats->nr_allocations = BLOCK_NUM;
	stats->avg_alloc_time = avg(m_elapsed_times, BLOCK_NUM);
	stats->avg_free_time = avg(f_elapsed_times, BLOCK_NUM);
	stats->mem_usage_mb = peak_mem;
	return stats;
}

struct Stats *bench_mmap()
{
	// Benchmark malloc function
	double peak_mem = 0.0;
	double m_elapsed_times[BLOCK_NUM] = {0};
	double f_elapsed_times[BLOCK_NUM] = {0};
	for (int i = 0; i < BLOCK_NUM; i++) {
		size_t size = size_blocks[i];
		struct timespec m_start, f_start, m_end, f_end;

		// malloc
		clock_gettime(CLOCK_MONOTONIC, &m_start);
		void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
				 MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		clock_gettime(CLOCK_MONOTONIC, &m_end);
		m_elapsed_times[i] = ((m_end.tv_sec - m_start.tv_sec) +
				      (m_end.tv_nsec - m_start.tv_nsec)) /
		    1e9;

		double curr_mem_usage = get_mem_usage();
		if (peak_mem <= curr_mem_usage) {
			peak_mem = curr_mem_usage;
		}

		// free
		clock_gettime(CLOCK_MONOTONIC, &f_start);
		munmap(ptr, size);
		clock_gettime(CLOCK_MONOTONIC, &f_end);
		f_elapsed_times[i] = ((f_end.tv_sec - f_start.tv_sec) +
				      (f_end.tv_nsec - f_start.tv_nsec)) /
		    1e9;
	}

	struct Stats *stats = (struct Stats *)malloc(sizeof(struct Stats));
	if (!stats) {
		perror("malloc");
		exit(1);
	}
	stats->allocator_type = "mmap";
	stats->nr_allocations = BLOCK_NUM;
	stats->avg_alloc_time = avg(m_elapsed_times, BLOCK_NUM);
	stats->avg_free_time = avg(f_elapsed_times, BLOCK_NUM);
	stats->mem_usage_mb = peak_mem;
	return stats;
}
