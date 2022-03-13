Se citeste lista de scrisori dintr-un fisier in cadrul clasei MosCraciun  intr-un vector
de tip structura cu datele corespunzatoare. Se foloseste incapsularea atributele fiecarei
clase fiind declarate private,setate cu ajutorul setterilor si transmise prin getters cu 
ajutorul mostenirii. Se foloseste polimorfismul in cadrul clasei Elf, supraincarcarea 
operatorului + si suprascrierea unor metode din clasa abstracta Cadouri. Suprascrierea
este folosita si in cadrul clasei DoamnaCraciun fata de niste metode din clasa template,
abstracta Buget. Se folosesc exceptii in cadrul clasei Elf in metoda AdaugaCadou(). 

1.Se declara clasa MosCraciun si se citesc in cadrul constructorului scrisorile din 
fisier, apoi se fac getter si setteri pentru scrisori.
2.Clasa de elf este derivata de la MosCraciun, inventarul se citeste dintr-un
 fisier, la fel si statusul fiecarui copil stabilindu-se un buget dupa status
(100$ daca este bun si 10 daca este rau).Se iau si scrisorile din clasa MosCraciun
cu ajutorul getterilor si seterilor. Trebuie parcurs inventarul verificand 
daca exista obiectul de pe lista de dorinte al copilului si se adauga in punga de 
cadouri in cazul in care exista, iar daca nu exista copiilor li se distribuie un
cadou default. 
-Se fac getteri pentru structura pungaCadouri pentru a o transmite trolilor, 
pentru numaurl de acadele pentru DoamnaCraciun
-Elfii stabilesc lista de orase intr-o matrice de adiacenta(ca la grafuri, asa ma 
gandesc) cu distanta dintre oresele i j in elementele matricei (am cautat fiecare
distanta pe site ul indicat) si o transmit lui MosCraciun in main.
-Am folosit o clasa abstracta Cadouri care ajuta la organizare
3.Trolii iau lista de cadouri si lista de scrisori cu ajutorul seterilor.
Apoi am facut o metoda care ma ajuta sa setez numarul de ambalaje pentru
baieti si pentru fete parcurgand lista de scrisori pentru a verifica genul
persoanei si numarul de cadouri din punga fiecarei persoane. Am facut alta 
metoda pentru a seta numarul de carbuni parcurgand vectorul de status.
4. DoamnaCraciun derivata de la clasa elf si o clasa buget abstracta 
calculeaza bugetul total si extra prin doua metode. Primeste statusul de la elfi,
 se parcurge vectorul si se aduna 100 pentru un copil bun si 10 pentru unul rau.
Bugetul extra se calculeaza astfel: numarul de acadele + 0.5 * numarul de carbuni.
5.Mos Craciun preia matricea de adiacenta cu distantele oraselor de la elfi in main.
matricea are numarul scrisorilor+1 linii si coloane deoarece se incepe din Finlanda.
  void MosCraciun::Traseu(int k)
{ 
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
6.Se afiseaza traseul
