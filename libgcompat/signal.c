#include <signal.h> /* sigpause */

/**
 * Remove a signal from the signal mask and suspend the thread.
 *
 * LSB 5.0: LSB-Core-generic/baselib---xpg-sigpause.html
 */
int __xpg_sigpause(int sig)
{
	return sigpause(sig);
}
