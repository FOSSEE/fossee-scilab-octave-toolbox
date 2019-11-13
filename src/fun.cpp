#include <iostream>
#include <stdlib.h>
#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/interpreter.h>
#include <math.h>
#include <string>
#include "fun.h"

extern "C"
{
	int fun(FUNCARGS *inp, FUNCCALL *funcall)
	{

		static octave::interpreter interpreter;
		bool status = interpreter.initialized();
		
		if(status==false)
		{
		interpreter.initialize ();
		int status_exec = interpreter.execute ();

			if (status_exec != 0)
			{
				std::cerr << "creating embedded Octave interpreter failed!"
						<< std::endl;
			}
		}
		
		try
		{	
			octave_value_list in;
			unsigned int k;
			int l;
			int str_count = 0;
			char str_fun[20];
			char str_pkg[20];
			int pkg=0;
			int nouts;
			for(l=0;l<funcall->n_in_arguments;l++)
			{
				if(inp[l].type==TYPE_DOUBLE)
				{
					if(inp[l].is_in_cmplx==1)
					{
						ComplexMatrix matr = ComplexMatrix (inp[l].n_in_rows,inp[l].n_in_cols); 
						double* id_real = (double *)inp[l].in_data_real;
						double* id_img = (double *)inp[l].in_data_img;
						k=0;
						for (int r=0;r<inp[l].n_in_rows;r++) 
							{ 
							for(int c=0;c<inp[l].n_in_cols;c++) 
								{ 
								Complex cc(id_real[k],id_img[k]); 
								matr(r,c) = cc;
								k++;
								} 
							} 
						in(l-str_count) = octave_value(matr);
					}
					else
					{
						Matrix inMatrix_x(inp[l].n_in_rows,inp[l].n_in_cols);
						double* id = (double *)inp[l].in_data_real;
						k=0;
						for( unsigned int i = 0; i < inp[l].n_in_rows; i++ )
						{
							for( unsigned int j = 0; j < inp[l].n_in_cols; j++ )
							{
									inMatrix_x(i, j) = id[k];
									k++;
							}
						}
						in(l-str_count) = inMatrix_x;
					}
				}
				else if(inp[l].type==TYPE_STRING)
				{
					//std::cout << "In fun string. l is : " << l << '\n';
					
					char* c = (char *)inp[l].in_data_real;
					//std::cout << "String is: " << c << '\n';
					if(l==0)
						strcpy(str_fun,c);
					else if(l==1)
					{
						strcpy(str_pkg,c);
						pkg=1;
					}					
					else
						in(l-str_count) = c;

					str_count++;
					//std::cout << "String is: " << c << '\n';
				}
			}

			if(pkg==1)
			{
				//std::cout << "loading package " << str_pkg << '\n';
				octave::feval ("pkg", ovl ("load", str_pkg), 0);
			}

			octave_value_list out = octave::feval (str_fun, in, funcall->n_out_user);


			int row;
			int col;
			nouts = out.length();
			funcall->n_out_arguments = nouts;
//std::cout << "funcall->n_out_arguments is: " << funcall->n_out_arguments << '\n';

			for( unsigned int ii = 0; ii < nouts; ii++ )
			{
				if(out(ii).iscomplex()==1)
				{
					inp[ii].is_out_cmplx=1;
					//std::cout << "out "<< ii<< " is complex" << '\n';
					ComplexMatrix cmOut(out(ii).complex_matrix_value());
					//std::cout << "cmOut "<< cmOut << '\n';
					//std::cout << "Out(ii) "<< out(ii).complex_matrix_value() << '\n';
					//std::cout << "out(ii) "<< out(ii) << '\n';
					row = cmOut.rows();
					col = cmOut.columns();
					inp[ii].n_out_rows = row;
					inp[ii].n_out_cols = col;
					k=0;
					inp[ii].out_data_real = malloc(sizeof(double)*(row*col));
					inp[ii].out_data_img = malloc(sizeof(double)*(row*col));
					double* rd = (double *)inp[ii].out_data_real;
					double* cd = (double *)inp[ii].out_data_img;
					for(unsigned int i=0;i<row;i++)
					{
						for(unsigned int j=0;j<col;j++)
						{
							rd[k]=real(cmOut(k));
							cd[k]=imag(cmOut(k));
							//std::cout << "out img "<< k << " is :" << (double)imag(cmOut(k)) << '\n';
							k++;
						}
					}
				}
				else
				{
					//std::cout << "out "<< ii<< " is NOT complex" << '\n';
					inp[ii].is_out_cmplx=0;
					Matrix mOut(out(ii).matrix_value());
					row = mOut.rows();
					col = mOut.columns();
					inp[ii].n_out_rows = row;
					inp[ii].n_out_cols = col;
					k=0;
					inp[ii].out_data_real = malloc(sizeof(double)*(row*col));
					double* dd = (double *)inp[ii].out_data_real;
					for(unsigned int i=0;i<row;i++)
					{
						for(unsigned int j=0;j<col;j++)
						{
							dd[k]=mOut(k);
							k++;
						}
					}
				}
			}
		}
		catch (const octave::exit_exception& ex)
		{
			std::cerr << "Octave interpreter exited with status = "
					<< ex.exit_status () << std::endl;
			return 1;
		}
		catch (const octave::execution_exception&)
		{
			std::cerr << "error encountered in Octave evaluator!" << std::endl;
			return 1;
		}
		return 0;
	}
}
