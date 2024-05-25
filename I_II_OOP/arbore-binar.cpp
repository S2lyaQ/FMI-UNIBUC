#include <iostream>
#include <string>

template<typename T>
class ArboreBinar;

// Nod
template<typename T>
class Nod {
public:
    Nod(const T& cheie, int contor = 1, Nod* stang = nullptr, Nod* drept = nullptr)
        : cheie(cheie), contor(contor), copilStang(stang), copilDrept(drept) {}

    // Copy constructor
    Nod(const Nod& alt)
        : cheie(alt.cheie), contor(alt.contor),
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

        cheie = alt.cheie;
        contor = alt.contor;

        // Eliberăm memoria existentă
        delete copilStang;
        delete copilDrept;

        // Copiem noile valori
        copilStang = alt.copilStang ? new Nod(*alt.copilStang) : nullptr;
        copilDrept = alt.copilDrept ? new Nod(*alt.copilDrept) : nullptr;

        return *this;
    }

    // Getteri si setteri
    const T& getCheie() const { return cheie; }
    int getContor() const { return contor; }
    Nod* getCopilStang() const { return copilStang; }
    Nod* getCopilDrept() const { return copilDrept; }

    void setCheie(const T& cheie) { this->cheie = cheie; }
    void setContor(int contor) { this->contor = contor; }
    void setCopilStang(Nod* copilStang) { this->copilStang = copilStang; }
    void setCopilDrept(Nod* copilDrept) { this->copilDrept = copilDrept; }

private:
    T cheie;
    int contor; 
    Nod* copilStang;
    Nod* copilDrept;
};

/*****************************************************************************************************/

// ArboreBinar
template<typename T>
class ArboreBinar {
public:
    ArboreBinar() : radacina(nullptr) {}

    // Constructor de copiere
    ArboreBinar(const ArboreBinar& alt) {
        radacina = alt.radacina ? new Nod<T>(*alt.radacina) : nullptr;
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

        return *this;
    }

    // Getteri si setteri
    Nod<T>* getRadacina() const { return radacina; }
    void setRadacina(Nod<T>* radacina) { this->radacina = radacina; }

private:
    Nod<T>* radacina;
};
