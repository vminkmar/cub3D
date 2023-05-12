#include </Users/vminkmar/.brew/include/criterion/criterion.h>
#include </Users/vminkmar/.brew/include/criterion/redirect.h>

#include "../include/cub3d.h"

void	redir(void)
{
	cr_redirect_stderr();
	cr_redirect_stdout();
}

TestSuite(map_tests);

Test(map_tests, correct_map, .init = redir)
{
    char *argv[2];
	argv[0] = "cub3D";
	argv[1] = "maps/map_correct_multiple_spaces";
	int argc = 2;
	int exit_status = main(argc, argv);
	cr_assert_eq(exit_status, 0, "Expected exit status of 0, but got %d", exit_status);
}