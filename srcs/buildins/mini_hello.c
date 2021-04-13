#include "minishell.h"

void	mini_hello(void)
{
	printf(CYN"\n"
		"	  ／＞　  フ\n"
		"　　　　　| 　_　 _|\n"
		"　 　　　／`ミ _x 彡\n"
		"　　 　 /　　　 　 |\n"
		"　　　 /　 ヽ　　 ﾉ\n"
		"　／￣|　　 |　|　|\n"
		"　| (￣ヽ＿_ヽ_)_)\n"
		"　＼二つ"RESET);
	g_errno = 0;
}
