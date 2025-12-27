#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<sstream>
using namespace std;

class Procesor;
class RAM;
class Interfata;

float calculeazaIndicePerformanta(Procesor& p, RAM& r);
bool esteSistemDeGaming(Procesor& p, RAM& r, Interfata& i);


// clasa Procesor
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
    Procesor() : anLansare(0) {
        this->model = "Necunoscut";
        this->nrNuclee = 0;
        this->frecventaGHz = 0;

        this->nrTemperaturi = 0;
        this->temperaturi = NULL;

        totalProcesoare++;
    }

    Procesor(string model) : anLansare(0) {
        this->model = model;
        this->nrNuclee = 4;
        this->frecventaGHz = 3.0f;

        this->nrTemperaturi = 0;
        this->temperaturi = NULL;

        totalProcesoare++;
    }

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

    static int getTotalProcesoare() { return totalProcesoare; }

    static float calculeazaScorPerformanta(int nrNuclee, float frecventaGHz) {
        return nrNuclee * frecventaGHz * 100.0f;
    }

    // 1) operator= 
    Procesor& operator=(const Procesor& p) {
        if (this != &p) {
            if (this->temperaturi != NULL) {
                delete[] this->temperaturi;
                this->temperaturi = NULL;
            }

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
        }
        return *this;
    }

    // 2) operator+ (combina doua procesoare)
    Procesor operator+(const Procesor& p) const {
        int anNou = 0;
        if (this->anLansare > 0 && p.anLansare > 0) anNou = (this->anLansare < p.anLansare ? this->anLansare : p.anLansare);
        else if (this->anLansare > 0) anNou = this->anLansare;
        else anNou = p.anLansare;

        int nrTempNou = this->nrTemperaturi + p.nrTemperaturi;
        float* tempNou = NULL;

        if (nrTempNou > 0) {
            tempNou = new float[nrTempNou];
            int k = 0;
            for (int i = 0; i < this->nrTemperaturi; i++) tempNou[k++] = this->temperaturi[i];
            for (int i = 0; i < p.nrTemperaturi; i++) tempNou[k++] = p.temperaturi[i];
        }

        Procesor rez(this->model + "+" + p.model,
            this->nrNuclee + p.nrNuclee,
            (this->frecventaGHz + p.frecventaGHz) / 2.0f,
            anNou,
            nrTempNou,
            tempNou);

        if (tempNou != NULL) delete[] tempNou;
        return rez;
    }

    // 3) operator< (comparare dupa scor performanta)
    bool operator<(const Procesor& p) const {
        float s1 = calculeazaScorPerformanta(this->nrNuclee, this->frecventaGHz);
        float s2 = calculeazaScorPerformanta(p.nrNuclee, p.frecventaGHz);
        return s1 < s2;
    }

    // 4) operator<< (afisare)
    friend ostream& operator<<(ostream& out, const Procesor& p) {
        out << "Procesor{model=" << p.model
            << ", nuclee=" << p.nrNuclee
            << ", frecventaGHz=" << p.frecventaGHz
            << ", anLansare=" << p.anLansare
            << ", nrTemperaturi=" << p.nrTemperaturi
            << "}";
        return out;
    }

    // 5) operator>> (citire)
    friend istream& operator>>(istream& in, Procesor& p) {
        cout << "Model: ";
        getline(in >> ws, p.model);
        cout << "Nr nuclee: ";
        in >> p.nrNuclee;
        cout << "Frecventa GHz: ";
        in >> p.frecventaGHz;

        cout << "Nr temperaturi: ";
        in >> p.nrTemperaturi;

        if (p.temperaturi != NULL) {
            delete[] p.temperaturi;
            p.temperaturi = NULL;
        }

        if (p.nrTemperaturi > 0) {
            p.temperaturi = new float[p.nrTemperaturi];
            for (int i = 0; i < p.nrTemperaturi; i++) {
                cout << "Temperatura[" << i << "]: ";
                in >> p.temperaturi[i];
            }
        }
        return in;
    }

    friend float ::calculeazaIndicePerformanta(Procesor& p, RAM& r);
    friend bool  ::esteSistemDeGaming(Procesor& p, RAM& r, Interfata& i);
};

int Procesor::totalProcesoare = 0;



// clasa ram
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

    static int getTotalModuleRAM() { return totalModuleRAM; }

    static int calculeazaLatimeBandaAprox(int frecventaMHz, int latentaCL) {
        if (latentaCL <= 0) return 0;
        return (frecventaMHz * 2) / latentaCL;
    }

 

    // 1) operator=
    RAM& operator=(const RAM& r) {
        if (this != &r) {
            if (this->timpiAcces != NULL) {
                delete[] this->timpiAcces;
                this->timpiAcces = NULL;
            }

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
        }
        return *this;
    }

    // 2) operator+ (aduna capacitatea + concateneaza timpii)
    RAM operator+(const RAM& r) const {
        int nrNou = this->nrTimpiAcces + r.nrTimpiAcces;
        float* tNou = NULL;

        if (nrNou > 0) {
            tNou = new float[nrNou];
            int k = 0;
            for (int i = 0; i < this->nrTimpiAcces; i++) tNou[k++] = this->timpiAcces[i];
            for (int i = 0; i < r.nrTimpiAcces; i++) tNou[k++] = r.timpiAcces[i];
        }

        // latentaCL la obiectul rezultat va fi latentaCL din stanga
        RAM rez(this->tip + "+" + r.tip,
            this->capacitateGB + r.capacitateGB,
            (this->frecventaMHz > r.frecventaMHz ? this->frecventaMHz : r.frecventaMHz),
            this->latentaCL,
            nrNou,
            tNou);

        if (tNou != NULL) delete[] tNou;
        return rez;
    }

    // 3) operator[] 
    float& operator[](int index) {
        return this->timpiAcces[index];
    }

    // 4) operator<<
    friend ostream& operator<<(ostream& out, const RAM& r) {
        out << "RAM{tip=" << r.tip
            << ", capGB=" << r.capacitateGB
            << ", frecventaMHz=" << r.frecventaMHz
            << ", latentaCL=" << r.latentaCL
            << ", nrTimpi=" << r.nrTimpiAcces
            << "}";
        return out;
    }

    // 5) operator>>
    friend istream& operator>>(istream& in, RAM& r) {
        cout << "Tip RAM: ";
        getline(in >> ws, r.tip);
        cout << "Capacitate GB: ";
        in >> r.capacitateGB;
        cout << "Frecventa MHz: ";
        in >> r.frecventaMHz;

        cout << "Nr timpi acces: ";
        in >> r.nrTimpiAcces;

        if (r.timpiAcces != NULL) {
            delete[] r.timpiAcces;
            r.timpiAcces = NULL;
        }

        if (r.nrTimpiAcces > 0) {
            r.timpiAcces = new float[r.nrTimpiAcces];
            for (int i = 0; i < r.nrTimpiAcces; i++) {
                cout << "Timp[" << i << "]: ";
                in >> r.timpiAcces[i];
            }
        }

        return in;
    }

    friend float ::calculeazaIndicePerformanta(Procesor& p, RAM& r);
    friend bool  ::esteSistemDeGaming(Procesor& p, RAM& r, Interfata& i);
};

int RAM::totalModuleRAM = 0;



// clasa interfata
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

    static int getTotalInterfete() { return totalInterfete; }

    // 1) operator= 
    Interfata& operator=(const Interfata& i) {
        if (this != &i) {
            if (this->descriere != NULL) {
                delete[] this->descriere;
                this->descriere = NULL;
            }

            this->tipInterfata = i.tipInterfata;
            this->versiune = i.versiune;

            if (i.descriere != NULL) {
                this->descriere = new char[strlen(i.descriere) + 1];
                strcpy(this->descriere, i.descriere);
            }
            else {
                this->descriere = NULL;
            }
        }
        return *this;
    }

    // 2) operator==
    bool operator==(const Interfata& i) const {
        return (this->tipInterfata == i.tipInterfata) && (this->versiune == i.versiune);
    }

    // 3) operator+ (concat descrieri, pastreaza tip+versiune din stanga)
    Interfata operator+(const Interfata& i) const {
        string descr1 = (this->descriere ? this->descriere : "");
        string descr2 = (i.descriere ? i.descriere : "");
        string descrNou = descr1 + " | " + descr2;

        Interfata rez(this->tipInterfata, this->versiune, this->producator, descrNou.c_str());
        return rez;
    }

    // 4) operator<<
    friend ostream& operator<<(ostream& out, const Interfata& i) {
        out << "Interfata{tip=" << i.tipInterfata
            << ", versiune=" << i.versiune
            << ", producator=" << i.producator
            << ", descriere=" << (i.descriere ? i.descriere : "NULL")
            << "}";
        return out;
    }

    // 5) operator>> (producator e const => nu se poate schimba)
    friend istream& operator>>(istream& in, Interfata& i) {
        cout << "Tip interfata: ";
        getline(in >> ws, i.tipInterfata);
        cout << "Versiune: ";
        in >> i.versiune;

        // citim descriere ca linie
        cout << "Descriere: ";
        string d;
        getline(in >> ws, d);

        if (i.descriere != NULL) {
            delete[] i.descriere;
            i.descriere = NULL;
        }
        i.descriere = new char[d.length() + 1];
        strcpy(i.descriere, d.c_str());

        return in;
    }

    friend bool  ::esteSistemDeGaming(Procesor& p, RAM& r, Interfata& i);
};

int Interfata::totalInterfete = 0;



// functii globale
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



// testare main
int main()
{
    cout << "=========== CREARE OBIECTE (Faza 1+2) ===========" << endl;

    float tempP3[] = { 45.5f, 55.0f, 60.3f };
    Procesor p1;
    Procesor p2("Ryzen 5 5600X");
    Procesor p3("Core i7 12700K", 12, 3.6f, 2021, 3, tempP3);

    float timpiR3[] = { 10.5f, 11.0f, 9.8f };
    RAM r1;
    RAM r2("DDR5");
    RAM r3("DDR4", 16, 3200, 16, 3, timpiR3);

    Interfata i1;
    Interfata i2("USB");
    Interfata i3("PCIe", 4, "Nvidia", "Slot pentru placa video");

    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;

    cout << r1 << endl;
    cout << r2 << endl;
    cout << r3 << endl;

    cout << i1 << endl;
    cout << i2 << endl;
    cout << i3 << endl;

    cout << "\n=========== Functii prietene===========" << endl;
    float indice = calculeazaIndicePerformanta(p3, r3);
    cout << "Indice performanta (p3 + r3): " << indice << endl;

    bool gaming = esteSistemDeGaming(p3, r3, i3);
    cout << "Sistem p3+r3+i3 este de gaming? " << (gaming ? "DA" : "NU") << endl;


    cout << "\n=========== Implementare operatori ===========" << endl;

    // operatori procesor
    cout << "\n--- Procesor operatori ---" << endl;

    Procesor pAssign;
    pAssign = p2;                 // operator=
    cout << "pAssign (=p2): " << pAssign << endl;  // operator<<

    Procesor pSum = p2 + p3;      // operator+
    cout << "pSum (p2+p3): " << pSum << endl;

    cout << "p2 < p3 ? " << (p2 < p3 ? "DA" : "NU") << endl; // operator<

    {
        stringstream ss;
        ss << "TestCPU\n8\n4.2\n2\n50.5\n52.1\n";
        ss >> p1;                 // operator>>
        cout << "p1 citit cu >>: " << p1 << endl;
    }

    // operatori RAM
    cout << "\n--- RAM operatori ---" << endl;

    RAM rAssign;
    rAssign = r3;                 // operator=
    cout << "rAssign (=r3): " << rAssign << endl; // operator<<

    RAM rSum = r2 + r3;           // operator+
    cout << "rSum (r2+r3): " << rSum << endl;

    if (r3.getNrTimpiAcces() > 0) {
        cout << "r3[0] inainte: " << r3[0] << endl; // operator[]
        r3[0] = r3[0] + 1.0f;                        // operator[] pe LHS
        cout << "r3[0] dupa: " << r3[0] << endl;
    }

    {
        stringstream ss;
        ss << "DDR4\n32\n3600\n2\n10.1\n10.2\n";
        ss >> r1;                 // operator>>
        cout << "r1 citit cu >>: " << r1 << endl;
    }

   
    // interfata operatori
    cout << "\n--- Interfata operatori ---" << endl;

    Interfata iAssign;
    iAssign = i3;                 // operator=
    cout << "iAssign (=i3): " << iAssign << endl; // operator<<

    cout << "i1 == i3 ? " << (i1 == i3 ? "DA" : "NU") << endl; // operator==

    Interfata iPlus = i1 + i3;    // operator+
    cout << "iPlus (i1+i3): " << iPlus << endl;

    {
        stringstream ss;
        ss << "PCIe\n5\nDescriere noua citita\n";
        ss >> i2;                 // operator>>
        cout << "i2 citit cu >>: " << i2 << endl;
    }

    cout << "\nGata: ai apelat functia prietena + toti operatorii (12+)." << endl;
    return 0;
}
