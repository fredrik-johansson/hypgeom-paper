#include "acb_hypgeom.h"
#include "flint/profiler.h"

#define TIMEIT_STOP_VAL(val) \
        TIMEIT_END_REPEAT(__timer, __reps) \
        (val) = __timer->cpu*0.001/__reps; \
    } while (0);

/*
Timing[N[Series[BesselJ[1+x,Pi],{x,0,1}],100];]
time(fdiff(BesselJ, [1$1], [1,Pi+1/9999], workprec=1));
*/

int
jparamderiv(slong n, slong goal)
{
    acb_poly_t a, z, t, u;
    acb_poly_struct ab[2];
    acb_t c;
    slong prec;

    acb_init(c);
    acb_poly_init(a);
    acb_poly_init(z);
    acb_poly_init(t);
    acb_poly_init(u);
    acb_poly_init(ab + 0);
    acb_poly_init(ab + 1);

    printf("n = %ld\n", n);

    TIMEIT_START
    for (prec = (goal * 1.05 + 25); ; prec *= 2)
    {
        if (n >= 1000)
            printf("try prec %ld\n", prec);
        acb_const_pi(c, prec);
        acb_poly_set_acb(z, c);
        acb_poly_scalar_mul_2exp_si(z, z, -1);

        acb_poly_set_coeff_si(a, 0, 1);
        acb_poly_set_coeff_si(a, 1, 1);
        acb_poly_pow_series(t, z, a, n + 1, prec);

        acb_poly_add_si(a, a, 1, prec);

#if 1
        acb_poly_rgamma_series(u, a, n + 1, prec);
        acb_poly_mullow(t, t, u, n + 1, prec);
#endif

        acb_poly_mullow(z, z, z, n + 1, prec);
        acb_poly_neg(z, z);

        acb_poly_set(ab + 0, a);
        acb_poly_one(ab + 1);
        acb_hypgeom_pfq_series_direct(u, NULL, 0, ab, 2, z, 0, -1, n + 1, prec);

        acb_poly_mullow(t, t, u, n + 1, prec);

        if (t->length > n && acb_rel_accuracy_bits(t->coeffs + n) >= goal)
            break;
    }
    TIMEIT_STOP

    acb_printd(t->coeffs + n, 30);
    printf("\n");

    acb_poly_clear(a);
    acb_poly_clear(z);
    acb_poly_clear(t);
    acb_poly_clear(u);
    acb_poly_clear(ab + 0);
    acb_poly_clear(ab + 1);
    acb_clear(c);
}

int main()
{
    acb_t a, b, c, z, w, r;
    slong dps, prec, goal;
    double tt;

    acb_init(a);
    acb_init(b);
    acb_init(c);
    acb_init(z);
    acb_init(r);
    acb_init(w);

    slong i, fun;

    jparamderiv(1, 333);
    jparamderiv(2, 333);
    jparamderiv(5, 333);
    jparamderiv(10, 333);
    jparamderiv(100, 333);
    jparamderiv(1000, 333);
    jparamderiv(10000, 333);

    return 0;


    printf("J_3(3.25)\n");
    for (dps = 10; dps <= 100000; dps *= 10)
    {
        prec = dps * 3.333 + 5;
        printf("dps = %6ld\n", dps);
        acb_set_d(a, 3.0);
        acb_set_d(z, 3.25);
        TIMEIT_START
        acb_hypgeom_bessel_j(r, a, z, prec);
        TIMEIT_STOP
        TIMEIT_START
        acb_hypgeom_bessel_j(r, a, z, prec);
        TIMEIT_STOP
    }

    printf("J_3(pi)\n");
    for (dps = 10; dps <= 100000; dps *= 10)
    {
        prec = dps * 3.333 + 5;
        printf("dps = %6ld\n", dps);
        acb_set_d(a, 3.0);
        acb_const_pi(z, prec);
        TIMEIT_START
        acb_hypgeom_bessel_j(r, a, z, prec);
        TIMEIT_STOP
        TIMEIT_START
        acb_hypgeom_bessel_j(r, a, z, prec);
        TIMEIT_STOP
    }

    printf("J_(pi)(pi)\n");
    for (dps = 10; dps <= 100000; dps *= 10)
    {
        prec = dps * 3.333 + 5;
        printf("dps = %6ld\n", dps);
        acb_const_pi(a, prec);
        acb_const_pi(z, prec);
        TIMEIT_START
        acb_hypgeom_bessel_j(r, a, z, prec);
        TIMEIT_STOP
        TIMEIT_START
        acb_hypgeom_bessel_j(r, a, z, prec);
        TIMEIT_STOP
    }

    printf("0F1(pi+1,-pi^2/4)\n");
    for (dps = 10; dps <= 100000; dps *= 10)
    {
        prec = dps * 3.333 + 5;
        printf("dps = %6ld\n", dps);
        acb_const_pi(a, prec);
        acb_add_ui(a, a, 1, prec);
        acb_const_pi(z, prec);
        acb_mul(z, z, z, prec);
        acb_mul_2exp_si(z, z, -2);
        acb_neg(z, z);
        TIMEIT_START
        acb_hypgeom_0f1(r, a, z, 0, prec);
        TIMEIT_STOP
        TIMEIT_START
        acb_hypgeom_0f1(r, a, z, 0, prec);
        TIMEIT_STOP
    }

    printf("K_3(3.25)\n");
    for (dps = 10; dps <= 100000; dps *= 10)
    {
        prec = dps * 3.333 + 5;
        printf("dps = %6ld\n", dps);
        acb_set_d(a, 3.0);
        acb_set_d(z, 3.25);
        TIMEIT_START
        acb_hypgeom_bessel_k(r, a, z, prec);
        TIMEIT_STOP
        TIMEIT_START
        acb_hypgeom_bessel_k(r, a, z, prec);
        TIMEIT_STOP
    }

    printf("K_3(pi)\n");
    for (dps = 10; dps <= 100000; dps *= 10)
    {
        prec = dps * 3.333 + 5;
        printf("dps = %6ld\n", dps);
        acb_set_d(a, 3.0);
        acb_const_pi(z, prec);
        TIMEIT_START
        acb_hypgeom_bessel_k(r, a, z, prec);
        TIMEIT_STOP
        TIMEIT_START
        acb_hypgeom_bessel_k(r, a, z, prec);
        TIMEIT_STOP
    }

/*
    {
        mpfr_t xx, yy;

        for (dps = 10; dps <= 10000; dps *= 10)
        {
            mpfr_init2(xx, dps * 3.321928094887);
            mpfr_init2(yy, dps * 3.321928094887);

            printf("mpfr_%ld = array([", dps);

            for (i = 1; i <= 100; i++)
            {
                TIMEIT_START
                mpfr_const_pi(xx, MPFR_RNDN);
                mpfr_mul_ui(xx, xx, i * i * i, MPFR_RNDN);
                mpfr_jn(yy, 0, xx, MPFR_RNDN);
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
*/

    for (fun = 10; fun <= 10; fun++)
    {
        if (fun != 0 && fun != 1 && fun != 3 && fun != 4 && fun != 10)
            continue;

        for (dps = 10; dps <= 10000; dps *= 10)
        {
            if (fun == 0)
                printf("besselj_");
            else if (fun == 1)
                printf("besseli_");
            else if (fun == 2)
                printf("besseljc_");
            else if (fun == 3)
                printf("besselk_");
            else if (fun == 4)
                printf("airy_");
            else if (fun == 5)
                printf("fresnel_");
            else if (fun == 6)
                printf("erf_");
            else if (fun == 7)
                printf("erfc_");
            else if (fun == 10)
                printf("big1f1_");

            printf("%ld = array([", dps);

            for (i = 1; i <= 100; i++)
            {
                if (fun == 10)
                    goal = 10 * 3.321928094887;
                else
                    goal = dps * 3.321928094887;

                TIMEIT_START
                for (prec = goal * 1.05 + 25; ; prec *= 2)
                {
                    acb_const_pi(z, prec);
                    acb_mul_ui(z, z, i * i * i, prec);
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
                        acb_neg(z, z);
                        acb_hypgeom_airy(r, NULL, NULL, NULL, z, prec);
                    }
                    else if (fun == 5)
                    {
                        acb_hypgeom_fresnel(r, NULL, z, 0, prec);
                    }
                    else if (fun == 6)
                    {
                        acb_hypgeom_erf(r, z, prec);
                    }
                    else if (fun == 7)
                    {
                        acb_hypgeom_erfc(r, z, prec);
                    }
                    else if (fun == 10)
                    {
                        acb_set_si_si(a, 0, dps);
                        acb_set_si_si(b, 1, 1);

                        arb_one(acb_realref(w));
                        arb_sqrt_ui(acb_imagref(w), 3, prec);
                        acb_mul_2exp_si(w, w, -1);
                        acb_mul(z, z, w, prec);

                        acb_hypgeom_m(r, a, b, z, 0, prec);
                    }

                    if (fun == 10)
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

