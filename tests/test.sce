
//exec build.sce
test_pass=[]
res=[]

test1=0
/////////Test case for       2) arburg                  //////////

a = octave_fun("arburg","signal", [1,2,3,4,5],2);
a = round(a*10000)/10000;

if(a == [1.  -1.8639    0.9571])
    test_pass=[test_pass,1]
else
    test_pass=[test_pass,0]
    disp("arburg test failed")
end

/////////Test case for       4) aryule                  //////////

a = octave_fun("aryule","signal", [1,2,3,4,5],2);
a = round(a*10000)/10000;

if(a == [1.  -0.814    0.1193])
    test_pass=[test_pass,1]
else
    test_pass=[test_pass,0]
    disp("aryule test failed")
end

/////////Test case for       38)levinson                  //////////

a = [1 0.1 -0.8];
v = 0.4;
rand("seed", 0);
w = sqrt(v)*rand(15000,1);
x=octave_fun("filter","signal",1,a,w);

r=octave_fun("xcorr","signal",x);

ar=octave_fun("levinson","signal",r,length(a)-1);

ar = round(ar*10000)/10000;

if(ar ~= 0)
           test_pass=[test_pass,1]
    else
	test_pass=[test_pass,0]
	disp("levinson Test failed")
end

/////////Test case for       **)sigmoid_train                  //////////

s = octave_fun("sigmoid_train",0.1,[1:3],[4]);
s = round(s*10000)/10000

if(s == 0.2737)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("sigmoid_train Test failed")
end

/////////Test case for       **)circshift                  /////////

 M = [1 2 3 4];
 R = octave_fun("circshift",M,[0 1]);

if(R == [4 1 2 3])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("circshift failed")
end

/////////////////////////////////////////////
/////////Test case for       **)kaiser                 //////////

win = octave_fun("kaiser",6,[0.2]) ;
win = round(win*10000)/10000;

if(win == [ 0.9901; 0.9964; 0.9996; 0.9996; 0.9964; 0.9901 ])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("kaiser Test failed")
end

/////////////////////////////////////////////

/////////////////////////////////////////////


/////////Test case for       autoreg_matrix                 //////////
m = octave_fun("autoreg_matrix",[1 2 3],[2]);

if(m == [1 0 0; 1 1 0; 1 2 1])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("autoreg_matrix test failed")
end

/////////////////////////////////////////////
/////////Test case for       arch_rnd                 //////////

a = [1 2 3 4 5];
b = [7 8 9 10];
t = 5 ;
rand("seed", 0)
m = octave_fun("arch_rnd",a,b,t);
m = round(m*1000)/1000

if(m ~=0 )
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("arch_rnd Test failed")
end

/////////////////////////////////////////////

/////////Test case for       postpad                 //////////

y = octave_fun("postpad",[1 2 3],6);

if(y == [1 2 3 0 0 0 ] )
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("postpad Test failed")
end


/////////Test case for       wconv                 //////////
a = [1 2 3 4 5];
b = [7 8 9 10];
y = octave_fun("wconv",[1],a,b);

if(y == [7.    22.    46.    80.    114.    106.    85.   50.])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("wconv Test failed")
end
/////////Test case for       dctmtx                 //////////
T = octave_fun("dctmtx",[3]);
T = round(T*10000)/10000;
if(T == [0.5774  0.5774  0.5774; 0.7071  0  -0.7071; 0.4082 -0.8165 0.4082])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("dctmtx Test failed")
end

/////////Test case for       40) medfilt1                  //////////


fs = 100;
t = 0:1/fs:1;
x = sin(2*%pi*t*3)+0.25*sin(2*%pi*t*40);

y = octave_fun("medfilt1","signal",x,10);
y = round(y*10000)/10000 ;
y = y'

if(length(y) ~= 0)
           test_pass=[test_pass,1]
    else
	test_pass=[test_pass,0]
	disp("medfilt1 Test failed")
end

/////////////////////////////////////////////
/////////Test case for       arma_rnd                 //////////

a = [1 2 3 4 5];
b = [7; 8; 9; 10; 11];
t = 5 ;
v = 10 ;
n = 100 ;
rand("seed", 0)
m = octave_fun("arma_rnd","signal",a, b, v, t, n);
m = round(m) ;

if(m ~= 0)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("arma_rnd Test failed")
end

/////////Test case for       ncauer                 //////////

[z p g] = octave_fun("ncauer","signal",3, 10, 4);
g = round(g*10000)/10000;

if(g == 0.32400)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("ncauer Test failed")
end

/////////Test case for       ellipap                 //////////

[z p g] = octave_fun("ellipap","signal",4, 3, 10);
g = round(g*10000)/10000;

if(g == 0.324)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("ellipap Test failed")
end

[z p g] = octave_fun("besselap","signal",5);
g = round(g*10000)/10000;
p = round(p*10000)/10000;

if(g == 1)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("besselap Test failed")
end

/////////Test case for       zp2tf                 //////////

[num, den] = octave_fun("zp2tf","signal",[1 2 3], [4 5 6], 5);
num = round(num*10000)/10000;
den = round(den*10000)/10000;

if(num == [5 -30 55 -30] & den == [1.  -15.    74.   -120])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("zp2tf Test failed")
end

/////////Test case for       tf2zp                 //////////

[z p k] = octave_fun("tf2zp","signal",[1 2 3], [4 5 6]);
k = round(k*10000)/10000;
p = round(p*10000)/10000;
z = round(z*10000)/10000;

if(k == 0.25)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("tf2zp Test failed")
end

/////////Test case for       buttap                 //////////

n = 5 ;
[z p g] = octave_fun("buttap", n);
g = round(g*10000)/10000;

if(g == 1)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("buttap Test failed")
end

/////////Test case for       cheb1ap                 //////////

[z p g] = octave_fun("cheb1ap", 10, 3);
g = round(g*10000)/10000;

if(g == 0.002)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("cheb1ap Test failed")
end

/////////Test case for       sftrans                 //////////
//fc = 100;
//[z p k] = octave_fun("tf2zp","signal",[1 2 3], [4 5 6])
//[Sz, Sp, Sg] = octave_fun("sftrans",z, p, k, 2*%pi*fc, %f);
//Sz = round(Sz*10000)/10000;


//if(Sz ~= 0)
//           test_pass=[test_pass,1]
//else
//	test_pass=[test_pass,0]
//	disp("sftrans Test failed")
//end

/////////Test case for       bilinear                 //////////

[b a] = octave_fun("bilinear","signal",[1 2 3], [4 5 6], 1, 1);
b = round(b*10000)/10000;
a = round(a*10000)/10000;


if(round(a) == [1 7 18 14])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("bilinear Test failed")
end
/////////Test case for       buttord                 //////////
[n, Wn] = octave_fun("buttord",40/500, 150/500, 3, 60);
Wn = round(Wn*10000)/10000;

if(n == 5 & Wn == 0.08)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("buttord Test failed")
end

/////////Test case for       butter                 //////////

[b a] = octave_fun("butter","signal",4,0.3,"high")
b = round(b*10000)/10000;
a = round(a*10000)/10000;

if(b == [0.2754 -1.1017 1.6525 -1.1017 0.2754] & a == [1 -1.5704 1.2756 -0.4844 0.0762])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("butter Test failed")
end

/////////Test case for       cheb1ord                 //////////

[n, Wn]=octave_fun("cheb1ord","signal",[0.25 0.3],[0.24 0.31],3,10)
Wn = round(Wn*10000)/10000;

if(n == 3 & Wn == [0.25 0.3])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("cheb1ord Test failed")
end

/////////Test case for       cheby1                 //////////

[z, p, k]=octave_fun("cheby1","signal",2,6,0.7,"high")// Note it shld return k as well
z = round(z*10000)/10000;
p = round(p*10000)/10000;
k = round(k*10000)/10000;

if(z == [1;1] & real(p) == [-0.6292; -0.6292] & k == 0.0556)
   test_pass=[test_pass,1]
else
	test_pass=[test_pass,0];
	disp("cheby1 Test failed")
end

/////////Test case for       cheb2ord                 //////////

Wp = 40/500;
Ws = 150/500;
Rp = 3;
Rs = 60;
[n,Ws] = octave_fun("cheb2ord",Wp,Ws,Rp,Rs)
Ws = round((Ws*10000)/1000);

if(n == 4 & Ws == 3)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("cheb2ord Test failed")
end

/////////////////////////////////////////////
res=find(test_pass==0)

if(res~=[])
    disp("One or more tests failed in test1")
		disp(length(test_pass),"Total functions tested:")
		//exit(1)
else
disp(length(test_pass),"Total functions tested:")
disp("ALL OK")
//exit()
end
