test_pass=[]
res=[]

test1=0

/////////Test case for       cartprod                 //////////

A = [-1 -3 -5];
B = [10 11]; 
C = [0 1];
y = octave_fun("cartprod","linear-algebra",A,B,C)

anss = [-1.   10.   0.;
  -3.   10.   0.;
  -5.   10.   0.;
  -1.   11.   0.;
  -3.   11.   0.;
  -5.   11.   0.;
  -1.   10.   1.;
  -3.   10.   1.;
  -5.   10.   1.;
  -1.   11.   1.;
  -3.   11.   1.;
  -5.   11.   1.];

if(y==anss)
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("cartprod Test failed")
end

/////////////////////////////////////////////
/////////Test case for       funm                 //////////

a = octave_fun("magic",3);
y = octave_fun("funm","linear-algebra",a,"sin");

anss = [-0.3849805 1.0190868 0.0161816; 0.6179247 0.2167626 -0.1843995; 0.4173437 -0.5855616 0.8185058];

if(round((y*10000)/1000)==round((anss*10000)/1000))
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("funm Test failed")
end

/////////////////////////////////////////////
/////////Test case for       circulant_inv                 //////////

y = octave_fun("circulant_inv","linear-algebra",[2 3 5]);

anss = [3,1];

if(anss==size(y))
           test_pass=[test_pass,1]
else
	test_pass=[test_pass,0]
	disp("funm Test failed")
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
