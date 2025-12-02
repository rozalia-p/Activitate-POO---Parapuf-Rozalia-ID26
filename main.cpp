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

	//constructor implicit procesor
	Procesor() :anLansare(0) {
		this->model = "Necunoscut";
		this->nrNuclee = 0;
		this->frecventaGHz = 0;
		this->nrTemperaturi = 0;
		this->temperaturi = NULL;
		totalProcesoare++;
	}
	//constructor cu un parametru procesor
	Procesor(string model) :anLansare(0) {
		this->model = model;
		this->nrNuclee = 4;
		this->frecventaGHz = 3.0f;
		this->temperaturi = NULL;
		totalProcesoare++;
	}

	//constructor cu toti parametrii procesor
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
	//constructor de copiere procesor
	Procesor(const Procesor& p) : anLansare(p.anLansare) {
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
	//destructor procesor
	~Procesor() {
		if (this->temperaturi != NULL) {
			delete[] this->temperaturi;
		}
	}
	//getteri procesor
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
//atribut static
int Procesor::totalProcesoare = 0;


//clasa RAM
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
	//constructor implicit RAM
	RAM() : latentaCL(0)
	{
		this->tip = "Necunoscut";
		this->capacitateGB = 0;
		this->frecventaMHz = 0;
		this->nrTimpiAcces = 0;
		this->timpiAcces = NULL;
		totalModuleRAM++;
	}
	//constructor cu un parametru RAM
	RAM(string tip) : latentaCL(0) {
		this->tip = tip;
		this->capacitateGB = 8;
		this->frecventaMHz = 2666;
		this->nrTimpiAcces = 0;
		this->timpiAcces = NULL;
		totalModuleRAM++;
	}
	//constructor cu toti parametrii
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

	//constructor de copiere
	RAM(const RAM& r) : latentaCL(r.latentaCL) {
		this->tip = r.tip;
		this->capacitateGB = r.capacitateGB;
		this->frecventaMHz = r.frecventaMHz;
		
		this->nrTimpiAcces = r.nrTimpiAcces;
		if (this->nrTimpiAcces > 0 && r.timpiAcces != NULL) {
			this->timpiAcces = new float[this->nrTimpiAcces];
			for (int i = 0; i < this->nrTimpiAcces; i++) {
				this->timpiAcces[i] = r.timpiAcces[i];
			}
		}
		else
		{
			this->timpiAcces = NULL;
		}
		totalModuleRAM++;
	}
	//destructor
	~RAM() {
		if (this->timpiAcces != NULL) {
			delete[] this->timpiAcces;
		}
	}

	//getteri ram
	string getTip() {
		return this->tip;
	}
	int getCapacitateGB() {
		return this->capacitateGB;
	}
	int getFrecventaMHz() {
		return this->frecventaMHz;
	}
	int getLatentaCL() {
		return this->latentaCL;
	}
	int getNrTimpiAcces() {
		return this->nrTimpiAcces;
	}
	float* getTimpiAcces() {
		return this->timpiAcces;
	}

	//setteri ram
	void setTip(string tipNou) {
		this->tip = tipNou;
	}
	void setCapacitateGB(int capacitateGBNou) {
		this->capacitateGB = capacitateGBNou;
	}
	void setFrecventaMHz(int frecventaMHzNou) {
		this->frecventaMHz = frecventaMHzNou;
	}
	void setTimpiAcces(int nrTimpiNou, float* timpiNou) {
		if (this->timpiAcces != NULL) {
			delete[] this->timpiAcces;
		}
		this->nrTimpiAcces = nrTimpiNou;
		if (this->nrTimpiAcces > 0 && timpiNou != NULL) {
			this->timpiAcces = new float[this->nrTimpiAcces];

		}
	}
	static int calculeazaLatimeBandaAprox(int frecventaMHz, int latentaCL) {
		if (latentaCL <= 0)
			return 0;
		return (frecventaMHz * 2) / latentaCL;
	}
};
int RAM::totalModuleRAM = 0;


//clasa Interfata
class Interfata {
private:
	string tipInterfata; // PCIe, USB, SATA ...
	int versiune;
	const string producator;
	static int totalInterfete;
	char* descriere;
public:
	//constructor fara parametrii
	Interfata() :producator("Necunoscut") {
		this->tipInterfata = "PCIe";
		this->versiune = 3;
		const char* text = "Interfata implicita PCIe 3.0";
		this->descriere = new char[strlen(text) + 1];
		strcpy(this->descriere, text);

		totalInterfete++;
	}

	//constructor cu un parametru
	Interfata(string tipInterfata) : producator("Necunoscut") {
		this->tipInterfata = tipInterfata;
		this->versiune = versiune;
		string text = "Interfata generica" + tipInterfata;
		this->descriere = new char[text.length() + 1];
		strcpy(this->descriere, text.c_str());

		totalInterfete++;
	}

};