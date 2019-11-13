#define fun_h__
//extern "C" int fun (double* answ, double* in1, int in1_row, std::string name, std::string opt);

extern "C"
{

	typedef enum
	{
		TYPE_DOUBLE,
		TYPE_STRING,
	}FUNCTYPE;

	typedef struct
	{
		FUNCTYPE type;
		int n_in_rows;
		int n_in_cols;
		int n_out_rows;
		int n_out_cols;
		int is_in_cmplx;
		int is_out_cmplx;
		void* in_data_real;
		void* in_data_img;
		void* out_data_real;
		void* out_data_img;
	}FUNCARGS;
	
	typedef struct {
	int n_in_arguments; // number of input arguments
	int n_out_arguments; // number of output arguments
	int n_out_user; // number of output arguments
	char *err; // Name
	//char *package; //Name of octave package to be loaded
	FUNCARGS *argument;
} FUNCCALL;

	int fun(FUNCARGS *arr, FUNCCALL *call);
}
