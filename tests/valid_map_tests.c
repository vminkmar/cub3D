#include </Users/vminkmar/.brew/include/criterion/criterion.h>
#include </Users/vminkmar/.brew/include/criterion/redirect.h>

#include "../include/cub3d.h"

void	redir(void)
{
	cr_redirect_stderr();
	cr_redirect_stdout();
}

TestSuite(check_input_tests);

Test(check_input_tests, correct_input, .init = redir)
{
    char *argv[2];
	argv[0] = "cub3D";
	argv[1] = "maps/";
	int argc = 2;
	cr_assert_eq(check_input(argc, argv), 0, "Expected 0 when no argument is provided");
}

Test(check_input_tests, one_argument, .init = redir)
{
    char *argv[1];
	argv[0] = "cub3D";
	int argc = 1;
	cr_assert_eq(check_input(argc, argv), 1, "Expected 1 when no argument is provided");
}

Test(check_input_tests, map_argument_test, .init = redir)
{
    char *argv[2];
	argv[0] = "cub3D";
	argv[1] = "map/";
	int argc = 2;
	cr_assert_eq(check_input(argc, argv), 1, "Expected 1 when no argument is provided");
}

Test(check_input_tests, second_argument_empty, .init = redir)
{
    char *argv[2];
	argv[0] = "cub3D";
	argv[1] = "";
	int argc = 2;
	cr_assert_eq(check_input(argc, argv), 1, "Expected 1 when no argument is provided");
}

Test(check_input_tests, second_argument_number, .init = redir)
{
    char *argv[2];
	argv[0] = "cub3D";
	argv[1] = "123";
	int argc = 2;
	cr_assert_eq(check_input(argc, argv), 1, "Expected 1 when no argument is provided");
}
Test(check_input_tests, second_argument_missing_s, .init = redir)
{
    char *argv[2];
	argv[0] = "cub3D";
	argv[1] = "map/";
	int argc = 2;
	cr_assert_eq(check_input(argc, argv), 1, "Expected 1 when no argument is provided");
}