#include <iostream> 
#include <fstream> 

bool isdelimiter(int ch) {

	return ch == ' '|| ch == '\n';

}


int main(int argc, char* argv[])
{
	const char* inputFileName = argv[1];
	const char* outputFileName = argv[2];
	

	std::ifstream inFile2(inputFileName);
	if (!inFile2) {
		std::cerr << "Can not open file" << inputFileName << "\n";
		std::system("pause");
		return 1;
	}

	int state = 2;
	int ch = 0;
	int k[100] = {};
	int x = 0;
	int y = 0;
	while ((ch = inFile2.get()) != EOF) {
		switch (state) {
		case 1:
			if (isdelimiter(ch)) {
				if (ch == '\n') {
					if (k[y] <= x) {
						k[y] = x;
					}
					x = 0;
					y = 0;
				}
				else {
					if (k[y] <= x) {
						k[y] = x;
					}
					x = 0;
					y += 1;
				}
				state = 2;
			}
			else {
				x += 1;
				break;
			}

		case 2:
			if (!isdelimiter(ch)) {
				x += 1;
				state = 1;
			}
			break;
		}
	}
	if (x != 0) {
		if (x > k[y]) {
			k[y] = x;
		}
	}

	
	inFile2.close();
	std::ifstream inFile(inputFileName);
	if (!inFile) {
		std::cerr << "Can not open fileeeee" << inputFileName << "\n";
		std::system("pause");
		return 1;
	}

	std::ofstream outFile(outputFileName);

	if (!outFile) {
		std::cerr << "Can not open file" << outputFileName << "\n";
		inFile.close();
		std::system("pause");
		return 2;
	}

	state = 2;
	ch = 0;
	int c = 0;
	int z = 0;

	while ((ch = inFile.get()) != EOF) {
		switch (state) {
		case 1:
			if (isdelimiter(ch)) {
				if (ch == '\n') {
					for (int i = 0; i < k[z]-c; ++i) {
						outFile << ' ';
					}
					if (k[z + 1] != 0) {
						while (true) {
							z += 1;
							for (int i = 0; i <= k[z]; ++i) {
								outFile << ' ';
							}
							if (k[z + 1] == 0) {
								break;
							}
						}
					}
					outFile << "\n";
					c = 0;
					z = 0;
				}
				else {
					for (int i = 0; i < k[z]+1 - c; ++i) {
						outFile << " ";
					}
					c = 0;
					z +=1;
				}
				state = 2;
			}
			else {
				outFile.put(ch);
				c += 1;
				break;
			}

		case 2:
			if (!isdelimiter(ch)) {
				outFile.put(ch);
				c += 1;
				state = 1;
			}
			break;
		}
	}
	for (int i = 0; i < k[z] - c; ++i) {
		outFile << ' ';
	}
	if (k[z + 1] != 0) {
		while (true) {
			z += 1;
			for (int i = 0; i <= k[z]; ++i) {
				outFile << ' ';
			}
			if (k[z + 1] == 0) {
				break;
			}
		}
	}

	return 0;
}