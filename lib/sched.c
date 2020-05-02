#include <env.h>
#include <pmap.h>
#include <printf.h>

/* Overview:
 *  Implement simple round-robin scheduling.
 *
 *
 * Hints:
 *  1. The variable which is for counting should be defined as 'static'.
 *  2. Use variable 'env_sched_list', which is a pointer array.
 *  3. CANNOT use `return` statement!
 */
/*** exercise 3.14 ***/
//int curtime = 0;
//int x = 0;
//struct Env* cur = NULL;
void sched_yield(void)
{   
	static int cur_time = 1;
	static int cur_index = 0;
	struct Env *e = NULL;
	int left = 0;
	cur_time--;
	if (cur_time <= 0 || curenv == NULL || curenv->env_status!=ENV_RUNNABLE) {
		left = 0;
		while(1) {
			if (LIST_EMPTY(&env_sched_list[cur_index])) {
				cur_index = !cur_index;
				break;
			}
			e = LIST_FIRST(&env_sched_list[cur_index]);
			if (e->env_status == ENV_RUNNABLE){
				left = 1;
				break;
			}
			LIST_REMOVE(e,env_sched_link);
			LIST_INSERT_HEAD(&env_sched_list[!cur_index],e,env_sched_link);
		}
		if (!left) {
			while(1) {
				if (LIST_EMPTY(&env_sched_list[cur_index])){
					break;
				}
				e = LIST_FIRST(&env_sched_list[cur_index]);
				if (e->env_status == ENV_RUNNABLE) {
					left = 1;
					break;
				}
				LIST_REMOVE(e,env_sched_link);
				LIST_INSERT_HEAD(&env_sched_list[!cur_index],e,env_sched_link);
			}
		}
		LIST_REMOVE(e, env_sched_link);
		LIST_INSERT_HEAD(&env_sched_list[!cur_index],e,env_sched_link);
		cur_time=e->env_pri;
		env_run(e);
	}
	env_run(curenv);
/*	static int x = 0;
	static int time_count = 0;
	static struct Env *e = NULL;
	static int i = 0;
	static int change = 0;
	if (change) {
		change = 0;
		e = NULL;
	}
	while(e == NULL || e->env_status != ENV_RUNNABLE) {
		LIST_FOREACH(e, &env_sched_list[x], env_sched_link) {
			if ((e->env_status == ENV_RUNNABLE) && (e->env_pri > 0)) {
				time_count = e->env_pri;
				break;
			}
		}
		if (e!=NULL) {
			break;
		}
		x = (x + 1) % 2;
	}
	time_count--;
	if (time_count <= 0) {
		LIST_REMOVE(e, env_sched_link);
		LIST_INSERT_HEAD(&env_sched_list[(x+1)%2], e, env_sched_link);
	}
	env_run(e);*/
/*	static int count = 0;
	static int t = 0;
	count++;
	if (curenv == NULL || count >= curenv->env_pri) {
		if (curenv != NULL) {
			LIST_INSERT_HEAD(&env_sched_list[1 - t], curenv, env_sched_link);
		}
		int flag = 0;
		while(1) {
			struct Env *e = LIST_FIRST(&env_sched_list[t]);
			if (e == NULL) {
				if (flag == 0) {
					flag = 1;
				} else {
					return;
				}
				t = 1 - t;
				continue;
			}
			if (e->env_status == ENV_RUNNABLE) {
				LIST_REMOVE(e, env_sched_link);
				count = 0;
				env_run(e);
				break;
			}
		}
	} else {
		env_run(curenv);
	}
	
//    static int curtime = 0; // remaining time slices of current env
//    static int x = 0; // current env_sched_list index
    

     * hint:
     *  1. if (count==0), insert `e` into `env_sched_list[1-point]`
     *     using LIST_REMOVE and LIST_INSERT_TAIL.
     *  2. if (env_sched_list[point] is empty), point = 1 - point;
     *     then search through `env_sched_list[point]` for a runnable env `e`, 
     *     and set count = e->env_pri
     *  3. count--
     *  4. env_run()
     *
     *  functions or macros below may be used (not all):
     *  LIST_INSERT_TAIL, LIST_REMOVE, LIST_FIRST, LIST_EMPTY
     */

//	static struct Env *cur = NULL;
//	cur = curenv;
	/*while (count == 0) {
		if (LIST_FIRST(&env_sched_list[point]) == NULL) {
			point = 1 - point;
		}
		cur = LIST_FIRST(&env_sched_list[point]);
		count = cur->env_pri;
		LIST_REMOVE(cur, env_sched_link);
		LIST_INSERT_TAIL(&env_sched_list[1 - point], cur, env_sched_link);
	}
	if (LIST_EMPTY(&env_sched_list[point])) {
		point = 1 - point;
		LIST_FOREACH(cur, &env_sched_list[point], env_sched_link) {
			if (cur->env_status == ENV_RUNNABLE) {
				count = cur->env_pri;
			}
		}
	}*/
/*	while (count == 0) {
//		printf("count = 0!\n");
		if ((LIST_FIRST(&(env_sched_list[point]))) == NULL) {
			point = 1 - point;
		}
		cur = LIST_FIRST(&(env_sched_list[point]));
		count = cur->env_pri;
		if (cur != NULL) {
		LIST_REMOVE(cur, env_sched_link);
		LIST_INSERT_TAIL(&(env_sched_list[1 - point]), cur, env_sched_link);
		}
	}
//	printf("%d\n", count);
	count--;
	env_run(cur);
*/
/*	while (curtime <= 0 || cur == NULL || cur->env_status == ENV_NOT_RUNNABLE) {
		if (cur != NULL) {
			LIST_REMOVE(cur, env_sched_link);
			LIST_INSERT_HEAD(&env_sched_list[1 - x], cur, env_sched_link);
		}
		while (LIST_FIRST(&env_sched_list[x]) == NULL) {
			x = 1 - x;
		}
		cur = LIST_FIRST(&env_sched_list[x]);
		curtime = cur->env_pri;
	}
	curtime--;
	env_run(cur);*/
//	env_run(LIST_FIRST(env_sched_list));
/*	if (count == 0) {
		if (cur != NULL) {
			LIST_REMOVE(cur, env_sched_link);
			LIST_INSERT_TAIL(&env_sched_list[1 - point], cur, env_sched_link);
		}
		if (LIST_EMPTY(&env_sched_list[point])) {
			point = 1 - point;
		}
		while(1) {
			cur = LIST_FIRST(&env_sched_list[point]);
			if (cur == NULL) {
				break;
			}
			if (cur->env_status == ENV_RUNNABLE) {
				break;
			}
			LIST_REMOVE(cur, env_sched_link);
		}
		if (cur != NULL) {
			count = cur->env_pri;
		}
	}
	count--;
	env_run(cur);*/
/*	while (curtime <= 0 || cur && cur->env_status != ENV_RUNNABLE) {
		if (cur != NULL) {
			LIST_REMOVE(cur, env_sched_link);
			LIST_INSERT_HEAD(&env_sched_list[1 - x], cur, env_sched_link);
		}
		while ((LIST_FIRST(&env_sched_list[x])) == NULL) {
			x = 1 - x;
		}
		cur = LIST_FIRST(&env_sched_list[x]);
		curtime = cur->env_pri;
	}*/
/*	if (curtime == 0 || cur == NULL || cur->env_status == ENV_NOT_RUNNABLE ) {
		do {
			cur = LIST_FIRST(&env_sched_list[x]);
			if (cur == NULL) {
				if (!LIST_EMPTY(&env_sched_list[1 - x])) {
					x = 1 - x;
					cur = LIST_FIRST(&env_sched_list[x]);
				}
			}
			curtime = cur->env_pri;
			LIST_REMOVE(cur, env_sched_link);
			LIST_INSERT_HEAD(&env_sched_list[1 - x], cur, env_sched_link);
			if (LIST_EMPTY(&env_sched_list[x])) {
				x = 1 - x;
			}
		} while (cur->env_status != ENV_RUNNABLE);
	}
	curtime--;
	cur->env_runs++;
	env_run(cur);*/
}
