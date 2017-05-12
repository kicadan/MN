#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <string> 
#include <fstream>
using namespace std;

//funckja a - odczytuje z pliku rozmiar n, macierz A i wektor B oraz zwraca rozmiar n
int odczytaj_dane_z_pliku(double **&A, double *&B)
{
	string nazwa; //nazwa pliku wej�ciowego
	cout << endl << "Podaj nazwe pliku (wraz z rozszerzeniem): ";
	cin >> nazwa;
	int n; //rozmiar macierzy A i wektor�w B i X
	cout << endl << "Podaj rozmiar macierzy n:  ";
	cin >> n;

	A = new double*[n];		//tworzenie tablicy dynamicznej A
	for (int i = 0; i < n; i++) {		//indeksowanie tablic od 0
		A[i] = new double[n];
	}
	B = new double[n];		//tworzenie tablicy dynamicznej B

	ifstream plik;
	plik.open(nazwa, ios::in);
	for (int i = 0; i < n; i++)		//wczytanie z pliku macierzy A
		for (int j = 0; j < n; j++)
			plik >> A[i][j];
	for (int i = 0; i < n; i++)
		plik >> B[i];		//wczytanie z pliku wektora B
	plik.close();
	return n;
}

//funkcja b - tworzenie macierzy L i  U metod� Gaussa
bool stworz_macierze_L_i_U(double **A, double **&U, double **&L, int n)
{
	U = new double*[n];				//tworzenie tablicy dynamicznej U
	for (int i = 0; i < n; i++) {
		U[i] = new double[n];
	}
	L = new double*[n];				//tworzenie tablicy dynamicznej L
	for (int i = 0; i < n; i++) {
		L[i] = new double[n];
	}

	for (int i = 0; i < n; i++)			//U=A
		for (int j = 0; j < n; j++)
			U[i][j] = A[i][j];

	for (int i = 0; i < n; i++)			//zerowanie L i wype�nianie jedynkami na przek�tnej
		for (int j = 0; j < n; j++) {
			L[i][j] = 0;
			if (i == j)
				L[i][j] = 1;
		}

	for (int k = 0; k < n - 1; k++)		//iteracja
		for (int i = k + 1; i < n; i++)		//wiersz
			for (int j = k + 1; j < n; j++) {	//kolumna
					if (U[k][k] != 0) {				//je�li nie jest zerem
						U[i][j] -= (U[i][k] / U[k][k])*U[k][j];
					}
					else return 0;	//je�li ma nast�pi� dzielenie przez zero- wyrzucany wyj�tek
					L[i][k] = U[i][k] / U[k][k];
			}

	for (int i = 1; i < n; i++)			//zerowanie macierzy U ponizej przekatnej
		for (int j = 0; j < i; j++)
			U[i][j] = 0;
	return true;				//je�li wszystko posz�o dobrze oraz nie zwr�cono wyj�tku dzielenia przez zero, funkcja zwraca true
}

//funkcja c - rozwi�zanie dw�ch uk�ad�w r�wna� z macierzammi tr�jk�tnymi
void rozwiaz_uklady_rownan(double **L, double **U, double *B, double *&X, double *&Y, int n)
{
	Y = new double[n]; //tworzenie tablicy dynamicznej Y
	X = new double[n]; //tworzenie tablicy dynamicznej X

					   //LY=B
	Y[0] = B[0];
	double suma_Y = 0;
	for (int i = 1; i < n; i++) {
		suma_Y = 0;
		for (int k = 0; k <= i - 1; k++)
			suma_Y += (L[i][k] * Y[k]);
		Y[i] = B[i] - suma_Y;
	}

	//UX=Y
	X[n - 1] = Y[n - 1] / U[n - 1][n - 1];
	double suma_X = 0;
	for (int i = (n - 2); i >= 0; i--) {
		suma_X = 0;
		for (int k = i + 1; k < n; k++)
			suma_X += (U[i][k] * X[k]);
		X[i] = (Y[i] - suma_X) / U[i][i];
	}
}

//funkcja d - generuje raport
void generuj_raport(double **A, double *B, double **L, double **U, double *Y, double *X, int n)
{
	string nazwa;
	cout << endl << "Nazwa pliku do zapisania raportu: ";
	cin >> nazwa;
	ofstream plik;
	plik.open(nazwa, ios::out);

	if (n != 0) {					//je�eli procedura zosta�a uruchomiona z argumentem n=0, to znaczy, �e wcze�niej wyst�pi� b��d dzielenia przez 0; je�li nie- wyst�pi normalne wygenerowanie raportu
		plik << "Macierz A: " << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				plik << "\t    " << A[i][j];
			plik << endl;
		}

		plik << "\nWektor B: " << endl;
		for (int i = 0; i < n; i++)
			plik << "\t" << B[i];

		plik << "\n\nMacierz L: " << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				plik << "\t    " << L[i][j];
			plik << endl;
		}

		plik << "\nMacierz U: " << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				plik << "\t    " << U[i][j];
			plik << endl;
		}

		plik.precision(10);		//zmiana precyzji na 10 miejsc znacz�cych
		plik.setf(ios::scientific, ios::floatfield);	//wy�wietlanie liczb jako cecha + mantysa

		plik << "\nWektor Y: " << endl;
		for (int i = 0; i < n; i++)
			plik << "\t" << Y[i] << endl;

		plik << "\nWektor X: " << endl;
		for (int i = 0; i < n; i++)
			plik << "\t" << X[i] << endl;
	}
	else     //je�li procedura wywo�ana z n=0, wcze�niej by�o dzielenie przez 0 to zostanie wygenerowany taki raport
		plik << "Podano nieprawid�owe dane wej�ciowe!" << endl << "Nastapilo dzielenie przez zero.";
	plik.close();
}

int main() {
	double **A = nullptr; //wska�niki na tablice dynamiczne
	double *B = nullptr;
	double **L = nullptr;
	double **U = nullptr;
	double *X = nullptr;
	double *Y = nullptr;

	int n = odczytaj_dane_z_pliku(A, B);
	if (!stworz_macierze_L_i_U(A, U, L, n))
		generuj_raport(A, B, L, U, Y, X, 0);			//je�li funkcja tworz�ca macierze zwr�ci�a false, oznacza to, �e nast�pi�o dzielenie przez 0, w takim wypadku raport wygeneruje odpowiedni� informacj�
	else {												//je�li nie by�o dzielenia przez 0 program kontynuuje swoje normalne dzia�anie
		rozwiaz_uklady_rownan(L, U, B, X, Y, n);
		generuj_raport(A, B, L, U, Y, X, n);
	}

	//usuni�cie tablic dynamicznych z pami�ci
	for (int i = 0; i < n; i++)
	{
		delete[] A[i];
		delete[] L[i];
		delete[] U[i];
	}
	delete[] A;
	delete[] B;
	delete[] L;
	delete[] U;
	delete[] X;
	delete[] Y;
	return 0;
}