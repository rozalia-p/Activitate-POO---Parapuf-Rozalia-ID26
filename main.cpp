#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
using namespace std;


class Procesor;
class RAM;
class Interfata;

float calculeazaIndicePerformanta(Procesor& p, RAM& r);
bool esteSistemDeGaming(Procesor& p, RAM& r, Interfata& i);


class Procesor {
private:
	string model;
	int nrNuclee;
	float frecventaGHz;
	const int anLansare;
	static int totalProcesoare;
	float* temperaturi;
	int nrTemperaturi;

public:
	Procesor() :anLansare(0) {
		this->model = "Necunoscut";
		this->nrNuclee = 0;
		this->frecventaGHz = 0;
		this->nrTemperaturi = 0;
		this->temperaturi = NULL;
		totalProcesoare++;
	}

	Procesor(string model) :anLansare(0) {
		this->model = model;
		this->nrNuclee = 4;
		this->frecventaGHz = 3.0f;
		this->temperaturi = NULL;
		totalProcesoare++;
	}
	Procesor(string model, int nrNuclee, float frecventaGHz, int anLansare, int nrTemperaturi, float* temperaturi) : anLansare(anLansare) {
		this->model = model;
		this->nrNuclee = nrNuclee;
		this->frecventaGHz = frecventaGHz;
		this->nrTemperaturi = nrTemperaturi;
		if (this->nrTemperaturi > 0 && temperaturi != NULL) {
			this->temperaturi = new float[this->nrTemperaturi];
			for (int i = 0; i < this->nrTemperaturi; i++) {
				this->temperaturi[i] = temperaturi[i];
			}
		}
		else {
			this->temperaturi = NULL;
		}
		totalProcesoare++;
	}

	Procesor(Procesor& p) : anLansare(p.anLansare) {
		this->model = p.model;
		this->nrNuclee = p.nrNuclee;
		this->frecventaGHz = p.frecventaGHz;
		this->nrTemperaturi = p.nrTemperaturi;
		if (this->nrTemperaturi > 0 && p.temperaturi != NULL) {
			this->temperaturi = new float[this->nrTemperaturi];
			for (int i = 0; i < this->nrTemperaturi; i++) {
				this->temperaturi[i] = p.temperaturi[i];
			}
		}
		else {
			this->temperaturi = NULL;
		}totalProcesoare++;
	}

	~Procesor() {
		if (this->temperaturi != NULL) {
			delete[] this->temperaturi;
		}
	}
	//getteri
	string getModel() {
		return this->model;
	}
	int getNrNuclee() {
		return this->nrNuclee;
	}
	float getFrecventaGHz() {
		return this->frecventaGHz;
	}
	int getAnLansare() {
		return this->anLansare;
	}
	int getNrTemperaturi() {
		return this->nrTemperaturi;
	}
	float* getTemperaturi() {
		return this->temperaturi;
	}
	//setteri
	void setModel(string modelNou) {
		this->model = modelNou;
	}
	void setNrNuclee(int nrNucleeNou) {
		this->nrNuclee = nrNucleeNou;
	}
	void setFrecventaGHz(float frecventaGHzNou) {
		this->frecventaGHz = frecventaGHzNou;
	}

};
