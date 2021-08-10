#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

#define maxWidth 8
#define precision 4

void printEquation(double* equationCoefficients, int variableNumber){
	for(int k = 0; k < variableNumber - 1; k++){
		if(equationCoefficients[k] != 0){
			if(k != 0){
				if(equationCoefficients[k] >= 0 && k != 0 && equationCoefficients[k-1] != 0)  //izliek +, ja atrodas pec mainiga ar koeficientu != 0
						cout << "+ ";
				else 
					if(equationCoefficients[k] < 0 && k != 0) 
						cout << "- ";	
					else	
						cout<< "  ";					
				cout << fixed << setw(maxWidth) << setprecision(precision) << abs(equationCoefficients[k]) << "*x" << k + 1 <<" ";
			}
			else
				cout << fixed << setw(maxWidth) << setprecision(precision) << equationCoefficients[k] << "*x" << k + 1 <<" ";
		}
		else{
			if( k == variableNumber - 1)
				cout << fixed << setw(maxWidth) << setprecision(precision) << equationCoefficients[k] << "*x" << k + 1 <<" ";  // Ja visi koeficienti == 0, parada pedejo mainigu ar 0 koeficientu
			else			
				cout << setw(maxWidth + 4) << "  ";
		}
			
	}		
	cout << fixed << "= " << setprecision(precision) << equationCoefficients[variableNumber - 1];
}	


void printSystem(double** systemMatrix, int variableNumber, int equationNumber){
	cout << "################################################" << endl;
	
	for(int i = 0; i < equationNumber; i++){
		
			cout << "{ ";
			printEquation(systemMatrix[i], variableNumber);
			cout << endl;
			
		}
		
	cout << "################################################" << endl << endl;
}

void getRoots(double** systemMatrix, int equationNumber, int variableNumber, double systemRoot[]){
	for (int equation = equationNumber - 1; equation > 0; equation--){
				
		systemRoot[equation] = systemMatrix[equation][variableNumber - 1];
					
		for(int column = variableNumber - 2; column >= equation; column--){
			systemMatrix[equation - 1][variableNumber - 1] -= systemMatrix[equation - 1][column] * systemRoot[column];
			systemMatrix[equation - 1][column] = 0;
		}	
		printSystem(systemMatrix, variableNumber, equationNumber);
	}
	systemRoot[0] = systemMatrix[0][variableNumber- 1];	
}

void checkRoots(double** systemMatrix, int equationNumber, int variableNumber, double* systemRoot){
	double* leftSideSum = new double[equationNumber];
	for(int row = 0; row < equationNumber; row++){
		for(int column = 0; column < variableNumber - 1; column++){
			leftSideSum[row] += systemMatrix[row][column] * systemRoot[column];
			cout << "+(" << systemMatrix[row][column] << ") * (" << systemRoot[column] << ")";
		}
		cout <<" = " << leftSideSum[row];
	
		if(leftSideSum[row] - systemMatrix[row][variableNumber - 1] < pow(10, (-1)*precision)) 
			cout << " (Atbilst sakotnejam vienadojumam) ";
		else
			cout << " (Neatbilst sakotnejam vienadojumam) ";
			
		cout << endl;	 	
		}
	delete[] leftSideSum;	
}

int main(){
	int variableNumber = 3;
	int equationNumber = 3;
	bool infRoots = false;
	bool roots = true;
	

	//Skailtu ievads sistema
	string answer;
	cout << "Gribat ievadit sistemu pasi?(Ja = Ja, Yes, +)" << endl;
	cin >> answer;
	if(answer == "Ja" || answer == "Yes" || answer == "+"){
		do{
			cout << "Ievadiet mainigo skaitu: " << endl;
			cin >> variableNumber;
		}while(variableNumber <= 0);
		do{
			cout << "Ievadiet vienadojumu skaitu (vienadu vai lielaku par maingo skaitu): " << endl;
			cin >> equationNumber;
		}while(equationNumber < variableNumber);
		
	}	
	
	variableNumber++; //brivais loceklis
	double **originalMatrix = new double*[equationNumber];
	for (int i = 0; i < equationNumber; i++)
		originalMatrix[i] = new double[variableNumber];
		
	double **systemMatrix = new double*[equationNumber]; 
	for (int i = 0; i < equationNumber; i++) 
		systemMatrix[i] = new double[variableNumber];
	
	double* systemRoot = new double[variableNumber - 1];
	
	double** systemRootInf = new double*[variableNumber - 1];
	for(int i = 0; i < variableNumber - 1; i++)
		systemRootInf[i] = new double[2];
		
	if(answer == "Ja" || answer == "Yes" || answer == "+")	{
		for(int row = 0; row < equationNumber; row++)
			for(int column = 0; column < variableNumber; column++){
				if(column != (variableNumber - 1))
					cout << "Ievadiet " << row + 1 << ". vienadojuma " << column + 1 << ". mainiga koeficientu:";
				else
					cout << "Ievadiet " << row + 1 << " vienadojuma brivo locekli: ";
				cin >> systemMatrix[row][column];		
			}
	}
	else{
		systemMatrix[0][0] = 0.1;
		systemMatrix[0][1] = 12;
		systemMatrix[0][2] = -0.13;
		systemMatrix[0][3] = 0.1;
	
		systemMatrix[1][0] = 0.12;
		systemMatrix[1][1] = 0.71;
		systemMatrix[1][2] = -0.15;
		systemMatrix[1][3] = 0.26;
		
		systemMatrix[2][0] = -0.13;
		systemMatrix[2][1] = 0.15;
		systemMatrix[2][2] = 0.63;
		systemMatrix[2][3] = 0.38; 
		
		
		
		
		
	/*	systemMatrix[0][0] = 1;
		systemMatrix[0][1] = 1;
		systemMatrix[0][2] = 1;
		systemMatrix[0][3] = 1;
	
		systemMatrix[1][0] = 2;
		systemMatrix[1][1] = -1;
		systemMatrix[1][2] = 1;
		systemMatrix[1][3] = 2;
		
		systemMatrix[2][0] = -3;
		systemMatrix[2][1] = -3;
		systemMatrix[2][2] = -3;
		systemMatrix[2][3] = -3;  */
	
	}

	
	for(int row = 0; row < equationNumber; row++)
		for(int column = 0; column < variableNumber; column++)
			originalMatrix[row][column] = systemMatrix[row][column];
	
	
	printSystem(systemMatrix, variableNumber, equationNumber);
	
	
	//Parveido sistemas matricu no tainstura formas uz trijstura formu
	for(int i = 0; i < variableNumber - 1; i++){
		if(systemMatrix[i][i] != 0){
			double divider = systemMatrix[i][i];
			for(int column = 0; column < variableNumber; column++){
				systemMatrix[i][column] /= divider;
			}
			for(int k = i + 1; k < equationNumber; k++){
				double multiplier = systemMatrix[k][i] * (-1.0);
				
				//Izvada komentaru par rindu saskaitisanu
				cout <<"[  " << multiplier << "*R" << i + 1 << " + R" << k + 1 << " ]" << endl;	
				printEquation(systemMatrix[i], variableNumber);
				cout << "| *(" << multiplier << ")" << endl;
				cout << "+" << endl;
				printEquation(systemMatrix[k], variableNumber);
				cout << endl << "------------------------------------------------" << endl;
				
				
				for(int column = 0; column < variableNumber; column++){
					double addend = systemMatrix[i][column] * multiplier;
					systemMatrix[k][column] += addend;
				}
				
				printEquation(systemMatrix[k], variableNumber);
				cout << endl << endl;
			}
			printSystem(systemMatrix, variableNumber, equationNumber);
		}
	}
	
	printSystem(systemMatrix, variableNumber, equationNumber);
	
	if(systemMatrix[equationNumber - 1][variableNumber - 2] != 0){ 
		
		getRoots(systemMatrix, equationNumber, variableNumber, systemRoot);
	
			
		cout << "Atbilde: (";
		for(int i = 0; i < variableNumber - 1; i++)
			cout << systemRoot[i] << "; ";
			
		cout << ")" << endl;	
	}
	else{
		
		if(systemMatrix[equationNumber - 1][variableNumber - 1] != 0){// Parbauda brivo locekli
			cout << "Sistema nav saderiga" << endl;
			roots = false;
		}
		else{
			infRoots = true;
			if(systemMatrix[variableNumber - 2][variableNumber - 2] == 1){
				getRoots(systemMatrix, variableNumber - 1, variableNumber, systemRoot);
					
				cout << "Atbilde: (";
				for(int i = 0; i < variableNumber - 1; i++)
					cout << systemRoot[i] << "; ";	
				cout << ")" << endl;	
			}
			if(systemMatrix[equationNumber - 1][variableNumber- 1] == 0 && variableNumber - 1 == equationNumber){
				//Iegut atbildes, izmantojot mainigo C
				systemRootInf[variableNumber - 2][0] = 1;
				systemRootInf[variableNumber - 2][1] = 0;
				for(int equation = variableNumber - 3; equation >= 0; equation--){
					systemRootInf[equation][1] = systemMatrix[equation][variableNumber - 1];
					for(int column = variableNumber - 2; column > equation; column--){
						systemRootInf[equation][0] -= systemMatrix[equation][column] * systemRootInf[column][0];
						systemRootInf[equation][1] -= systemMatrix[equation][column] * systemRootInf[column][1];
						
						systemMatrix[equation][column] = 0;
					}
				}
				
				printSystem(originalMatrix, variableNumber, equationNumber);
				
				cout << "Atbilde: (";
				for(int i = 0; i < variableNumber - 1; i++){
					cout << systemRootInf[i][0] << "*C ";
					if(systemRootInf[i][1] >= 0)
						cout << "+ ";
					else
						cout << "- ";
					cout << abs(systemRootInf[i][1]) << "; ";		 
				}
				cout << "), C pieder realu skaitlu kopai" << endl;	
			}
		}	
	}
	printSystem(originalMatrix, variableNumber, equationNumber);
	//Parbaude
	
	
	double* leftSideSum = new double[equationNumber];
	if(roots == true && infRoots == false)
		checkRoots(originalMatrix, equationNumber, variableNumber, systemRoot);
	if(infRoots == true){
		double* systemRootFreePart = new double[variableNumber - 1];
		for(int i = 0; i < variableNumber - 1; i++)
			systemRootFreePart[i] = systemRootInf[i][1];
		checkRoots(originalMatrix, equationNumber, variableNumber, systemRootFreePart);
		delete[] systemRootFreePart;
	}
	
		
		
				

	for(int i = 0; i < equationNumber; i++) delete[] systemMatrix[i];
	delete[] systemMatrix;
	delete[] systemRoot;
	delete[] systemRootInf;
	delete[] leftSideSum;

	system("pause");
	return 0;
}
