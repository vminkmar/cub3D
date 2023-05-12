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
	cr_assert_eq(main(argc, argv), 0, "Expected 0 when multiple spaces before paths");
}

Test(map_tests, correct_map1, .init = redir)
{
    char *argv[2];
	argv[0] = "cub3D";
	argv[1] = "maps/map_spaces_in_color";
	int argc = 2;
	cr_assert_eq(main(argc, argv), 1, "Expected 1 when spaces in colors");
}