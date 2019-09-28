test_pass=[]
res=[]

test1=0
exec loader.sce
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

if(ar == [1 0.0984 -0.793])
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

if(m == [ 7.211
    65.48
    654.008
    7194.657
    78364.905 ])
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

if(y ~= 0)
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

if(m == [    61401.
    158177.
    407440.
    1049604.
    2703841. ])
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

[z p k] = octave_fun("zp2tf","signal",[1 2 3], [4 5 6]);
k = round(k*10000)/10000;
p = round(p*10000)/10000;
z = round(z*10000)/10000;

if(k == 0.25 & p == [-0.625+1.0533*%i; -0.625-1.0533*%i] & z == [-1+1.4142*%i; -1-1.4142*%i])
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("tf2zp Test failed")
end
/////////////////////////////////////////////
res=find(test_pass==0)

if(res~=[])
    disp("One or more tests failed in test1")
    disp(length(test_pass),"Total functions tested in test1:")
    test1=1;
end
