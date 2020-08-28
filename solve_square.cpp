#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

const int ROOTS_INFIN = -1;
const double Precision = 1E-6;

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

int SolveSquare( double a, double b, double c,
                double* x1, double* x2);
bool isZero(double d);

int main ()
{
    printf ("# Square equation solver\n"
            " # (c) FLEXA, 2020\n\n");

    printf ("# Enter a, b, c: ");

    double a = 0, b = 0, c = 0;
    scanf ("%lg %lg %lg", &a, &b, &c);

    double x1 = 0, x2 = 0;
    int nRoots = SolveSquare (a, b, c, &x1, &x2) ;
        switch (nRoots)

        { case 0:
                printf ("No roots\n");
                break;

          case 1:
                printf ("x=%lg\n", x1);
                break;

          case 2:
                printf ("x=%lg, x2= %lg\n", x1, x2);
                break;

          case ROOTS_INFIN:
                printf ("Any number");
                break;

          default:
                printf("ERROR") ;
                return 1;
        }


    return 0;
}

int SolveSquare( double a, double b, double c,
                double* x1, double* x2)

{   assert (std::isfinite (a));
    assert (std::isfinite (b));
    assert (std::isfinite (c));

    assert (x1  != NULL);
    assert (x2  != NULL);
    assert (x1  != x2);

    if (a == 0)
        {
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
        }
    else
        {
            double d = b * b - 4 * a * c;

            if (d < 0 && isZero(d)==0)
                return 0;

            if (isZero(d))
                {
                *x1 = -b / 2 * a;
                return 1;
                }
            else
                {
                double sqrt_d = sqrt (d);

                *x1 = (-b + sqrt_d) / (2 * a);
                *x2 = (-b - sqrt_d) / (2 * a);
                return 2;
                }
        }
}

bool isZero(double d)

{
    if (abs(d)==Precision)
        {
        return 1;
        }
    else
        return 0;
}
