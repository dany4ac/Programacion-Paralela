#include<iostream>

#define max 200

using namespace std;
int matriz[max][max], value[max], pesos[max], cap, sum = 0;
void burbuja(int n) {
	int temp, i, j;
	for (i = 2; i <= n; i++)
		for (j = 1; j <= n - 1; j++) {

			if (pesos[j] < pesos[j + 1]) {
				temp = pesos[j];
				pesos[j] = pesos[j + 1];
				pesos[j + 1] = temp;
			}
		}
}
void prueba(int j, int c) {
	if (j > 0) {
		if (c < pesos[j])
			prueba(j - 1, c);
		else {
			if ((matriz[j - 1][c - pesos[j]] + value[j]) > matriz[j - 1][c]) {
				prueba(j - 1, c - pesos[j]);
				cout << "se tiene " << pesos[j] << endl;
				sum = value[j] + sum;
			} else
				prueba(j - 1, c);
		}
	}
}

void objetos(int n) {
	prueba(n, cap);
}

void mochila(int n) {
	int maxint = 998;
	int c, i, j;
	for (c = 0; c <= cap; c++)
		matriz[0][c] = 0;
	for (j = 1; j <= n; j++)
		matriz[j][0] = 0;
	for (j = 1; j <= n; j++)
		for (c = 1; c <= cap; c++) {
			if (c < pesos[j])
				matriz[j][c] = matriz[j - 1][c];
			else {
				if (matriz[j - 1][c]
						>= (matriz[j - 1][c - pesos[j]] + value[j]))
					matriz[j][c] = matriz[j - 1][c];
				else
					matriz[j][c] = matriz[j - 1][c - pesos[j]] + value[j];

			}
		}
}

int main() {
	int i = 1, j;
	char continuar;

	cout << "\t\t\tWELCOME" << endl;
	cout << "ingrese peso  mochila: " << endl;
	cin >> cap;
	cout << "ingrese peso de objetos : " << endl;
	while (1) {
		cin >> pesos[i];
		i++;
		cout << "desea continuar s/n";
		cin >> continuar;
		if (continuar == 'n')
			break;
	}

	int mon;
	mon = i - 1;
	burbuja(mon);
	for (j = 1; j <= mon; j++) {
		cout << "valores de peso " << pesos[j] << ": ";
		cin >> value[j];
		cout << endl;
	}

	mochila(mon);
	objetos(mon);
	/* ver matriz
	 for(int t=0;t<mon;t++){
	 for(int h=0;h<cap;h++){
	 cout<<matriz[t][h];}cout<<endl;}*/
	cout << endl << sum;

	return 0;

}
