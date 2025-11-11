#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
using namespace std;


class Procesor {
	static int totalProcesoare;
	const string arhitectura;
	int nuclee;
	string producator;
	double frecventaGHz;
	double* temperatura;
public:

	//constructor implicit
	Procesor() : arhitectura(""){
		this->nuclee = 0;
		this->frecventaGHz = 0;
		this->producator = "Necunoscut";
		this->temperatura = NULL;
	}

	//constructor cu un parametru
	Procesor() :arhitectura(arhitectura) {
		this->nuclee = 0;
		this->frecventaGHz = 0;
		this->temperatura = NULL;
		this->producator = "Necunoscut";
	}


	//constructor cu toti parametrii
	Procesor(int nuclee, string producator, double frecventaGHz, double* temperatura):arhitectura(arhitectura) {
		this->nuclee = nuclee;
		this->frecventaGHz = frecventaGHz;
		this->temperatura = new double[this->totalProcesoare];
		for (int i = 0; i < this->totalProcesoare; i++) {
			this->temperatura[i] = temperatura[i];
		}
		this->producator = producator;
	}

	~Procesor() {
		if (this->temperatura != NULL) {
			delete[] this->temperatura;
		}
	}
	static double scorPerformanta(double frecventaGHz, int nuclee) {
		return frecventaGHz * nuclee * 1000.0;
	}

	friend ostream& operator<<(ostream& out, const Procesor& obj) {
		out << "Arhitectura procesor: " << obj.arhitectura << endl;
		out << "Productor: " << obj.producator << endl;
		out << "Nuclee: " << obj.nuclee << endl;
		out << "Frecventa: " << obj.frecventaGHz << endl;


	}
	
};

int Procesor::totalProcesoare = 0;
