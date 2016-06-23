Print["J_3(3.25)"];
u = N[325/100,10];
Print[Timing[Do[BesselJ[3,u], {i,1,100000}];] / 100000]
u = N[325/100,100];
Print[Timing[Do[BesselJ[3,u], {i,1,1000}];] / 1000]
u = N[325/100,1000];
Print[Timing[Do[BesselJ[3,u], {i,1,100}];] / 100]
u = N[325/100,10000];
Print[Timing[Do[BesselJ[3,u], {i,1,10}];] / 10]
u = N[325/100,100000];
Print[Timing[Do[BesselJ[3,u], {i,1,1}];] / 1]
Print["J_3(Pi)"];
u = N[Pi,10];
Print[Timing[Do[BesselJ[3,u], {i,1,100000}];] / 100000]
u = N[Pi,100];
Print[Timing[Do[BesselJ[3,u], {i,1,1000}];] / 1000]
u = N[Pi,1000];
Print[Timing[Do[BesselJ[3,u], {i,1,100}];] / 100]
u = N[Pi,10000];
Print[Timing[Do[BesselJ[3,u], {i,1,10}];] / 10]
u = N[Pi,100000];
Print[Timing[Do[BesselJ[3,u], {i,1,1}];] / 1]
Print[Timing[Do[BesselJ[3,u], {i,1,1}];] / 1]
Print["J_Pi(Pi)"];
u = N[Pi,10];
Print[Timing[Do[BesselJ[u,u], {i,1,100000}];] / 100000]
u = N[Pi,100];
Print[Timing[Do[BesselJ[u,u], {i,1,1000}];] / 1000]
u = N[Pi,1000];
Print[Timing[Do[BesselJ[u,u], {i,1,100}];] / 100]
u = N[Pi,10000];
Print[Timing[Do[BesselJ[u,u], {i,1,1}];] / 1]
u = N[Pi,100000];
Print[Timing[Do[BesselJ[u,u], {i,1,1}];] / 1]
Print[Timing[Do[BesselJ[u,u], {i,1,1}];] / 1]
Print["0F1"];
u = N[-Pi^2/4,10];
v = N[Pi+1,10];
Print[Timing[Do[Hypergeometric0F1[v,u], {i,1,100000}];] / 100000]
u = N[-Pi^2/4,100];
v = N[Pi+1,100];
Print[Timing[Do[Hypergeometric0F1[v,u], {i,1,1000}];] / 1000]
u = N[-Pi^2/4,1000];
v = N[Pi+1,1000];
Print[Timing[Do[Hypergeometric0F1[v,u], {i,1,100}];] / 100]
u = N[-Pi^2/4,10000];
v = N[Pi+1,10000];
Print[Timing[Do[Hypergeometric0F1[v,u], {i,1,1}];] / 1]
u = N[-Pi^2/4,100000];
v = N[Pi+1,100000];
Print[Timing[Do[Hypergeometric0F1[v,u], {i,1,1}];] / 1]
Print[Timing[Do[Hypergeometric0F1[v,u], {i,1,1}];] / 1]
Print["K_3(3.25)"];
u = N[325/100,10];
Print[Timing[Do[BesselK[3,u], {i,1,100000}];] / 100000]
u = N[325/100,100];
Print[Timing[Do[BesselK[3,u], {i,1,1000}];] / 1000]
u = N[325/100,1000];
Print[Timing[Do[BesselK[3,u], {i,1,100}];] / 100]
u = N[325/100,10000];
Print[Timing[Do[BesselK[3,u], {i,1,10}];] / 10]
u = N[325/100,100000];
Print[Timing[Do[BesselK[3,u], {i,1,1}];] / 1]
Print[Timing[Do[BesselK[3,u], {i,1,1}];] / 1]
Print["K_3(Pi)"];
u = N[Pi,10];
Print[Timing[Do[BesselK[3,u], {i,1,100000}];] / 100000]
u = N[Pi,100];
Print[Timing[Do[BesselK[3,u], {i,1,1000}];] / 1000]
u = N[Pi,1000];
Print[Timing[Do[BesselK[3,u], {i,1,100}];] / 100]
u = N[Pi,10000];
Print[Timing[Do[BesselK[3,u], {i,1,10}];] / 10]
u = N[Pi,100000];
Print[Timing[Do[BesselK[3,u], {i,1,1}];] / 1]
Print[Timing[Do[BesselK[3,u], {i,1,1}];] / 1]

