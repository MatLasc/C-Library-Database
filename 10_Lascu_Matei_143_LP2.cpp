
#include <iostream>
#include <cstring>
using namespace std;

class Proces{ //clasa baza
 protected:
    int nr_proces;
    char* reclamant;
    char* parat;

    // setteri
    void set_nr_proces(int nr_proces){this -> nr_proces = nr_proces;}

    void set_reclamant(char* reclamant){
        if(this -> reclamant != nullptr)
            delete [] this -> reclamant; //eliberez eu memoria
        this -> reclamant = new char[strlen(reclamant) + 1];
        strcpy(this -> reclamant, reclamant);
     }

    void set_parat(char* parat){
        if(this -> parat != nullptr)
            delete [] this -> parat; //eliberez eu memoria
        this -> parat = new char[strlen(parat) + 1];
        strcpy(this -> parat, parat);
    }

 public:
    // constructori
    Proces(){
        this -> nr_proces = 0;
        this -> reclamant = nullptr;
        this -> parat = nullptr;
    }

    Proces(int nr_proces, char* reclamant, char* parat){
        this -> nr_proces = nr_proces;
        this -> reclamant = new char(strlen(reclamant) + 1);
        strcpy(this -> reclamant, reclamant);
        this -> parat = new char(strlen(parat) + 1);
        strcpy(this -> parat, parat);
    }

    Proces(const Proces &proces){
      this -> nr_proces = proces.nr_proces;
      this -> reclamant = new char[strlen(proces.reclamant) + 1];
      strcpy(this -> reclamant, proces.reclamant);
      this -> parat = new char[strlen(proces.parat) + 1];
      strcpy(this -> parat, proces.parat);
    }

    //getteri
    int get_nr_proces(){return this -> nr_proces;}
    char* get_reclmant(){return this -> reclamant;}
    char* get_parat(){return this -> parat;}

    //supraincarcarea operatorului de atribuire, a citirii si a scrierii
    Proces& operator=(const Proces& proces);
    friend istream &operator>>(istream &is, Proces &proces);
    friend ostream &operator<<(ostream &os, Proces &proces);

    void sort_procese(Proces* procese, int nr_procese);

    //destructor
    ~Proces(){
        if(this -> reclamant != nullptr)
          delete [] this -> reclamant; //eliberez eu memoria
        if(this -> reclamant != nullptr)
          delete [] this -> parat;
    }

};



class Proces_civil : public Proces{ // clasa derivata Proces_civil
  double dauneMorale, dauneMateriale;
  int nr_martori;
  bool stadiu;
  //setteri
  void set_dauneMorale(double dauneMorale){
      this ->dauneMorale = dauneMorale;
  }
  void set_dauneMateriale(double dauneMateriale){
      this -> dauneMateriale = dauneMateriale;
  }

  void set_nr_martori(int nr_martori){
      this -> nr_martori = nr_martori;
  }

  void set_stadiu(bool stadiu){
      this -> stadiu = stadiu;
  }

public:
    //constructori
    Proces_civil() : Proces(){
         this -> stadiu = false;
         this -> nr_martori = 0;
         this -> dauneMorale = 0;
         this -> dauneMateriale = 0;
    }

    Proces_civil(int nr_proces, char* reclamant, char* parat, int nr_martori, double dauneMorale, double dauneMateriale) : Proces(nr_proces, reclamant, parat){
      this -> nr_martori = nr_martori;
      this -> dauneMorale = dauneMorale;
      this -> dauneMateriale = dauneMateriale;
      if(nr_martori > 5)
          this -> stadiu = true;
      else
          this -> stadiu = false;
  }


    Proces_civil(const Proces_civil &proces) : Proces(proces){
      this -> stadiu = proces.stadiu;
      this -> nr_martori = proces.nr_martori;
      this -> dauneMorale = proces.dauneMorale;
      this -> dauneMateriale = proces.dauneMateriale;
  }

    //supraincarcarea operatorului de atribuire, a citirii si a scrierii
    Proces_civil& operator=(const Proces_civil& proces);
    friend istream &operator>>(istream &is, Proces_civil& proces);
    friend ostream &operator>>(ostream &os, Proces_civil& proces);


    //getteri
    double get_dauneMorale(){return this -> dauneMorale;}
    double get_dauneMateriale(){return this -> dauneMateriale;}
    int get_nr_martori(){return this -> nr_martori;}
    bool get_stadiu(){return this -> stadiu;}

    double calcul_taxa_timbru(); // calculul taxei de timbru
    void max_taxa_timbru(Proces_civil pc[], int nr_procese_civile); // aflarea procesului civil cu taxa maxima de timbru

    //destructor
    ~Proces_civil(){

    }
};

class Proces_penal : public Proces{ // clasa derivata pt procese penale
 protected:
  int nr_dovezi;
  bool stadiu;

  //setteri
  void set_dovezi(int nr_dovezi){
      this -> nr_dovezi = nr_dovezi;
  }

  void set_stadiu(bool stadiu){
      this -> stadiu = stadiu;
  }

 public:

 //constructori
    Proces_penal() : Proces() {
        this->stadiu = false;
        this->nr_dovezi = 0;
  }

  Proces_penal(int nr_proces, char* reclamant, char* parat, int nr_dovezi): Proces(nr_proces, reclamant, parat){
      this -> nr_dovezi = nr_dovezi;
      this -> stadiu = (nr_dovezi > 25);
  }

   Proces_penal(const Proces_penal &proces) : Proces(proces){
      this -> stadiu = proces.stadiu;
      this -> nr_dovezi = proces.nr_dovezi;
  }

  //supraincarcarea operatorului de atribuire, a citirii si a scrierii
    Proces_penal& operator=(const Proces_penal& proces);
    friend istream &operator>>(istream &is, Proces_penal& proces);
    friend ostream &operator<<(ostream &os, Proces_penal& proces);

    //getteri
    int get_dovezi(){return this -> nr_dovezi;}
    bool get_stadiu(){return this -> stadiu;}

    virtual double calcul_taxa_timbru();

    //destructor
    ~Proces_penal(){

  }
};


class Proces_infractiuni_economice : public Proces_penal{
  protected:
    float prejudiciu;
    void set_prejudciu(float prejudiciu){
        this -> prejudiciu = prejudiciu;
    }
    public:
    Proces_infractiuni_economice() : Proces_penal(){
        this -> prejudiciu = 0;
    }
    Proces_infractiuni_economice(int nr_proces, char* reclamant, char* parat, int nr_dovezi, float prejudiciu) : Proces_penal(nr_proces, reclamant, parat, nr_dovezi){
        this -> prejudiciu = prejudiciu;
    }
    Proces_infractiuni_economice(const Proces_infractiuni_economice &proces) : Proces_penal(proces){
        this -> prejudiciu = proces.prejudiciu;
    }
    float get_prejudiciu(){return this -> prejudiciu;}

    Proces_infractiuni_economice& operator=(const Proces_infractiuni_economice& proces);
    friend istream &operator>>(istream &is, Proces_infractiuni_economice& proces);
    friend ostream &operator<<(ostream &os, Proces_infractiuni_economice& proces);

    virtual double calcul_taxa_timbru();



    ~Proces_infractiuni_economice(){
    }
};

class Proces_infractiuni_electorale : public Proces_penal{
  protected:
    int estimare_Voturi_Viciate;
    void set_estimare_Voturi_Viciate(int estimare_Voturi_Viciate){
        this -> estimare_Voturi_Viciate = estimare_Voturi_Viciate;
    }
public:
    Proces_infractiuni_electorale() : Proces_penal(){
        this -> estimare_Voturi_Viciate = 0;
    }
    Proces_infractiuni_electorale(int nr_proces, char* reclamant, char* parat, int nr_dovezi, int estimare_Voturi_Viciate) : Proces_penal(nr_proces, reclamant, parat, nr_dovezi){
        this -> estimare_Voturi_Viciate = estimare_Voturi_Viciate;
    }
    Proces_infractiuni_electorale(const Proces_infractiuni_electorale &proces) : Proces_penal(proces){
        this -> estimare_Voturi_Viciate = proces.estimare_Voturi_Viciate;
    }

    virtual double calcul_taxa_timbru();

    int get_estimare_Voturi_viciate(){return this ->estimare_Voturi_Viciate;}

    Proces_infractiuni_electorale& operator=(const Proces_infractiuni_electorale& proces);
    friend istream &operator>>(istream &is, Proces_infractiuni_electorale& proces);
    friend ostream &operator<<(ostream &os, Proces_infractiuni_electorale& proces);

    ~Proces_infractiuni_electorale(){
    }
};

class Proces_coruptie : public Proces_infractiuni_economice, public Proces_infractiuni_electorale{
    float valoareMitaElectorala;
    void set_valoareMitaElectorala(float valoareMitaElectorala){
        this -> valoareMitaElectorala = valoareMitaElectorala;
    }
  public:
    Proces_coruptie() : Proces_infractiuni_economice(), Proces_infractiuni_electorale() {
        this->valoareMitaElectorala = 0;
    }

    Proces_coruptie(int nr_proces, char* reclamant, char* parat, int nr_dovezi, int estimare_Voturi_Viciate, float prejudiciu, float valoareMitaElectorala): Proces_infractiuni_electorale(nr_proces, reclamant, parat,  nr_dovezi,  estimare_Voturi_Viciate), Proces_infractiuni_economice( nr_proces, reclamant, parat, nr_dovezi,  prejudiciu){
        this -> valoareMitaElectorala = valoareMitaElectorala;
    }

    Proces_coruptie(const Proces_coruptie &proces) : Proces_infractiuni_economice(proces), Proces_infractiuni_electorale(proces){
        this -> valoareMitaElectorala = proces.valoareMitaElectorala;
    }

    double calcul_taxa_timbru();

    double get_valoareMitaElectorala(){return valoareMitaElectorala;}

    Proces_coruptie& operator=(const Proces_coruptie& proces);
    friend istream &operator>>(istream &is, Proces_coruptie& proces);
    friend ostream &operator<<(ostream &os, Proces_coruptie& proces);

    ~Proces_coruptie(){

    }
};

Proces& Proces :: operator=(const Proces& proces){
    this -> nr_proces = proces.nr_proces;
    if(this -> reclamant != nullptr)
        delete [] this -> reclamant; //eliberez eu memoria
    this -> reclamant = new char[strlen(proces.reclamant) + 1];
    strcpy(this -> reclamant, proces.reclamant);
    if(this -> parat != nullptr)
        delete [] this -> parat; //eliberez eu memoria
    this -> parat = new char[strlen(proces.parat) + 1];
    strcpy(this -> parat, proces.parat);

    return *this;
}

Proces_civil& Proces_civil :: operator=(const Proces_civil& proces){
      Proces :: operator=(proces);
      this -> nr_martori = proces.nr_martori;
      this -> stadiu = proces.stadiu;
      this -> dauneMorale = proces.dauneMorale;
      this -> dauneMateriale = proces.dauneMateriale;
      return *this;

}

Proces_penal& Proces_penal :: operator=(const Proces_penal& proces){
    Proces :: operator=(proces);
    this -> nr_dovezi = proces.nr_dovezi;
    this -> stadiu = proces.stadiu;
    return *this;
}

Proces_infractiuni_economice& Proces_infractiuni_economice :: operator=(const Proces_infractiuni_economice& proces){
    Proces_penal :: operator=(proces);
    this ->prejudiciu = proces.prejudiciu;
    return *this;
}

Proces_infractiuni_electorale& Proces_infractiuni_electorale :: operator=(const Proces_infractiuni_electorale& proces){
    Proces_penal :: operator=(proces);
    this ->estimare_Voturi_Viciate = proces.estimare_Voturi_Viciate;
    return *this;
}
Proces_coruptie& Proces_coruptie :: operator=(const Proces_coruptie& proces){
    Proces_infractiuni_economice :: operator=(proces);
    this -> estimare_Voturi_Viciate = proces.estimare_Voturi_Viciate;
    this ->valoareMitaElectorala = proces.valoareMitaElectorala;
    return *this;
}

istream &operator>>(istream &is, Proces &proces){
    cout << "\nNumarul procesului: ";
    is >> proces.nr_proces;
    is.get();
    proces.reclamant = new char[30];
    cout <<"\nNumele reclamantului: ";
    is.getline(proces.reclamant, 30);
    cout <<"\nNumele paratului: ";
    proces.parat = new char[30];
    is.getline(proces.parat, 30);
    return is;
}

istream &operator>>(istream &is, Proces_civil &proces){

    Proces pr;
    is >> pr;
    proces = static_cast<const Proces_civil&> (pr); //downcasting pentru citirea atributelor din clasa parinte
    cout <<"\nNumar de matori: ";
    is >> proces.nr_martori;
    cout <<"\nDaune materiale in valoare de:";
    is >> proces.dauneMateriale;
    cout <<"\nDaune morale in valoare de:";
    is >> proces.dauneMorale;
    proces.stadiu = (proces.nr_martori > 5);

    is.get();
    return is;
}

istream &operator>>(istream &is, Proces_penal &proces){

    Proces pr;
    is >> pr;
    proces = static_cast<const Proces_penal&> (pr);

    cout <<"\nNumar de dovezi: ";
    is >> proces.nr_dovezi;
    proces.stadiu = (proces.nr_dovezi > 25);

    is.get();
    return is;
}

istream &operator>>(istream &is, Proces_infractiuni_economice &proces){
    Proces_penal pr;
    is >> pr;
    proces = static_cast<const Proces_infractiuni_economice&> (pr);
    cout <<"\nValoare prejudiciu : ";
    is >> proces.prejudiciu;
    is.get();
    return is;
}

istream &operator>>(istream &is, Proces_infractiuni_electorale &proces){
    Proces_penal pr;
    is >> pr;
    proces = static_cast<const Proces_infractiuni_electorale&>(pr);
    cout <<"\nEstimare voturi viciate: ";
    is >> proces.estimare_Voturi_Viciate;
    is.get();
    return is;
}

istream &operator>>(istream &is, Proces_coruptie &proces){
    Proces_infractiuni_economice pr;
    is >> pr;
    proces = static_cast<const Proces_coruptie&>(pr);
    cout <<"\nEstimare voturi viciate: ";
    is >> proces.estimare_Voturi_Viciate;
    cout <<"\nValoare mita:";
    is >> proces.valoareMitaElectorala;
    is.get();
    return is;
}

ostream &operator<<(ostream &os, Proces &proces){
    os << "\nProcesul ";
    os << proces.get_nr_proces();
    os << "\nReclamant : " << proces.get_reclmant() ;
    os << "\nParat : " << proces.get_parat();
    return os;
}

ostream &operator<<(ostream &os, Proces_civil &proces){
    os << "\nProcesul ";
    os << proces.get_nr_proces();
    os << "\nReclamant : " << proces.get_reclmant();
    os << "\nParat : " << proces.get_parat();
    os << "\nProces : civil";
    os << "\nNumarul de martori: " << proces.get_nr_martori();
    os << "\nStadiu: " << int(proces.get_stadiu());
    os << "\nDaune morale in valoare de: " << proces.get_dauneMorale() << " lei";
    os << "\nDaune materiale in valoare de: " << proces.get_dauneMateriale() <<" lei";
    return os;
}

ostream &operator<<(ostream &os, Proces_penal &proces){
    Proces* prc = &proces;//upcasting pentru afisarea atributelor din clasa parinte
    os << prc;
    os << "\nProces : penal";
    os << "\nNumarul de dovezi: "<< proces.get_dovezi();
    os << "\nStadiu : "<< int(proces.get_stadiu());
    os << "\n";
    return os;
}

ostream &operator<<(ostream &os, Proces_infractiuni_electorale &proces){
    Proces_penal* prc = &proces;
    os << prc;
    os << "\nInfractiune de tip : electoral";
    os << "\nEstimare voturi viciate : " << proces.get_estimare_Voturi_viciate();
    return os;
}

ostream &operator<< (ostream &os, Proces_infractiuni_economice &proces){
    Proces_penal *prc = &proces;
    os << prc;
    os <<"\nInfractiune de tip : economic";
    os <<"\nValoare prejudiciu : "<<proces.get_prejudiciu();
    return os;
}

ostream &operator<<(ostream &os, Proces_coruptie &proces){
    Proces_infractiuni_economice *prc = &proces;
    os << prc;
    os << "\nInfractiune de tip : electoral";
    os << "\nEstimare voturi viciate : " << proces.get_estimare_Voturi_viciate();
    os << "\nCoruptie";
    os << "\nMita electorala in valoare de: " << proces.get_valoareMitaElectorala();
    return os;
}

double Proces_civil :: calcul_taxa_timbru(){
    return 0.1 * this -> get_dauneMateriale() + 0.1 * this -> get_dauneMorale();
}

double Proces_penal :: calcul_taxa_timbru(){
    return 0.15 * this -> get_dovezi();

}

double Proces_infractiuni_economice :: calcul_taxa_timbru() {
    return 0.1 * this -> get_prejudiciu();
}

double Proces_infractiuni_electorale :: calcul_taxa_timbru() {
    return 100.0;
}

double Proces_coruptie ::calcul_taxa_timbru() {
    return 100.0 + 0.01 * get_valoareMitaElectorala() + 0.2 * get_prejudiciu();
}

void Proces_civil :: max_taxa_timbru(Proces_civil* pc, int nr_procese_civile){
    int  i, k;
    double max, tx;
    max = -1;
    for(i = 0; i < nr_procese_civile; i++){
        tx = pc[i].calcul_taxa_timbru();
        if(max < tx) {
            max = tx;
            k = i;
        }
    }
    cout << "Procesul "<< pc[k].get_nr_proces() << " are cea mai mare taxa de timbru";
}

void Proces :: sort_procese(Proces* procese, int nr_procese){
    int i,j;
    Proces aux;
    for(i = 1; i < nr_procese; i++){
        j = i;
        while(j > 0 && procese[j].nr_proces < procese[j - 1].nr_proces){
            aux = procese[j];
            procese[j] = procese[j - 1];
            procese[j - 1] = aux;
            j--;
        }
    }
}

int main() {
    int nr_procese,i, nr_procese_civile = 0;
    Proces* procese;
    Proces_civil* procese_civile;
    Proces_penal* procese_penale;
    Proces pr;
    Proces_civil prc;
    Proces_penal prp;
    char tip_proces[6];
    char cerinta;
    cin >> nr_procese;
    cin.get();
    procese_civile = new Proces_civil[nr_procese];
    for(i = 0; i < nr_procese; i++){

        cout << "\nProces de tip: ";
        cin.getline(tip_proces, 6);
        if(strcmp(tip_proces, "penal") == 0){
             cin >> prp;
        }
        else{
            if(strcmp(tip_proces, "civil") == 0){
                   cin >> procese_civile[nr_procese_civile++] ;
            }

            else{
                cout << "Input incorect\n";
               }
        }

    }

    procese_civile -> max_taxa_timbru(procese_civile, nr_procese); // calculez taxa maxima
    for(i = 0; i < nr_procese_civile; i++) // afisare procese
        cout << procese_civile[i];
    delete [] procese_civile;
    return 0;
}
