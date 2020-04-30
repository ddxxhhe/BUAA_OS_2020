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
void sched_yield(void)
{   
	
    static int curtime = 0; // remaining time slices of current env
    static int x = 0; // current env_sched_list index
    

    /* hint:
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

	static struct Env *cur = NULL;
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
/*	while (curtime <= 0 || cur && cur->env_status != ENV_RUNNABLE) {
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
	while (curtime <= 0 || cur && cur->env_status != ENV_RUNNABLE) {
		if (cur != NULL) {
			LIST_REMOVE(cur, env_sched_link);
			LIST_INSERT_HEAD(&env_sched_list[1 - x], cur, env_sched_link);
		}
		while ((LIST_FIRST(&env_sched_list[x])) == NULL) {
			x = 1 - x;
		}
		cur = LIST_FIRST(&env_sched_list[x]);
		curtime = cur->env_pri;
	}
	curtime--;
	env_run(cur);
}
