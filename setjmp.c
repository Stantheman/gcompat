#include <assert.h>
#include <setjmp.h>

void __longjmp_chk(jmp_buf env, int val)
{
	longjmp(env, val);
}
