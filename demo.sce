clc
disp("Testing octaves built in function hamming")
y = octave_fun("hamming",5)
pause

disp("Testing octaves built in function hamming with optional arguments")
y = octave_fun("hamming",5,"periodic")
pause

disp("Testing arburg function from signal package")
a = octave_fun("arburg","signal", [1,2,3,4,5],2)
pause


disp("Testing aryule function from signal package")
a = octave_fun("aryule","signal", [1,2,3,4,5],2)
pause


disp("Testing filter, xcorr and levinson function from signal package")
a = [1 0.1 -0.8];
v = 0.4;
rand("seed", 0);
w = sqrt(v)*rand(15000,1);
x=octave_fun("filter","signal",1,a,w);

r=octave_fun("xcorr","signal",x);

ar=octave_fun("levinson","signal",r,length(a)-1)
pause

disp("Testing sigmoid_train function from signal package")
s = octave_fun("sigmoid_train",0.1,[1:3],[4])
pause


disp("Testing circshift function from signal package")
 M = [1 2 3 4];
 R = octave_fun("circshift",M,[0 1])
pause


disp("Testing kaiser function from signal package")
win = octave_fun("kaiser",6,[0.2])
pause



disp("Testing autoreg_matrix function from signal package")
m = octave_fun("autoreg_matrix",[1 2 3],[2])
pause


disp("Testing arch_rnd function from signal package")
a = [1 2 3 4 5];
b = [7 8 9 10];
t = 5 ;
rand("seed", 0)
m = octave_fun("arch_rnd",a,b,t)
pause


disp("Testing postpad function from signal package")
y = octave_fun("postpad",[1 2 3],6)
pause


disp("Testing wconv function from signal package")
a = [1 2 3 4 5];
b = [7 8 9 10];
y = octave_fun("wconv",[1],a,b)
pause


disp("Testing dctmtx function from signal package")
T = octave_fun("dctmtx",[3])
pause


disp("Testing medfilt1 function from signal package")

fs = 100;
t = 0:1/fs:1;
x = sin(2*%pi*t*3)+0.25*sin(2*%pi*t*40);

y = octave_fun("medfilt1","signal",x,10);
pause


disp("Testing arma_rnd function from signal package")

a = [1 2 3 4 5];
b = [7; 8; 9; 10; 11];
t = 5 ;
v = 10 ;
n = 100 ;
rand("seed", 0)
m = octave_fun("arma_rnd","signal",a, b, v, t, n)
pause


disp("Testing ncauer function from signal package")
[z p g] = octave_fun("ncauer","signal",3, 10, 4)
pause


disp("Testing ellipap function from signal package")
[z p g] = octave_fun("ellipap","signal",4, 3, 10)
pause


disp("Testing besselap function from signal package")
[z p g] = octave_fun("besselap","signal",5)
pause


disp("Testing zp2tf function from signal package")
[num, den] = octave_fun("zp2tf","signal",[1 2 3], [4 5 6], 5)
pause

disp("Testing tf2zp function from signal package")
[z p k] = octave_fun("tf2zp","signal",[1 2 3], [4 5 6]);
pause


disp("Testing ctrb function from control package")
y = octave_fun("ctrb","control",[1, 0; 0, -0.5], [8; 8]);
pause
