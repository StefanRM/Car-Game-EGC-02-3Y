.___________. _______ .___  ___.      ___          ___   
|           ||   ____||   \/   |     /   \        |__ \  
`---|  |----`|  |__   |  \  /  |    /  ^  \          ) | 
    |  |     |   __|  |  |\/|  |   /  /_\  \        / /  
    |  |     |  |____ |  |  |  |  /  _____  \      / /_  
    |__|     |_______||__|  |__| /__/     \__\    |____| 

Nume:    Maftei Stefan - Radu
Grupa:   336CC
Materie: EGC

	Pentru implementarea temei am folosit functiile si fisierele din
laboratoarele 5 (crearea camerei) si 6 (crearea unui shader).
	Terenul de joc se afla pe o suprafata verde extinsa. Soseaua este
creata din cateva dreptunghiuri, iar bordurile sunt generate din cuburi, puse
unul langa altul. Terenul de joc este generat in cadrul programului principal.
	Cerul este creat dupa modelul skybox. Un cub inconjoara intreg terenul,
iar in functie de timpul de cand s-a pornit jocul va trece prin ciclul
zi-noapte, astfel incat peisajul va fi de dimineata, amiaza, seara si noapte.
Ca si cerul, pamantul si soseaua se coloreaza diferit in functie de timp.
Aceasta tranzitie este realizata in VertexShader, unde se primesc valorile
culorilor initiale si finale si timpul pentru a face tranzitia intre cele 2.
Pentru a avea timp egal intre cele 4 stari am ales sa folosesc functiile
trigonometrice pentru timp, astfel reducand problema la cercul trigonometric.
Cadranele 1, 2, 3 si 4 reprezinta fiecare moment al zilei mentionat inainte,
in ordinea specificata. In VertexShader se porneste de la culoarea initiala
si se aduna gradual folosind timpul transmis pana la culoarea finala, rezultand
o tranzitie uniforma si placuta.
	Jucatorul este reprezentat de o masina, fiind creata dupa un model
descarcat de pe site-ul https://free3d.com/ . Masinii i-au fost adaugate 4 roti
descarcate de pe acelasi site. In timp ce masina porneste sau accelereaza,
rotile se invartesc, iar cand aceasta merge cu spatele rotile se invartesc in
sens invers. Cand se doreste rotirea masinii prin luarea curbelor, rotile se
invart ca atare pentru a da directia masinii. Pentru a reda aspecte din
realitate, am introdus si o inertie a masinii daca dupa accelerare nu se mai
apasa nicio tasta, masina mergand inca o portiune de sosea.
	Obstacolele sunt reprezentate de cuburi de culoare neagra: 3 dintre ele
sunt dinamice (se translateaza), iar 3 sunt statice. Acestea sunt plasate in
diferite puncte pe harta traseului cu scopul maririi dificultatii. Linia de
finish este tratata ca un obstacol mai special: odata atinsa, jocul s-a
incheiat; aceasta este de culoare albastra.
	Jocul permite 2 camere: camera 'First Person' si camera 'Third Person'.
Ambele sunt actualizate in functie de actualizarile masinii. Comutarea intre
cele 2 camere se realizeaza prin apasarea unei taste. Camera 'First Person' se
afla pe botul masinii, astfel incat este mai aproape de sosea si nu se vede
masina; camera 'Third Person' se afla in spatele masinii, tinandu-se strans de
spatele masinii la fiecare miscare a ei.
	Pentru detectarea coliziunilor am utilizat tipul de coliziune
dreptunghi-dreptunghi. Functia verifica daca varfurile unui dreptunghi se afla
in interiorul celuilalt dreptunghi. In caz de coliziune masina se opreste,
lasand posibilitatea jucatorului de a da inapoi cu masina si sa se repozitioneze.
Lovindu-se de unul din obstacole, acestea din urma dispar, iar masina isi poate
continua drumul. Lovindu-se de borduri, masina se opreste si nu mai poate
inainta: jucatorul trebuie sa repozitioneze masina, dar atent pentru ca poate
ajunge sa atinga din nou bordurile cu alt colt al masinii.
	Ca in orice joc, exista si un sistem de scor: jucatorul are 3 vieti, adica
la a 3-a coliziune jocul s-a incheiat. Pentru fiecare coliziune este depunctat.
Scorul este calculat in functie de timp, iar aceasta regula se aplica doar daca
jucatorul a ajuns la linia de finish. Scorul este invers proportional cu
timpul, formula bazandu-se pe puterea numerelor subunitare si niste constante
magice adaugate ca bonus pentru reusita completarii jocului.

Taste control:
-> UP key pentru accelerare;
-> DOWN key pentru franare si mers inapoi;
-> LEFT/RIGHT key pentru rotire;
-> X key pentru schimbarea camerei;
-> SPACE key pentru vizualizarea wireframe.