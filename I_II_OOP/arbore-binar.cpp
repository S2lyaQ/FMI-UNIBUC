#include <iostream>
#include <string>
using namespace std;

// Definition of the Nod class
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

    Nod(const Nod& alt)
        : cheie(alt.cheie), pozitie(alt.pozitie),
          copilStang(alt.copilStang ? new Nod(*alt.copilStang) : nullptr),
          copilDrept(alt.copilDrept ? new Nod(*alt.copilDrept) : nullptr) {}

    ~Nod() {
        delete copilStang;
        delete copilDrept;
    }

    Nod& operator=(const Nod& alt) {
        if (this == &alt) return *this;

        delete copilStang;
        delete copilDrept;

        copilStang = alt.copilStang ? new Nod(*alt.copilStang) : nullptr;
        copilDrept = alt.copilDrept ? new Nod(*alt.copilDrept) : nullptr;

        cheie = alt.cheie;
        pozitie = alt.pozitie;

        return *this;
    }

    bool operator==(const Nod& alt) const {
        if (cheie != alt.cheie) return false;
        if ((copilStang && !alt.copilStang) || (!copilStang && alt.copilStang)) return false;
        if ((copilDrept && !alt.copilDrept) || (!copilDrept && alt.copilDrept)) return false;
        if (copilStang && alt.copilStang && !(*copilStang == *alt.copilStang)) return false;
        if (copilDrept && alt.copilDrept && !(*copilDrept == *alt.copilDrept)) return false;
        return true;
    }

    bool operator<(const Nod& alt) const {
        return cheie < alt.cheie;
    }

    bool operator>(const Nod& alt) const {
        return cheie > alt.cheie;
    }

    bool operator<=(const Nod& alt) const {
        return !(*this > alt);
    }

    bool operator>=(const Nod& alt) const {
        return !(*this < alt);
    }

    Nod& operator+(const T& cheieNoua) {
        if (cheie != cheieNoua) {
            if (cheie > cheieNoua) {
                if (!copilStang) {
                    copilStang = new Nod<T>(cheieNoua);
                } else {
                    *copilStang + cheieNoua;
                }
            } else {
                if (!copilDrept) {
                    copilDrept = new Nod<T>(cheieNoua);
                } else {
                    *copilDrept + cheieNoua;
                }
            }
        }
        return *this;
    }

    Nod* remove(const T& cheieNoua, Nod* parent = nullptr) {
        if (cheieNoua < cheie) {
            if (copilStang) {
                copilStang = copilStang->remove(cheieNoua, this);
            }
        } else if (cheieNoua > cheie) {
            if (copilDrept) {
                copilDrept = copilDrept->remove(cheieNoua, this);
            }
        } else {
            if (!copilStang && !copilDrept) {
                delete this;
                return nullptr;
            } else if (!copilStang) {
                Nod* temp = copilDrept;
                delete this;
                return temp;
            } else if (!copilDrept) {
                Nod* temp = copilStang;
                delete this;
                return temp;
            } else {
                Nod* temp = copilDrept;
                while (temp->copilStang) {
                    temp = temp->copilStang;
                }
                cheie = temp->cheie;
                copilDrept = copilDrept->remove(temp->cheie, this);
            }
        }
        return this;
    }

    const T& getCheie() const { return cheie; }
    int getPozitie() const { return pozitie; }
    Nod* getCopilStang() const { return copilStang; }
    Nod* getCopilDrept() const { return copilDrept; }
    Nod* getNodByPosition(int pozitieNod) {
        if (pozitie > pozitieNod) {
            if (copilStang) {
                return copilStang->getNodByPosition(pozitieNod);
            }
            return nullptr;
        }

        if (pozitie == pozitieNod) return this;

        if (pozitie < pozitieNod) {
            if (copilDrept) {
                return copilDrept->getNodByPosition(pozitieNod);
            }
            return nullptr;
        }

        return nullptr;
    }

    void setCheie(const T& cheie) { this->cheie = cheie; }
    void setPozitie(int pozitie) { this->pozitie = pozitie; }
    void setCopilStang(Nod* copilStang) { this->copilStang = copilStang; }
    void setCopilDrept(Nod* copilDrept) { this->copilDrept = copilDrept; }
};

// Definition of the ArboreBinar class
template<typename T>
class ArboreBinar {
private:
    Nod<T>* radacina;
    int contor;

    void updateContor(Nod<T>* radacina) {
        contor = 0;
        updateContorInordine(radacina);
    }

    void updateContorInordine(Nod<T>* nod) {
        if (nod) {
            if (nod->getCopilStang()) {
                updateContorInordine(nod->getCopilStang());
            }

            contor++;
            nod->setPozitie(contor);

            if (nod->getCopilDrept()) {
                updateContorInordine(nod->getCopilDrept());
            }
        }
    }

public:
    ArboreBinar() : radacina(nullptr), contor(0) {}

    ArboreBinar(const ArboreBinar& alt) {
        radacina = alt.radacina ? new Nod<T>(*alt.radacina) : nullptr;
        contor = alt.contor;
    }

    ~ArboreBinar() {
        delete radacina;
    }

    ArboreBinar& operator=(ArboreBinar& alt) {
        if (this == &alt) return *this;

        delete radacina;

        radacina = alt.radacina ? new Nod<T>(*alt.radacina) : nullptr;
        contor = alt.contor;

        return *this;
    }

    bool operator==(const ArboreBinar& alt) const {
        if (!radacina && !alt.radacina) return true;
        if ((radacina && !alt.radacina) || (!radacina && alt.radacina)) return false;
        return *radacina == *alt.radacina;
    }

    ArboreBinar& operator+(const T& cheie) {
        if (radacina) {
            *radacina + cheie;
        } else {
            radacina = new Nod<T>(cheie);
        }

        updateContor(radacina);

        return *this;
    }

    ArboreBinar& operator+(const ArboreBinar& alt) {
        if (alt.radacina) {
            for (int i = 1; i <= alt.contor; ++i) {
                Nod<T>* nod = alt.radacina->getNodByPosition(i);
                if (nod) {
                    *radacina + nod->getCheie();
                }
            }
        }

        updateContor(radacina);
        return *this;
    }

    ArboreBinar& operator-(const T& cheie) {
        if (radacina) {
            radacina = radacina->remove(cheie);
            updateContor(radacina);
        }
        return *this;
    }

    ArboreBinar& operator-(const ArboreBinar& alt) {
        if (alt.radacina) {
            for (int i = 1; i <= alt.contor; ++i) {
                Nod<T>* nod = alt.radacina->getNodByPosition(i);
                if (nod) {
                    *this - nod->getCheie();
                }
            }
        }

        updateContor(radacina);
        return *this;
    }

    Nod<T>* getRadacina() const { return radacina; }
    void setRadacina(Nod<T>* radacina) { this->radacina = radacina; }

    void traversareInOrdine(Nod<T>* node) const {
        if (node) {
            if (node->getCopilStang()) traversareInOrdine(node->getCopilStang());
            cout << node->getCheie() << " ";
            if (node->getCopilDrept()) traversareInOrdine(node->getCopilDrept());
        }
    }
};

// Operator overloads for ArboreBinar
template<typename T>
ArboreBinar<T> operator+(const T& cheie, ArboreBinar<T>& arb) {
    return arb + cheie;
}

template<typename T>
ArboreBinar<T> operator-(const T& cheie, ArboreBinar<T>& arb) {
    return arb - cheie;
}

int main() {
    ArboreBinar<int> arbore;
    arbore + 5 + 3 + 7 + 2 + 4 + 6 + 8;

    // Displaying the in-order traversal of the tree
    Nod<int>* root = arbore.getRadacina();
    if (root) {
        cout << "In-order traversal of the tree: ";
        arbore.traversareInOrdine(root);
        cout << endl;
    }

    // Test - elimina elementele
    arbore - 3 - 7;

    root = arbore.getRadacina();
    if (root) {
        cout << "Traversare in ordine dupa eliminare: ";
        arbore.traversareInOrdine(root);
        cout << endl;
    }

    // Test - merge de arbori
    ArboreBinar<int> arbore2;
    arbore2 + 1 + 9 + 10;
    arbore + arbore2;

    root = arbore.getRadacina();
    if (root) {
        cout << "Traversare in ordine dupa merge: ";
        arbore.traversareInOrdine(root);
        cout << endl;
    }

    return 0;
}
