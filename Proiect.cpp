#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
//O variabila care ma ajuta in functia Traseu() din cadrul 
//clasei MosCraciun pentru a pune o conditie
int nr=0;
//Structura pentru scrisoare
typedef struct scrisoare{
    string culoare,oras,nume,prenume;
    int varsta,index,NumarDorinte;
    char wishlist[10][30],dorinte[50];
}SCRISOARE;
//Structura pentru status
typedef struct status{
    string stare;
    float suma;
}STATUS;
//Structura pentru inventar
typedef struct inventar{
    int nr;
    char obiect[20];
    float pret;
}INVENTAR;
//Structura pentru punga de cadouri
typedef struct cadou{
    char listaCadouri[100];
    int NrCadouri;
}CADOU;
//clasa MosCraciun
class MosCraciun{
private:
//atributele clasei declarate private
    SCRISOARE scris[100];
    int NumarScris;
    int DistantaOrase[100][100];
    int DistantaTraseu;
public:
//metodele, constructorii si destructorii folositi in cadrul clasei MosCraciun
    MosCraciun();
    ~MosCraciun(){};
    void setScrisoare(int i,string culoare,string oras,string nume,string prenume,int varsta,char text[]);
    void showScrisoare(int i);
    SCRISOARE getScrisoare(int i);
    int getNumarScris();
    void Traseu(int k);
    void setDistantaOrase(int i,int j,int a);
    int getDistantaOrase(int i,int j);
    int minLinie(int a[100][100],int k);
    int getDistantaTraseu();
};
MosCraciun::MosCraciun(){
//Citirea scrisorilor din Scrisori.txt
//Programul le citeste in variabile corespunzatoare in cadrul metodei
//apoi sunt introduse in structura scris declarata private in cadrul clasei
    ifstream Scrisoarein("Scrisori.txt");
    string culoare,oras,nume,prenume;
    int varsta;
    char text[50];
//Se citeste numarul de scrisori
    Scrisoarein>>this->NumarScris;
    for(int i=1;i<=this->NumarScris;i++)
        {
        Scrisoarein>>culoare;
        Scrisoarein>>oras;
        Scrisoarein>>nume;
        Scrisoarein>>prenume;
        Scrisoarein>>varsta;
        Scrisoarein.getline(text,50,'.');
//setterul pentru citirea unei scrisori 
        setScrisoare(i,culoare,oras,nume,prenume,varsta,text);
        }
//Inchiderea fisierului 
    Scrisoarein.close();
//Distanta tresului este initializata din constructor cu 0 pentru ca
//ii va fi de folos in cadrul functiei Traseu
    this->DistantaTraseu=0;
}
//setter pentru distanta dintre orase care este retinuta intr o matrice
//de tipul unei matrice de adiacenta
void MosCraciun::setDistantaOrase(int i,int j,int a)
{   
    this->DistantaOrase[i][j]=a;
}
//getter pentru distanta dintre orase pentru a afisa in main
//matricea respectiva
int MosCraciun::getDistantaOrase(int i,int j){
    return this->DistantaOrase[i][j];
}
//getter pentru afisarea in main a distantei traseului facut 
//de mos craciun
int MosCraciun::getDistantaTraseu(){
    return this->DistantaTraseu;
}
//O functie pentru calcularea minimului unei coloane care
//ma ajuta sa determin distanta cea mai mica pe care o poate
//face mos craciun dintr-un oras in altul
int MosCraciun::minLinie(int a[100][100],int k){
//am luat un minim de 40000 pentru ca este imposibil ca
//distanta dintre 2 orase sa fie mai mare
    int i,min=40000;
//NumarScris este numarul de scrisori +1 pentru ca in matrice
//este si aeroportul din finlanda(punctul de plecare)
    for(i=1;i<=NumarScris+1;i++)
//Conditia de k!=i este pentru ca pe diagonala principala 
//matricea este 0(pentru claritate) si acesta ar fi minimul
        if(a[i][k]<min&& k!=i)
            min=a[k][i];
    return min;
}
//Metoda care alcatuieste traseul lui mos craciun
void MosCraciun::Traseu(int k)
{
//NumarScris este numarul de scrisori +1 pentru ca in matrice
//este si aeroportul din finlanda(punctul de plecare)    
    for(int i=1;i<=NumarScris+1;i++) 
//Se cauta cea mai mica distanta din punctul k in celelalte 
//puncte nevizitate calculand minimul de pe coloana k a matricei
//care contine distantele dintre orasul k si celelalte orase
//k!=i pentru ca distanta de la un oras la el insusi este 0 si 
//acesta ar fi minimul nr<NumarScris pentru siguranta. Metoda sa se
//execute doar de NumarScris ori  
    if(DistantaOrase[k][i]==minLinie(DistantaOrase,k)&& nr<NumarScris && k!=i && DistantaOrase[k][i]!=40000)
    {
//o data ce a fost gasita o distanta nr creste cu 1
        nr++;
//Distanta este adunata in distanta traseului
        DistantaTraseu+=DistantaOrase[k][i];
//Afisarea oraselor in ordinea corespunzatoare
        cout<<scris[i-1].oras<<"--";
//Dupa ce un oras este vizitat toate valorile acestuia de pe linia
//i vor deveni 40000  
        for(int j=1;j<=NumarScris+1;j++)
            DistantaOrase[k][j]=40000;
//Se executa din nou functia
        Traseu(i); 
    }
}
//Setter pentru scrisoare
void MosCraciun::setScrisoare(int i,string c,string o,string num,string pr,int v,char text[])
{
//citirea scrisorilor
    char delim[]=",.";
    scris[i].NumarDorinte=1;
    int n;
    char *p;
    scris[i].index=i;
    scris[i].culoare=c;
    scris[i].oras=o;
    scris[i].nume=num;
    scris[i].prenume=pr;
    scris[i].varsta=v;
//se retine lista dorintelor unui copil 
    strcpy(scris[i].dorinte,text);
//Se extrag dorintele separat pentru a fi posibila compararea
//cu obiectele din inventar
    p=strtok(text,delim);
    while(p)
        {
            strcpy(scris[i].wishlist[scris[i].NumarDorinte++],strlwr(p));
            p=strtok(NULL,delim);
        }
//Eliminare spatii nedorite din componenta dorintelor
//la afisare imi apareau spatii in plus doar in primul caracter
    for(int l=1;l<scris[i].NumarDorinte;l++)
            {
            n=strlen(scris[i].wishlist[l]);
            if(scris[i].wishlist[l][0]==' ')
                {
                    for(int j=1;j<n;j++)
                        scris[i].wishlist[l][j-1]=scris[i].wishlist[l][j];
                    scris[i].wishlist[l][n-1]='\0';
                }
            }
}
//Metoda pentru afisarea unei scrisori
void MosCraciun::showScrisoare(int i){
    cout<<scris[i].nume<<'\t';
    cout<<scris[i].prenume<<'\t';
    cout<<scris[i].oras<<'\t';
    cout<<scris[i].varsta<<" ani"<<'\t';
    cout<<scris[i].culoare<<'\t';
    cout<<scris[i].dorinte<<endl;
}
//getter pentru o scrisoare
SCRISOARE MosCraciun::getScrisoare(int i){
    return this->scris[i];
}
//getter pentru numarul de scrisori
int MosCraciun::getNumarScris(){
    return this->NumarScris;
}
//clasa cadou abstracta
class Cadouri{
public:
//declararea functiilor abstracte
    virtual void AdaugaCadou()=0;
    virtual void showCadouri()=0;

};
//Clasa Elf care este derivata claselor MosCraciun
//si Cadouri
class Elf:public Cadouri, public MosCraciun{
private:
    STATUS stat[100];
    INVENTAR inv[100];
    int NumarAcadele;
    int NumarObiecte;
    int NumarCadouri;
    CADOU pungaCadouri[100];
    SCRISOARE scris[100];
    int NumarScrisoare;
    int DistantaOrase[100][100];
public:
    Elf();
    ~Elf(){
//Apelare destructor
        };
    STATUS getStatus(int i);
    INVENTAR getInventar(int i);
    CADOU getPungaCadouri(int i);
    int getNumarAcadele();
    int getNumarObiecte();
//are loc overloadingul
    void operator+(int adaugare){
        this->NumarAcadele+=adaugare; 
    };
//overriding din clasa abstracta cadouri
    void AdaugaCadou();
    void showCadouri();
    void Traseu(int DistantaOrase[100][100]);
    int getDistantaOrase(int i,int j);

};
Elf::Elf(){
//se preia numarul de scrisor din clasa MosCraciun
    NumarScrisoare=getNumarScris();
//se preiau scrisorile intr o structura scris
    for(int k=0;k<100;k++)
        scris[k]=getScrisoare(k);
//se citeste statusul fiecarui copil din fisierul Status.txt
    ifstream statusin("Status.txt");
    for(int i=1;i<=NumarScrisoare;i++)
        {
            statusin>>this->stat[i].stare;
//daca statusul este bun i se acorda o suma de 100$
//in alt caz i se acorda 10$
            if(stat[i].stare=="bun")
                stat[i].suma=100;
            else
                stat[i].suma=10;
        }
//Inchiderea fiserului
    statusin.close();
//Se citeste inventarul cu obiecte
    ifstream inventarin("Inventar.txt");
//Se initializeaza numarul de obiecte cu 1    
    this->NumarObiecte=1;
//cat timp exista date in fisier 
    while(!inventarin.eof()){
//se retin in structura inv datele corespunzatoare 
        inventarin>>inv[this->NumarObiecte].nr;
        inventarin>>inv[NumarObiecte].pret;
//am folosit getline pentru ca numele unor obiecte au spatii
        inventarin.getline(inv[NumarObiecte].obiect,20,',');
//Se copiaza numele obiectului cu litere mici pentru a fi mai usor pentru comparare
//mai tarziu in program
        strcpy(inv[NumarObiecte].obiect,strlwr(inv[NumarObiecte].obiect));
        NumarObiecte++;
    }
//se inchide fisierul
    inventarin.close();
//Eliminare spatii nedorite din lista de obiecte din inventar:
    for(int l=1;l<NumarObiecte;l++)
        {
            int n=strlen(inv[l].obiect);
            if(inv[l].obiect[0]==' ')
                {
                    for(int j=1;j<n;j++)
                        inv[l].obiect[j-1]=inv[l].obiect[j];
                    inv[l].obiect[n-1]='\0';
                }   
        }
//Se executa metoda de adaugare cadou
    AdaugaCadou();
//Se executa metoda de preluare a datelor pentru matricea cu distantele oraselor
    Traseu(this->DistantaOrase);
}
void Elf::Traseu(int DistantaOrase[100][100]){
    int i,j;
    ifstream distin("DistantaOrase.txt");
//Se pune 0 pe diagonala principala
    for(j=1;j<=this->NumarScrisoare+1;j++)
        DistantaOrase[j][j]=0;
//se citesc datele corespunzatoare din fisierul DistantaOrase.txt
    while(!distin.eof())    
    {
        distin>>i;
        distin>>j;
        distin>>DistantaOrase[i][j];
    }
    for(i=1;i<=this->NumarScrisoare+1;i++)
        for(j=1;j<=this->NumarScrisoare+1;j++)
            DistantaOrase[j][i]=DistantaOrase[i][j];
//Inchiderea fisierului
    distin.close();
}
//Getter pentru un element din matrice de distanteOrase
int Elf::getDistantaOrase(int i,int j){
    return DistantaOrase[i][j];
}
//Getter pentru un element din vectorul de structuri stat
STATUS Elf::getStatus(int i){
    return stat[i];
}
//Getter pentru un element din vectorul de structuri inv
INVENTAR Elf::getInventar(int i){
    return inv[i];
}
//Getter pentru un element din vectorul de structuri pungaCadouri
CADOU Elf::getPungaCadouri(int i){
    return pungaCadouri[i];
}
//Getter pentru numarul de acadele
int Elf::getNumarAcadele(){
    return this->NumarAcadele;
}
//getter pentru numarul de obiecte
int Elf::getNumarObiecte(){
    return this->NumarObiecte;
}
void Elf::AdaugaCadou(){
    for(int i=1;i<=NumarScrisoare;i++)
        {   
//numarul de caoduri din punga este initial 0
        pungaCadouri[i].NrCadouri=0;
//se elimina caracterele nedorite din lista de cadouri din punga
        pungaCadouri[i].listaCadouri[0]='\0';
//se parcurg dorintele de pe lista de scrisori si se compara cu
//obiectele din inventar in cazul in care se gaseste un obiect
//se adauga in punga de cadouri
        for(int k=1;k<scris[i].NumarDorinte;k++)
            for(int j=1;j<NumarObiecte;j++) 
                if(strcmp(scris[i].wishlist[k],inv[j].obiect)==0)
                {
                    try
                    {
        //Daca mai sunt bani in contul copiluli stabilit mai sus
                        if(stat[i].suma-inv[j].pret>=0)
                            throw 1;
                    }
                    catch(int a)
                    {
            
                        stat[i].suma-=inv[j].pret;
        //daca obiectul se gaseste in inventar si sunt destui bani atunci 
        //acesta se adauga in punga si se scade din suma copilului obiectul;
                        strcat(pungaCadouri[i].listaCadouri,scris[i].wishlist[k]);
                        strcat(pungaCadouri[i].listaCadouri," ");
        //creste numarul de cadouri din punga cu 1
                        pungaCadouri[i].NrCadouri++;
                    }
                }
        //Se verifica daca s-a adaugat breun cadou in punga
        //In cazul in care nu s-a adaugat inseamna ca dorinta copilului nu era in 
        //inventarul mosului si i se va oferi un cadou default
            if(pungaCadouri[i].NrCadouri==0) 
                if(stat[i].suma==10)
                    {
        //Cadoul default pentru un copil rau este jocul nu te supara frate
                        strcpy(pungaCadouri[i].listaCadouri,"Jocul 'Nu te supara frate!'");
                        stat[i].suma=0;
                        pungaCadouri[i].NrCadouri++;
                    }
                else
                    {
        //Cadoul default pentru un copil bun este un laptop
                        strcpy(pungaCadouri[i].listaCadouri,"Laptop");
                        stat[i].suma=0;
                        pungaCadouri[i].NrCadouri++;
                    } 
//Daca au mai ramas bani dupa stabilirea cadourilor copilul 
//va primi acadele de toti banii ramasi
        this->NumarAcadele+=stat[i].suma;
        }
}
void Elf::showCadouri(){
//Metoda pentru afisarea Cadourilor fiecarui copil
    for(int i=1;i<=NumarScrisoare;i++)
        {
            cout<<scris[i].nume<<" "<<scris[i].prenume<<" "<<pungaCadouri[i].listaCadouri;
            if(stat[i].suma>0)
            { 
               +(stat[i].suma);
               cout<<" si "<<stat[i].suma<<" acadele"<<endl; 
            }
               else
            cout<<endl;    
        }
}
//Clasa Trol
class Trol: public Elf{
private:
    CADOU pungaCadouri[100];
    SCRISOARE scris[100];
    STATUS stat[100];
    int NumarScris;
    int NumarCarbuni;
    int NumarCadoufete,NumarCadoubaieti;
public:
    Trol();
    ~Trol(){
//Apelare destructor
    }
    void setNumarAmbalaje();
    void showAmbalajFete();
    void showAmbalajBaieti();
    void setNumarCarbuni();
    int getNumarCarbuni();
};

Trol::Trol(){
//Se preiau datele de la elfi cu ajutorul getterilor
    this->NumarScris=getNumarScris();
    int i;
    for(i=1;i<=NumarScris;i++)
        scris[i]=getScrisoare(i);
    for(i=1;i<=NumarScris;i++)
        pungaCadouri[i]=getPungaCadouri(i);
//Se seteaza numarul de ambalaje
    this->setNumarAmbalaje();
    for(i=1;i<=NumarScris;i++)
        stat[i]=getStatus(i);
//Se seteaza numarul de carbuni
    this->setNumarCarbuni();
}
void Trol::setNumarCarbuni(){
//Pentru fiecare copil rau se adauga cate un carbune
//in numarul total de carbuni
    this->NumarCarbuni=0;
    for(int i=1;i<=this->NumarScris;i++)
        if(stat[i].stare=="rau")
            {
                this->NumarCarbuni++;
                strcat(pungaCadouri[i].listaCadouri,"+ Carbune");
            }
}
//Metoda pentru setarea numarului de ambalaje
void Trol::setNumarAmbalaje(){
    this->NumarCadoubaieti=0;
    this->NumarCadoufete=0;
//Se parcurg scrisorile verificand in punga de cadouri
//cate cadouri a primit fiecare copil adunand 
    for(int i=1;i<=this->NumarScris;i++)
    {   
        for(int j=1;j<=pungaCadouri[i].NrCadouri;j++)
            if(scris[i].culoare=="roz")
                    this->NumarCadoufete++;
                    else
                    this->NumarCadoubaieti++;
    }
}
//Metoda pentru afisarea numarului de ambalaje pt baieti
void Trol::showAmbalajBaieti(){
    cout<<"Numarul de ambalaje folosite pentru baieti este: "<<this->NumarCadoubaieti<<endl;
}
//Metoda pentru afisarea numarului de ambalaje pt fete
void Trol::showAmbalajFete(){
    cout<<"Numarul de ambalaje folosite pentru fete este: "<<this->NumarCadoufete<<endl;
}
//getter pentru numarul de carbuni
int Trol::getNumarCarbuni(){
    return this->NumarCarbuni;
}
//clasa tamplate abstracta pentru buget
template <class T>
class Buget{
public:
    virtual float getBuget()=0;
    virtual float getBugetExtra()=0;
};
//clasa DoamnaCraciun derivata de la clasa Trol si Buget
class DoamnaCraciun:public Trol, public Buget<float> {
private:
    int NumarCarbuni;
    int NumarAcadele;
    int NumarScris;
    STATUS stat[100];
public:
    DoamnaCraciun();
    ~DoamnaCraciun(){
        //Apelare Destructor
        }
//Buget extra
    float getBugetExtra();
//Buget total
    float getBuget();
    void showBugetExtra();
    void showSumaTotala();
};
DoamnaCraciun::DoamnaCraciun(){
//Se preiau numarul de carbuni de la troli si
//numarul de acadele de la elfi 
    this->NumarCarbuni=getNumarCarbuni();
    this->NumarAcadele=getNumarAcadele();
    this->NumarScris=getNumarScris();
    for(int i=1;i<=NumarScris;i++)
        stat[i]=getStatus(i);
}
//getter pentru bugetul extra
float DoamnaCraciun::getBugetExtra(){
    return float(this->NumarAcadele+float(this->NumarCarbuni*1/2));
}
//getter pentru bugetul total
float DoamnaCraciun::getBuget(){
    float suma=0;
    for(int i=1;i<=NumarScris;i++)
        if(stat[i].stare=="rau")
        suma+=10;
        else
        suma+=100;
    return suma+float(NumarCarbuni*1/2);
}
//Metoda pentru afisarea bugetului total
void DoamnaCraciun::showSumaTotala(){
    cout<<"Dupa calculele doamnei Craciun bugetul este de "<<getBuget()<<" $, bugetul extra fiind de "<<getBugetExtra()<<" $"<<endl;
}
int main()
{
    int i;
    Elf elf;
    MosCraciun mos;
    elf.showCadouri();
    Trol trol;
    trol.showAmbalajBaieti();
    trol.showAmbalajFete();
    DoamnaCraciun dmn;
    dmn.showSumaTotala();
//Preluarea datelor de catre mos craciun de la elfi privind
//distanta dintre orase
    for(int i=1;i<=mos.getNumarScris()+1;i++)   
        for(int j=1;j<=mos.getNumarScris()+1;j++)
            mos.setDistantaOrase(i,j,elf.getDistantaOrase(i,j));
    cout<<"aeroportul Rovaniemi din Laponia (Finlanda)  ";
    mos.Traseu(1);
    cout<<endl<<mos.getDistantaTraseu()<<" mile";
    return 0;
}