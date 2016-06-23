$MaxExtraPrecision = 1000

Print["machine"];
Print[Timing[Do[Do[Do[Do[Module[{nu=N[(183 i+178 j I)/10], z=N[(186 k + 11)/10 + (1740 l + 21) I/100]},
    {BesselJ[nu,z],
     BesselY[nu,z], 
     HankelH1[nu,z], 
     HankelH2[nu,z],
     BesselJ[nu+1,z],
     BesselY[nu+1,z],
     HankelH1[nu+1,z],
     HankelH2[nu+1, z]}],
    {l,-3,3}],{k,-3,3}],{j,-3,3}],{i,-3,3}]]]

Print["N, 16"];
Print[Timing[Do[Do[Do[Do[Module[{d=16,nu=SetPrecision[N[(183 i+178 j I)/10],Infinity],
    z=SetPrecision[N[(186 k + 11)/10 + (1740 l + 21) I/100],Infinity]},
    {N[BesselJ[nu,z],d],
     N[BesselY[nu,z],d], 
     N[HankelH1[nu,z],d], 
     N[HankelH2[nu,z],d],
     N[BesselJ[nu+1,z],d],
     N[BesselY[nu+1,z],d],
     N[HankelH1[nu+1,z],d],
     N[HankelH2[nu+1, z],d]}],
    {l,-3,3}],{k,-3,3}],{j,-3,3}],{i,-3,3}]]]

Print["N, 34"];
Print[Timing[Do[Do[Do[Do[Module[{d=34,nu=SetPrecision[N[(183 i+178 j I)/10],Infinity],
    z=SetPrecision[N[(186 k + 11)/10 + (1740 l + 21) I/100],Infinity]},
    {N[BesselJ[nu,z],d],
     N[BesselY[nu,z],d], 
     N[HankelH1[nu,z],d], 
     N[HankelH2[nu,z],d],
     N[BesselJ[nu+1,z],d],
     N[BesselY[nu+1,z],d],
     N[HankelH1[nu+1,z],d],
     N[HankelH2[nu+1, z],d]}],
    {l,-3,3}],{k,-3,3}],{j,-3,3}],{i,-3,3}]]]

