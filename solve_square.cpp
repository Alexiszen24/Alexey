#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

//-----------------------------------------------------------------------------

const int ROOTS_INFIN = -1;
const double Precision = 1E-6;

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//!  Solves a square equation a*x^2 + bx + c = 0
//!
//!  @perem [in] a-coef
//!  @perem [in] b-coef
//!  @perem [in] c-coef
//!  @perem [out] x1-pointer to the 1st root
//!  @perem [out] x2-pointer to the 2st root
//!
//!  @Return Number of roots
//!
//!  @BUT In case of infinite number of roots returns ROOTS_INFIN.
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int SolveSquare( double a, double b, double c,
                double* x1, double* x2);
bool isZero(double d);
int check_correct_enter(double* a, double* b, double* c);
void clean_stdin ();
void unitest_Is_Zero();
void unitest_Solve_Square();

//-----------------------------------------------------------------------------

int main ()
{
    unitest_Is_Zero();
    unitest_Solve_Square();

    printf ("# Square equation solver\n"
            "# (c) FLEXA, 2020\n\n");

    printf ("#Solution of an equation of the form: a*x^2 + b*x + c = 0\n"
            "#Enter a, b, c: ");

    double a = 0, b = 0, c = 0;

    int counter_for_main = check_correct_enter( &a, &b, &c);

    if (counter_for_main)
        {
        double x1 = 0, x2 = 0;
        int nRoots = SolveSquare (a, b, c, &x1, &x2) ;
        switch (nRoots)

            {
                case 0:
                    printf ("Answer:\n"
                            "No roots\n");
                    break;

                case 1:
                    printf ("Answer:\n"
                            "x=%+lg\n", x1);
                    break;

                case 2:
                    printf ("Answer:\n"
                            "x1=%+lg, x2= %+lg\n", x1, x2);
                    break;

                case ROOTS_INFIN:
                    printf ("Answer:\n"
                            "Any number");
                    break;

                default:
                        printf("ERROR") ;
                        return 1;
            }
        }
    else
        return 0;

    return 0;
}

int SolveSquare( double a, double b, double c,
                double* x1, double* x2)
{
    assert (std::isfinite (a));
    assert (std::isfinite (b));
    assert (std::isfinite (c));

    assert (x1  != NULL);
    assert (x2  != NULL);
    assert (x1  != x2);

    if (a == 0)
        {
        if (b == 0)
            {
            if (c == 0)
                {
                return ROOTS_INFIN;
                }
            else
                return 0;
            }
        else
            {
            *x1 = -c / b;
            return 1;
            }
        }
    else
        {
            double d = b * b - 4 * a * c;

            if (isZero(d))
                {
                *x1 = -b / 2 * a;
                return 1;
                }

            else if (d < 0)
                return 0;

            else
                {
                double sqrt_d = sqrt(d);

                *x1 = (-b + sqrt_d) / (2 * a);
                *x2 = (-b - sqrt_d) / (2 * a);
                return 2;
                }
        }
}

//The function shown represents the numerical error

bool isZero(double value)

{
    return (abs(value) <= Precision);
}

// The presented function checks the correctness of the entered data

int check_correct_enter(double* a, double* b, double* c)
{
    assert (a != NULL);
	assert (b != NULL);
	assert (c != NULL);
	assert (a != b);
	assert (a != c);
	assert (b != c);

    int checkInput = scanf("%lg %lg %lg", a, b, c);
    int enter_counter = 0;

        while (checkInput < 3 && enter_counter < 5)
            {
                printf ("\n #Incorrect input. Attempts left: %d."
				"\n # Please, put numeric values: ",
                5 - enter_counter);

                clean_stdin();

                checkInput = scanf("%lg %lg %lg", a, b, c);
                enter_counter++;
            }
        if (enter_counter > 4)
            {
            printf ("\n # Number of attempts exceeded"
                        "\n # End of the program");
            return 0;
            }
        else
            return 1;

}

//-----------------------------------------------------------------------------
//The provided function frees up space for valid input.

//By means of the getchar() function, which takes
//the current (incorrect) value and transfers it
//to another memory location, freeing up space for
//entering correct data.

//The loop continues until the next line breaks
//-----------------------------------------------------------------------------

void clean_stdin ()
{
	int stdin_char = 24;

	while (stdin_char != '\n' && stdin_char != EOF)
	{
		stdin_char = getchar();
	}

	stdin_char = 0;
}

void unitest_Is_Zero()
{
    printf (" # Testing 'Is_Zero()'.\n");

    double param_for_check = 0;

    if (isZero(param_for_check) == 0)
        {
            printf ("\n # UNITTEST ERROR: 'bool Is_Zero ()' test failed.\n"
				    "param_for_check = %lg\n"
				    " expected_result: true//1\n", param_for_check);
        }

    param_for_check = 0.01;

    if (isZero(param_for_check) == 1)
        {
            printf ("\n # UNITTEST ERROR: 'bool Is_Zero ()' test failed.\n"
				    "param_for_check = %lg\n"
				    " expected_result: false//0\n", param_for_check);
        }

    param_for_check = 0.0000000001;

    if (isZero(param_for_check) == 0)
        {
            printf ("\n # UNITTEST ERROR: 'bool Is_Zero ()' test failed.\n"
				    "param_for_check = %lg\n"
				    " expected_result: true//1\n", param_for_check);
        }

    param_for_check = 1E-6;

    if (isZero(param_for_check) == 0)
        {
        printf ("\n # UNITTEST ERROR: 'bool Is_Zero ()' test failed.\n"
                "param_for_check = %lg\n"
                " expected_result: true//1\n", param_for_check);
        }

    printf("\n # Testing 'IsZero()' complete.\n\n");

}

void unitest_Solve_Square()
{
    printf (" # Testing 'Solve_Square()'.\n");

    double unitest_a = 0;
    double unitest_b = 0;
    double unitest_c = 0;
    double unitest_x1 = 0;
    double unitest_x2 = 0;

//Test #1
//a = 0, b = 0, c = 0

    unitest_a = 0;
    unitest_b = 0;
    unitest_c = 0;

    if (SolveSquare(unitest_a, unitest_b, unitest_c, &unitest_x1, &unitest_x2) != ROOTS_INFIN)
        {
        printf ("\n # UNITTEST ERROR: 'int SolveSquare()' test failed.\n"
				    " unitest_a = %lg\n"
                    " unitest_b = %lg\n"
                    " unitest_c = %lg\n"
                    " expected_result: ROOTS_INFIN\n"
                    " real_result: %lg %lg\n", unitest_a, unitest_b, unitest_c, unitest_x1, unitest_x2);
        }

//Test #2
//a = 0, b = 0, c = 7

    unitest_a = 0;
    unitest_b = 0;
    unitest_c = 7;

    if (SolveSquare(unitest_a, unitest_b, unitest_c, &unitest_x1, &unitest_x2) != 0)
        {
        printf ("\n # UNITTEST ERROR: 'int SolveSquare()' test failed.\n"
				    " unitest_a = %lg\n"
                    " unitest_b = %lg\n"
                    " unitest_c = %lg\n"
                    " expected_result: 0 //No Roots//\n"
                    " real_result: %lg %lg\n", unitest_a, unitest_b, unitest_c, unitest_x1, unitest_x2);
        }

//Test #3
//a = 1, b = 2, c = 1

    unitest_a = 1;
    unitest_b = 2;
    unitest_c = 1;

    if (SolveSquare(unitest_a, unitest_b, unitest_c, &unitest_x1, &unitest_x2) != 1)
        {
        printf ("\n # UNITTEST ERROR: 'int SolveSquare()' test failed.\n"
				    " unitest_a = %lg\n"
                    " unitest_b = %lg\n"
                    " unitest_c = %lg\n"
                    " expected_result: 1 //Only one solve//\n"
                    " expected_solve: x1 = -1\n"
                    " real_result: %lg %lg\n", unitest_a, unitest_b, unitest_c, unitest_x1, unitest_x2);
        }

//Test #4
//a = 2, b = 8, c = -10

    unitest_a = 2;
    unitest_b = 8;
    unitest_c = -10;

    if (SolveSquare(unitest_a, unitest_b, unitest_c, &unitest_x1, &unitest_x2) != 2)
        {
        printf ("\n # UNITTEST ERROR: 'int SolveSquare()' test failed.\n"
				    " unitest_a = %lg\n"
                    " unitest_b = %lg\n"
                    " unitest_c = %lg\n"
                    " expected_result: 2 //Two solves//\n"
                    " expected_solves: x1 = %lg x2 = -5\n"
                    " real_result: %lg %lg\n", unitest_a, unitest_b, unitest_c, unitest_x1, unitest_x2);
        }

//Test #5
//a = 5, b = 7, c = 9

    unitest_a = 5;
    unitest_b = 7;
    unitest_c = 9;

    if (SolveSquare(unitest_a, unitest_b, unitest_c, &unitest_x1, &unitest_x2) != 0)
        {
        printf ("\n # UNITTEST ERROR: 'int SolveSquare()' test failed.\n"
				    " unitest_a = %lg\n"
                    " unitest_b = %lg\n"
                    " unitest_c = %lg\n"
                    " expected_result: 0 //No Roots//\n"
                    " real_result: %lg %lg\n", unitest_a, unitest_b, unitest_c, unitest_x1, unitest_x2);
        }

    printf("\n # Testing 'int solve_square ()' complete.\n\n");

}













