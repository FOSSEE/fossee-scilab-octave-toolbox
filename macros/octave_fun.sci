function [y] = octave_fun()
    //   Calls an octave function with given inputs and returns the expected output
    //
    //   Syntax
    //   [y1, y2, ...] = octave_fun("octave_function",input1,input2,...)
    //   [y1, y2, ...] = octave_fun("octave_function",input1,input2,...,optional_input1,optional_input2,...)
    //   [y1, y2, ...] = octave_fun("octave_function","octave_package",input1,input2,...)
    //   [y1, y2, ...] = octave_fun("octave_function","octave_package",input1,input2,...,optional_input1,optional_input2,...)
    //   
    //   Parameters
    //   y : ouput as returned by octave. It can be a vector or matrix of doubles
    //   octave_function : name of the function in octave that has to be called. It has to be a string in double quotes
    //   input : input as expected by the octave function. It can be a vector or matrix of doubles
    //   optional_input : an optional argument that the given octave function can accept. It has to be a string in double quotes
    //   octave_package : name of the package in octave that has to be loaded as required by the octave function. It has to be a string in double quotes
    //   
    //   Description
    //   This function accepts an octave function name with the relevant inputs and returns the output as generated. It requires Octave to be installed along with necessary packages.
    //
    //   <latex>
    //  \begin{eqnarray}
    // &\mbox{min}_{x}
    // & C^T⋅x \\
    // & \text{subject to}& A⋅x = b \\
    // & & G⋅x \preceq_K h \\
    // & & x_i \in \{0,1\}, i \in \!\, bool_vars\
    // & & x_j \in \!\, \mathbb{Z}, i \in \!\, int_vars\\
    //  \end{eqnarray}
    //   </latex>
    //
    // Examples 
    // // Finding the inverse of a matrix using octave
    // A=[1 2 3;4 5 6;7 8 0]
		// y = octave_fun("inv",A)
		// y*A
		//
    // Examples
    //
    // // Finding the roots of a polynomial using its coefficients as inputs, using octave
    // p = [1 2 3];
    // y = octave_fun("roots",p)
		//
    // Examples
    //
    // // Generating filter coefficients of a Hamming window of length M, using octave.
		// M = 5
    // y = octave_fun("hamming",M)
		//
    // Examples
    //
    // // Generating filter coefficients of a Hamming window of length M with optional arguments, using octave.
		// M = 5
    // y = octave_fun("hamming",M,"periodic")
		//
		//
    // Examples
    //
    // // Generating an elliptic or Cauer filter with given passband ripple and stopband attenuation, using octave and its "signal" package. 
		// // See help in octave for more information about "ellip" function. 
		// // Note that this example requires the "signal" package to be installed in octave.
    // [b, a]=octave_fun("ellip","signal",5,1,90,[0.1 0.2])
		//
// Authors
// Rupak Rokade
endfunction
