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

    // Getteri si setteri
    const T& getCheie() const { return cheie; }
    int getContor() const { return contor; }
    Nod* getCopilStang() const { return copilStang; }
    Nod* getCopilDrept() const { return copilDrept; }

    void setCheie(const T& key) { this->cheie = cheie; }
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

    // Getteri si setteri
    Nod<T>* getRadacina() const { return radacina; }
    void setRadacina(Nod<T>* radacina) { this->radacina = radacina; }

private:
    Nod<T>* radacina;
};


