X = {{0.1, 0, 0.2, 0, 0.5, 0},
  {-0.1, 0, 0.2, 0, 0.5, 0},
  {0.1, 0, 0.2, 0, -0.5, 1},
  {1, 1, 1, 1, 1, -1},
  {10^-8, 0, 10^-8, 0, 10^-10, 0},
  {10^-8, 0, 10^-12, 0, -10^-10, 10^-12},
  {1, 0, 1, 0, 10, 10^-9},
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
  {1, 0, 10^-12, 0, 1, 0},
  {10, 0, 10^-12, 0, 10, 0},
  {1, 0, -1, 10^-12, 1, 0},
  {1000, 0, 1, 0, -1000, 0},
  {-1000, 0, 1, 0, 1000, 0},
  {-10, 500, 0, 5, 10, 0},
  {20, 0, 10, 1000, -5, 0}
}

X = Table[{X[[i,1]] + X[[i,2]] I, X[[i,3]] + X[[i,4]] I, X[[i,5]] + X[[i,6]] I}, {i,1,40}]
Xapprox = N[X]
Xexact = SetPrecision[Xapprox,Infinity]

(*
showval[x_, y_] := Module[{},
  va1 = Hypergeometric1F1[x[[1]], x[[2]], x[[3]]];
  va2 = N[Hypergeometric1F1[y[[1]], y[[2]], y[[3]]], 1000];
  error = N[Abs[va1-va2]/Abs[va2]];
  Print[error]];
Do[showval[Xapprox[[i]], Xexact[[i]]], {i,1,30}] *)

Print["..."];

(*
timing[cs_,x_,y_] := Module[{},
  reps=1/10;
  t=0.0;
  While[t<0.1,
    reps = reps * 10;
    t=Timing[
        Do[
          HypergeometricU[x[[1]], x[[2]], x[[3]]];, {i,1,reps}];
        ][[1]];
  ];
  va1 = HypergeometricU[x[[1]], x[[2]], x[[3]]];
  (* Print[Re[va1], " ", Im[va1]]; *)
  va2 = Release[N[Hold[HypergeometricU[y[[1]], y[[2]], y[[3]]]], 500]];
  error = N[Abs[va1-va2]/Abs[va2]];
 (* Print[t / reps, "   ", reps, "   ", error, "  ", If[error>2^-47, {va1, N[va2,15]}, ""]]; *)
  Print[cs, "  ", t / reps, "   ", va1];
];
*)


evalfunc[a_,b_,z_,d_] := Module[{},
  wp = 20;
  acc = 0.0;
  While[acc < d,
    aa = N[a,wp]; bb = N[b,wp]; zz = N[z, wp];
    w = HypergeometricU[aa,bb,zz];
    acc = Precision[w];
    wp = wp * 2;
  ];
  Return[w];
];

timing2[ii_,x_,y_,d_] := Module[{},
  reps=1/10;
  t=0.0;
  While[t<0.1,
    reps = reps * 10;
    t=Timing[Do[evalfunc[y[[1]], y[[2]], y[[3]], d]; , {i, 1, reps}];][[1]];
  ];
  va1 = evalfunc[y[[1]], y[[2]], y[[3]], d];
  (* Print[Re[va1], " ", Im[va1]]; *)
  va2 = HypergeometricU[y[[1]], y[[2]], N[y[[3]], 5000]];
  error = N[Abs[va1-va2]/Abs[va2]];
  Print[ii, "  ", t / reps, "   ", error, "  ", N[va1, 18]];
];

(*
Print["doubles"];
Do[timing[i,Xapprox[[i]], Xexact[[i]]], {i,1,Length[X]}]
*)

Print["N[,16]"];
Do[timing2[i, Xapprox[[i]], Xexact[[i]],16], {i,1,Length[X]}]

(* %Print["N[,34]"]; *)
(* Do[timing2[Xapprox[[i]], Xexact[[i]],34], {i,1,Length[X]}] *)


