#include<iostream>
#include <stdlib.h>
#include <string.h>
#include"fun.h"
//octave_fun("arburg","signal", [1,2,3,4,5],2)
int main(void)
{
	FUNCCALL funcall;
	FUNCCALL *funptr = &funcall;
	funcall.n_in_arguments = 2;
	funcall.n_out_user = 1;

	FUNCARGS ins[funcall.n_in_arguments*funcall.n_out_user];
	FUNCARGS *argptr = ins;
	
	int a;
	int in_type[4] = {10,1};
	char str[3][20] = {"hamming","signal"};
	int si;
	double* d;
	int size_double;
	for(a = 0; a<funcall.n_in_arguments;a++)
	{
		if(in_type[a]==1)
		{
			ins[a].is_in_cmplx = 0;
			ins[a].n_in_rows = 1;
			ins[a].n_in_cols = 1;
			//if(a>2)
				//ins[a].n_in_cols = 1;
			
			size_double = ins[a].n_in_rows*ins[a].n_in_cols;
			ins[a].type = TYPE_DOUBLE;
			ins[a].in_data_real = malloc(sizeof(double)*size_double);
			d = (double *)ins[a].in_data_real;
			for(int i=0;i<size_double;i++)
				d[i] = (i+4);
		}
		else if(in_type[a]==10)
		{
			if(a==0)
				si=0;// "hamming";
			else if(a==1)
				si=1;// "pkg";
			else
				si=2;// "symmetric";

			ins[a].type = TYPE_STRING;
			int len = strlen(str[si]);
			ins[a].n_in_rows = 1;
			ins[a].n_in_cols = len;
			ins[a].in_data_real = malloc(sizeof(char)*len+1);
			char* c = (char *)ins[a].in_data_real;
			strcpy(c,str[si]);

			std::cout << "func string in main is: " << c << '\n';
		}

	}

	for(int j=0;j<funcall.n_in_arguments;j++)
	{
	if(in_type[j]==1)
		{
			d = (double *)ins[j].in_data_real;
			size_double = ins[j].n_in_rows*ins[j].n_in_cols;
			for(int i=0;i<size_double;i++)
				std::cout << "input data" << j<< " is: " << d[i] << '\n';
		}
	}

	fun(argptr, funptr);



	for(int j=0;j<funcall.n_out_user;j++)
	{
		double* rd = (double *)ins[j].out_data_real;
		for(int i=0;i<(ins[j].n_out_rows*ins[j].n_out_cols);i++)
			std::cout << "output data real: " << j<< " is: " << rd[i] << '\n';

		if(ins[j].is_out_cmplx==1)
		{
			double* cd = (double *)ins[j].out_data_img;
			for(int i=0;i<(ins[j].n_out_rows*ins[j].n_out_cols);i++)
				std::cout << "output data img: " << j<< " is: " << cd[i] << '\n';
		}
	}

	std::cout << "ins[0].n_in_rows is: " << ins[0].n_in_rows << '\n';
	std::cout << "ins[0].n_in_cols is: " << ins[0].n_in_cols << '\n';

	for(int i=0;i<funcall.n_in_arguments;i++)	
	{
		free(ins[i].in_data_real);

		if(ins[i].is_in_cmplx==1)
			free(ins[i].in_data_img);
	}

	for(int i=0;i<funcall.n_out_user;i++)	
	{
		free(ins[i].out_data_real);

		if(ins[i].is_out_cmplx==1)
			free(ins[i].out_data_img);
	}
	//free(ins[1].in_data);
	//free(ins[2].in_data);
	//free(ins[0].out_data);
return 0;
}
