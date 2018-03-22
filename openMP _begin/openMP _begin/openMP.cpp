#include <omp.h>
#include<iostream>
#include<random>
#include <chrono>
using namespace std;


void sumuj(int tab[], int n, int* calkowita)
{
	omp_set_num_threads(4);
	int  i, k = 0;
	int sum = 0;

#pragma omp parallel for  default(none) schedule(static) private(i) shared(n,k,tab) \
reduction(+:sum)
	for (i = 0; i < n; ++i)
		sum = sum + tab[i];



	cout << "WYWOLANIE" << sum << endl;

	//static -auto rownowaga

	*calkowita = sum;

}




int main() {

	// std::thread threads[10];

	int n = 10000;
	//cin >> n;
	int tab[10000];

	for (int i = 0; i < n; ++i)
		tab[i] = 1;
	int* calkowita = new int(0);




	//std::cout << endl << "wynik" <<*calkowita;


	using namespace std::chrono;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; ++i)
		sumuj(tab, n, calkowita);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << endl << "Czas wykonywania obliczen: %f.\n\n " << time_span.count() << " seconds.";
	std::cout << std::endl;

}
