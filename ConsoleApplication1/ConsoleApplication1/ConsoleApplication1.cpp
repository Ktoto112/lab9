#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int determinant(const vector<vector<int>>& matrix) {
    int det = 0;
    if (matrix.size() == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    for (int i = 0; i < matrix[0].size(); i++) {
        vector<vector<int>> subMatrix;
        for (int j = 1; j < matrix.size(); j++) {
            vector<int> row;
            for (int k = 0; k < matrix[0].size(); k++) {
                if (k != i) {
                    row.push_back(matrix[j][k]);
                }
            }
            subMatrix.push_back(row);
        }
        det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(subMatrix);
    }
    return det;
}


vector<vector<int>> inverseMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    int det = determinant(matrix);
    if (det == 0) {
        throw runtime_error("The matrix has no inverse");
    }

    vector<vector<int>> adj(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<vector<int>> subMatrix;
            for (int row = 0; row < n; row++) {
                if (row != i) {
                    vector<int> subRow;
                    for (int col = 0; col < n; col++) {
                        if (col != j) {
                            subRow.push_back(matrix[row][col]);
                        }
                    }
                    subMatrix.push_back(subRow);
                }
            }
            adj[i][j] = (i + j) % 2 == 0 ? determinant(subMatrix) : -determinant(subMatrix);
        }
    }

    vector<vector<int>> adjT(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjT[i][j] = adj[j][i];
        }
    }

    vector<vector<int>> inv(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i][j] = adjT[i][j] / det;
        }
    }

    return inv;
}

int main() {
    
    vector<vector<int>> matrix(5, vector<int>(5));

    cout << "Enter the elements of the 5x5 matrix:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> matrix[i][j];
        }
    }

   
    try {
        vector<vector<int>> invMatrix = inverseMatrix(matrix);
        cout << "Inverse matrix:\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << invMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    
    vector<int> minArray(5);
    for (int i = 0; i < 5; i++) {
        int minElem = matrix[i][0];
        for (int j = 1; j < 5; j++) {
            if (matrix[i][j] < minElem) {
                minElem = matrix[i][j];
            }
        }
        minArray[i] = minElem;
    }

    
    sort(minArray.rbegin(), minArray.rend());

    
    cout << "An array of minimum elements sorted in descending order:\n";
    for (int i = 0; i < 5; i++) {
        cout << minArray[i] << " ";
    }
    cout << endl;

    return 0;
}
