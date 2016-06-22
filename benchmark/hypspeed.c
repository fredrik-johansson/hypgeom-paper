#include "acb_hypgeom.h"
#include "flint/profiler.h"

#define TIMEIT_STOP_VAL(val) \
        TIMEIT_END_REPEAT(__timer, __reps) \
        (val) = __timer->cpu*0.001/__reps; \
    } while (0);

int main()
{
    acb_t a, b, c, z, w, r;
    slong dps, prec, goal;
    double tt, x;
    slong i, fun;

    acb_init(a); acb_init(b);
    acb_init(c); acb_init(z);
    acb_init(r); acb_init(w);

    if (0)
    {
        for (dps = 10; dps <= 10000; dps *= 10)
        {
            mpfr_t fx, fy, fz;
            prec = dps * 3.321928094887;

            mpfr_init2(fx, prec);
            mpfr_init2(fy, prec);
            mpfr_init2(fz, prec);

            printf("mpfr_besselj_%ld = array([", dps);

            for (i = 0; i <= 60; i++)
            {
                x = pow(10.0, i * 0.1);

                TIMEIT_START
                mpfr_const_pi(fx, MPFR_RNDN);
                mpfr_mul_d(fx, fx, x, MPFR_RNDN);
                mpfr_jn(fy, 0, fx, MPFR_RNDN);
                TIMEIT_STOP_VAL(tt)
                printf("%g,", tt);
                fflush(stdout);
                if (i % 16 == 15)
                    printf("\n   ");
            }

            printf("])\n");

            mpfr_clear(fx);
            mpfr_clear(fy);
            mpfr_clear(fz);
        }

        for (dps = 10; dps <= 10000; dps *= 10)
        {
            mpfr_t fx, fy, fz;
            prec = 10 * 3.321928094887;

            mpfr_init2(fx, prec);
            mpfr_init2(fy, prec);
            mpfr_init2(fz, prec);

            printf("mpfr_bessel_j%ld = array([", dps);

            for (i = 0; i <= 60; i++)
            {
                x = pow(10.0, i * 0.1);

                TIMEIT_START
                mpfr_const_pi(fx, MPFR_RNDN);
                mpfr_mul_d(fx, fx, x, MPFR_RNDN);
                mpfr_jn(fy, dps, fx, MPFR_RNDN);
                TIMEIT_STOP_VAL(tt)
                printf("%g,", tt);
                fflush(stdout);
                if (i % 16 == 15)
                    printf("\n   ");
            }

            printf("])\n");

            mpfr_clear(fx);
            mpfr_clear(fy);
            mpfr_clear(fz);
        }
    }


    for (fun = 0; fun <= 6; fun++)
    {
        for (dps = 10; dps <= 10000; dps *= 10)
        {
            if (fun == 0)
                printf("besselj_");
            else if (fun == 1)
                printf("besseli_");
            else if (fun == 2)
                printf("besselc_");
            else if (fun == 3)
                printf("besselk_");
            else if (fun == 4)
                printf("bessel_n_");
            else if (fun == 5)
                printf("bessel_ni_");
            else if (fun == 6)
                printf("big1f1_");

            printf("%ld = array([", dps);

            for (i = 0; i <= 60; i++)
            {
                if (fun == 10)
                    goal = 10 * 3.321928094887;
                else
                    goal = dps * 3.321928094887;

                TIMEIT_START
                for (prec = goal * 1.05 + 25; ; prec *= 2)
                {
                    x = pow(10.0, i * 0.1);

                    acb_const_pi(z, prec);
                    acb_set_d(b, x);
                    acb_mul(z, z, b, prec);
                    acb_zero(a);

                    if (fun == 0)
                    {
                        acb_hypgeom_bessel_j(r, a, z, prec);
                    }
                    else if (fun == 1)
                    {
                        acb_hypgeom_bessel_i(r, a, z, prec);
                    }
                    else if (fun == 2)
                    {
                        arb_one(acb_realref(w));
                        arb_sqrt_ui(acb_imagref(w), 3, prec);
                        acb_mul_2exp_si(w, w, -1);
                        acb_mul(z, z, w, prec);
                        acb_hypgeom_bessel_j(r, a, z, prec);
                    }
                    else if (fun == 3)
                    {
                        acb_hypgeom_bessel_k(r, a, z, prec);
                    }
                    else if (fun == 4)
                    {
                        acb_set_si(a, dps);
                        acb_hypgeom_bessel_j(r, a, z, prec);
                    }
                    else if (fun == 5)
                    {
                        acb_set_si_si(a, 0, dps);
                        acb_hypgeom_bessel_j(r, a, z, prec);
                    }
                    else if (fun == 6)
                    {
                        acb_set_si_si(a, 0, dps);
                        acb_set_si_si(b, 1, 1);

                        arb_one(acb_realref(w));
                        arb_sqrt_ui(acb_imagref(w), 3, prec);
                        acb_mul_2exp_si(w, w, -1);
                        acb_mul(z, z, w, prec);

                        acb_hypgeom_m(r, a, b, z, 0, prec);
                    }

                    if (fun >= 4)
                    {
                        if (acb_rel_accuracy_bits(r) >= 10 * 3.321928094887)
                            break;
                    }
                    else
                    {
                        if (acb_rel_accuracy_bits(r) >= goal)
                            break;
                    }
                }

                TIMEIT_STOP_VAL(tt)
                printf("%g", tt);
                fflush(stdout);

                if (i != 100) printf(", ");

                if (i % 16 == 15)
                    printf("\n   ");
            }

            printf("])\n");
        }
    }
}

