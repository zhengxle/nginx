/*
 * =====================================================================================
 *
 *       Filename:  ngx_pool_t_test.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/08/13 20:16:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiaoliang (zxl), xiaoliang.zxl@taobao.com
 *        Company:  Taobao.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "ngx_config.h"
#include "ngx_conf_file.h"
#include "nginx.h"
#include "ngx_core.h"
#include "ngx_string.h"
#include "ngx_palloc.h"

volatile ngx_cycle_t *ngx_cycle;
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, ...)
{
}


void dump_pool(ngx_pool_t *pool)
{
	while (pool) {
		printf("pool = 0x%p\n", pool);
		printf("	.d\n");
		printf("		.last = 0x%p\n", pool->d.last);
		printf("		.end  = 0x%p\n", pool->d.end);
		printf("		.next = 0x%p\n", pool->d.next);
		printf("		.failed = %zu\n", pool->d.failed);
		printf("	.max = %zu\n", pool->max);
		printf("	.current = 0x%p\n", pool->current);
		printf("	.chain = 0x%p\n", pool->chain);
		printf("	.large = 0x%p\n", pool->large);
		printf("	.cleanup = 0x%p\n", pool->cleanup);
		printf("	.log = 0x%p\n", pool->log);
		printf("avaliable pool memory = %ld\n\n", pool->d.end - pool->d.last);
		pool = pool->d.next;
	}
}

int main()
{
	ngx_pool_t *pool;
	printf("--------------------------\n");
	printf("create a new pool:\n");
	printf("--------------------------\n");
	pool = ngx_create_pool(1024, NULL);
	dump_pool(pool);

	printf("--------------------------\n");
	printf("alloc block 1 from the pool:\n");
	printf("--------------------------\n");
	ngx_palloc(pool, 512);
	dump_pool(pool);

	printf("--------------------------------\n");
	printf("alloc block 2 from the pool:\n");
	printf("--------------------------------\n");
	ngx_palloc(pool, 512);
	dump_pool(pool);

	printf("--------------------------------\n");
	printf("alloc block 3 from the pool :\n");
	printf("--------------------------------\n");
	ngx_palloc(pool, 512);
	dump_pool(pool);

	ngx_destroy_pool(pool);
	return 0;
}
