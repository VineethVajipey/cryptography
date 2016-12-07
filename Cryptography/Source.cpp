#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <ctime>
#include <cmath>
using namespace std;

vector<vector<int>> vMultiply(vector<vector<double>> vec1, vector<vector<int>> vec2) {
	// Find the product of matrices
	vector<vector<int>> vec3(3);
	for (int i = 0; i < 3; i++) {
		long double sum = 0;
		for (int j = 0; j < 3; j++) {
			sum += vec1[i][j] * vec2[j][0];
		}
		vec3[i].push_back(round(sum));
	}

	// DEBUG: Output product
	/*for (int i = 0; i < 3; i++) {
	cout << vec3[i][0] << endl;
	}*/

	return vec3;
}

vector<vector<int>> vMultiply(vector<vector<int>> vec1, vector<vector<int>> vec2) {
	// Find the product of matrices
	vector<vector<int>> vec3(3);
	for (int i = 0; i < 3; i++) {
		int sum = 0;
		for (int j = 0; j < 3; j++) {
			sum += vec1[i][j] * vec2[j][0];
		}
		vec3[i].push_back(sum);
	}

	// DEBUG: Output product
	/*for (int i = 0; i < 3; i++) {
	cout << vec3[i][0] << endl;
	}*/

	return vec3;
}

vector<vector<int>> toVectors(string input) {
	// Convert to vector of numbers
	vector<int> numInput;
	for (int i = 0; i < input.length(); i++) {
		int value;
		// Note: Using ASCII numbers
		if (input[i] == ' ') {
			value = 26;
		}
		else {
			value = toupper(input[i]) - 65;
		}
		numInput.push_back(value);
	}
	// Append 0's if necessary
	while (numInput.size() % 3 != 0) {
		numInput.push_back(26);
	}

	// DEBUG: Output numInput
	/*for (int i = 0; i < input.length(); i++) {
	cout << numInput[i] << " ";
	}
	cout << endl;*/

	// Convert to vector of vector3's
	int numberOfVectors = ceil(input.length() / 3.0);
	vector<vector<int>> vectors(3);
	for (int j = 0; j < numberOfVectors; j++) {
		for (int i = 0; i < 3; i++) {
			vectors[i].push_back(numInput[3 * j + i]);
		}
	}

	// DEBUG: Output vectors
	cout << "input vectors:" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < numberOfVectors; j++) {
			cout << vectors[i][j] << " ";
		}
		cout << endl;
	}

	return vectors;
}

vector<vector<int>> getVector(vector<vector<int>> vectors, int index) {
	vector<vector<int>> result(3);

	for (int i = 0; i < 3; i++) {
		result[i].push_back(vectors[i][index]);
	}

	// DEBUG: Display result
	/*for (int i = 0; i < 3; i++) {
	cout << result[i][0] << endl;
	}*/

	return result;
}

vector<vector<int>> keyGenerate() {
	srand(time(0));

	vector<vector<int>> key(3, vector<int>(3));

	/* Enough entropy such that if a key is tried every *nanosecond*, it takes an average of over
	40,000 years to crack, which is the time since Neanderthals went extinct. If a key is tried
	every millisecond (more realistic), it takes an average of over 3 times the age of the
	universe to crack. So it's very secure.
	*/

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			key[i][j] = rand() % 241 - 10;
		}
	}


	// DEBUG: Output key
	cout << "key: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << key[i][j] << " ";
		}
		cout << endl;
	}

	return key;
}

vector<vector<int>> consolidateVectors(vector<vector<int>> vectors, vector<vector<int>> key) {
	vector<vector<int>> transferVectors(vectors);

	for (int i = 0; i < vectors[0].size(); i++) {
		vector<vector<int>> column = vMultiply(key, getVector(vectors, i));
		for (int j = 0; j < 3; j++) {
			transferVectors[j][i] = column[j][0];
		}
	}

	// DEBUG: Output transferVectors
	cout << "transfer vectors: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < transferVectors[0].size(); j++) {
			cout << transferVectors[i][j] << " ";
		}
		cout << endl;
	}

	return transferVectors;
}

vector<vector<int>> consolidateVectors(vector<vector<int>> vectors, vector<vector<double>> inverse) {
	vector<vector<int>> transferVectors(vectors); // transferVectors to vectors size, values don't matter

	for (int i = 0; i < vectors[0].size(); i++) {
		vector<vector<int>> column = vMultiply(inverse, getVector(vectors, i));
		for (int j = 0; j < 3; j++) {
			transferVectors[j][i] = ceil(column[j][0]);
		}
	}

	// DEBUG: Output transferVectors
	cout << "transfer vectors: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < transferVectors[0].size(); j++) {
			cout << transferVectors[i][j] << " ";
		}
		cout << endl;
	}

	return transferVectors;
}

double determinant3(vector<vector<int>> key) {
	double determinant;

	determinant = key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]) - key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]) + key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);

	// DEBUG: print determinant
	cout << "determinant: " << endl;
	cout << determinant << endl;

	return determinant;
}

vector<vector<int>> transpose(vector<vector<int>> key) {

	int i, j;
	vector<vector<int>> transpose(3, vector<int>(3));
	for (i = 0; i<3; i++) {
		for (j = 0; j < 3; j++) 
			transpose[i][j] = key[j][i];
		
		
	}

	// DEBUG
	for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	cout << transpose[i][j] << " ";
	}
	cout << endl;
	}

	return transpose;
}

vector<vector<int>> cofactors(vector<vector<int>> key) {

	vector<vector<int>> cofactor(3, vector<int>(3));

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {
			int a, b, c, d, e, f, g, h;

			if (i == 0) {
				a = 1;
				b = 2;
				c = 2;
				d = 1;
			}
			else if (i == 1) {
				a = 0;
				b = 2;
				c = 2;
				d = 0;
			}
			else if (i == 2) {
				a = 0;
				b = 1;
				c = 1;
				d = 0;
			}

			if (j == 0) {
				e = 1;
				f = 2;
				g = 1;
				h = 2;
			}
			else if (j == 1) {
				e = 0;
				f = 2;
				g = 0;
				h = 2;
			}
			else {
				e = 0;
				f = 1;
				g = 0;
				h = 1;
			}

			// DEBUG
			/*cout << a << " " << b << " " << c << " " << d << " " << endl << e << " " << f << " " << g << " " << h << endl;*/

			cofactor[i][j] = (key[a][e] * key[b][f] - key[c][g] * key[d][h])*pow(-1, (i + j));

		}
	}

	// DEBUG
	cout << "cofactor matrix:" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << cofactor[i][j] << " ";
		}
		cout << endl;
	}

	return cofactor;
}

vector<vector<int>> adjoint(vector<vector<int>> cofactor) {

	return transpose(cofactor);
}

vector<vector<double>> inverse(vector<vector<int>> adjoint, double determinant) {
	vector<vector<double>> inverse(3, vector<double>(3));

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			inverse[i][j] = static_cast<double>(adjoint[i][j]) / determinant;

	// DEBUG
	cout << "inverse key: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << inverse[i][j] << " ";
		}
		cout << endl;
	}

	return inverse;
}

//vector<vector<double>> toOutputVectors(vector<vector<int>> transferVectors, vector<vector<double>> inverseKey) {}


int main() {
	vector<vector<int>> key;
	double determinant;

	do {
		key = keyGenerate();
		determinant = determinant3(key);
	} while (determinant == 0);

	string input;
	getline(cin, input);

	transpose(key);

	vector<vector<int>> vectors = toVectors(input);

	vector<vector<int>> transfer = consolidateVectors(vectors, key);

	vector<vector<int>> cofactor = cofactors(key);

	vector<vector<double>> inverseKey = inverse(adjoint(cofactor), determinant);

	// testing, remove if you feel like it

	vector<vector<int>> test1= consolidateVectors(key, inverseKey);

	vector<vector<int>> test2 = consolidateVectors(transfer, inverseKey);

	system("pause");
}