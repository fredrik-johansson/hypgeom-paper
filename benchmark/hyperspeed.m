$MaxExtraPrecision = 1000000;

X = Table[Pi * SetPrecision[10.0^(i/10.0), Infinity], {i, 0, 60}]
Print[X];

timing[f_,x_,n_] := Module[{},
  reps=1/10;
  t=0.0;
  While[t<0.1,
    reps = reps * 10;
    t=Timing[Do[val=f[x,n], {i,1,reps}];][[1]];
  ];
  Print[t / reps, "   ", N[val, 15]];
];

f1[x_,d_] := Module[{},
  wp = Floor[1.1 d + 3];
  acc = 0.0;
  While[acc < d,
    w = BesselJ[0, N[x,wp]];
    If[NumericQ[w], acc = Precision[w], acc = 0.0];
    wp = wp * 2;
  ];
  Return[w];
];

f2[x_,d_] := Module[{},
  wp = Floor[1.1 d + 3];
  acc = 0.0;
  While[acc < d,
    w = BesselI[0, N[x,wp]];
    If[NumericQ[w], acc = Precision[w], acc = 0.0];
    wp = wp * 2;
  ];
  Return[w];
];

f3[x_,d_] := Module[{},
  wp = Floor[1.1 d + 3];
  acc = 0.0;
  ww = Exp[Pi I / 3];
  While[acc < d,
    w = BesselJ[0, N[ww x,wp]];
    If[NumericQ[w], acc = Precision[w], acc = 0.0];
    wp = wp * 2;
  ];
  Return[w];
];

f4[x_,d_] := Module[{},
  wp = Floor[1.1 d + 3];
  acc = 0.0;
  While[acc < d,
    w = BesselK[0, N[x,wp]];
    If[NumericQ[w], acc = Precision[w], acc = 0.0];
    wp = wp * 2;
  ];
  Return[w];
];

f5[x_,d_] := Module[{},
  wp = Floor[1.1 * 10 + 3];
  acc = 0.0;
  While[acc < 10,
    w = BesselJ[d, N[x,wp]];
    If[NumericQ[w], acc = Precision[w], acc = 0.0];
    wp = wp * 2;
  ];
  Return[w];
];

f6[x_,d_] := Module[{},
  wp = Floor[1.1 * 10 + 3];
  acc = 0.0;
  While[acc < 10,
    w = BesselJ[I d, N[x,wp]];
    If[NumericQ[w], acc = Precision[w], acc = 0.0];
    wp = wp * 2;
  ];
  Return[w];
];

f7[x_,d_] := Module[{},
  wp = Floor[1.1 * 10 + 3];
  acc = 0.0;
  ww = Exp[Pi I / 3];
  While[acc < 10,
    w = Hypergeometric1F1[I d, 1+I, ww N[x,wp]];
    If[NumericQ[w], acc = Precision[w], acc = 0.0];
    wp = wp * 2;
  ];
  Return[w];
];

Print[];

MM=Length[X];

Print["F_Ni"]; Print[10^4]; Do[timing[f7,X[[i]],10^4], {i,MM,1,-1}]
Print[];

Do[
  Print["J_0"]; Print[10^j]; Do[timing[f1,X[[i]],10^j], {i,1,MM}];
  Print["I_0"]; Print[10^j]; Do[timing[f2,X[[i]],10^j], {i,1,MM}];
  Print["C_0"]; Print[10^j]; Do[timing[f3,X[[i]],10^j], {i,1,MM}];
  Print["K_0"]; Print[10^j]; Do[timing[f4,X[[i]],10^j], {i,1,MM}];
  Print["J_N"]; Print[10^j]; Do[timing[f5,X[[i]],10^j], {i,1,MM}];
  (* Print["J_Ni"]; Print[10^j]; Do[timing[f6,X[[i]],10^j], {i,1,MM}]; *)
  Print["F_Ni"]; Print[10^j]; Do[timing[f7,X[[i]],10^j], {i,1,MM}];,
  {j,3,4}];


