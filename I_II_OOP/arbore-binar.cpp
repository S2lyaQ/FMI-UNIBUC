#include <iostream>
#include <string>

using namespace std;

// arbore binar de cautare strict cu contor avand chei de tip neprecizat prevazut cu o ordine totala inseamna:
// 1. intre oricare 2 elemente din arbore nu poate exista relatia de egalitate, ci doar > sau <
// 2. fiecare element are un contor care indica al catelea element a fost citit parcurgand arborele in inordine
// 3. chei de tip neprecizat: folosim un tip generic, typename T, iar relatia dintre elementele din arbore este data de relatia dintre cheile lor
// 4. prevazut cu ordine totala: oricare 2 elemente din arbore pot fi comparate

// Nu avem nevoie de asta pentru nu folosim ArboreBinar in Nod
// template<typename T>
// class ArboreBinar;

// Nod
template<typename T>
class Nod {
private:
    T cheie;
    int pozitie; 
    Nod* copilStang;
    Nod* copilDrept;

public:
    Nod(const T& cheie, int pozitie = 1, Nod* stang = nullptr, Nod* drept = nullptr)
        : cheie(cheie), pozitie(pozitie), copilStang(stang), copilDrept(drept) {}

    // Copy constructor
    Nod(const Nod& alt)
        : cheie(alt.cheie), pozitie(alt.pozitie),
          copilStang(alt.copilStang ? new Nod(*alt.copilStang) : nullptr),
          copilDrept(alt.copilDrept ? new Nod(*alt.copilDrept) : nullptr) {}

    // Destructor
    ~Nod() {
        delete copilStang;
        delete copilDrept;
    }

    // Operatorul de atribuire
    Nod& operator=(const Nod& alt) {
        if (this == &alt) return *this;

        // Eliberăm memoria existentă
        delete copilStang;
        delete copilDrept;

        // Copiem noile valori in inordine
        copilStang = alt.copilStang ? new Nod(*alt.copilStang) : nullptr; 

        cheie = alt.cheie;
        pozitie = alt.pozitie;

        copilDrept = alt.copilDrept ? new Nod(*alt.copilDrept) : nullptr;
        
        return *this;
    }

    // Operatorul egalitate
    bool operator==(const Nod& alt) const {
        if (cheie != alt.cheie) return false;
        if ((copilStang && !alt.copilStang) || (!copilStang && alt.copilStang)) return false;
        if ((copilDrept && !alt.copilDrept) || (!copilDrept && alt.copilDrept)) return false;
        if (copilStang && alt.copilStang && !(*copilStang == *alt.copilStang)) return false;
        if (copilDrept && alt.copilDrept && !(*copilDrept == *alt.copilDrept)) return false;
        return true;
    }

    // Operatorul <
    bool operator<(const Nod& alt) const {
        return cheie < alt.cheie;
    }

    // Operatorul >
    bool operator>(const Nod& alt) const {
        return cheie > alt.cheie;
    }

    // Operatorul <=
    bool operator<=(const Nod& alt) const {
        return !(*this > alt);
    }

    // Operatorul >=
    bool operator>=(const Nod& alt) const {
        return !(*this < alt);
    }

    // Operatorul + (Nod + cheieNoua)
    Nod& operator+(T& cheieNoua) {
        if(cheie != cheieNoua) {
            if(cheie > cheieNoua) {
                if(!copilStang) {
                    copilStang = new Nod<T>(cheieNoua);
                } else {
                    *copilStang + cheieNoua;
                }
            } else {
                if(!copilDrept) {
                    copilDrept = new Nod<T>(cheieNoua);
                } else {
                    *copilDrept + cheieNoua;
                }
            }
        }
        return *this;
    }

    // Getteri si setteri
    const T& getCheie() const { return cheie; }
    int getPozitie() const { return pozitie; }
    Nod* getCopilStang() const { return copilStang; }
    Nod* getCopilDrept() const { return copilDrept; }
    Nod* getNodByPosition(int pozitieNod) { // parcurgerea in inordine
        if(pozitie > pozitieNod) {
            if(copilStang) {
                return copilStang->getNodByPosition(pozitieNod);
            }
            return nullptr;
        }

        if(pozitie == pozitieNod) return this;
        
        if(pozitie < pozitieNod) {
            if(copilDrept) {
                return copilDrept->getNodByPosition(pozitieNod);
            }
            return nullptr;
        }

        return nullptr; // pentru evitarea erorilor la compilare
    }

    void setCheie(const T& cheie) { this->cheie = cheie; }
    void setPozitie(int pozitie) { this->pozitie = pozitie; }
    void setCopilStang(Nod* copilStang) { this->copilStang = copilStang; }
    void setCopilDrept(Nod* copilDrept) { this->copilDrept = copilDrept; }
};

/*****************************************************************************************************/

// ArboreBinar
template<typename T>
class ArboreBinar {
private:
    Nod<T>* radacina;
    int contor;

    // functie pentru actualizarea contorului in inordine (copil stang - radacina - copil drept)
    void updateContor(Nod<T>* radacina) {
        contor = 0;
        updateContorInordine(radacina);
    }

    void updateContorInordine(Nod<T>* nod) {
        if(nod) {
            if(nod->getCopilStang()) {
                updateContorInordine(nod->getCopilStang());
            }

            contor++;
            nod->setPozitie(contor);

            if(nod->getCopilDrept()) {
                updateContorInordine(nod->getCopilDrept());
            }
        }
    }

public:
    ArboreBinar() : radacina(nullptr), contor(0) {}

    // Constructor de copiere
    ArboreBinar(const ArboreBinar& alt) {
        radacina = alt.radacina ? new Nod<T>(*alt.radacina) : nullptr;
        contor = alt.contor;
    }

    // Destructor
    ~ArboreBinar() {
        delete radacina;
    }

    // Operatorul de atribuire
    ArboreBinar& operator=(const ArboreBinar& alt) {
        if (this == &alt) return *this;

        // Eliberăm memoria existentă
        delete radacina;

        // Copiem noua valoare
        radacina = alt.radacina ? new Nod<T>(*alt.radacina) : nullptr;
        contor = alt.contor;

        return *this;
    }

    // Operatorul egalitate
    bool operator==(const ArboreBinar& alt) const {
        if (!radacina && !alt.radacina) return true;
        if ((radacina && !alt.radacina) || (!radacina && alt.radacina)) return false;
        return *radacina == *alt.radacina;
    }

    // Operatorul adunare: cheie + arbore
    ArboreBinar& operator+(T& cheie) {
        if(radacina) {
            *radacina + cheie;
        } else {
            radacina = new Nod<T>(cheie);
        }

        updateContor(radacina);

        return *this;
    }

    // Operatorul adunare: arbore + arbore
    ArboreBinar& operator+(ArboreBinar& alt) {
        if(alt.radacina) {
            for(int i = 1; i <= alt.contor; ++i) {
                Nod<T>* nod = alt.radacina->getNodByPosition(i);
                if(nod) {
                    this->radacina + nod->getCheie();
                }
            }
        }

        updateContor(radacina);
        return *this;
    }
    
    // Getteri si setteri
    Nod<T>* getRadacina() const { return radacina; }
    void setRadacina(Nod<T>* radacina) { this->radacina = radacina; }
};

// Operatorul adunare: cheie + arbore
template<typename T>
ArboreBinar<T> operator+(const T& cheie, ArboreBinar<T>& arb) {
    return arb + cheie;
}

int main() {
    ArboreBinar<int> a, b;
    int cheieA, cheieB;
    for(int i = 0; i < 20; ++i) {
        cheieA = 10 + i;
        cheieB = -10 - i;
        a = a + cheieA;
        b = b + cheieB;
    }

    // Afisare arbore a
    cout << "Arborele a: ";
    for(int i = 1; i <= a.getRadacina()->getPozitie(); ++i) {
        Nod<int>* nod = a.getRadacina()->getNodByPosition(i);
        if(nod) {
            cout << nod->getCheie() << " ";
        }
    }
    cout << endl;

    // Afisare arbore b
    cout << "Arborele b: ";
    for(int i = 1; i <= b.getRadacina()->getPozitie(); ++i) {
        Nod<int>* nod = b.getRadacina()->getNodByPosition(i);
        if(nod) {
            cout << nod->getCheie() << " ";
        }
    }
    cout << endl;

    // Arborele a + b
    a = a + b;
    cout << "Arborele a + b: ";
    for(int i = 1; i <= a.getRadacina()->getPozitie(); ++i) {
        Nod<int>* nod = a.getRadacina()->getNodByPosition(i);
        if(nod) {
            cout << nod->getCheie() << " ";
        }
    }
    cout << endl;

    return 0;
}