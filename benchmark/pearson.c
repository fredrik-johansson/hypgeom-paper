#include <string.h>
#include "acb_hypgeom.h"
#include "flint/profiler.h"

#define TIMEIT_STOP_VAL(val) \
        TIMEIT_END_REPEAT(__timer, __reps) \
        (val) = __timer->cpu*0.001/__reps; \
    } while (0);

const double input_1f1[40][6] = {
  {0.1, 0, 0.2, 0, 0.5, 0},
  {-0.1, 0, 0.2, 0, 0.5, 0},
  {0.1, 0, 0.2, 0, -0.5, 1},
  {1, 1, 1, 1, 1, -1},
  {1e-08, 0, 1e-08, 0, 1e-10, 0},
  {1e-08, 0, 1e-12, 0, -1e-10, 1e-12},
  {1, 0, 1, 0, 10, 1e-09},
  {1, 0, 3, 0, 10, 0},
  {500, 0, 511, 0, 10, 0},
  {8.1, 0, 10.1, 0, 100, 0},
  {1, 0, 2, 0, 600, 0},
  {100, 0, 1.5, 0, 2.5, 0},
  {-60, 0, 1, 0, 10, 0},
  {60, 0, 1, 0, 10, 0},
  {60, 0, 1, 0, -10, 0},
  {-60, 0, 1, 0, -10, 0},
  {1000, 0, 1, 0, 0.001, 0},
  {0.001, 0, 1, 0, 700, 0},
  {500, 0, 1, 0, -5, 0},
  {-500, 0, 1, 0, 5, 0},
  {20, 0, -9.999999999, 0, -2.5, 0},
  {20, 0, 9.999999999, 0, 2.5, 0},
  {-20, 0, -9.999999999999, 0, 2.5, 0},
  {50, 0, 10, 0, 0, 200},
  {-5, 0, -4.999999999, -4.999999999, -1, 0},
  {4, 0, 80, 0, 200, 0},
  {-4, 0, 500, 0, 300, 0},
  {5, 0, 0.1, 0, -2, 300},
  {-5, 0, 0.1, 0, 2, 300},
  {2, 8, -150, 1, 150, 0},
  {5, 0, 2, 0, 100, -1000},
  {-5, 0, 2, 0, -100, 1000},
  {-5, 0, -2, -1, 1, 1.9999999999},
  {1, 0, 1e-12, 0, 1, 0},
  {10, 0, 1e-12, 0, 10, 0},
  {1, 0, -1, 1e-12, 1, 0},
  {1000, 0, 1, 0, -1000, 0},
  {-1000, 0, 1, 0, 1000, 0},
  {-10, 500, 0, 5, 10, 0},
  {20, 0, 10, 1000, -5, 0},
};

const double
input_2f1[40][8] = {
  {0.1, 0, 0.2, 0, 0.3, 0, 0.5, 0},
  {-0.1, 0, 0.2, 0, 0.3, 0, 0.5, 0},
  {0.1, 0, 0.2, 0, -0.3, 0, -0.5, 0.5},
  {1e-08, 0, 1e-08, 0, 1e-08, 0, 1e-06, 0},
  {1e-08, 0, -1e-06, 0, 1e-12, 0, -1e-10, 1e-12},
  {1, 0, 10, 0, 1, 0, 0.5, 1e-09},
  {1, 0, -1, 1e-12, 1, 0, -0.8, 0},
  {2, 8, 3, -5, 1.41421356237309505, -3.14159265358979324, 0.75, 0},
  {100, 0, 200, 0, 350, 0, 0, 1},
  {2.000000001, 0, 3, 0, 5, 0, -0.75, 0},
  {-2, 0, -3, 0, -4.999999999, 0, 0.5, 0},
  {-1, 0, -1.5, 0, -2.000000000000001, 0, 0.5, 0},
  {500, 0, -500, 0, 500, 0, 0.75, 0},
  {500, 0, 500, 0, 500, 0, -0.6, 0},
  {-1000, 0, -2000, 0, -4000.1, 0, -0.5, 0},
  {-100, 0, -200, 0, -299.999999999, 0, 0.707106781186547524, 0},
  {300, 0, 10, 0, 5, 0, 0.5, 0},
  {5, 0, -300, 0, 10, 0, 0.5, 0},
  {10, 0, 5, 0, -300.5, 0, 0.5, 0},
  {2, 200, 5, 0, 10, 0, 0.6, 0},
  {2, 200, 5, -100, 10, 500, 0.8, 0},
  {2, 0, 5, 0, 10, -500, -0.8, 0},
  {2.25, 0, 3.75, 0, -0.5, 0, -1, 0},
  {1, 0, 2, 0, 4, 3, 0.6, -0.8},
  {1, 0, 0.9, 0, 2, 0, 0.5, 0.866025403784438647},
  {1, 0, 2.5, 0, 5, 0, 0.5, 0.866025403784438647},
  {-1, 0, 0.9, 0, 2, 0, 0.5, -0.866025403784438647},
  {4, 0, 1.1, 0, 2, 0, 0.5, 0.856025403784438647},
  {5, 0, 2.2, 0, -2.5, 0, 0.49, -0.866025403784438647},
  {0.666666666666666667, 0, 1, 0, 1.33333333333333333, 0, 0.5, 0.866025403784438647},
};

static void
_acb_print(const acb_t z, slong n)
{
    arb_printn(acb_realref(z), n, ARB_STR_NO_RADIUS);

    if (!arb_is_zero(acb_imagref(z)))
    {
        if (arb_is_negative(acb_imagref(z)))
        {
            arb_t t;
            arb_init(t);
            arb_neg(t, acb_imagref(z));
            printf(" - ");
            arb_printn(t, n, ARB_STR_NO_RADIUS);
        }
        else
        {
            printf(" + ");
            arb_printn(acb_imagref(z), n, ARB_STR_NO_RADIUS);
        }
        printf("i");
    }
}

int main(int argc, char *argv[])
{
    int function, i, numtests;
    slong prec, goal;
    double t, total, logtotal;

    acb_t a, b, c, z, r, s;

    acb_init(a);
    acb_init(b);
    acb_init(c);
    acb_init(z);
    acb_init(r);
    acb_init(s);

    goal = 53;

    for (function = 0; function < 4; function++)
    {
        total = 0.0;
        logtotal = 0.0;

        if (function < 2)
            numtests = 40;
        else
            numtests = 30;

        for (i = 0; i < numtests; i++)
        {
//            printf("%2d ", i + 1); fflush(stdout);

            TIMEIT_START
            prec = 96;

            for (;;)
            {
                if (function == 0)
                {
                    acb_set_d_d(a, input_1f1[i][0], input_1f1[i][1]);
                    acb_set_d_d(b, input_1f1[i][2], input_1f1[i][3]);
                    acb_set_d_d(z, input_1f1[i][4], input_1f1[i][5]);
                    acb_hypgeom_m(r, a, b, z, 0, prec);
                }
                else if (function == 1)
                {
                    acb_set_d_d(a, input_1f1[i][0], input_1f1[i][1]);
                    acb_set_d_d(b, input_1f1[i][2], input_1f1[i][3]);
                    acb_set_d_d(z, input_1f1[i][4], input_1f1[i][5]);
                    acb_hypgeom_u(r, a, b, z, prec);
                }
                else if (function == 2)
                {
                    acb_set_d_d(a, input_2f1[i][0], input_2f1[i][1]);
                    acb_set_d_d(b, input_2f1[i][2], input_2f1[i][3]);
                    acb_set_d_d(c, input_2f1[i][4], input_2f1[i][5]);
                    acb_set_d_d(z, input_2f1[i][6], input_2f1[i][7]);
                    acb_hypgeom_2f1(r, a, b, c, z, 0, prec);
                }
                else
                {
                    acb_set_d_d(a, input_2f1[i][0], input_2f1[i][1]);
                    acb_set_d_d(b, input_2f1[i][2], input_2f1[i][3]);
                    acb_set_d_d(c, input_2f1[i][4], input_2f1[i][5]);
                    acb_set_d_d(z, input_2f1[i][6], input_2f1[i][7]);
                    acb_mul_2exp_si(z, z, 1);
                    acb_sub_ui(z, z, 1, prec);
                    acb_neg(z, z);
                    acb_hypgeom_legendre_q(r, a, c, z, 0, prec);
                }

                if (function == 3)
                {
                    if (acb_rel_accuracy_bits(r) >= goal)
                        break;
                }
                else
                {
                    if (arb_can_round_arf(acb_realref(r), goal, ARF_RND_NEAR) &&
                        arb_can_round_arf(acb_imagref(r), goal, ARF_RND_NEAR))
                        break;
                }

                prec *= 2;
            }

            TIMEIT_STOP_VAL(t)

            total += t;
            logtotal += log(t);

#if 1
            printf("%8g, ", t);
#else
            printf("%8ld    %8g    ", prec, t);
            _acb_print(r, 25);
            printf("\n");
#endif
        }

        printf("---------------------------------------------------------------\n");
        printf("Mean %g s; geometric mean %g\n", total, exp(logtotal / numtests));
        printf("---------------------------------------------------------------\n");
    }

    acb_clear(a);
    acb_clear(b);
    acb_clear(c);
    acb_clear(z);
    acb_clear(r);
    acb_clear(s);
}

