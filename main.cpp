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

	static int getTotalProcesoare() {
		return totalProcesoare;
	}

	static float calculeazaScorPerformanta(int nrNuclee, float frecventaGHz) {
		return nrNuclee * frecventaGHz * 100.0f;
	}
	friend float ::calculeazaIndicePerformanta(Procesor& p, RAM& r);
};

int Procesor::totalProcesoare = 0;



class RAM
{
private:
	string tip;
	int capacitateGB;
	int frecventaMHz;
	const int latentaCL;
	static int totalModuleRAM;
	float* timpiAcces;
	int nrTimpiAcces;

public:
	RAM() : latentaCL(0)
	{
		this->tip = "Necunoscut";
		this->capacitateGB = 0;
		this->frecventaMHz = 0;
		this->nrTimpiAcces = 0;
		this->timpiAcces = NULL;
		totalModuleRAM++;
	}

	RAM(string tip) : latentaCL(0) {
		this->tip = tip;
		this->capacitateGB = 8;
		this->frecventaMHz = 2666;
		this->nrTimpiAcces = 0;
		this->timpiAcces = NULL;
		totalModuleRAM++;
	}

	RAM(string tip, int capacitateGB, int frecventaMHz, int latentaCL, int nrTimpiAcces, float* timpi) : latentaCL(latentaCL) {
		this->tip = tip;
		this->capacitateGB = capacitateGB;
		this->frecventaMHz = frecventaMHz;
		this->nrTimpiAcces = nrTimpiAcces;
		if (this->nrTimpiAcces > 0 && timpi != NULL) {
			this->timpiAcces = new float[this->nrTimpiAcces];
			for (int i = 0; i < this->nrTimpiAcces; i++) {
				this->timpiAcces[i] = timpi[i];
			}
		}
		else
		{
			this->timpiAcces = NULL;
		}
		totalModuleRAM++;
	}





};
