X = {{0.1, 0, 0.2, 0, 0.3, 0, 0.5, 0},
  {-0.1, 0, 0.2, 0, 0.3, 0, 0.5, 0},
  {0.1, 0, 0.2, 0, -0.3, 0, -0.5, 0.5},
  {10.^-8, 0, 10.^-8, 0, 10.^-8, 0, 10.^-6, 0},
  {10.^-8, 0, -10.^-6, 0, 10.^-12, 0, -10.^-10, 10.^-12},
  {1, 0, 10, 0, 1, 0, 0.5, 10.^-9},
  {1, 0, -1, 10.^-12, 1, 0, -0.8, 0},
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
  {0.666666666666666667, 0, 1, 0, 1.33333333333333333, 0, 0.5, 0.866025403784438647}}

X = Table[{X[[i,1]] + X[[i,2]] I, X[[i,3]] + X[[i,4]] I, X[[i,5]] + X[[i,6]] I, X[[i,7]] + X[[i,8]] I}, {i,1,30}]
Xapprox = N[X]
Xexact = SetPrecision[Xapprox,Infinity]

(* Do[showval[Xapprox[[i]], Xexact[[i]]], {i,1,30}] *)

Print["..."];

Print["..."];

timing[x_,y_] := Module[{},
  reps=1/10;
  t=0.0;
  While[t<0.1,
    reps = reps * 10;
    t=Timing[
        Do[v=LegendreQ[x[[1]], x[[3]], 1-2x[[4]]];, {i,1,reps}];][[1]];
  ];
  va1 = LegendreQ[x[[1]], x[[3]], 1-2x[[4]]];
  (* Print[Re[va1], " ", Im[va1]]; *)
  va2 = LegendreQ[y[[1]], y[[3]], 1-2 N[y[[4]],500]];
  error = N[Abs[va1-va2]/Abs[va2]];
  (* Print[t / reps, "   ", reps, "   ", error, "  ", If[error>2^-47, {va1, N[va2,15]}, ""]]; *)
   Print[t / reps, "   ", va1];
];

Print["doubles"];
Do[timing[Xapprox[[i]], Xexact[[i]]], {i,1,Length[X]}]

(*
Print["N[,16]"];
Do[timing2[Xapprox[[i]], Xexact[[i]],16], {i,1,Length[X]}]
Print["N[,34]"];
Do[timing2[Xapprox[[i]], Xexact[[i]],34], {i,1,Length[X]}]
*)

