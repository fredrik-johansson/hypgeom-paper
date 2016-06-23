$MaxExtraPrecision = 1000

Print["16"];

good = 0;
fair = 0;
poor = 0;
wrong = 0;
err = 0;

error[f_,nu_,z_] := Module[{},
    a = N[f[nu,z],16];
    b = N[f[SetPrecision[nu,Infinity], SetPrecision[z,Infinity]],100];
    e = N[Abs[a-b]/Abs[b]];
    If[Precision[a] < 14, Print["exit"]; Exit[]];
    If[e < 2^-40, good++, If[e < 2^-20, fair++, If[e < 2^-1, poor++, wrong++]]];
    (* If[e >= 2^-1, Print[f, " ", N[nu,15], " ", N[z,15], " ", N[a,15], " ", N[b,15], " ", e]]; *)
    Return[e];
];

Do[Do[Do[Do[
    Module[{nu=SetPrecision[N[(183 i+178 j I)/10],Infinity], z=SetPrecision[N[(186 k + 11)/10 + (1740 l + 21) I/100],Infinity]},
    {e1=error[BesselJ,nu,z];
     e2=error[BesselY,nu,z]; 
     e3=error[HankelH1,nu,z];
     e4=error[HankelH2,nu,z];
     e5=error[BesselJ,nu+1,z];
     e6=error[BesselY,nu+1,z];
     e7=error[HankelH1,nu+1,z];
     e8=error[HankelH2,nu+1,z];
     err = Max[err,Max[e1,e2,e3,e4,e5,e6,e7,e8]];
     Print[good, " ", fair, " ", poor, " ", wrong];
    }],
    {l,-3,3}],{k,-3,3}],{j,-3,3}],{i,-3,3}]

