#define fun_h__
//extern "C" int fun (double* answ, double* in1, int in1_row, std::string name, std::string opt);

extern "C"
{
typedef struct octave_fun
{
	char* name1 = "";
	char* name2 = "";
	double* input1;
	int size_input1[2];
	double* output1;
	int size_output1[2];
}octf;

int fun(octf *inp);
}
