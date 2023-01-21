#include "GeneralRegression.h"

/*
 *@brief This namespace contains the functions that do the linear regression on
 *a basis of functions using the Eigen library
 *
 */

namespace TheRegression {

/*
 *@brief This functions sets up the Eigen matrix Q of type Xd (dense matrix
 *because the data isn't sparse) such that:
 *@brief (Q)_(i, j) = (phi_j(x_i)) where phi_j denotes the j-th function of the
 *basis and x_i the i-th chessboard
 *@param basis:  a given basis of functions chosen from the different bases
 *below
 *@param X: the chessboard (we only care for the positions of the pons so for
 *each i: X[2 * i] is the position of the i-th chessboard top pons) and X[2 * i
 *+ 1] the i-th chessboards bottom pons
 *@param dimension: dimension of the function basis (probably always 23)
 *@param num_data_points: how manys chessboards we are given
 *@return Q: an eigen matrix as described above.
 */

Eigen::MatrixXd setUpQ(Func *basis, int **X, int dimension,
											 int num_data_points) {
	Eigen::MatrixXd Q(num_data_points, dimension);

	for (int j = 0; j < dimension; j++) {
		for (int i = 0; i < num_data_points; i++) {
			Q(i, j) = basis[j].Eval(X[2 * i], X[2 * i + 1]);
		}
	}

	return Q;
}

/*
 *@brief This function creates the vector containing the closness (on a interval
 *from 0 to 1) of each give chessboard in order
 *@param data_outputs: the data outputs for closness given by the data team
 *@param num_data_points: how manys chessboards we are given
 *@return Y: the vector described above.
 */

Eigen::VectorXd setUpYVect(double *data_outputs, int num_data_points) {
	Eigen::VectorXd Y(num_data_points);
	for (int i = 0; i < num_data_points; i++) {
		Y(i) = data_outputs[i];
	}

	return Y;
}

/*
 *@brief This function uses the two function below to create  Q and Y. Then,
 *using a statistical method  it determines the best linear
 *@brief combination of the basis of functions to best approximate the outputs
 *in Y. This regression is based on least square method.
 *@brief note that at some point we ad a matrix mu. The reason for this is that
 *we need to make sure trans_Q * Q is invertible, by adding
 *@brief and identity matrix times a small value, the new obtained matrix isn't
 *invertible iff minus the small value is an eigenvalue which isn't probable.
 *@param basis:  a given basis of functions chosen from the different bases
 *below
 *@param X: the chessboard (we only care for the positions of the pons so for
 *each i: X[2 * i] is the position of the i-th chessboard top pons) and X[2 * i
 *+ 1] the i-th chessboards bottom pons
 *@param dimension: dimension of the function basis (probably always 23)
 *@param num_data_points: how manys chessboards we are given
 *@return theta: of length dimension, gives the best linear combination of the
 *basis of functions to best approximate the data.
 */

Eigen::VectorXd bestFitF(Func *basis, int **X, double *data_outputs,
												 int dimension, int num_data_points) {

	Eigen::MatrixXd Q = setUpQ(basis, X, dimension, num_data_points);
	Eigen::VectorXd Y = setUpYVect(data_outputs, num_data_points);

	Eigen::MatrixXd trans_Q = Q.transpose();
	Eigen::MatrixXd mu(23, 23);
	mu.setIdentity();
	Eigen::MatrixXd helper_M = (trans_Q * Q + mu * 0.001).inverse();

	return (helper_M * trans_Q) * Y;
}

} // namespace TheRegression

/*
 *@brief This first namespace enables us to Genearate a basis based on the
 *square distance function solely.
 *
 */

namespace SqrtDifBasis {

/*
 *@brief this method constructs the basis of functions described below:
 *@brief     - first we have the square distance between the heights of
 *consecutive pons of the top player
 *@brief     - same thing for the bottom player
 *@brief     - then the square difference between pons of distinct players that
 *share the same collumn
 *@brief     - finally the last function is the distance between the average
 *height of the players and 3.5 (middle of the board)
 *@return basis: the basis described above.
 */

Func *GenerateBasis() {
	Func *basis = new Func[23];

	for (int i = 0; i < 7; i++) {
		basis[i].InitFunc(1, i, 1, 2);		 // top pons consecutive difference
		basis[i + 7].InitFunc(1, i, 1, 1); // bottom pons consecutive difference
	}
	for (int j = 0; j < 8; j++) {
		basis[j + 14].InitFunc(1, j, 2, -1);
	}

	basis[22].InitFunc(0, -1, 2, -1);

	return basis;
}

} // namespace SqrtDifBasis
/*
 *@brief This first namespace enables us to Genearate a basis based on the
 *modified erf distance function solely.
 *
 */

namespace AbsErfBasis {
/*
 *@brief this method constructs the basis of functions described below:
 *@brief     - first we have the modified erf distance  between the heights of
 *consecutive pons of the top player
 *@brief     - same thing for the bottom player
 *@brief     - then the modified erf distance between pons of distinct players
 *that share the same collumn
 *@brief     - finally the last function is the distance between the average
 *height of the players and 3.5 (middle of the board)
 *@return basis: the basis described above.
 */

Func *GenerateBasis() {
	Func *basis = new Func[23];

	for (int i = 0; i < 7; i++) {
		basis[i].InitFunc(2, i, 1, 2);		 // top pons consecutive difference
		basis[i + 7].InitFunc(2, i, 1, 1); // bottom pons consecutive difference
	}
	for (int j = 0; j < 8; j++) {
		basis[j + 14].InitFunc(2, j, 2, -1);
	}

	basis[22].InitFunc(0, -1, 2, -1);

	return basis;
}

} // namespace AbsErfBasis

namespace AbsSqrtDifBasis {
Func *GenerateBasis() {
	Func *basis = new Func[23];

	for (int i = 0; i < 7; i++) {
		basis[i].InitFunc(2, i, 1, 2);		 // top pons consecutive difference
		basis[i + 7].InitFunc(2, i, 1, 1); // bottom pons consecutive difference
	}
	for (int j = 0; j < 8; j++) {
		basis[j + 14].InitFunc(1, j, 2, -1);
	}

	basis[22].InitFunc(0, -1, 2, -1);

	return basis;
}

} // namespace AbsSqrtDifBasis

namespace SqrtAbsDifBasis {
Func *GenerateBasis() {
	Func *basis = new Func[23];

	for (int i = 0; i < 7; i++) {
		basis[i].InitFunc(1, i, 1, 2);		 // top pons consecutive difference
		basis[i + 7].InitFunc(1, i, 1, 1); // bottom pons consecutive difference
	}
	for (int j = 0; j < 8; j++) {
		basis[j + 14].InitFunc(2, j, 2, -1);
	}

	basis[22].InitFunc(0, -1, 2, -1);

	return basis;
}
} // namespace SqrtAbsDifBasis

namespace EvaluationFunction {

float Evaluate(Func *basis, Eigen::VectorXd theta, int *l_top_pons,
							 int *l_bottom_pons, int dimension) {
	float output_val = 0;
	for (int i = 0; i < dimension; i++) {
		output_val += basis[i].Eval(l_top_pons, l_bottom_pons) * theta[i];
	}
	if (output_val >= 1) {
		return 1;
	}

	else if (output_val <= 0) {
		return 0;
	}

	return output_val;
}
/*
 *@brief this function enables us to test how well the ai performs on the data
 *that wasn't used for training it but for testing.
 *@return emp_risk: the empirical risk of the outputed data.
 */

float TestAi(Func *basis, Eigen::VectorXd theta, int **test_data_points,
						 double *outputs, int dimension, int num_data_points) 
{
	float emp_risk = 0;

	for (int i = 0; i < num_data_points; i++) {
		emp_risk +=
				pow(outputs[i] - Evaluate(basis, theta, test_data_points[2 * i],
																	test_data_points[2 * i + 1], dimension),
						2);
	}

	return emp_risk / (float)num_data_points;

	
}

Eigen::VectorXd getTheta() 
{
	Func *basis = SqrtDifBasis::GenerateBasis();

	// training data set for ai:
	double data_outputs[500];
	int *X[1000];

#pragma region declarations
	X[0] = new int[8]{3, 3, 4, 1, 1, 2, 2, 5};
	X[1] = new int[8]{4, 4, 5, 2, 2, 3, 3, 6};

	X[2] = new int[8]{4, 3, 3, 4, 3, 3, 5, 4};
	X[3] = new int[8]{5, 4, 4, 5, 4, 4, 6, 5};

	X[4] = new int[8]{5, 4, 2, 2, 2, 5, 1, 4};
	X[5] = new int[8]{6, 5, 3, 3, 3, 6, 2, 5};

	X[6] = new int[8]{5, 5, 3, 3, 2, 2, 3, 5};
	X[7] = new int[8]{6, 6, 4, 4, 3, 3, 4, 6};

	X[8] = new int[8]{4, 3, 4, 3, 3, 3, 5, 4};
	X[9] = new int[8]{5, 4, 5, 4, 4, 4, 6, 5};

	X[10] = new int[8]{3, 3, 5, 4, 3, 1, 4, 4};
	X[11] = new int[8]{4, 4, 6, 5, 4, 2, 5, 5};

	X[12] = new int[8]{4, 1, 4, 1, 1, 4, 5, 5};
	X[13] = new int[8]{5, 2, 5, 2, 2, 5, 6, 6};

	X[14] = new int[8]{5, 1, 5, 2, 4, 1, 2, 1};
	X[15] = new int[8]{6, 2, 6, 3, 5, 2, 3, 2};

	X[16] = new int[8]{4, 3, 2, 1, 2, 5, 4, 5};
	X[17] = new int[8]{5, 4, 3, 2, 3, 6, 5, 6};

	X[18] = new int[8]{2, 1, 2, 3, 1, 3, 1, 1};
	X[19] = new int[8]{3, 2, 3, 4, 2, 4, 2, 2};

	X[20] = new int[8]{4, 3, 4, 3, 5, 5, 2, 1};
	X[21] = new int[8]{5, 4, 5, 4, 6, 6, 3, 2};

	X[22] = new int[8]{3, 2, 2, 3, 3, 2, 1, 4};
	X[23] = new int[8]{4, 3, 3, 4, 4, 3, 2, 5};

	X[24] = new int[8]{5, 1, 5, 3, 4, 3, 1, 3};
	X[25] = new int[8]{6, 2, 6, 4, 5, 4, 2, 4};

	X[26] = new int[8]{5, 2, 1, 5, 1, 4, 3, 1};
	X[27] = new int[8]{6, 3, 2, 6, 2, 5, 4, 2};

	X[28] = new int[8]{3, 2, 5, 2, 1, 5, 4, 1};
	X[29] = new int[8]{4, 3, 6, 3, 2, 6, 5, 2};

	X[30] = new int[8]{3, 4, 5, 2, 3, 3, 5, 2};
	X[31] = new int[8]{4, 5, 6, 3, 4, 4, 6, 3};

	X[32] = new int[8]{3, 1, 2, 1, 4, 1, 5, 1};
	X[33] = new int[8]{4, 2, 3, 2, 5, 2, 6, 2};

	X[34] = new int[8]{5, 3, 3, 4, 1, 5, 2, 3};
	X[35] = new int[8]{6, 4, 4, 5, 2, 6, 3, 4};

	X[36] = new int[8]{4, 4, 3, 4, 5, 3, 5, 1};
	X[37] = new int[8]{5, 5, 4, 5, 6, 4, 6, 2};

	X[38] = new int[8]{4, 1, 3, 3, 1, 4, 2, 5};
	X[39] = new int[8]{5, 2, 4, 4, 2, 5, 3, 6};

	X[40] = new int[8]{4, 2, 3, 3, 4, 3, 2, 5};
	X[41] = new int[8]{5, 3, 4, 4, 5, 4, 3, 6};

	X[42] = new int[8]{3, 2, 3, 1, 3, 2, 4, 4};
	X[43] = new int[8]{4, 3, 4, 2, 4, 3, 5, 5};

	X[44] = new int[8]{4, 3, 4, 5, 4, 2, 2, 3};
	X[45] = new int[8]{5, 4, 5, 6, 5, 3, 3, 4};

	X[46] = new int[8]{2, 5, 3, 5, 5, 3, 1, 3};
	X[47] = new int[8]{3, 6, 4, 6, 6, 4, 2, 4};

	X[48] = new int[8]{2, 3, 2, 2, 5, 3, 5, 1};
	X[49] = new int[8]{3, 4, 3, 3, 6, 4, 6, 2};

	X[50] = new int[8]{3, 5, 5, 4, 5, 1, 1, 3};
	X[51] = new int[8]{4, 6, 6, 5, 6, 2, 2, 4};

	X[52] = new int[8]{2, 4, 4, 1, 1, 4, 3, 5};
	X[53] = new int[8]{3, 5, 5, 2, 2, 5, 4, 6};

	X[54] = new int[8]{2, 2, 3, 4, 5, 4, 5, 3};
	X[55] = new int[8]{3, 3, 4, 5, 6, 5, 6, 4};

	X[56] = new int[8]{5, 1, 3, 5, 3, 4, 3, 1};
	X[57] = new int[8]{6, 2, 4, 6, 4, 5, 4, 2};

	X[58] = new int[8]{3, 1, 3, 5, 1, 1, 3, 5};
	X[59] = new int[8]{4, 2, 4, 6, 2, 2, 4, 6};

	X[60] = new int[8]{2, 2, 3, 3, 5, 5, 1, 5};
	X[61] = new int[8]{3, 3, 4, 4, 6, 6, 2, 6};

	X[62] = new int[8]{3, 3, 3, 1, 5, 5, 4, 3};
	X[63] = new int[8]{4, 4, 4, 2, 6, 6, 5, 4};

	X[64] = new int[8]{4, 1, 2, 4, 1, 1, 3, 2};
	X[65] = new int[8]{5, 2, 3, 5, 2, 2, 4, 3};

	X[66] = new int[8]{2, 5, 2, 4, 4, 2, 1, 2};
	X[67] = new int[8]{3, 6, 3, 5, 5, 3, 2, 3};

	X[68] = new int[8]{5, 3, 3, 4, 3, 4, 5, 5};
	X[69] = new int[8]{6, 4, 4, 5, 4, 5, 6, 6};

	X[70] = new int[8]{3, 2, 3, 3, 3, 3, 3, 5};
	X[71] = new int[8]{4, 3, 4, 4, 4, 4, 4, 6};

	X[72] = new int[8]{3, 2, 2, 1, 1, 4, 1, 4};
	X[73] = new int[8]{4, 3, 3, 2, 2, 5, 2, 5};

	X[74] = new int[8]{5, 5, 3, 2, 2, 4, 2, 1};
	X[75] = new int[8]{6, 6, 4, 3, 3, 5, 3, 2};

	X[76] = new int[8]{3, 4, 4, 5, 5, 1, 2, 2};
	X[77] = new int[8]{4, 5, 5, 6, 6, 2, 3, 3};

	X[78] = new int[8]{4, 4, 5, 3, 2, 1, 1, 3};
	X[79] = new int[8]{5, 5, 6, 4, 3, 2, 2, 4};

	X[80] = new int[8]{3, 1, 1, 3, 2, 2, 3, 5};
	X[81] = new int[8]{4, 2, 2, 4, 3, 3, 4, 6};

	X[82] = new int[8]{5, 1, 1, 2, 2, 1, 1, 4};
	X[83] = new int[8]{6, 2, 2, 3, 3, 2, 2, 5};

	X[84] = new int[8]{4, 1, 2, 1, 4, 1, 4, 2};
	X[85] = new int[8]{5, 2, 3, 2, 5, 2, 5, 3};

	X[86] = new int[8]{3, 5, 3, 2, 2, 3, 3, 4};
	X[87] = new int[8]{4, 6, 4, 3, 3, 4, 4, 5};

	X[88] = new int[8]{3, 1, 3, 4, 2, 4, 2, 2};
	X[89] = new int[8]{4, 2, 4, 5, 3, 5, 3, 3};

	X[90] = new int[8]{4, 3, 5, 5, 4, 3, 5, 3};
	X[91] = new int[8]{5, 4, 6, 6, 5, 4, 6, 4};

	X[92] = new int[8]{2, 3, 5, 2, 2, 3, 1, 5};
	X[93] = new int[8]{3, 4, 6, 3, 3, 4, 2, 6};

	X[94] = new int[8]{3, 4, 2, 5, 2, 1, 2, 3};
	X[95] = new int[8]{4, 5, 3, 6, 3, 2, 3, 4};

	X[96] = new int[8]{5, 1, 3, 4, 5, 4, 2, 2};
	X[97] = new int[8]{6, 2, 4, 5, 6, 5, 3, 3};

	X[98] = new int[8]{2, 3, 1, 1, 2, 3, 3, 3};
	X[99] = new int[8]{3, 4, 2, 2, 3, 4, 4, 4};

	X[100] = new int[8]{3, 3, 5, 3, 4, 2, 1, 5};
	X[101] = new int[8]{4, 4, 6, 4, 5, 3, 2, 6};

	X[102] = new int[8]{5, 1, 3, 1, 1, 2, 4, 3};
	X[103] = new int[8]{6, 2, 4, 2, 2, 3, 5, 4};

	X[104] = new int[8]{2, 3, 5, 5, 3, 3, 3, 1};
	X[105] = new int[8]{3, 4, 6, 6, 4, 4, 4, 2};

	X[106] = new int[8]{4, 2, 2, 2, 3, 2, 5, 4};
	X[107] = new int[8]{5, 3, 3, 3, 4, 3, 6, 5};

	X[108] = new int[8]{2, 2, 2, 3, 4, 2, 2, 5};
	X[109] = new int[8]{3, 3, 3, 4, 5, 3, 3, 6};

	X[110] = new int[8]{5, 3, 4, 2, 1, 3, 2, 3};
	X[111] = new int[8]{6, 4, 5, 3, 2, 4, 3, 4};

	X[112] = new int[8]{2, 3, 3, 3, 2, 4, 2, 3};
	X[113] = new int[8]{3, 4, 4, 4, 3, 5, 3, 4};

	X[114] = new int[8]{3, 3, 3, 5, 4, 4, 5, 4};
	X[115] = new int[8]{4, 4, 4, 6, 5, 5, 6, 5};

	X[116] = new int[8]{4, 3, 3, 3, 2, 1, 1, 4};
	X[117] = new int[8]{5, 4, 4, 4, 3, 2, 2, 5};

	X[118] = new int[8]{3, 3, 2, 5, 1, 1, 4, 1};
	X[119] = new int[8]{4, 4, 3, 6, 2, 2, 5, 2};

	X[120] = new int[8]{3, 4, 3, 2, 2, 1, 3, 1};
	X[121] = new int[8]{4, 5, 4, 3, 3, 2, 4, 2};

	X[122] = new int[8]{3, 4, 1, 3, 5, 4, 3, 3};
	X[123] = new int[8]{4, 5, 2, 4, 6, 5, 4, 4};

	X[124] = new int[8]{4, 5, 2, 2, 2, 1, 4, 4};
	X[125] = new int[8]{5, 6, 3, 3, 3, 2, 5, 5};

	X[126] = new int[8]{4, 4, 4, 3, 2, 3, 3, 5};
	X[127] = new int[8]{5, 5, 5, 4, 3, 4, 4, 6};

	X[128] = new int[8]{2, 3, 2, 3, 5, 2, 4, 2};
	X[129] = new int[8]{3, 4, 3, 4, 6, 3, 5, 3};

	X[130] = new int[8]{5, 5, 2, 2, 5, 3, 5, 1};
	X[131] = new int[8]{6, 6, 3, 3, 6, 4, 6, 2};

	X[132] = new int[8]{5, 1, 4, 1, 3, 4, 2, 5};
	X[133] = new int[8]{6, 2, 5, 2, 4, 5, 3, 6};

	X[134] = new int[8]{5, 1, 3, 2, 4, 5, 5, 5};
	X[135] = new int[8]{6, 2, 4, 3, 5, 6, 6, 6};

	X[136] = new int[8]{3, 3, 1, 5, 5, 4, 5, 5};
	X[137] = new int[8]{4, 4, 2, 6, 6, 5, 6, 6};

	X[138] = new int[8]{4, 5, 4, 4, 1, 2, 1, 1};
	X[139] = new int[8]{5, 6, 5, 5, 2, 3, 2, 2};

	X[140] = new int[8]{3, 1, 5, 5, 5, 2, 1, 1};
	X[141] = new int[8]{4, 2, 6, 6, 6, 3, 2, 2};

	X[142] = new int[8]{5, 3, 2, 2, 5, 3, 5, 3};
	X[143] = new int[8]{6, 4, 3, 3, 6, 4, 6, 4};

	X[144] = new int[8]{3, 2, 5, 4, 3, 4, 1, 1};
	X[145] = new int[8]{4, 3, 6, 5, 4, 5, 2, 2};

	X[146] = new int[8]{5, 4, 1, 1, 1, 5, 5, 5};
	X[147] = new int[8]{6, 5, 2, 2, 2, 6, 6, 6};

	X[148] = new int[8]{3, 4, 2, 5, 2, 4, 4, 2};
	X[149] = new int[8]{4, 5, 3, 6, 3, 5, 5, 3};

	X[150] = new int[8]{4, 1, 3, 4, 4, 4, 2, 4};
	X[151] = new int[8]{5, 2, 4, 5, 5, 5, 3, 5};

	X[152] = new int[8]{4, 2, 3, 5, 4, 4, 2, 2};
	X[153] = new int[8]{5, 3, 4, 6, 5, 5, 3, 3};

	X[154] = new int[8]{4, 1, 3, 1, 5, 1, 4, 3};
	X[155] = new int[8]{5, 2, 4, 2, 6, 2, 5, 4};

	X[156] = new int[8]{2, 3, 4, 4, 1, 5, 3, 2};
	X[157] = new int[8]{3, 4, 5, 5, 2, 6, 4, 3};

	X[158] = new int[8]{3, 4, 5, 2, 2, 1, 1, 4};
	X[159] = new int[8]{4, 5, 6, 3, 3, 2, 2, 5};

	X[160] = new int[8]{2, 5, 4, 5, 2, 4, 2, 1};
	X[161] = new int[8]{3, 6, 5, 6, 3, 5, 3, 2};

	X[162] = new int[8]{4, 5, 1, 4, 2, 1, 4, 2};
	X[163] = new int[8]{5, 6, 2, 5, 3, 2, 5, 3};

	X[164] = new int[8]{5, 1, 2, 4, 1, 2, 2, 3};
	X[165] = new int[8]{6, 2, 3, 5, 2, 3, 3, 4};

	X[166] = new int[8]{5, 3, 3, 2, 1, 3, 1, 3};
	X[167] = new int[8]{6, 4, 4, 3, 2, 4, 2, 4};

	X[168] = new int[8]{3, 1, 3, 1, 5, 5, 1, 5};
	X[169] = new int[8]{4, 2, 4, 2, 6, 6, 2, 6};

	X[170] = new int[8]{3, 4, 5, 1, 1, 3, 4, 3};
	X[171] = new int[8]{4, 5, 6, 2, 2, 4, 5, 4};

	X[172] = new int[8]{4, 1, 1, 5, 4, 2, 5, 1};
	X[173] = new int[8]{5, 2, 2, 6, 5, 3, 6, 2};

	X[174] = new int[8]{4, 1, 5, 3, 5, 4, 4, 4};
	X[175] = new int[8]{5, 2, 6, 4, 6, 5, 5, 5};

	X[176] = new int[8]{5, 2, 5, 2, 1, 1, 5, 3};
	X[177] = new int[8]{6, 3, 6, 3, 2, 2, 6, 4};

	X[178] = new int[8]{5, 2, 3, 3, 2, 2, 4, 5};
	X[179] = new int[8]{6, 3, 4, 4, 3, 3, 5, 6};

	X[180] = new int[8]{3, 2, 3, 5, 5, 5, 4, 2};
	X[181] = new int[8]{4, 3, 4, 6, 6, 6, 5, 3};

	X[182] = new int[8]{4, 3, 5, 4, 2, 1, 2, 3};
	X[183] = new int[8]{5, 4, 6, 5, 3, 2, 3, 4};

	X[184] = new int[8]{3, 3, 4, 2, 3, 3, 1, 5};
	X[185] = new int[8]{4, 4, 5, 3, 4, 4, 2, 6};

	X[186] = new int[8]{4, 3, 1, 2, 3, 3, 4, 3};
	X[187] = new int[8]{5, 4, 2, 3, 4, 4, 5, 4};

	X[188] = new int[8]{5, 3, 2, 5, 5, 1, 3, 5};
	X[189] = new int[8]{6, 4, 3, 6, 6, 2, 4, 6};

	X[190] = new int[8]{2, 2, 2, 3, 5, 3, 2, 5};
	X[191] = new int[8]{3, 3, 3, 4, 6, 4, 3, 6};

	X[192] = new int[8]{2, 5, 5, 5, 2, 1, 4, 4};
	X[193] = new int[8]{3, 6, 6, 6, 3, 2, 5, 5};

	X[194] = new int[8]{3, 1, 1, 3, 4, 5, 2, 1};
	X[195] = new int[8]{4, 2, 2, 4, 5, 6, 3, 2};

	X[196] = new int[8]{5, 4, 5, 1, 1, 1, 1, 5};
	X[197] = new int[8]{6, 5, 6, 2, 2, 2, 2, 6};

	X[198] = new int[8]{3, 1, 2, 3, 5, 1, 3, 2};
	X[199] = new int[8]{4, 2, 3, 4, 6, 2, 4, 3};

	X[200] = new int[8]{2, 1, 1, 4, 5, 1, 4, 3};
	X[201] = new int[8]{3, 2, 2, 5, 6, 2, 5, 4};

	X[202] = new int[8]{3, 4, 3, 2, 3, 4, 5, 4};
	X[203] = new int[8]{4, 5, 4, 3, 4, 5, 6, 5};

	X[204] = new int[8]{4, 5, 5, 2, 5, 3, 5, 2};
	X[205] = new int[8]{5, 6, 6, 3, 6, 4, 6, 3};

	X[206] = new int[8]{2, 3, 5, 3, 5, 1, 3, 3};
	X[207] = new int[8]{3, 4, 6, 4, 6, 2, 4, 4};

	X[208] = new int[8]{2, 5, 2, 3, 4, 4, 4, 5};
	X[209] = new int[8]{3, 6, 3, 4, 5, 5, 5, 6};

	X[210] = new int[8]{2, 3, 2, 3, 3, 4, 3, 5};
	X[211] = new int[8]{3, 4, 3, 4, 4, 5, 4, 6};

	X[212] = new int[8]{4, 4, 2, 1, 1, 5, 5, 4};
	X[213] = new int[8]{5, 5, 3, 2, 2, 6, 6, 5};

	X[214] = new int[8]{3, 5, 2, 5, 5, 4, 4, 1};
	X[215] = new int[8]{4, 6, 3, 6, 6, 5, 5, 2};

	X[216] = new int[8]{5, 5, 3, 1, 5, 3, 2, 5};
	X[217] = new int[8]{6, 6, 4, 2, 6, 4, 3, 6};

	X[218] = new int[8]{3, 4, 1, 5, 3, 3, 4, 4};
	X[219] = new int[8]{4, 5, 2, 6, 4, 4, 5, 5};

	X[220] = new int[8]{5, 4, 3, 5, 2, 4, 2, 3};
	X[221] = new int[8]{6, 5, 4, 6, 3, 5, 3, 4};

	X[222] = new int[8]{2, 1, 2, 1, 1, 4, 5, 4};
	X[223] = new int[8]{3, 2, 3, 2, 2, 5, 6, 5};

	X[224] = new int[8]{2, 5, 5, 4, 1, 5, 3, 5};
	X[225] = new int[8]{3, 6, 6, 5, 2, 6, 4, 6};

	X[226] = new int[8]{2, 3, 1, 1, 1, 1, 3, 2};
	X[227] = new int[8]{3, 4, 2, 2, 2, 2, 4, 3};

	X[228] = new int[8]{4, 1, 1, 3, 1, 3, 2, 3};
	X[229] = new int[8]{5, 2, 2, 4, 2, 4, 3, 4};

	X[230] = new int[8]{4, 2, 5, 2, 5, 5, 3, 2};
	X[231] = new int[8]{5, 3, 6, 3, 6, 6, 4, 3};

	X[232] = new int[8]{5, 1, 1, 1, 3, 4, 4, 1};
	X[233] = new int[8]{6, 2, 2, 2, 4, 5, 5, 2};

	X[234] = new int[8]{4, 5, 5, 5, 5, 4, 5, 2};
	X[235] = new int[8]{5, 6, 6, 6, 6, 5, 6, 3};

	X[236] = new int[8]{2, 5, 5, 2, 3, 5, 4, 4};
	X[237] = new int[8]{3, 6, 6, 3, 4, 6, 5, 5};

	X[238] = new int[8]{5, 2, 1, 4, 5, 1, 3, 2};
	X[239] = new int[8]{6, 3, 2, 5, 6, 2, 4, 3};

	X[240] = new int[8]{2, 4, 4, 4, 2, 1, 2, 5};
	X[241] = new int[8]{3, 5, 5, 5, 3, 2, 3, 6};

	X[242] = new int[8]{3, 1, 3, 3, 5, 5, 2, 1};
	X[243] = new int[8]{4, 2, 4, 4, 6, 6, 3, 2};

	X[244] = new int[8]{3, 3, 5, 4, 5, 3, 1, 5};
	X[245] = new int[8]{4, 4, 6, 5, 6, 4, 2, 6};

	X[246] = new int[8]{5, 3, 4, 4, 5, 5, 1, 1};
	X[247] = new int[8]{6, 4, 5, 5, 6, 6, 2, 2};

	X[248] = new int[8]{3, 2, 2, 1, 2, 1, 4, 1};
	X[249] = new int[8]{4, 3, 3, 2, 3, 2, 5, 2};

	X[250] = new int[8]{4, 5, 1, 4, 5, 4, 2, 4};
	X[251] = new int[8]{5, 6, 2, 5, 6, 5, 3, 5};

	X[252] = new int[8]{4, 1, 1, 1, 4, 5, 1, 3};
	X[253] = new int[8]{5, 2, 2, 2, 5, 6, 2, 4};

	X[254] = new int[8]{4, 2, 5, 1, 3, 1, 1, 1};
	X[255] = new int[8]{5, 3, 6, 2, 4, 2, 2, 2};

	X[256] = new int[8]{3, 3, 2, 3, 2, 5, 1, 5};
	X[257] = new int[8]{4, 4, 3, 4, 3, 6, 2, 6};

	X[258] = new int[8]{4, 5, 3, 2, 1, 1, 1, 5};
	X[259] = new int[8]{5, 6, 4, 3, 2, 2, 2, 6};

	X[260] = new int[8]{2, 3, 3, 3, 5, 2, 2, 2};
	X[261] = new int[8]{3, 4, 4, 4, 6, 3, 3, 3};

	X[262] = new int[8]{4, 3, 1, 1, 2, 4, 2, 2};
	X[263] = new int[8]{5, 4, 2, 2, 3, 5, 3, 3};

	X[264] = new int[8]{3, 5, 4, 2, 1, 1, 2, 5};
	X[265] = new int[8]{4, 6, 5, 3, 2, 2, 3, 6};

	X[266] = new int[8]{5, 4, 3, 5, 4, 4, 2, 4};
	X[267] = new int[8]{6, 5, 4, 6, 5, 5, 3, 5};

	X[268] = new int[8]{2, 4, 4, 1, 2, 2, 2, 3};
	X[269] = new int[8]{3, 5, 5, 2, 3, 3, 3, 4};

	X[270] = new int[8]{5, 1, 1, 5, 1, 3, 1, 4};
	X[271] = new int[8]{6, 2, 2, 6, 2, 4, 2, 5};

	X[272] = new int[8]{5, 3, 3, 5, 5, 3, 5, 1};
	X[273] = new int[8]{6, 4, 4, 6, 6, 4, 6, 2};

	X[274] = new int[8]{5, 4, 5, 1, 1, 1, 1, 5};
	X[275] = new int[8]{6, 5, 6, 2, 2, 2, 2, 6};

	X[276] = new int[8]{5, 3, 5, 3, 5, 5, 5, 4};
	X[277] = new int[8]{6, 4, 6, 4, 6, 6, 6, 5};

	X[278] = new int[8]{4, 5, 3, 4, 3, 2, 2, 3};
	X[279] = new int[8]{5, 6, 4, 5, 4, 3, 3, 4};

	X[280] = new int[8]{2, 3, 1, 1, 2, 1, 3, 3};
	X[281] = new int[8]{3, 4, 2, 2, 3, 2, 4, 4};

	X[282] = new int[8]{3, 5, 3, 4, 1, 2, 3, 4};
	X[283] = new int[8]{4, 6, 4, 5, 2, 3, 4, 5};

	X[284] = new int[8]{2, 1, 4, 3, 1, 1, 2, 5};
	X[285] = new int[8]{3, 2, 5, 4, 2, 2, 3, 6};

	X[286] = new int[8]{4, 3, 3, 1, 3, 4, 2, 3};
	X[287] = new int[8]{5, 4, 4, 2, 4, 5, 3, 4};

	X[288] = new int[8]{5, 1, 5, 3, 5, 1, 4, 3};
	X[289] = new int[8]{6, 2, 6, 4, 6, 2, 5, 4};

	X[290] = new int[8]{5, 5, 2, 4, 3, 5, 2, 2};
	X[291] = new int[8]{6, 6, 3, 5, 4, 6, 3, 3};

	X[292] = new int[8]{2, 4, 2, 3, 3, 3, 5, 1};
	X[293] = new int[8]{3, 5, 3, 4, 4, 4, 6, 2};

	X[294] = new int[8]{3, 4, 3, 5, 4, 1, 2, 2};
	X[295] = new int[8]{4, 5, 4, 6, 5, 2, 3, 3};

	X[296] = new int[8]{5, 2, 2, 5, 4, 4, 4, 1};
	X[297] = new int[8]{6, 3, 3, 6, 5, 5, 5, 2};

	X[298] = new int[8]{4, 1, 2, 5, 2, 5, 3, 5};
	X[299] = new int[8]{5, 2, 3, 6, 3, 6, 4, 6};

	X[300] = new int[8]{3, 3, 4, 2, 1, 1, 4, 1};
	X[301] = new int[8]{4, 4, 5, 3, 2, 2, 5, 2};

	X[302] = new int[8]{3, 1, 2, 2, 1, 5, 3, 3};
	X[303] = new int[8]{4, 2, 3, 3, 2, 6, 4, 4};

	X[304] = new int[8]{2, 3, 4, 5, 1, 2, 3, 4};
	X[305] = new int[8]{3, 4, 5, 6, 2, 3, 4, 5};

	X[306] = new int[8]{5, 3, 4, 2, 2, 1, 2, 1};
	X[307] = new int[8]{6, 4, 5, 3, 3, 2, 3, 2};

	X[308] = new int[8]{3, 4, 3, 1, 4, 1, 2, 4};
	X[309] = new int[8]{4, 5, 4, 2, 5, 2, 3, 5};

	X[310] = new int[8]{5, 1, 3, 4, 4, 2, 4, 1};
	X[311] = new int[8]{6, 2, 4, 5, 5, 3, 5, 2};

	X[312] = new int[8]{4, 2, 1, 4, 2, 3, 4, 2};
	X[313] = new int[8]{5, 3, 2, 5, 3, 4, 5, 3};

	X[314] = new int[8]{3, 1, 3, 4, 5, 4, 3, 5};
	X[315] = new int[8]{4, 2, 4, 5, 6, 5, 4, 6};

	X[316] = new int[8]{3, 3, 2, 4, 5, 4, 4, 2};
	X[317] = new int[8]{4, 4, 3, 5, 6, 5, 5, 3};

	X[318] = new int[8]{2, 3, 2, 5, 2, 5, 5, 1};
	X[319] = new int[8]{3, 4, 3, 6, 3, 6, 6, 2};

	X[320] = new int[8]{3, 1, 3, 2, 3, 4, 4, 3};
	X[321] = new int[8]{4, 2, 4, 3, 4, 5, 5, 4};

	X[322] = new int[8]{3, 2, 5, 3, 1, 3, 3, 1};
	X[323] = new int[8]{4, 3, 6, 4, 2, 4, 4, 2};

	X[324] = new int[8]{2, 1, 1, 5, 1, 1, 3, 3};
	X[325] = new int[8]{3, 2, 2, 6, 2, 2, 4, 4};

	X[326] = new int[8]{5, 2, 1, 4, 5, 1, 1, 4};
	X[327] = new int[8]{6, 3, 2, 5, 6, 2, 2, 5};

	X[328] = new int[8]{3, 1, 2, 5, 5, 5, 5, 2};
	X[329] = new int[8]{4, 2, 3, 6, 6, 6, 6, 3};

	X[330] = new int[8]{2, 1, 1, 2, 4, 3, 3, 4};
	X[331] = new int[8]{3, 2, 2, 3, 5, 4, 4, 5};

	X[332] = new int[8]{2, 4, 3, 3, 2, 5, 4, 2};
	X[333] = new int[8]{3, 5, 4, 4, 3, 6, 5, 3};

	X[334] = new int[8]{4, 1, 3, 1, 1, 1, 4, 1};
	X[335] = new int[8]{5, 2, 4, 2, 2, 2, 5, 2};

	X[336] = new int[8]{5, 1, 4, 4, 3, 2, 2, 3};
	X[337] = new int[8]{6, 2, 5, 5, 4, 3, 3, 4};

	X[338] = new int[8]{3, 2, 1, 2, 4, 2, 4, 2};
	X[339] = new int[8]{4, 3, 2, 3, 5, 3, 5, 3};

	X[340] = new int[8]{4, 1, 4, 1, 3, 3, 4, 4};
	X[341] = new int[8]{5, 2, 5, 2, 4, 4, 5, 5};

	X[342] = new int[8]{2, 5, 1, 1, 1, 2, 5, 2};
	X[343] = new int[8]{3, 6, 2, 2, 2, 3, 6, 3};

	X[344] = new int[8]{2, 5, 1, 5, 5, 5, 3, 4};
	X[345] = new int[8]{3, 6, 2, 6, 6, 6, 4, 5};

	X[346] = new int[8]{2, 4, 5, 4, 3, 4, 1, 1};
	X[347] = new int[8]{3, 5, 6, 5, 4, 5, 2, 2};

	X[348] = new int[8]{3, 4, 2, 5, 5, 1, 5, 2};
	X[349] = new int[8]{4, 5, 3, 6, 6, 2, 6, 3};

	X[350] = new int[8]{5, 5, 4, 1, 4, 2, 4, 5};
	X[351] = new int[8]{6, 6, 5, 2, 5, 3, 5, 6};

	X[352] = new int[8]{2, 5, 3, 3, 2, 3, 5, 4};
	X[353] = new int[8]{3, 6, 4, 4, 3, 4, 6, 5};

	X[354] = new int[8]{3, 4, 4, 4, 2, 4, 3, 2};
	X[355] = new int[8]{4, 5, 5, 5, 3, 5, 4, 3};

	X[356] = new int[8]{5, 3, 1, 3, 5, 3, 1, 5};
	X[357] = new int[8]{6, 4, 2, 4, 6, 4, 2, 6};

	X[358] = new int[8]{3, 1, 1, 2, 2, 3, 2, 2};
	X[359] = new int[8]{4, 2, 2, 3, 3, 4, 3, 3};

	X[360] = new int[8]{3, 3, 5, 3, 2, 2, 1, 4};
	X[361] = new int[8]{4, 4, 6, 4, 3, 3, 2, 5};

	X[362] = new int[8]{5, 1, 4, 1, 4, 3, 2, 3};
	X[363] = new int[8]{6, 2, 5, 2, 5, 4, 3, 4};

	X[364] = new int[8]{3, 1, 4, 2, 5, 3, 3, 1};
	X[365] = new int[8]{4, 2, 5, 3, 6, 4, 4, 2};

	X[366] = new int[8]{3, 4, 3, 5, 5, 5, 1, 3};
	X[367] = new int[8]{4, 5, 4, 6, 6, 6, 2, 4};

	X[368] = new int[8]{5, 1, 5, 1, 1, 4, 1, 3};
	X[369] = new int[8]{6, 2, 6, 2, 2, 5, 2, 4};

	X[370] = new int[8]{4, 1, 5, 1, 5, 3, 1, 3};
	X[371] = new int[8]{5, 2, 6, 2, 6, 4, 2, 4};

	X[372] = new int[8]{4, 3, 4, 1, 1, 1, 3, 3};
	X[373] = new int[8]{5, 4, 5, 2, 2, 2, 4, 4};

	X[374] = new int[8]{2, 3, 1, 3, 4, 3, 5, 5};
	X[375] = new int[8]{3, 4, 2, 4, 5, 4, 6, 6};

	X[376] = new int[8]{4, 2, 2, 5, 3, 2, 1, 4};
	X[377] = new int[8]{5, 3, 3, 6, 4, 3, 2, 5};

	X[378] = new int[8]{5, 3, 2, 3, 3, 1, 1, 5};
	X[379] = new int[8]{6, 4, 3, 4, 4, 2, 2, 6};

	X[380] = new int[8]{3, 3, 4, 2, 4, 1, 4, 1};
	X[381] = new int[8]{4, 4, 5, 3, 5, 2, 5, 2};

	X[382] = new int[8]{2, 4, 4, 3, 1, 4, 5, 5};
	X[383] = new int[8]{3, 5, 5, 4, 2, 5, 6, 6};

	X[384] = new int[8]{5, 1, 2, 2, 2, 5, 1, 2};
	X[385] = new int[8]{6, 2, 3, 3, 3, 6, 2, 3};

	X[386] = new int[8]{3, 3, 2, 1, 5, 2, 4, 4};
	X[387] = new int[8]{4, 4, 3, 2, 6, 3, 5, 5};

	X[388] = new int[8]{2, 2, 4, 2, 4, 4, 2, 3};
	X[389] = new int[8]{3, 3, 5, 3, 5, 5, 3, 4};

	X[390] = new int[8]{4, 4, 1, 3, 1, 3, 5, 3};
	X[391] = new int[8]{5, 5, 2, 4, 2, 4, 6, 4};

	X[392] = new int[8]{2, 4, 1, 3, 3, 2, 1, 5};
	X[393] = new int[8]{3, 5, 2, 4, 4, 3, 2, 6};

	X[394] = new int[8]{2, 3, 2, 2, 4, 4, 2, 5};
	X[395] = new int[8]{3, 4, 3, 3, 5, 5, 3, 6};

	X[396] = new int[8]{3, 2, 1, 5, 3, 3, 3, 4};
	X[397] = new int[8]{4, 3, 2, 6, 4, 4, 4, 5};

	X[398] = new int[8]{5, 5, 1, 5, 2, 4, 5, 4};
	X[399] = new int[8]{6, 6, 2, 6, 3, 5, 6, 5};

	X[400] = new int[8]{2, 2, 1, 4, 4, 3, 3, 4};
	X[401] = new int[8]{3, 3, 2, 5, 5, 4, 4, 5};

	X[402] = new int[8]{2, 2, 3, 4, 3, 1, 4, 5};
	X[403] = new int[8]{3, 3, 4, 5, 4, 2, 5, 6};

	X[404] = new int[8]{3, 4, 4, 1, 5, 5, 4, 4};
	X[405] = new int[8]{4, 5, 5, 2, 6, 6, 5, 5};

	X[406] = new int[8]{3, 3, 5, 2, 2, 2, 1, 5};
	X[407] = new int[8]{4, 4, 6, 3, 3, 3, 2, 6};

	X[408] = new int[8]{5, 4, 4, 3, 1, 4, 5, 3};
	X[409] = new int[8]{6, 5, 5, 4, 2, 5, 6, 4};

	X[410] = new int[8]{4, 4, 4, 5, 5, 3, 4, 4};
	X[411] = new int[8]{5, 5, 5, 6, 6, 4, 5, 5};

	X[412] = new int[8]{5, 2, 1, 1, 3, 1, 4, 1};
	X[413] = new int[8]{6, 3, 2, 2, 4, 2, 5, 2};

	X[414] = new int[8]{2, 3, 4, 4, 2, 1, 5, 5};
	X[415] = new int[8]{3, 4, 5, 5, 3, 2, 6, 6};

	X[416] = new int[8]{3, 4, 2, 5, 1, 5, 4, 4};
	X[417] = new int[8]{4, 5, 3, 6, 2, 6, 5, 5};

	X[418] = new int[8]{4, 4, 1, 1, 1, 1, 5, 5};
	X[419] = new int[8]{5, 5, 2, 2, 2, 2, 6, 6};

	X[420] = new int[8]{2, 3, 3, 2, 5, 2, 2, 3};
	X[421] = new int[8]{3, 4, 4, 3, 6, 3, 3, 4};

	X[422] = new int[8]{5, 3, 3, 1, 4, 3, 2, 5};
	X[423] = new int[8]{6, 4, 4, 2, 5, 4, 3, 6};

	X[424] = new int[8]{2, 2, 1, 5, 3, 1, 3, 4};
	X[425] = new int[8]{3, 3, 2, 6, 4, 2, 4, 5};

	X[426] = new int[8]{2, 5, 5, 3, 5, 1, 3, 3};
	X[427] = new int[8]{3, 6, 6, 4, 6, 2, 4, 4};

	X[428] = new int[8]{3, 5, 4, 3, 4, 5, 3, 1};
	X[429] = new int[8]{4, 6, 5, 4, 5, 6, 4, 2};

	X[430] = new int[8]{3, 3, 4, 1, 5, 2, 3, 3};
	X[431] = new int[8]{4, 4, 5, 2, 6, 3, 4, 4};

	X[432] = new int[8]{4, 4, 3, 4, 4, 2, 4, 1};
	X[433] = new int[8]{5, 5, 4, 5, 5, 3, 5, 2};

	X[434] = new int[8]{3, 2, 1, 4, 5, 3, 1, 4};
	X[435] = new int[8]{4, 3, 2, 5, 6, 4, 2, 5};

	X[436] = new int[8]{2, 2, 1, 4, 2, 1, 2, 3};
	X[437] = new int[8]{3, 3, 2, 5, 3, 2, 3, 4};

	X[438] = new int[8]{2, 1, 5, 1, 4, 5, 1, 2};
	X[439] = new int[8]{3, 2, 6, 2, 5, 6, 2, 3};

	X[440] = new int[8]{4, 2, 3, 2, 5, 4, 5, 4};
	X[441] = new int[8]{5, 3, 4, 3, 6, 5, 6, 5};

	X[442] = new int[8]{5, 1, 4, 4, 5, 2, 4, 1};
	X[443] = new int[8]{6, 2, 5, 5, 6, 3, 5, 2};

	X[444] = new int[8]{2, 1, 4, 3, 2, 4, 5, 3};
	X[445] = new int[8]{3, 2, 5, 4, 3, 5, 6, 4};

	X[446] = new int[8]{2, 3, 1, 5, 4, 2, 3, 5};
	X[447] = new int[8]{3, 4, 2, 6, 5, 3, 4, 6};

	X[448] = new int[8]{2, 1, 5, 3, 3, 2, 1, 4};
	X[449] = new int[8]{3, 2, 6, 4, 4, 3, 2, 5};

	X[450] = new int[8]{2, 1, 5, 4, 1, 3, 5, 3};
	X[451] = new int[8]{3, 2, 6, 5, 2, 4, 6, 4};

	X[452] = new int[8]{3, 3, 5, 5, 1, 5, 4, 2};
	X[453] = new int[8]{4, 4, 6, 6, 2, 6, 5, 3};

	X[454] = new int[8]{4, 3, 1, 4, 1, 4, 4, 4};
	X[455] = new int[8]{5, 4, 2, 5, 2, 5, 5, 5};

	X[456] = new int[8]{2, 5, 5, 5, 4, 4, 5, 5};
	X[457] = new int[8]{3, 6, 6, 6, 5, 5, 6, 6};

	X[458] = new int[8]{4, 2, 4, 2, 4, 5, 5, 2};
	X[459] = new int[8]{5, 3, 5, 3, 5, 6, 6, 3};

	X[460] = new int[8]{4, 3, 3, 5, 1, 1, 2, 4};
	X[461] = new int[8]{5, 4, 4, 6, 2, 2, 3, 5};

	X[462] = new int[8]{4, 1, 3, 2, 1, 4, 3, 3};
	X[463] = new int[8]{5, 2, 4, 3, 2, 5, 4, 4};

	X[464] = new int[8]{5, 5, 1, 4, 5, 5, 3, 3};
	X[465] = new int[8]{6, 6, 2, 5, 6, 6, 4, 4};

	X[466] = new int[8]{2, 1, 1, 3, 2, 1, 5, 4};
	X[467] = new int[8]{3, 2, 2, 4, 3, 2, 6, 5};

	X[468] = new int[8]{5, 1, 2, 1, 5, 5, 4, 5};
	X[469] = new int[8]{6, 2, 3, 2, 6, 6, 5, 6};

	X[470] = new int[8]{5, 4, 4, 2, 3, 4, 5, 5};
	X[471] = new int[8]{6, 5, 5, 3, 4, 5, 6, 6};

	X[472] = new int[8]{2, 3, 3, 5, 4, 2, 5, 2};
	X[473] = new int[8]{3, 4, 4, 6, 5, 3, 6, 3};

	X[474] = new int[8]{2, 3, 5, 5, 3, 3, 2, 4};
	X[475] = new int[8]{3, 4, 6, 6, 4, 4, 3, 5};

	X[476] = new int[8]{3, 2, 3, 5, 2, 3, 2, 5};
	X[477] = new int[8]{4, 3, 4, 6, 3, 4, 3, 6};

	X[478] = new int[8]{4, 4, 1, 3, 1, 5, 3, 4};
	X[479] = new int[8]{5, 5, 2, 4, 2, 6, 4, 5};

	X[480] = new int[8]{2, 3, 3, 4, 3, 4, 4, 4};
	X[481] = new int[8]{3, 4, 4, 5, 4, 5, 5, 5};

	X[482] = new int[8]{2, 1, 1, 3, 3, 3, 4, 2};
	X[483] = new int[8]{3, 2, 2, 4, 4, 4, 5, 3};

	X[484] = new int[8]{4, 2, 2, 5, 2, 1, 3, 4};
	X[485] = new int[8]{5, 3, 3, 6, 3, 2, 4, 5};

	X[486] = new int[8]{5, 4, 4, 5, 5, 1, 4, 1};
	X[487] = new int[8]{6, 5, 5, 6, 6, 2, 5, 2};

	X[488] = new int[8]{2, 4, 4, 2, 4, 4, 3, 5};
	X[489] = new int[8]{3, 5, 5, 3, 5, 5, 4, 6};

	X[490] = new int[8]{5, 1, 5, 1, 1, 4, 4, 4};
	X[491] = new int[8]{6, 2, 6, 2, 2, 5, 5, 5};

	X[492] = new int[8]{2, 5, 1, 2, 4, 2, 4, 3};
	X[493] = new int[8]{3, 6, 2, 3, 5, 3, 5, 4};

	X[494] = new int[8]{4, 5, 1, 2, 1, 1, 3, 3};
	X[495] = new int[8]{5, 6, 2, 3, 2, 2, 4, 4};

	X[496] = new int[8]{2, 4, 4, 2, 3, 1, 2, 4};
	X[497] = new int[8]{3, 5, 5, 3, 4, 2, 3, 5};

	X[498] = new int[8]{3, 2, 3, 4, 1, 5, 2, 4};
	X[499] = new int[8]{4, 3, 4, 5, 2, 6, 3, 5};

	X[500] = new int[8]{8, 2, 1, 4, 4, 2, 2, 8};
	X[501] = new int[8]{2, 3, 3, -1, -1, 3, 4, 3};

	X[502] = new int[8]{3, 2, 3, 3, 2, 2, 3, 4};
	X[503] = new int[8]{5, 3, 5, 5, 4, 3, 5, -1};

	X[504] = new int[8]{3, 4, 8, 8, 5, 8, 1, 1};
	X[505] = new int[8]{4, -1, 3, 3, -1, 2, 3, 3};

	X[506] = new int[8]{8, 5, 1, 8, 1, 2, 8, 1};
	X[507] = new int[8]{2, -1, 3, 1, 3, 4, 2, 2};

	X[508] = new int[8]{5, 8, 8, 8, 8, 3, 1, 4};
	X[509] = new int[8]{-1, 3, 2, 1, 2, 5, 3, -1};

	X[510] = new int[8]{5, 3, 4, 8, 8, 4, 3, 4};
	X[511] = new int[8]{-1, 5, -1, 3, 3, -1, 5, -1};

	X[512] = new int[8]{8, 2, 8, 4, 8, 5, 8, 4};
	X[513] = new int[8]{3, 3, 1, -1, 1, -1, 1, -1};

	X[514] = new int[8]{5, 8, 5, 8, 3, 3, 1, 2};
	X[515] = new int[8]{-1, 1, -1, 1, 5, 5, 2, 3};

	X[516] = new int[8]{4, 2, 5, 5, 4, 5, 4, 5};
	X[517] = new int[8]{-1, 3, -1, -1, -1, -1, -1, -1};

	X[518] = new int[8]{4, 5, 5, 5, 2, 1, 2, 3};
	X[519] = new int[8]{-1, -1, -1, -1, 4, 3, 4, 5};

	X[520] = new int[8]{5, 8, 4, 4, 3, 4, 5, 5};
	X[521] = new int[8]{-1, 3, -1, -1, 5, -1, -1, -1};

	X[522] = new int[8]{3, 3, 3, 8, 4, 3, 8, 8};
	X[523] = new int[8]{5, 5, 5, 3, -1, 4, 2, 2};

	X[524] = new int[8]{4, 3, 5, 8, 3, 1, 8, 5};
	X[525] = new int[8]{-1, 4, -1, 2, 5, 2, 2, -1};

	X[526] = new int[8]{3, 5, 2, 5, 5, 4, 5, 1};
	X[527] = new int[8]{5, -1, 3, -1, -1, -1, -1, 2};

	X[528] = new int[8]{5, 2, 3, 8, 8, 4, 3, 2};
	X[529] = new int[8]{-1, 4, 4, 2, 2, -1, 5, 3};

	X[530] = new int[8]{8, 2, 3, 1, 2, 8, 1, 5};
	X[531] = new int[8]{3, 3, 4, 3, 3, 2, 3, -1};

	X[532] = new int[8]{3, 8, 1, 5, 3, 4, 2, 5};
	X[533] = new int[8]{4, 2, 3, -1, 5, -1, 3, -1};

	X[534] = new int[8]{5, 5, 8, 5, 8, 8, 5, 3};
	X[535] = new int[8]{-1, -1, 2, -1, 2, 1, -1, 4};

	X[536] = new int[8]{2, 3, 4, 4, 3, 8, 2, 3};
	X[537] = new int[8]{3, 4, -1, -1, 5, 3, 3, 5};

	X[538] = new int[8]{3, 1, 5, 3, 3, 1, 4, 2};
	X[539] = new int[8]{4, 3, -1, 4, 5, 2, -1, 3};

	X[540] = new int[8]{8, 4, 3, 3, 2, 4, 3, 1};
	X[541] = new int[8]{3, -1, 5, 5, 4, -1, 4, 3};

	X[542] = new int[8]{3, 4, 2, 4, 8, 2, 8, 3};
	X[543] = new int[8]{5, -1, 4, -1, 2, 3, 2, 4};

	X[544] = new int[8]{3, 8, 1, 4, 4, 8, 2, 4};
	X[545] = new int[8]{5, 2, 2, -1, -1, 3, 3, -1};

	X[546] = new int[8]{2, 8, 2, 8, 5, 4, 8, 1};
	X[547] = new int[8]{4, 1, 4, 3, -1, -1, 1, 3};

	X[548] = new int[8]{4, 2, 5, 4, 1, 3, 3, 8};
	X[549] = new int[8]{-1, 3, -1, -1, 2, 4, 5, 2};

	X[550] = new int[8]{2, 5, 1, 8, 8, 1, 1, 8};
	X[551] = new int[8]{3, -1, 2, 3, 1, 2, 3, 1};

	X[552] = new int[8]{2, 8, 2, 2, 5, 2, 8, 1};
	X[553] = new int[8]{4, 1, 3, 3, -1, 4, 1, 3};

	X[554] = new int[8]{3, 5, 4, 1, 8, 8, 3, 8};
	X[555] = new int[8]{4, -1, -1, 3, 3, 3, 5, 2};

	X[556] = new int[8]{2, 5, 4, 4, 3, 1, 1, 8};
	X[557] = new int[8]{4, -1, -1, -1, 4, 3, 3, 1};

	X[558] = new int[8]{2, 3, 8, 8, 4, 2, 8, 4};
	X[559] = new int[8]{4, 5, 2, 3, -1, 4, 3, -1};

	X[560] = new int[8]{4, 5, 2, 1, 8, 2, 8, 3};
	X[561] = new int[8]{-1, -1, 4, 3, 1, 3, 3, 4};

	X[562] = new int[8]{3, 8, 8, 2, 8, 1, 8, 1};
	X[563] = new int[8]{4, 2, 1, 4, 3, 3, 1, 2};

	X[564] = new int[8]{3, 2, 8, 8, 5, 1, 1, 5};
	X[565] = new int[8]{4, 3, 2, 2, -1, 3, 2, -1};

	X[566] = new int[8]{3, 8, 3, 8, 5, 5, 5, 4};
	X[567] = new int[8]{5, 1, 4, 2, -1, -1, -1, -1};

	X[568] = new int[8]{8, 3, 2, 2, 4, 8, 5, 1};
	X[569] = new int[8]{3, 4, 3, 4, -1, 1, -1, 3};

	X[570] = new int[8]{3, 5, 8, 3, 3, 2, 8, 8};
	X[571] = new int[8]{4, -1, 3, 4, 5, 4, 3, 3};

	X[572] = new int[8]{3, 8, 2, 5, 5, 8, 3, 4};
	X[573] = new int[8]{5, 1, 3, -1, -1, 3, 5, -1};

	X[574] = new int[8]{8, 4, 2, 5, 5, 3, 2, 2};
	X[575] = new int[8]{3, -1, 4, -1, -1, 5, 3, 4};

	X[576] = new int[8]{2, 8, 5, 3, 1, 3, 8, 8};
	X[577] = new int[8]{4, 2, -1, 4, 2, 4, 1, 2};

	X[578] = new int[8]{2, 2, 4, 2, 1, 3, 3, 1};
	X[579] = new int[8]{3, 4, -1, 4, 2, 5, 4, 2};

	X[580] = new int[8]{3, 8, 2, 4, 4, 2, 8, 5};
	X[581] = new int[8]{5, 3, 3, -1, -1, 3, 3, -1};

	X[582] = new int[8]{2, 5, 3, 1, 2, 8, 2, 2};
	X[583] = new int[8]{3, -1, 4, 3, 3, 2, 3, 4};

	X[584] = new int[8]{8, 8, 3, 4, 3, 2, 8, 3};
	X[585] = new int[8]{3, 1, 4, -1, 5, 4, 3, 4};

	X[586] = new int[8]{2, 3, 1, 1, 3, 3, 8, 8};
	X[587] = new int[8]{3, 4, 3, 3, 5, 4, 1, 1};

	X[588] = new int[8]{4, 8, 1, 8, 1, 3, 8, 5};
	X[589] = new int[8]{-1, 2, 3, 1, 2, 5, 3, -1};

	X[590] = new int[8]{4, 4, 2, 4, 5, 2, 5, 5};
	X[591] = new int[8]{-1, -1, 3, -1, -1, 4, -1, -1};

	X[592] = new int[8]{4, 1, 2, 3, 1, 3, 1, 1};
	X[593] = new int[8]{-1, 2, 3, 4, 2, 5, 2, 2};

	X[594] = new int[8]{2, 4, 1, 4, 4, 5, 2, 5};
	X[595] = new int[8]{4, -1, 2, -1, -1, -1, 3, -1};

	X[596] = new int[8]{3, 2, 4, 5, 5, 8, 2, 2};
	X[597] = new int[8]{5, 4, -1, -1, -1, 2, 4, 4};

	X[598] = new int[8]{4, 5, 5, 1, 5, 5, 8, 1};
	X[599] = new int[8]{-1, -1, -1, 3, -1, -1, 3, 3};

	X[600] = new int[8]{8, 8, 3, 3, 4, 1, 5, 4};
	X[601] = new int[8]{2, 2, 4, 4, -1, 2, -1, -1};

	X[602] = new int[8]{5, 5, 4, 5, 4, 3, 8, 3};
	X[603] = new int[8]{-1, -1, -1, -1, -1, 5, 2, 4};

	X[604] = new int[8]{2, 5, 8, 8, 4, 2, 2, 5};
	X[605] = new int[8]{4, -1, 2, 3, -1, 3, 3, -1};

	X[606] = new int[8]{4, 4, 1, 8, 5, 8, 4, 4};
	X[607] = new int[8]{-1, -1, 3, 3, -1, 3, -1, -1};

	X[608] = new int[8]{3, 5, 4, 1, 3, 5, 8, 8};
	X[609] = new int[8]{4, -1, -1, 3, 4, -1, 3, 1};

	X[610] = new int[8]{2, 5, 5, 5, 8, 4, 1, 5};
	X[611] = new int[8]{3, -1, -1, -1, 3, -1, 2, -1};

	X[612] = new int[8]{4, 1, 8, 5, 8, 5, 1, 4};
	X[613] = new int[8]{-1, 3, 1, -1, 2, -1, 3, -1};

	X[614] = new int[8]{5, 2, 8, 4, 8, 2, 2, 4};
	X[615] = new int[8]{-1, 4, 2, -1, 1, 4, 4, -1};

	X[616] = new int[8]{4, 5, 8, 1, 2, 1, 2, 1};
	X[617] = new int[8]{-1, -1, 3, 3, 3, 2, 4, 3};

	X[618] = new int[8]{2, 4, 4, 3, 5, 4, 8, 2};
	X[619] = new int[8]{4, -1, -1, 4, -1, -1, 3, 3};

	X[620] = new int[8]{8, 3, 4, 2, 4, 2, 3, 1};
	X[621] = new int[8]{2, 5, -1, 4, -1, 3, 4, 3};

	X[622] = new int[8]{5, 2, 2, 1, 8, 2, 5, 8};
	X[623] = new int[8]{-1, 4, 3, 2, 2, 3, -1, 1};

	X[624] = new int[8]{5, 1, 4, 3, 4, 1, 2, 1};
	X[625] = new int[8]{-1, 3, -1, 5, -1, 2, 4, 3};

	X[626] = new int[8]{4, 1, 1, 5, 4, 5, 4, 2};
	X[627] = new int[8]{-1, 3, 2, -1, -1, -1, -1, 4};

	X[628] = new int[8]{2, 1, 3, 8, 5, 8, 8, 3};
	X[629] = new int[8]{3, 2, 5, 3, -1, 2, 1, 5};

	X[630] = new int[8]{3, 4, 5, 4, 5, 3, 5, 4};
	X[631] = new int[8]{4, -1, -1, -1, -1, 5, -1, -1};

	X[632] = new int[8]{4, 5, 8, 1, 2, 1, 5, 5};
	X[633] = new int[8]{-1, -1, 2, 2, 3, 2, -1, -1};

	X[634] = new int[8]{4, 8, 1, 2, 5, 8, 1, 1};
	X[635] = new int[8]{-1, 1, 3, 4, -1, 2, 2, 2};

	X[636] = new int[8]{5, 1, 2, 3, 8, 8, 1, 5};
	X[637] = new int[8]{-1, 3, 3, 4, 1, 2, 3, -1};

	X[638] = new int[8]{5, 4, 2, 8, 5, 2, 5, 3};
	X[639] = new int[8]{-1, -1, 4, 3, -1, 4, -1, 5};

	X[640] = new int[8]{8, 5, 1, 2, 4, 3, 5, 5};
	X[641] = new int[8]{2, -1, 2, 3, -1, 4, -1, -1};

	X[642] = new int[8]{8, 8, 8, 4, 4, 4, 8, 5};
	X[643] = new int[8]{2, 3, 1, -1, -1, -1, 3, -1};

	X[644] = new int[8]{2, 8, 5, 8, 5, 2, 8, 4};
	X[645] = new int[8]{3, 1, -1, 3, -1, 4, 2, -1};

	X[646] = new int[8]{3, 3, 5, 1, 4, 1, 4, 4};
	X[647] = new int[8]{4, 4, -1, 3, -1, 3, -1, -1};

	X[648] = new int[8]{8, 4, 5, 3, 1, 2, 5, 2};
	X[649] = new int[8]{2, -1, -1, 5, 3, 3, -1, 3};

	X[650] = new int[8]{3, 5, 4, 2, 4, 8, 8, 3};
	X[651] = new int[8]{5, -1, -1, 4, -1, 3, 2, 4};

	X[652] = new int[8]{4, 1, 2, 2, 5, 1, 2, 8};
	X[653] = new int[8]{-1, 2, 3, 4, -1, 3, 4, 1};

	X[654] = new int[8]{3, 5, 4, 4, 1, 4, 5, 8};
	X[655] = new int[8]{5, -1, -1, -1, 2, -1, -1, 3};

	X[656] = new int[8]{2, 5, 1, 1, 3, 3, 2, 5};
	X[657] = new int[8]{4, -1, 2, 2, 4, 4, 4, -1};

	X[658] = new int[8]{5, 3, 1, 5, 2, 3, 8, 1};
	X[659] = new int[8]{-1, 4, 2, -1, 4, 5, 1, 3};

	X[660] = new int[8]{5, 1, 1, 2, 5, 3, 4, 5};
	X[661] = new int[8]{-1, 2, 2, 3, -1, 5, -1, -1};

	X[662] = new int[8]{4, 5, 2, 2, 4, 5, 1, 2};
	X[663] = new int[8]{-1, -1, 4, 3, -1, -1, 2, 3};

	X[664] = new int[8]{4, 4, 4, 5, 8, 4, 8, 3};
	X[665] = new int[8]{-1, -1, -1, -1, 2, -1, 2, 5};

	X[666] = new int[8]{4, 2, 2, 3, 2, 1, 8, 3};
	X[667] = new int[8]{-1, 4, 4, 4, 3, 3, 3, 4};

	X[668] = new int[8]{3, 1, 8, 5, 8, 8, 4, 8};
	X[669] = new int[8]{4, 2, 2, -1, 1, 3, -1, 2};

	X[670] = new int[8]{4, 4, 1, 8, 3, 3, 3, 8};
	X[671] = new int[8]{-1, -1, 2, 3, 4, 5, 5, 2};

	X[672] = new int[8]{3, 8, 5, 4, 8, 3, 2, 5};
	X[673] = new int[8]{4, 1, -1, -1, 1, 4, 4, -1};

	X[674] = new int[8]{4, 3, 2, 8, 2, 8, 8, 8};
	X[675] = new int[8]{-1, 5, 4, 2, 3, 3, 2, 2};

	X[676] = new int[8]{5, 5, 3, 8, 4, 5, 5, 5};
	X[677] = new int[8]{-1, -1, 5, 1, -1, -1, -1, -1};

	X[678] = new int[8]{8, 2, 8, 1, 4, 2, 2, 4};
	X[679] = new int[8]{3, 3, 3, 2, -1, 3, 3, -1};

	X[680] = new int[8]{3, 1, 1, 1, 4, 3, 8, 3};
	X[681] = new int[8]{5, 3, 3, 2, -1, 4, 1, 4};

	X[682] = new int[8]{2, 1, 2, 3, 4, 2, 2, 4};
	X[683] = new int[8]{4, 2, 4, 5, -1, 3, 3, -1};

	X[684] = new int[8]{4, 2, 1, 8, 4, 2, 3, 5};
	X[685] = new int[8]{-1, 3, 3, 2, -1, 4, 4, -1};

	X[686] = new int[8]{4, 4, 1, 5, 4, 8, 4, 1};
	X[687] = new int[8]{-1, -1, 2, -1, -1, 3, -1, 2};

	X[688] = new int[8]{4, 3, 5, 5, 5, 3, 2, 8};
	X[689] = new int[8]{-1, 5, -1, -1, -1, 4, 3, 3};

	X[690] = new int[8]{5, 5, 8, 2, 8, 2, 5, 3};
	X[691] = new int[8]{-1, -1, 3, 4, 3, 3, -1, 4};

	X[692] = new int[8]{3, 1, 4, 8, 8, 4, 1, 2};
	X[693] = new int[8]{4, 2, -1, 1, 1, -1, 2, 3};

	X[694] = new int[8]{5, 5, 5, 3, 3, 1, 8, 4};
	X[695] = new int[8]{-1, -1, -1, 4, 4, 3, 3, -1};

	X[696] = new int[8]{5, 4, 5, 4, 5, 3, 4, 8};
	X[697] = new int[8]{-1, -1, -1, -1, -1, 5, -1, 1};

	X[698] = new int[8]{8, 2, 4, 4, 4, 2, 3, 1};
	X[699] = new int[8]{2, 3, -1, -1, -1, 3, 5, 3};

	X[700] = new int[8]{5, 5, 1, 2, 3, 8, 4, 8};
	X[701] = new int[8]{-1, -1, 3, 3, 4, 1, -1, 3};

	X[702] = new int[8]{3, 1, 3, 4, 5, 1, 1, 1};
	X[703] = new int[8]{5, 2, 5, -1, -1, 3, 2, 3};

	X[704] = new int[8]{2, 4, 2, 3, 1, 1, 3, 5};
	X[705] = new int[8]{4, -1, 4, 5, 2, 2, 5, -1};

	X[706] = new int[8]{8, 5, 5, 1, 1, 1, 2, 8};
	X[707] = new int[8]{2, -1, -1, 3, 3, 3, 4, 2};

	X[708] = new int[8]{5, 2, 3, 5, 1, 1, 1, 8};
	X[709] = new int[8]{-1, 3, 4, -1, 3, 3, 3, 2};

	X[710] = new int[8]{4, 4, 4, 8, 5, 3, 8, 5};
	X[711] = new int[8]{-1, -1, -1, 1, -1, 5, 3, -1};

	X[712] = new int[8]{2, 2, 1, 8, 2, 3, 3, 1};
	X[713] = new int[8]{4, 4, 2, 3, 3, 4, 4, 3};

	X[714] = new int[8]{4, 2, 4, 3, 4, 3, 8, 5};
	X[715] = new int[8]{-1, 4, -1, 5, -1, 4, 3, -1};

	X[716] = new int[8]{4, 1, 8, 3, 1, 5, 8, 4};
	X[717] = new int[8]{-1, 3, 1, 4, 2, -1, 1, -1};

	X[718] = new int[8]{3, 3, 1, 3, 3, 5, 3, 3};
	X[719] = new int[8]{4, 5, 2, 5, 4, -1, 4, 4};

	X[720] = new int[8]{5, 8, 5, 5, 4, 4, 5, 5};
	X[721] = new int[8]{-1, 2, -1, -1, -1, -1, -1, -1};

	X[722] = new int[8]{2, 1, 5, 4, 3, 2, 4, 1};
	X[723] = new int[8]{3, 3, -1, -1, 5, 3, -1, 2};

	X[724] = new int[8]{8, 4, 5, 5, 2, 4, 2, 3};
	X[725] = new int[8]{2, -1, -1, -1, 3, -1, 4, 5};

	X[726] = new int[8]{5, 1, 1, 3, 2, 8, 4, 4};
	X[727] = new int[8]{-1, 3, 3, 4, 4, 3, -1, -1};

	X[728] = new int[8]{4, 2, 3, 4, 8, 3, 1, 4};
	X[729] = new int[8]{-1, 4, 5, -1, 3, 5, 3, -1};

	X[730] = new int[8]{4, 8, 4, 5, 5, 4, 5, 5};
	X[731] = new int[8]{-1, 2, -1, -1, -1, -1, -1, -1};

	X[732] = new int[8]{4, 4, 3, 8, 8, 5, 1, 1};
	X[733] = new int[8]{-1, -1, 4, 1, 1, -1, 2, 2};

	X[734] = new int[8]{3, 4, 4, 5, 2, 5, 5, 1};
	X[735] = new int[8]{5, -1, -1, -1, 4, -1, -1, 3};

	X[736] = new int[8]{4, 3, 4, 8, 5, 4, 1, 4};
	X[737] = new int[8]{-1, 5, -1, 2, -1, -1, 2, -1};

	X[738] = new int[8]{8, 1, 8, 1, 3, 5, 4, 8};
	X[739] = new int[8]{3, 2, 3, 3, 5, -1, -1, 2};

	X[740] = new int[8]{4, 4, 4, 5, 4, 2, 8, 4};
	X[741] = new int[8]{-1, -1, -1, -1, -1, 3, 1, -1};

	X[742] = new int[8]{2, 5, 5, 4, 3, 4, 8, 5};
	X[743] = new int[8]{4, -1, -1, -1, 4, -1, 2, -1};

	X[744] = new int[8]{5, 8, 4, 8, 1, 8, 5, 5};
	X[745] = new int[8]{-1, 3, -1, 3, 3, 2, -1, -1};

	X[746] = new int[8]{4, 4, 5, 2, 4, 8, 2, 5};
	X[747] = new int[8]{-1, -1, -1, 4, -1, 3, 3, -1};

	X[748] = new int[8]{2, 3, 5, 4, 4, 5, 4, 1};
	X[749] = new int[8]{4, 4, -1, -1, -1, -1, -1, 3};

	X[750] = new int[8]{5, 3, 5, 2, 8, 8, 4, 2};
	X[751] = new int[8]{-1, 5, -1, 3, 3, 3, -1, 3};

	X[752] = new int[8]{5, 1, 8, 4, 5, 8, 3, 4};
	X[753] = new int[8]{-1, 3, 3, -1, -1, 2, 4, -1};

	X[754] = new int[8]{2, 1, 5, 5, 4, 8, 8, 4};
	X[755] = new int[8]{4, 2, -1, -1, -1, 2, 1, -1};

	X[756] = new int[8]{4, 4, 5, 3, 3, 5, 1, 2};
	X[757] = new int[8]{-1, -1, -1, 4, 4, -1, 3, 3};

	X[758] = new int[8]{5, 8, 1, 5, 2, 3, 5, 4};
	X[759] = new int[8]{-1, 1, 3, -1, 3, 5, -1, -1};

	X[760] = new int[8]{2, 3, 3, 4, 5, 5, 3, 5};
	X[761] = new int[8]{3, 4, 4, -1, -1, -1, 4, -1};

	X[762] = new int[8]{2, 1, 4, 5, 8, 2, 1, 2};
	X[763] = new int[8]{3, 3, -1, -1, 3, 4, 2, 4};

	X[764] = new int[8]{3, 5, 2, 4, 3, 8, 2, 5};
	X[765] = new int[8]{4, -1, 3, -1, 4, 1, 4, -1};

	X[766] = new int[8]{5, 3, 3, 5, 2, 5, 1, 8};
	X[767] = new int[8]{-1, 4, 4, -1, 4, -1, 3, 1};

	X[768] = new int[8]{4, 5, 8, 2, 8, 3, 3, 8};
	X[769] = new int[8]{-1, -1, 2, 3, 2, 4, 4, 1};

	X[770] = new int[8]{4, 4, 2, 5, 8, 4, 5, 2};
	X[771] = new int[8]{-1, -1, 4, -1, 3, -1, -1, 3};

	X[772] = new int[8]{5, 1, 5, 4, 8, 4, 5, 5};
	X[773] = new int[8]{-1, 2, -1, -1, 2, -1, -1, -1};

	X[774] = new int[8]{3, 8, 5, 8, 2, 1, 5, 4};
	X[775] = new int[8]{4, 3, -1, 3, 3, 3, -1, -1};

	X[776] = new int[8]{4, 8, 4, 5, 1, 4, 3, 1};
	X[777] = new int[8]{-1, 1, -1, -1, 2, -1, 4, 3};

	X[778] = new int[8]{2, 4, 2, 1, 4, 4, 3, 5};
	X[779] = new int[8]{4, -1, 3, 3, -1, -1, 4, -1};

	X[780] = new int[8]{4, 4, 3, 4, 8, 8, 8, 1};
	X[781] = new int[8]{-1, -1, 4, -1, 2, 3, 3, 2};

	X[782] = new int[8]{5, 8, 5, 4, 8, 4, 4, 3};
	X[783] = new int[8]{-1, 1, -1, -1, 1, -1, -1, 4};

	X[784] = new int[8]{5, 4, 8, 3, 5, 4, 1, 2};
	X[785] = new int[8]{-1, -1, 3, 5, -1, -1, 2, 4};

	X[786] = new int[8]{5, 8, 8, 5, 4, 2, 4, 2};
	X[787] = new int[8]{-1, 3, 1, -1, -1, 3, -1, 4};

	X[788] = new int[8]{5, 2, 2, 2, 3, 3, 4, 4};
	X[789] = new int[8]{-1, 4, 4, 3, 5, 5, -1, -1};

	X[790] = new int[8]{5, 8, 3, 5, 5, 8, 4, 1};
	X[791] = new int[8]{-1, 3, 5, -1, -1, 2, -1, 2};

	X[792] = new int[8]{2, 1, 4, 1, 3, 5, 3, 5};
	X[793] = new int[8]{4, 2, -1, 3, 5, -1, 4, -1};

	X[794] = new int[8]{5, 5, 3, 1, 5, 4, 8, 1};
	X[795] = new int[8]{-1, -1, 5, 2, -1, -1, 1, 2};

	X[796] = new int[8]{3, 8, 5, 5, 4, 5, 3, 8};
	X[797] = new int[8]{4, 1, -1, -1, -1, -1, 5, 3};

	X[798] = new int[8]{5, 3, 5, 2, 4, 1, 5, 8};
	X[799] = new int[8]{-1, 5, -1, 3, -1, 3, -1, 1};

	X[800] = new int[8]{2, 2, 2, 5, 5, 5, 5, 4};
	X[801] = new int[8]{3, 4, 3, -1, -1, -1, -1, -1};

	X[802] = new int[8]{2, 1, 8, 3, 4, 1, 5, 5};
	X[803] = new int[8]{3, 3, 3, 4, -1, 3, -1, -1};

	X[804] = new int[8]{4, 4, 2, 5, 1, 8, 5, 2};
	X[805] = new int[8]{-1, -1, 3, -1, 2, 3, -1, 3};

	X[806] = new int[8]{5, 1, 5, 3, 3, 4, 1, 3};
	X[807] = new int[8]{-1, 2, -1, 4, 4, -1, 3, 5};

	X[808] = new int[8]{8, 5, 8, 3, 4, 5, 5, 1};
	X[809] = new int[8]{2, -1, 2, 4, -1, -1, -1, 2};

	X[810] = new int[8]{3, 4, 1, 4, 1, 4, 8, 4};
	X[811] = new int[8]{4, -1, 3, -1, 3, -1, 3, -1};

	X[812] = new int[8]{8, 4, 4, 4, 4, 3, 1, 3};
	X[813] = new int[8]{2, -1, -1, -1, -1, 4, 3, 4};

	X[814] = new int[8]{5, 4, 8, 4, 3, 8, 8, 2};
	X[815] = new int[8]{-1, -1, 2, -1, 4, 3, 1, 4};

	X[816] = new int[8]{5, 2, 8, 3, 8, 4, 2, 3};
	X[817] = new int[8]{-1, 4, 1, 5, 3, -1, 4, 4};

	X[818] = new int[8]{8, 5, 4, 5, 2, 4, 5, 8};
	X[819] = new int[8]{2, -1, -1, -1, 4, -1, -1, 3};

	X[820] = new int[8]{8, 8, 5, 1, 2, 2, 5, 5};
	X[821] = new int[8]{3, 1, -1, 2, 4, 4, -1, -1};

	X[822] = new int[8]{4, 5, 8, 8, 4, 2, 8, 3};
	X[823] = new int[8]{-1, -1, 3, 3, -1, 3, 3, 4};

	X[824] = new int[8]{5, 5, 3, 4, 8, 4, 5, 5};
	X[825] = new int[8]{-1, -1, 5, -1, 2, -1, -1, -1};

	X[826] = new int[8]{8, 8, 1, 5, 8, 4, 8, 8};
	X[827] = new int[8]{2, 1, 3, -1, 3, -1, 3, 1};

	X[828] = new int[8]{2, 5, 5, 5, 5, 5, 2, 4};
	X[829] = new int[8]{4, -1, -1, -1, -1, -1, 3, -1};

	X[830] = new int[8]{3, 8, 5, 4, 5, 5, 3, 3};
	X[831] = new int[8]{4, 3, -1, -1, -1, -1, 4, 5};

	X[832] = new int[8]{5, 1, 5, 2, 2, 5, 4, 3};
	X[833] = new int[8]{-1, 2, -1, 3, 4, -1, -1, 5};

	X[834] = new int[8]{5, 5, 5, 4, 5, 5, 8, 5};
	X[835] = new int[8]{-1, -1, -1, -1, -1, -1, 2, -1};

	X[836] = new int[8]{5, 5, 3, 2, 3, 4, 4, 5};
	X[837] = new int[8]{-1, -1, 5, 4, 4, -1, -1, -1};

	X[838] = new int[8]{2, 8, 1, 1, 4, 5, 8, 1};
	X[839] = new int[8]{4, 2, 3, 3, -1, -1, 2, 2};

	X[840] = new int[8]{4, 1, 2, 2, 8, 4, 4, 2};
	X[841] = new int[8]{-1, 2, 3, 4, 1, -1, -1, 4};

	X[842] = new int[8]{4, 5, 8, 8, 5, 4, 5, 8};
	X[843] = new int[8]{-1, -1, 3, 3, -1, -1, -1, 2};

	X[844] = new int[8]{2, 2, 1, 5, 4, 3, 8, 1};
	X[845] = new int[8]{4, 3, 2, -1, -1, 5, 1, 3};

	X[846] = new int[8]{4, 1, 3, 3, 4, 5, 3, 1};
	X[847] = new int[8]{-1, 3, 4, 4, -1, -1, 4, 3};

	X[848] = new int[8]{8, 2, 3, 8, 4, 3, 3, 8};
	X[849] = new int[8]{2, 3, 5, 2, -1, 4, 5, 3};

	X[850] = new int[8]{8, 3, 3, 3, 1, 8, 2, 8};
	X[851] = new int[8]{2, 4, 4, 5, 3, 3, 4, 3};

	X[852] = new int[8]{4, 3, 2, 4, 1, 5, 1, 5};
	X[853] = new int[8]{-1, 5, 3, -1, 2, -1, 3, -1};

	X[854] = new int[8]{8, 3, 2, 5, 3, 1, 5, 2};
	X[855] = new int[8]{3, 4, 3, -1, 5, 3, -1, 4};

	X[856] = new int[8]{5, 2, 4, 1, 4, 2, 8, 2};
	X[857] = new int[8]{-1, 3, -1, 3, -1, 3, 3, 4};

	X[858] = new int[8]{2, 4, 5, 4, 3, 5, 5, 4};
	X[859] = new int[8]{3, -1, -1, -1, 4, -1, -1, -1};

	X[860] = new int[8]{8, 8, 3, 3, 1, 1, 5, 5};
	X[861] = new int[8]{3, 3, 4, 4, 2, 3, -1, -1};

	X[862] = new int[8]{8, 5, 5, 5, 5, 5, 2, 4};
	X[863] = new int[8]{2, -1, -1, -1, -1, -1, 4, -1};

	X[864] = new int[8]{5, 8, 4, 2, 1, 1, 4, 4};
	X[865] = new int[8]{-1, 3, -1, 4, 3, 2, -1, -1};

	X[866] = new int[8]{8, 4, 5, 2, 5, 2, 2, 4};
	X[867] = new int[8]{2, -1, -1, 3, -1, 4, 3, -1};

	X[868] = new int[8]{3, 2, 1, 4, 1, 2, 4, 3};
	X[869] = new int[8]{4, 3, 2, -1, 2, 4, -1, 5};

	X[870] = new int[8]{8, 5, 2, 5, 3, 4, 5, 8};
	X[871] = new int[8]{3, -1, 4, -1, 5, -1, -1, 3};

	X[872] = new int[8]{8, 5, 3, 8, 1, 1, 8, 8};
	X[873] = new int[8]{2, -1, 5, 1, 3, 3, 2, 1};

	X[874] = new int[8]{3, 1, 1, 5, 2, 8, 3, 3};
	X[875] = new int[8]{5, 3, 2, -1, 3, 2, 4, 5};

	X[876] = new int[8]{4, 5, 2, 5, 8, 8, 3, 4};
	X[877] = new int[8]{-1, -1, 4, -1, 1, 2, 5, -1};

	X[878] = new int[8]{4, 4, 4, 4, 5, 4, 3, 8};
	X[879] = new int[8]{-1, -1, -1, -1, -1, -1, 5, 2};

	X[880] = new int[8]{3, 8, 4, 5, 4, 4, 1, 2};
	X[881] = new int[8]{5, 1, -1, -1, -1, -1, 3, 4};

	X[882] = new int[8]{5, 2, 8, 1, 4, 4, 1, 1};
	X[883] = new int[8]{-1, 3, 3, 3, -1, -1, 2, 2};

	X[884] = new int[8]{2, 1, 5, 8, 3, 2, 3, 3};
	X[885] = new int[8]{4, 3, -1, 3, 4, 3, 4, 4};

	X[886] = new int[8]{4, 3, 2, 8, 4, 4, 8, 1};
	X[887] = new int[8]{-1, 4, 3, 1, -1, -1, 3, 3};

	X[888] = new int[8]{3, 4, 4, 5, 5, 5, 3, 4};
	X[889] = new int[8]{4, -1, -1, -1, -1, -1, 4, -1};

	X[890] = new int[8]{3, 5, 8, 4, 2, 5, 2, 3};
	X[891] = new int[8]{4, -1, 1, -1, 3, -1, 4, 4};

	X[892] = new int[8]{4, 2, 2, 8, 3, 8, 4, 8};
	X[893] = new int[8]{-1, 4, 4, 2, 5, 2, -1, 3};

	X[894] = new int[8]{3, 2, 3, 4, 4, 3, 2, 5};
	X[895] = new int[8]{4, 4, 4, -1, -1, 5, 3, -1};

	X[896] = new int[8]{5, 2, 5, 4, 3, 1, 4, 8};
	X[897] = new int[8]{-1, 3, -1, -1, 5, 3, -1, 2};

	X[898] = new int[8]{5, 3, 5, 3, 3, 4, 1, 5};
	X[899] = new int[8]{-1, 4, -1, 4, 5, -1, 2, -1};

	X[900] = new int[8]{4, 1, 8, 3, 1, 2, 8, 2};
	X[901] = new int[8]{-1, 3, 2, 4, 2, 3, 2, 4};

	X[902] = new int[8]{8, 8, 3, 2, 3, 4, 8, 1};
	X[903] = new int[8]{2, 3, 4, 4, 4, -1, 2, 3};

	X[904] = new int[8]{4, 3, 4, 8, 5, 5, 8, 8};
	X[905] = new int[8]{-1, 4, -1, 2, -1, -1, 2, 1};

	X[906] = new int[8]{4, 5, 5, 2, 2, 2, 5, 2};
	X[907] = new int[8]{-1, -1, -1, 3, 3, 3, -1, 4};

	X[908] = new int[8]{4, 8, 4, 3, 4, 5, 4, 1};
	X[909] = new int[8]{-1, 2, -1, 4, -1, -1, -1, 2};

	X[910] = new int[8]{5, 4, 8, 5, 4, 8, 4, 5};
	X[911] = new int[8]{-1, -1, 3, -1, -1, 3, -1, -1};

	X[912] = new int[8]{3, 3, 8, 4, 4, 4, 3, 4};
	X[913] = new int[8]{5, 4, 2, -1, -1, -1, 5, -1};

	X[914] = new int[8]{5, 3, 4, 8, 3, 2, 1, 2};
	X[915] = new int[8]{-1, 4, -1, 3, 5, 4, 3, 4};

	X[916] = new int[8]{3, 8, 1, 1, 8, 1, 5, 8};
	X[917] = new int[8]{5, 3, 2, 3, 2, 2, -1, 3};

	X[918] = new int[8]{3, 3, 5, 4, 3, 5, 5, 8};
	X[919] = new int[8]{4, 5, -1, -1, 4, -1, -1, 1};

	X[920] = new int[8]{8, 2, 8, 5, 8, 3, 3, 4};
	X[921] = new int[8]{2, 4, 3, -1, 3, 4, 4, -1};

	X[922] = new int[8]{2, 3, 2, 4, 4, 1, 4, 1};
	X[923] = new int[8]{4, 5, 4, -1, -1, 3, -1, 3};

	X[924] = new int[8]{5, 4, 8, 4, 5, 8, 5, 3};
	X[925] = new int[8]{-1, -1, 1, -1, -1, 1, -1, 4};

	X[926] = new int[8]{5, 5, 8, 3, 8, 8, 5, 4};
	X[927] = new int[8]{-1, -1, 3, 5, 1, 1, -1, -1};

	X[928] = new int[8]{3, 4, 8, 2, 2, 1, 8, 2};
	X[929] = new int[8]{5, -1, 1, 4, 3, 3, 2, 4};

	X[930] = new int[8]{4, 5, 8, 2, 4, 4, 8, 1};
	X[931] = new int[8]{-1, -1, 2, 3, -1, -1, 2, 2};

	X[932] = new int[8]{5, 4, 4, 1, 2, 5, 5, 8};
	X[933] = new int[8]{-1, -1, -1, 2, 3, -1, -1, 3};

	X[934] = new int[8]{2, 1, 1, 8, 4, 2, 1, 5};
	X[935] = new int[8]{3, 3, 3, 2, -1, 4, 3, -1};

	X[936] = new int[8]{8, 4, 3, 5, 1, 2, 2, 8};
	X[937] = new int[8]{2, -1, 5, -1, 3, 4, 4, 3};

	X[938] = new int[8]{5, 1, 5, 1, 3, 8, 5, 1};
	X[939] = new int[8]{-1, 3, -1, 2, 4, 3, -1, 3};

	X[940] = new int[8]{4, 3, 5, 5, 4, 5, 2, 5};
	X[941] = new int[8]{-1, 5, -1, -1, -1, -1, 4, -1};

	X[942] = new int[8]{4, 8, 1, 1, 5, 5, 8, 5};
	X[943] = new int[8]{-1, 2, 2, 2, -1, -1, 3, -1};

	X[944] = new int[8]{3, 4, 4, 8, 2, 1, 3, 5};
	X[945] = new int[8]{5, -1, -1, 2, 3, 2, 5, -1};

	X[946] = new int[8]{3, 1, 4, 1, 1, 8, 5, 8};
	X[947] = new int[8]{5, 2, -1, 2, 3, 2, -1, 2};

	X[948] = new int[8]{5, 3, 4, 2, 5, 5, 1, 1};
	X[949] = new int[8]{-1, 4, -1, 3, -1, -1, 3, 3};

	X[950] = new int[8]{5, 8, 4, 5, 2, 4, 5, 1};
	X[951] = new int[8]{-1, 2, -1, -1, 4, -1, -1, 2};

	X[952] = new int[8]{5, 4, 5, 4, 2, 4, 4, 4};
	X[953] = new int[8]{-1, -1, -1, -1, 4, -1, -1, -1};

	X[954] = new int[8]{4, 2, 2, 8, 2, 3, 1, 1};
	X[955] = new int[8]{-1, 4, 4, 1, 4, 5, 3, 2};

	X[956] = new int[8]{8, 5, 4, 8, 5, 8, 2, 1};
	X[957] = new int[8]{3, -1, -1, 1, -1, 1, 4, 2};

	X[958] = new int[8]{5, 8, 5, 8, 8, 2, 4, 2};
	X[959] = new int[8]{-1, 2, -1, 1, 3, 4, -1, 4};

	X[960] = new int[8]{4, 4, 3, 5, 3, 1, 4, 2};
	X[961] = new int[8]{-1, -1, 4, -1, 4, 3, -1, 4};

	X[962] = new int[8]{8, 8, 5, 8, 5, 8, 5, 8};
	X[963] = new int[8]{3, 2, -1, 1, -1, 1, -1, 1};

	X[964] = new int[8]{8, 3, 8, 4, 1, 8, 4, 2};
	X[965] = new int[8]{2, 5, 2, -1, 2, 3, -1, 3};

	X[966] = new int[8]{4, 2, 8, 4, 5, 1, 1, 4};
	X[967] = new int[8]{-1, 3, 3, -1, -1, 2, 2, -1};

	X[968] = new int[8]{4, 2, 3, 5, 2, 3, 5, 1};
	X[969] = new int[8]{-1, 3, 4, -1, 3, 4, -1, 3};

	X[970] = new int[8]{3, 5, 4, 8, 8, 5, 4, 5};
	X[971] = new int[8]{4, -1, -1, 3, 2, -1, -1, -1};

	X[972] = new int[8]{3, 4, 2, 5, 4, 1, 1, 2};
	X[973] = new int[8]{5, -1, 4, -1, -1, 3, 2, 4};

	X[974] = new int[8]{3, 1, 1, 5, 8, 8, 1, 3};
	X[975] = new int[8]{4, 2, 2, -1, 2, 3, 3, 4};

	X[976] = new int[8]{8, 4, 5, 8, 2, 5, 4, 8};
	X[977] = new int[8]{2, -1, -1, 3, 4, -1, -1, 3};

	X[978] = new int[8]{8, 4, 3, 2, 1, 3, 5, 4};
	X[979] = new int[8]{2, -1, 4, 3, 3, 5, -1, -1};

	X[980] = new int[8]{5, 1, 5, 2, 2, 4, 4, 8};
	X[981] = new int[8]{-1, 3, -1, 4, 3, -1, -1, 1};

	X[982] = new int[8]{4, 3, 5, 1, 1, 1, 8, 4};
	X[983] = new int[8]{-1, 4, -1, 2, 3, 2, 3, -1};

	X[984] = new int[8]{5, 3, 3, 5, 4, 1, 1, 8};
	X[985] = new int[8]{-1, 4, 4, -1, -1, 2, 3, 3};

	X[986] = new int[8]{3, 4, 2, 1, 1, 8, 8, 4};
	X[987] = new int[8]{4, -1, 4, 3, 3, 1, 2, -1};

	X[988] = new int[8]{2, 4, 8, 5, 5, 4, 1, 1};
	X[989] = new int[8]{3, -1, 2, -1, -1, -1, 3, 3};

	X[990] = new int[8]{2, 4, 5, 4, 1, 4, 3, 5};
	X[991] = new int[8]{4, -1, -1, -1, 2, -1, 5, -1};

	X[992] = new int[8]{8, 3, 4, 5, 1, 1, 3, 4};
	X[993] = new int[8]{2, 5, -1, -1, 3, 2, 4, -1};

	X[994] = new int[8]{2, 2, 8, 8, 8, 3, 8, 4};
	X[995] = new int[8]{3, 3, 1, 2, 2, 4, 3, -1};

	X[996] = new int[8]{5, 2, 2, 4, 4, 4, 8, 5};
	X[997] = new int[8]{-1, 4, 4, -1, -1, -1, 3, -1};

	X[998] = new int[8]{3, 4, 3, 1, 4, 5, 8, 4};
	X[999] = new int[8]{5, -1, 4, 3, -1, -1, 2, -1};

	for (int i = 0; i < 250; i++) {
		data_outputs[i] = 0.01;
	}

	for (int i = 250; i < 500; i++) {
		data_outputs[i] = 0.99;
	}

	// testing dataset for ai:

	double data_outputs_tst[500];
	int *Y[200];
	Y[1] = new int[8]{-1, 3, 5, 6, 4, 3, -1, 4};
	Y[0] = new int[8]{8, 2, 4, 5, 3, 2, 8, 3};
	Y[3] = new int[8]{6, 4, 6, 6, 6, -1, 4, -1};
	Y[2] = new int[8]{5, 3, 5, 5, 5, 8, 3, 8};
	Y[5] = new int[8]{-1, 3, 4, 2, -1, 6, 3, 5};
	Y[4] = new int[8]{8, 2, 3, 1, 8, 5, 2, 4};
	Y[7] = new int[8]{6, 2, 3, -1, -1, 6, 4, 2};
	Y[6] = new int[8]{5, 1, 2, 8, 8, 5, 3, 1};
	Y[9] = new int[8]{5, 4, 6, 4, 6, 2, -1, -1};
	Y[8] = new int[8]{4, 3, 5, 3, 5, 1, 8, 8};
	Y[11] = new int[8]{-1, 5, 5, 4, 5, 3, -1, 6};
	Y[10] = new int[8]{8, 4, 4, 3, 4, 2, 8, 5};
	Y[13] = new int[8]{-1, 3, 3, 5, 5, 4, 6, -1};
	Y[12] = new int[8]{8, 2, 2, 4, 4, 3, 5, 8};
	Y[15] = new int[8]{-1, -1, 5, 2, 2, 2, 4, 3};
	Y[14] = new int[8]{8, 8, 4, 1, 1, 1, 3, 2};
	Y[17] = new int[8]{6, 6, 3, 6, -1, -1, 2, 5};
	Y[16] = new int[8]{5, 5, 2, 5, 8, 8, 1, 4};
	Y[19] = new int[8]{6, -1, 5, 3, -1, 4, 5, 3};
	Y[18] = new int[8]{5, 8, 4, 2, 8, 3, 4, 2};
	Y[21] = new int[8]{5, 4, 4, 4, -1, 5, 2, -1};
	Y[20] = new int[8]{4, 3, 3, 3, 8, 4, 1, 8};
	Y[23] = new int[8]{5, -1, 3, 3, 6, 3, -1, 3};
	Y[22] = new int[8]{4, 8, 2, 2, 5, 2, 8, 2};
	Y[25] = new int[8]{-1, 5, 3, 4, 2, 3, -1, 5};
	Y[24] = new int[8]{8, 4, 2, 3, 1, 2, 8, 4};
	Y[27] = new int[8]{5, 5, -1, 5, 5, 5, -1, 3};
	Y[26] = new int[8]{4, 4, 8, 4, 4, 4, 8, 2};
	Y[29] = new int[8]{6, 6, -1, 3, -1, 3, 6, 4};
	Y[28] = new int[8]{5, 5, 8, 2, 8, 2, 5, 3};
	Y[31] = new int[8]{5, 5, 6, -1, 3, -1, 6, 2};
	Y[30] = new int[8]{4, 4, 5, 8, 2, 8, 5, 1};
	Y[33] = new int[8]{4, -1, -1, 2, 2, 6, 5, 6};
	Y[32] = new int[8]{3, 8, 8, 1, 1, 5, 4, 5};
	Y[35] = new int[8]{3, 2, -1, -1, 2, 3, 6, 4};
	Y[34] = new int[8]{2, 1, 8, 8, 1, 2, 5, 3};
	Y[37] = new int[8]{3, 2, 2, -1, 5, -1, 2, 5};
	Y[36] = new int[8]{2, 1, 1, 8, 4, 8, 1, 4};
	Y[39] = new int[8]{5, 5, -1, 5, 3, 3, 3, -1};
	Y[38] = new int[8]{4, 4, 8, 4, 2, 2, 2, 8};
	Y[41] = new int[8]{4, -1, 2, 5, -1, 2, 6, 4};
	Y[40] = new int[8]{3, 8, 1, 4, 8, 1, 5, 3};
	Y[43] = new int[8]{6, 5, 4, -1, -1, 5, 6, 3};
	Y[42] = new int[8]{5, 4, 3, 8, 8, 4, 5, 2};
	Y[45] = new int[8]{3, 2, 6, -1, 5, -1, 6, 3};
	Y[44] = new int[8]{2, 1, 5, 8, 4, 8, 5, 2};
	Y[47] = new int[8]{-1, 6, -1, 3, 6, 6, 5, 5};
	Y[46] = new int[8]{8, 5, 8, 2, 5, 5, 4, 4};
	Y[49] = new int[8]{-1, 5, 4, 3, 4, -1, 2, 2};
	Y[48] = new int[8]{8, 4, 3, 2, 3, 8, 1, 1};
	Y[51] = new int[8]{6, 4, 2, -1, 3, 3, -1, 5};
	Y[50] = new int[8]{5, 3, 1, 8, 2, 2, 8, 4};
	Y[53] = new int[8]{-1, 3, 2, 2, 3, 4, -1, 6};
	Y[52] = new int[8]{8, 2, 1, 1, 2, 3, 8, 5};
	Y[55] = new int[8]{-1, -1, 5, 6, 3, 5, 2, 4};
	Y[54] = new int[8]{8, 8, 4, 5, 2, 4, 1, 3};
	Y[57] = new int[8]{4, 6, 4, -1, 3, -1, 2, 2};
	Y[56] = new int[8]{3, 5, 3, 8, 2, 8, 1, 1};
	Y[59] = new int[8]{-1, 5, 4, -1, 5, 6, 4, 3};
	Y[58] = new int[8]{8, 4, 3, 8, 4, 5, 3, 2};
	Y[61] = new int[8]{4, 2, 3, -1, 4, 6, -1, 3};
	Y[60] = new int[8]{3, 1, 2, 8, 3, 5, 8, 2};
	Y[63] = new int[8]{4, 6, -1, 5, 6, 4, -1, 3};
	Y[62] = new int[8]{3, 5, 8, 4, 5, 3, 8, 2};
	Y[65] = new int[8]{3, 6, -1, 3, 5, -1, 3, 4};
	Y[64] = new int[8]{2, 5, 8, 2, 4, 8, 2, 3};
	Y[67] = new int[8]{4, 3, 4, -1, 6, 2, 2, -1};
	Y[66] = new int[8]{3, 2, 3, 8, 5, 1, 1, 8};
	Y[69] = new int[8]{5, -1, -1, 6, 5, 6, 2, 6};
	Y[68] = new int[8]{4, 8, 8, 5, 4, 5, 1, 5};
	Y[71] = new int[8]{6, 5, -1, 3, 3, 6, 3, -1};
	Y[70] = new int[8]{5, 4, 8, 2, 2, 5, 2, 8};
	Y[73] = new int[8]{-1, 2, 4, 6, 5, 6, -1, 3};
	Y[72] = new int[8]{8, 1, 3, 5, 4, 5, 8, 2};
	Y[75] = new int[8]{6, 3, 3, -1, 5, 6, 3, -1};
	Y[74] = new int[8]{5, 2, 2, 8, 4, 5, 2, 8};
	Y[77] = new int[8]{4, 5, 6, 2, 2, -1, 6, -1};
	Y[76] = new int[8]{3, 4, 5, 1, 1, 8, 5, 8};
	Y[79] = new int[8]{5, 3, 4, -1, -1, 2, 2, 2};
	Y[78] = new int[8]{4, 2, 3, 8, 8, 1, 1, 1};
	Y[81] = new int[8]{5, 6, 2, -1, 6, -1, 3, 4};
	Y[80] = new int[8]{4, 5, 1, 8, 5, 8, 2, 3};
	Y[83] = new int[8]{-1, -1, 2, 2, 5, 3, 4, 3};
	Y[82] = new int[8]{8, 8, 1, 1, 4, 2, 3, 2};
	Y[85] = new int[8]{-1, 5, -1, 6, 5, 2, 3, 3};
	Y[84] = new int[8]{8, 4, 8, 5, 4, 1, 2, 2};
	Y[87] = new int[8]{3, 2, 6, -1, 2, 4, -1, 2};
	Y[86] = new int[8]{2, 1, 5, 8, 1, 3, 8, 1};
	Y[89] = new int[8]{4, 6, -1, 2, 6, 6, 5, -1};
	Y[88] = new int[8]{3, 5, 8, 1, 5, 5, 4, 8};
	Y[91] = new int[8]{4, -1, 3, 2, 4, 4, 5, -1};
	Y[90] = new int[8]{3, 8, 2, 1, 3, 3, 4, 8};
	Y[93] = new int[8]{4, 3, 5, -1, -1, 4, 6, 3};
	Y[92] = new int[8]{3, 2, 4, 8, 8, 3, 5, 2};
	Y[95] = new int[8]{6, 5, 2, -1, 2, -1, 4, 6};
	Y[94] = new int[8]{5, 4, 1, 8, 1, 8, 3, 5};
	Y[97] = new int[8]{-1, 3, 5, 4, 3, -1, 4, 6};
	Y[96] = new int[8]{8, 2, 4, 3, 2, 8, 3, 5};
	Y[99] = new int[8]{-1, 2, 5, -1, 6, 6, 4, 6};
	Y[98] = new int[8]{8, 1, 4, 8, 5, 5, 3, 5};
	Y[101] = new int[8]{-1, 6, 6, 5, 6, -1, 2, 6};
	Y[100] = new int[8]{8, 5, 5, 4, 5, 8, 1, 5};
	Y[103] = new int[8]{3, 2, 5, -1, 5, 6, 5, -1};
	Y[102] = new int[8]{2, 1, 4, 8, 4, 5, 4, 8};
	Y[105] = new int[8]{-1, -1, 4, 4, 2, 6, 3, 6};
	Y[104] = new int[8]{8, 8, 3, 3, 1, 5, 2, 5};
	Y[107] = new int[8]{4, 3, -1, 6, 2, -1, 5, 4};
	Y[106] = new int[8]{3, 2, 8, 5, 1, 8, 4, 3};
	Y[109] = new int[8]{5, 3, 5, -1, 2, 3, -1, 4};
	Y[108] = new int[8]{4, 2, 4, 8, 1, 2, 8, 3};
	Y[111] = new int[8]{5, 5, 6, 3, 5, 4, -1, -1};
	Y[110] = new int[8]{4, 4, 5, 2, 4, 3, 8, 8};
	Y[113] = new int[8]{-1, 2, 6, 6, 4, 5, -1, 2};
	Y[112] = new int[8]{8, 1, 5, 5, 3, 4, 8, 1};
	Y[115] = new int[8]{-1, 4, 2, 2, 6, -1, 3, 3};
	Y[114] = new int[8]{8, 3, 1, 1, 5, 8, 2, 2};
	Y[117] = new int[8]{4, 4, -1, 4, 6, 4, 4, -1};
	Y[116] = new int[8]{3, 3, 8, 3, 5, 3, 3, 8};
	Y[119] = new int[8]{6, 4, 6, 2, 5, -1, 3, -1};
	Y[118] = new int[8]{5, 3, 5, 1, 4, 8, 2, 8};
	Y[121] = new int[8]{6, -1, 3, 6, 4, 6, -1, 2};
	Y[120] = new int[8]{5, 8, 2, 5, 3, 5, 8, 1};
	Y[123] = new int[8]{5, 5, -1, 5, -1, 4, 4, 4};
	Y[122] = new int[8]{4, 4, 8, 4, 8, 3, 3, 3};
	Y[125] = new int[8]{5, 6, 2, 2, 4, -1, -1, 5};
	Y[124] = new int[8]{4, 5, 1, 1, 3, 8, 8, 4};
	Y[127] = new int[8]{6, 6, 4, -1, 5, -1, 2, 5};
	Y[126] = new int[8]{5, 5, 3, 8, 4, 8, 1, 4};
	Y[129] = new int[8]{6, -1, 4, 6, 6, -1, 4, 5};
	Y[128] = new int[8]{5, 8, 3, 5, 5, 8, 3, 4};
	Y[131] = new int[8]{-1, 4, 6, 5, -1, 3, 4, 3};
	Y[130] = new int[8]{8, 3, 5, 4, 8, 2, 3, 2};
	Y[133] = new int[8]{-1, 6, 4, -1, 5, 5, 5, 6};
	Y[132] = new int[8]{8, 5, 3, 8, 4, 4, 4, 5};
	Y[135] = new int[8]{-1, 5, 4, 5, -1, 3, 5, 2};
	Y[134] = new int[8]{8, 4, 3, 4, 8, 2, 4, 1};
	Y[137] = new int[8]{3, -1, 5, -1, 3, 6, 2, 4};
	Y[136] = new int[8]{2, 8, 4, 8, 2, 5, 1, 3};
	Y[139] = new int[8]{3, -1, 4, -1, 5, 2, 2, 4};
	Y[138] = new int[8]{2, 8, 3, 8, 4, 1, 1, 3};
	Y[141] = new int[8]{-1, 3, 6, 2, -1, 5, 4, 2};
	Y[140] = new int[8]{8, 2, 5, 1, 8, 4, 3, 1};
	Y[143] = new int[8]{5, 3, 6, 2, -1, 4, -1, 6};
	Y[142] = new int[8]{4, 2, 5, 1, 8, 3, 8, 5};
	Y[145] = new int[8]{6, 5, 3, 3, -1, 2, 3, -1};
	Y[144] = new int[8]{5, 4, 2, 2, 8, 1, 2, 8};
	Y[147] = new int[8]{6, 5, 2, 2, 2, -1, 2, -1};
	Y[146] = new int[8]{5, 4, 1, 1, 1, 8, 1, 8};
	Y[149] = new int[8]{-1, 6, 6, 3, 6, -1, 6, 4};
	Y[148] = new int[8]{8, 5, 5, 2, 5, 8, 5, 3};
	Y[151] = new int[8]{6, -1, 4, -1, 2, 2, 2, 2};
	Y[150] = new int[8]{5, 8, 3, 8, 1, 1, 1, 1};
	Y[153] = new int[8]{3, -1, 2, -1, 5, 3, 5, 6};
	Y[152] = new int[8]{2, 8, 1, 8, 4, 2, 4, 5};
	Y[155] = new int[8]{-1, 3, 6, 5, -1, 4, 6, 2};
	Y[154] = new int[8]{8, 2, 5, 4, 8, 3, 5, 1};
	Y[157] = new int[8]{-1, 4, 5, 6, 2, -1, 6, 3};
	Y[156] = new int[8]{8, 3, 4, 5, 1, 8, 5, 2};
	Y[159] = new int[8]{6, -1, 4, -1, 6, 4, 2, 5};
	Y[158] = new int[8]{5, 8, 3, 8, 5, 3, 1, 4};
	Y[161] = new int[8]{-1, -1, 2, 5, 2, 4, 2, 3};
	Y[160] = new int[8]{8, 8, 1, 4, 1, 3, 1, 2};
	Y[163] = new int[8]{5, 5, -1, -1, 6, 3, 2, 4};
	Y[162] = new int[8]{4, 4, 8, 8, 5, 2, 1, 3};
	Y[165] = new int[8]{-1, 4, 3, 4, 4, -1, 4, 3};
	Y[164] = new int[8]{8, 3, 2, 3, 3, 8, 3, 2};
	Y[167] = new int[8]{4, -1, 6, 3, 6, -1, 6, 5};
	Y[166] = new int[8]{3, 8, 5, 2, 5, 8, 5, 4};
	Y[169] = new int[8]{5, -1, 2, 5, 2, -1, 3, 4};
	Y[168] = new int[8]{4, 8, 1, 4, 1, 8, 2, 3};
	Y[171] = new int[8]{-1, 2, 5, 5, -1, 5, 5, 3};
	Y[170] = new int[8]{8, 1, 4, 4, 8, 4, 4, 2};
	Y[173] = new int[8]{4, -1, 4, -1, 2, 4, 3, 6};
	Y[172] = new int[8]{3, 8, 3, 8, 1, 3, 2, 5};
	Y[175] = new int[8]{3, 6, 4, -1, 2, 4, 3, -1};
	Y[174] = new int[8]{2, 5, 3, 8, 1, 3, 2, 8};
	Y[177] = new int[8]{4, 6, 6, 3, -1, 4, 2, -1};
	Y[176] = new int[8]{3, 5, 5, 2, 8, 3, 1, 8};
	Y[179] = new int[8]{-1, 2, -1, 2, 3, 5, 5, 6};
	Y[178] = new int[8]{8, 1, 8, 1, 2, 4, 4, 5};
	Y[181] = new int[8]{5, 2, 4, 5, 3, -1, 4, -1};
	Y[180] = new int[8]{4, 1, 3, 4, 2, 8, 3, 8};
	Y[183] = new int[8]{5, 4, 6, -1, 2, 3, 3, -1};
	Y[182] = new int[8]{4, 3, 5, 8, 1, 2, 2, 8};
	Y[185] = new int[8]{5, 3, 6, -1, -1, 4, 4, 2};
	Y[184] = new int[8]{4, 2, 5, 8, 8, 3, 3, 1};
	Y[187] = new int[8]{5, -1, 3, -1, 5, 4, 2, 3};
	Y[186] = new int[8]{4, 8, 2, 8, 4, 3, 1, 2};
	Y[189] = new int[8]{5, 2, -1, 3, 4, -1, 5, 3};
	Y[188] = new int[8]{4, 1, 8, 2, 3, 8, 4, 2};
	Y[191] = new int[8]{3, 4, 4, -1, 4, -1, 5, 3};
	Y[190] = new int[8]{2, 3, 3, 8, 3, 8, 4, 2};
	Y[193] = new int[8]{3, -1, 2, 2, 4, 5, -1, 6};
	Y[192] = new int[8]{2, 8, 1, 1, 3, 4, 8, 5};
	Y[195] = new int[8]{5, -1, -1, 6, 6, 5, 5, 3};
	Y[194] = new int[8]{4, 8, 8, 5, 5, 4, 4, 2};
	Y[197] = new int[8]{6, -1, -1, 2, 3, 6, 3, 6};
	Y[196] = new int[8]{5, 8, 8, 1, 2, 5, 2, 5};
	Y[199] = new int[8]{3, 6, 2, -1, 3, 5, -1, 2};
	Y[198] = new int[8]{2, 5, 1, 8, 2, 4, 8, 1};
#pragma endregion

	for (int i = 0; i < 50; i++) {
		data_outputs_tst[i] = 0.99;
	}

	for (int i = 50; i < 100; i++) {
		data_outputs_tst[i] = 0.99;
	}

	int dimension = 23;
	int num_data_points = 500;
	int num_data_points_tst = 100;


	return TheRegression::bestFitF(basis, X, data_outputs, dimension, num_data_points);
}



} // namespace EvaluationFunction