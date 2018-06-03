#include "PoseMath.h"

/**
 * TODO: see header file for documentation
 */
void convertTicksTo2DPositions(uint32_t clockTicks[8], double pos2D[8])
{

  // this is for the horizontal sweep
  for (int i=0; i<8; i+=2)
  {

    // compute angle
    double angle_rad = -(double(clockTicks[i])/CLOCKS_PER_SECOND) / ( (1.0/60.0)/(2*PI) ) + PI/2.0;
    // compute coordinates on plane at unit distance
    pos2D[i] = tan(angle_rad);

  }

  // this is for the vertical sweep
  for (int i=1; i<8; i+=2)
  {

    // compute angle
    double angle_rad = (double(clockTicks[i])/CLOCKS_PER_SECOND) / ( (1.0/60.0)/(2*PI) ) - PI/2.0;
    // compute coordinates on plane at unit distance
    pos2D[i] = tan(angle_rad);

  }


}

/**
 * TODO: see header file for documentation
 */
void formA(double pos2D[8], double posRef[8], double Aout[8][8]) {

  //form matrix A
  double A[8][8] = {

    {posRef[0], posRef[1], 1.0, 0.0, 0.0, 0.0, -posRef[0]*pos2D[0], -posRef[1]*pos2D[0]},

    {0.0, 0.0, 0.0, posRef[0], posRef[1], 1.0, -posRef[0]*pos2D[1], -posRef[1]*pos2D[1]},

    {posRef[2], posRef[3], 1.0, 0.0, 0.0, 0.0, -posRef[2]*pos2D[2], -posRef[3]*pos2D[2]},

    {0.0, 0.0, 0.0, posRef[2], posRef[3], 1.0, -posRef[2]*pos2D[3], -posRef[3]*pos2D[3]},

    {posRef[4], posRef[5], 1.0, 0.0, 0.0, 0.0, -posRef[4]*pos2D[4], -posRef[5]*pos2D[4]},

    {0.0, 0.0, 0.0, posRef[4], posRef[5], 1.0, -posRef[4]*pos2D[5], -posRef[5]*pos2D[5]},

    {posRef[6], posRef[7], 1.0, 0.0, 0.0, 0.0, -posRef[6]*pos2D[6], -posRef[7]*pos2D[6]},

    {0.0, 0.0, 0.0, posRef[6], posRef[7], 1.0, -posRef[6]*pos2D[7], -posRef[7]*pos2D[7]},

  };

  //copy to output variable
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Aout[i][j] = A[i][j];
    }
  }

}


/**
 * TODO: see header file for documentation
 */
bool solveForH(double A[8][8], double b[8], double hOut[8]) {

  //invert A
  int inv = Matrix.Invert((double*)A, 8);
  if (inv == 0) {
    return false;
  }

  //multiply with b, h = A^{-1} * b
  Matrix.Multiply((double*)A, b, 8, 8, 1, hOut);

  return true;

}


/**
 * TODO: see header file for documentation
 */
void getRtFromH(double h[8], double ROut[3][3], double pos3DOut[3]) {

  // get length of rotation vectors, i.e. first and second columns of homography matrix
  double lengthR1 = sqrt( h[0]*h[0] + h[3]*h[3] + h[6]*h[6] );
  double lengthR2 = sqrt( h[1]*h[1] + h[4]*h[4] + h[7]*h[7] );

  // normalization factor for position
  double normalizationFactor = (lengthR1 + lengthR2) / 2.0;

  // Translation vector:
  pos3DOut[0] = h[2]/normalizationFactor;
  pos3DOut[1] = h[5]/normalizationFactor;
  pos3DOut[2] = -1.0/normalizationFactor;

  // get rotation
  // get first column of rotation matrix and normalize
  double r1[3] = { h[0]/lengthR1, h[3]/lengthR1, -h[6]/lengthR1 };


  // get second column
  double dotProd = r1[0]*h[1] + r1[1]*h[4] - r1[2]*h[7];

  double r2[3] = {
    h[1] - dotProd*r1[0],
    h[4] - dotProd*r1[1],
    -h[7] - dotProd*r1[2] };

  double normr2 = sqrt( r2[0]*r2[0] + r2[1]*r2[1] + r2[2]*r2[2] );
  r2[0] = r2[0] / normr2;
  r2[1] = r2[1] / normr2;
  r2[2] = r2[2] / normr2;

  // get 3rd column that is orthogonal to both of the others
  double r3[3] = {
    r1[1]*r2[2] - r1[2]*r2[1],
    r1[2]*r2[0] - r1[0]*r2[2],
    r1[0]*r2[1] - r1[1]*r2[0] };

  // populate rotation matrix in row-major order
  for (int i = 0; i < 3; i++) {
    ROut[i][0] = r1[i];
    ROut[i][1] = r2[i];
    ROut[i][2] = r3[i];
  }

}



/**
 * TODO: see header file for documentation
 */
Quaternion getQuaternionFromRotationMatrix(double R[3][3]) {

  //decompose rotation matrix into columns
  double r1[3] = {R[0][0], R[1][0], R[2][0]};
  double r2[3] = {R[0][1], R[1][1], R[2][1]};
  double r3[3] = {R[0][2], R[1][2], R[2][2]};

  double c = 1.0 + r1[0] + r2[1] + r3[2];
  float q[4];
  q[0] = 0.5 * sqrt(c);
  q[1] = (r2[2] - r3[1])/(4*q[0]);
  q[2] = (r3[0] - r1[2])/(4*q[0]);
  q[3] = (r1[1] - r2[0])/(4*q[0]);

  //note there is a sign ambiguity in the quaternion because of the square root
  //i.e. q and -q give the same R
  return Quaternion(q[0], q[1], q[2], q[3]);

}
