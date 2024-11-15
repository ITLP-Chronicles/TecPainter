#include "rotationutils.h"
#include <stdexcept>

bool RotationUtils::isRotationMatrix(const Matrix& R) {
    if (R.rows != 3 || R.columns != 3) return false;

    // Create transpose matrix
    Matrix Rt(3, 3);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            Rt.data[i][j] = R.data[j][i];
        }
    }

    // Calculate Rt * R
    Matrix shouldBeIdentity = Rt * R;

    // Create identity matrix
    Matrix I(3, 3, {
                       {1, 0, 0},
                       {0, 1, 0},
                       {0, 0, 1}
                   });

    // Calculate norm difference
    double norm = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            norm += pow(shouldBeIdentity.data[i][j] - I.data[i][j], 2);
        }
    }
    norm = sqrt(norm);

    return norm < 1e-6;
}

Vertex RotationUtils::rotationMatrixToEulerAngles(const Matrix& R) {
    if (!isRotationMatrix(R)) {
        throw std::runtime_error("Matrix is not a valid rotation matrix");
    }

    double sy = sqrt(R.data[0][0] * R.data[0][0] + R.data[1][0] * R.data[1][0]);
    bool singular = sy < 1e-6;

    double x, y, z;
    if (!singular) {
        x = atan2(R.data[2][1], R.data[2][2]);
        y = atan2(-R.data[2][0], sy);
        z = atan2(R.data[1][0], R.data[0][0]);
    } else {
        x = atan2(-R.data[1][2], R.data[1][1]);
        y = atan2(-R.data[2][0], sy);
        z = 0;
    }

    return Vertex(x, y, z);
}

Matrix RotationUtils::eulerAnglesToRotationMatrix(const Vertex& angles) {
    // Create rotation matrices for each axis
    Matrix R_x(3, 3, {
                         {1, 0, 0},
                         {0, cos(angles.x), -sin(angles.x)},
                         {0, sin(angles.x), cos(angles.x)}
                     });

    Matrix R_y(3, 3, {
                         {cos(angles.y), 0, sin(angles.y)},
                         {0, 1, 0},
                         {-sin(angles.y), 0, cos(angles.y)}
                     });

    Matrix R_z(3, 3, {
                         {cos(angles.z), -sin(angles.z), 0},
                         {sin(angles.z), cos(angles.z), 0},
                         {0, 0, 1}
                     });

    // Combined rotation matrix
    return R_z * (R_y * R_x);
}
