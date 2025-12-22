#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
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
    // constructor implicit
    Procesor() : anLansare(0) {
        this->model = "Necunoscut";
        this->nrNuclee = 0;
        this->frecventaGHz = 0;

        this->nrTemperaturi = 0;
        this->temperaturi = NULL;

        totalProcesoare++;
    }

    // constructor cu un parametru
    Procesor(string model) : anLansare(0) {
        this->model = model;
        this->nrNuclee = 4;
        this->frecventaGHz = 3.0f;

        this->nrTemperaturi = 0;     
        this->temperaturi = NULL;

        totalProcesoare++;
    }

    // constructor cu toti parametrii
    Procesor(string model, int nrNuclee, float frecventaGHz, int anLansare, int nrTemperaturi, float* temperaturi)
        : anLansare(anLansare) {
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

    // constructor de copiere
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
        }

        totalProcesoare++;
    }

    // destructor
    ~Procesor() {
        if (this->temperaturi != NULL) {
            delete[] this->temperaturi;
            this->temperaturi = NULL;
        }
    }

    // getteri
    string getModel() { return this->model; }
    int getNrNuclee() { return this->nrNuclee; }
    float getFrecventaGHz() { return this->frecventaGHz; }
    int getAnLansare() { return this->anLansare; }
    int getNrTemperaturi() { return this->nrTemperaturi; }
    float* getTemperaturi() { return this->temperaturi; }

    // setteri
    void setModel(string modelNou) { this->model = modelNou; }
    void setNrNuclee(int nrNucleeNou) { this->nrNuclee = nrNucleeNou; }
    void setFrecventaGHz(float frecventaGHzNou) { this->frecventaGHz = frecventaGHzNou; }

    void setTemperaturi(int nrTemperaturiNou, float* temperaturiNoi) {
        if (this->temperaturi != NULL) {
            delete[] this->temperaturi;
        }
        this->nrTemperaturi = nrTemperaturiNou;

        if (this->nrTemperaturi > 0 && temperaturiNoi != NULL) {
            this->temperaturi = new float[this->nrTemperaturi];
            for (int i = 0; i < this->nrTemperaturi; i++) {
                this->temperaturi[i] = temperaturiNoi[i];
            }
        }
        else {
            this->temperaturi = NULL;
        }
    }

    // static
    static int getTotalProcesoare() { return totalProcesoare; }

    static float calculeazaScorPerformanta(int nrNuclee, float frecventaGHz) {
        return nrNuclee * frecventaGHz * 100.0f;
    }

    friend float ::calculeazaIndicePerformanta(Procesor& p, RAM& r);
    friend bool  ::esteSistemDeGaming(Procesor& p, RAM& r, Interfata& i);
};

int Procesor::totalProcesoare = 0;


// =======================================================================
// CLASA RAM
// =======================================================================
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

    RAM(string tip, int capacitateGB, int frecventaMHz, int latentaCL, int nrTimpiAcces, float* timpi)
        : latentaCL(latentaCL) {
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
        else {
            this->timpiAcces = NULL;
        }

        totalModuleRAM++;
    }

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
        else {
            this->timpiAcces = NULL;
        }

        totalModuleRAM++;
    }

    ~RAM() {
        if (this->timpiAcces != NULL) {
            delete[] this->timpiAcces;
            this->timpiAcces = NULL;
        }
    }

    // getteri
    string getTip() { return this->tip; }
    int getCapacitateGB() { return this->capacitateGB; }
    int getFrecventaMHz() { return this->frecventaMHz; }
    int getLatentaCL() { return this->latentaCL; }
    int getNrTimpiAcces() { return this->nrTimpiAcces; }
    float* getTimpiAcces() { return this->timpiAcces; }

    // setteri
    void setTip(string tipNou) { this->tip = tipNou; }
    void setCapacitateGB(int capacitateGBNou) { this->capacitateGB = capacitateGBNou; }
    void setFrecventaMHz(int frecventaMHzNou) { this->frecventaMHz = frecventaMHzNou; }

    void setTimpiAcces(int nrTimpiNou, float* timpiNou) {
        if (this->timpiAcces != NULL) {
            delete[] this->timpiAcces;
        }

        this->nrTimpiAcces = nrTimpiNou;
        if (this->nrTimpiAcces > 0 && timpiNou != NULL) {
            this->timpiAcces = new float[this->nrTimpiAcces];
            for (int i = 0; i < this->nrTimpiAcces; i++) {
                this->timpiAcces[i] = timpiNou[i];
            }
        }
        else {
            this->timpiAcces = NULL;
        }
    }

    // static
    static int getTotalModuleRAM() { return totalModuleRAM; }

    static int calculeazaLatimeBandaAprox(int frecventaMHz, int latentaCL) {
        if (latentaCL <= 0) return 0;
        return (frecventaMHz * 2) / latentaCL;
    }

    friend float ::calculeazaIndicePerformanta(Procesor& p, RAM& r);
    friend bool  ::esteSistemDeGaming(Procesor& p, RAM& r, Interfata& i);
};

int RAM::totalModuleRAM = 0;


// =======================================================================
// CLASA INTERFATA
// =======================================================================
class Interfata {
private:
    string tipInterfata; // PCIe, USB, SATA ...
    int versiune;
    const string producator;
    static int totalInterfete;
    char* descriere;

public:
    Interfata() : producator("Necunoscut") {
        this->tipInterfata = "PCIe";
        this->versiune = 3;

        const char* text = "Interfata implicita PCIe 3";
        this->descriere = new char[strlen(text) + 1];
        strcpy(this->descriere, text);

        totalInterfete++;
    }

    Interfata(string tipInterfata) : producator("Necunoscut") {
        this->tipInterfata = tipInterfata;
        this->versiune = 1;

        string text = "Interfata generica " + tipInterfata;
        this->descriere = new char[text.length() + 1];
        strcpy(this->descriere, text.c_str());

        totalInterfete++;
    }

    Interfata(string tipInterfata, int versiune, string producator, const char* descriere)
        : producator(producator) {
        this->tipInterfata = tipInterfata;
        this->versiune = versiune;

        if (descriere != NULL) {
            this->descriere = new char[strlen(descriere) + 1];
            strcpy(this->descriere, descriere);
        }
        else {
            const char* text = "Fara descriere";
            this->descriere = new char[strlen(text) + 1];
            strcpy(this->descriere, text);
        }

        totalInterfete++;
    }

    Interfata(const Interfata& i) : producator(i.producator) {
        this->tipInterfata = i.tipInterfata;
        this->versiune = i.versiune;

        if (i.descriere != NULL) {
            this->descriere = new char[strlen(i.descriere) + 1];
            strcpy(this->descriere, i.descriere);
        }
        else {
            this->descriere = NULL;
        }

        totalInterfete++;
    }

    ~Interfata() {
        if (this->descriere != NULL) {
            delete[] this->descriere;
            this->descriere = NULL;
        }
    }

    // getteri
    string getTipInterfata() { return this->tipInterfata; }
    int getVersiune() { return this->versiune; }
    string getProducator() { return this->producator; }
    char* getDescriere() { return this->descriere; }

    // setteri
    void setTipInterfata(string tipInterfataNoua) { this->tipInterfata = tipInterfataNoua; }
    void setVersiune(int versiuneNoua) { this->versiune = versiuneNoua; }

    void setDescriere(const char* descriereNoua) {
        if (this->descriere != NULL) {
            delete[] this->descriere;
        }
        if (descriereNoua != NULL) {
            this->descriere = new char[strlen(descriereNoua) + 1];
            strcpy(this->descriere, descriereNoua);
        }
        else {
            this->descriere = NULL;
        }
    }

    // statice
    static int getTotalInterfete() { return totalInterfete; }

    // functie statica de procesare
    static bool suntCompatibileTip(Interfata& i1, Interfata& i2) {
        return (i1.tipInterfata == i2.tipInterfata) && (i1.versiune == i2.versiune);
    }

    friend bool  ::esteSistemDeGaming(Procesor& p, RAM& r, Interfata& i);
};

int Interfata::totalInterfete = 0;


// =======================================================================
// FUNCTII GLOBALE
// =======================================================================
float calculeazaIndicePerformanta(Procesor& p, RAM& r)
{
    float scorCPU = p.nrNuclee * p.frecventaGHz;
    float scorRAM = r.capacitateGB * (r.frecventaMHz / 1000.0f);
    return scorCPU + scorRAM;
}

bool esteSistemDeGaming(Procesor& p, RAM& r, Interfata& i)
{
    bool cpuBun = (p.nrNuclee >= 6 && p.frecventaGHz >= 3.5f);
    bool ramBun = (r.capacitateGB >= 16 && r.frecventaMHz >= 3000);
    bool interfataBuna = (i.tipInterfata == "PCIe" && i.versiune >= 4);

    return cpuBun && ramBun && interfataBuna;
}


// =======================================================================
// testare main
// =======================================================================
int main()
{
    cout << "=========== PROCESOR ===========" << endl;
    float tempP3[] = { 45.5f, 55.0f, 60.3f };

    Procesor p1;
    Procesor p2("Ryzen 5 5600X");
    Procesor p3("Core i7 12700K", 12, 3.6f, 2021, 3, tempP3);

    cout << "p1: " << p1.getModel() << ", nuclee=" << p1.getNrNuclee()
        << ", frecv=" << p1.getFrecventaGHz()
        << ", an=" << p1.getAnLansare() << endl;

    cout << "p2: " << p2.getModel() << ", nuclee=" << p2.getNrNuclee()
        << ", frecv=" << p2.getFrecventaGHz()
        << ", an=" << p2.getAnLansare() << endl;

    cout << "p3: " << p3.getModel() << ", nuclee=" << p3.getNrNuclee()
        << ", frecv=" << p3.getFrecventaGHz()
        << ", an=" << p3.getAnLansare() << endl;

    cout << "Temperaturi p3: ";
    for (int i = 0; i < p3.getNrTemperaturi(); i++)
    {
        cout << p3.getTemperaturi()[i] << " ; ";
    }
    cout << endl;

    cout << "Total procesoare create: " << Procesor::getTotalProcesoare() << endl;
    cout << "Scor static p3: "
        << Procesor::calculeazaScorPerformanta(p3.getNrNuclee(), p3.getFrecventaGHz())
        << endl << endl;


    cout << "=========== RAM ===========" << endl;
    float timpiR3[] = { 10.5f, 11.0f, 9.8f };

    RAM r1;
    RAM r2("DDR5");
    RAM r3("DDR4", 16, 3200, 16, 3, timpiR3);

    cout << "r1: tip=" << r1.getTip() << ", cap=" << r1.getCapacitateGB()
        << " GB, frecv=" << r1.getFrecventaMHz()
        << " MHz, CL=" << r1.getLatentaCL() << endl;

    cout << "r2: tip=" << r2.getTip() << ", cap=" << r2.getCapacitateGB()
        << " GB, frecv=" << r2.getFrecventaMHz()
        << " MHz, CL=" << r2.getLatentaCL() << endl;

    cout << "r3: tip=" << r3.getTip() << ", cap=" << r3.getCapacitateGB()
        << " GB, frecv=" << r3.getFrecventaMHz()
        << " MHz, CL=" << r3.getLatentaCL() << endl;

    cout << "Timpi acces r3: ";
    for (int i = 0; i < r3.getNrTimpiAcces(); i++)
    {
        cout << r3.getTimpiAcces()[i] << " ; ";
    }
    cout << endl;

    cout << "Total module RAM: " << RAM::getTotalModuleRAM() << endl;
    cout << "Latime banda aproximativa r3: "
        << RAM::calculeazaLatimeBandaAprox(r3.getFrecventaMHz(), r3.getLatentaCL())
        << endl << endl;


    cout << "=========== INTERFATA ===========" << endl;
    Interfata i1;
    Interfata i2("USB");
    Interfata i3("PCIe", 4, "Nvidia", "Slot pentru placa video");

    cout << "i1: tip=" << i1.getTipInterfata()
        << ", versiune=" << i1.getVersiune()
        << ", producator=" << i1.getProducator()
        << ", descriere=" << i1.getDescriere() << endl;

    cout << "i2: tip=" << i2.getTipInterfata()
        << ", versiune=" << i2.getVersiune()
        << ", producator=" << i2.getProducator()
        << ", descriere=" << i2.getDescriere() << endl;

    cout << "i3: tip=" << i3.getTipInterfata()
        << ", versiune=" << i3.getVersiune()
        << ", producator=" << i3.getProducator()
        << ", descriere=" << i3.getDescriere() << endl;

    cout << "Total interfete: " << Interfata::getTotalInterfete() << endl;
    cout << "i1 si i3 compatibile (tip+versiune)? "
        << (Interfata::suntCompatibileTip(i1, i3) ? "DA" : "NU") << endl << endl;


    cout << "=========== FUNCTII PRIETENE ===========" << endl;
    float indice = calculeazaIndicePerformanta(p3, r3);
    cout << "Indice performanta (p3 + r3): " << indice << endl;

    bool gaming = esteSistemDeGaming(p3, r3, i3);
    cout << "Sistem p3+r3+i3 este de gaming? " << (gaming ? "DA" : "NU") << endl;

    return 0;
}
