#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

//Simulation von Fahrzeugen erfordert, dass alle Fahrzeuge denselben Zeitverlauf kennen.
double dGlobaleZeit = 0.0;

//Überprüfung der Benutzereingabe für positive double Werte
double eingabeKontrolle(){
						double wert;
						while(true){

							std::cin >> wert;

							if(std::cin.fail() || wert <= 0){
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
								std::cout << "Ungültige Eingabe, bitte geben Sie eine positive Zahl ein"<< std::endl;
								}else{
									return wert;
							}
						}
					}


void vAufgabe_1(){

	std::cout<<"-----vAufgabe_1() gestartet-----"<<std::endl;

	Fahrzeug fzg1("Stack-Fahrzeug");//Erstellen eines Stack-Objekts
	//Es wird automatisch gelöscht, wenn der Block endet

	Fahrzeug* pFzg = new Fahrzeug("Heap-Fahrzeug");//Erstellen eines Heap-Objekts
	delete pFzg;


	// Erstellen eines unique_ptr mit make_unique
	auto uPtr1 = std::make_unique<Fahrzeug>("Unique-1");//auto bedeutet --> std::unique_ptr<Fahrzeug>, es wird automatisch erkannt

	auto uPtr2_move = std::make_unique<Fahrzeug>("Unique-2-Move");

	// Erstellen eines shared_ptr mit make_shared
	auto sPtr1 = std::make_shared<Fahrzeug>("Shared-1");
	//  noch einmal für den Test
	auto sPtr_move = std::make_shared<Fahrzeug>("Shared-2-Move");

	// Shared Pointer Kopiertest startet
	std::cout << "Shared Pointer Kopiertest" << std::endl;
	std::cout << "sPtr1 Referenzanzahl (vor dem Kopieren): " << sPtr1.use_count() << std::endl;

	auto sPtr2_kopieren = sPtr1; // Kopieren, use_count = 2

	auto sptr3_kopieren = sPtr1; //use_count = 3

	std::cout << "sPtr1 Referanzanzahl (nach dem Kopieren): " << sPtr1.use_count() << std::endl;
	std::cout << "sPtr2 Referanzanzahl: " << sPtr2_kopieren.use_count() << std::endl;

	// Unique Pointer Kopiervorgang (ERROR!)
	// Wenn wir den Kommentar in der folgenden Zeile entfernen, wird der Code NICHT KOMPILIERT.
    //auto uPtr_copy = uPtr1;
    // Weil unique_ptr kann nicht kopiert werden,wurde diese Zeile ein Error verursachen



	// Unique Pointer Transporttest
	std::cout << "Unique Pointer Transporttest" << std::endl;
	std::vector<std::unique_ptr<Fahrzeug>> vecUniquePtr; //Erstellen einen Vector, der unique_ptr zu Fahrzeugen speichert.

	// uPtr1 kann man nicht kopieren, weil unique_ptr ist.
	// Besitz muss verchoben werden -mit move()-
	//push_back fügt das Objekt am ende des Vektors ein
	vecUniquePtr.push_back(std::move(uPtr1));

	vecUniquePtr.push_back(std::move(uPtr2_move));

	//Kontroltest, ob uPtr1 null ist.
	if(!uPtr1){
		std::cout << "uPtr1 ist jetzt null (Besitz ist verschoben)." << std::endl;
	}

	//Vektör wird geleert werden mit clear().
	std::cout << "vecUniquePtr.clear() wird aufgerufen." << std::endl;

	vecUniquePtr.clear();//Der Vektor ist nun leer und size ist 0.

	std::cout << "vecUniquePtr.clear() wurde aufgerufen." << std::endl;


	// Hier werden wir sehen, dass die Fahrzeuge(Unique-1 und Unique-2-Move) gelöscht werden.


	// Shared Pointer Transporttest
	std::cout << "Shared Pointer Transporttest" << std::endl;

	// Erstellen einen Vector, der shared_ptr zu Fahrzeugen speichert.
	std::vector<std::shared_ptr<Fahrzeug>> vecSharedPtr;

	// Zuerst KOPIEREN wir sPtr1 in den Vektor.(Ohne move() nutzen)
	  std::cout << "sPtr1 Referenzanzahl (vor dem Kopieren): "
	              << sPtr1.use_count() << std::endl; // Ausgabe: 3

	  //sPtr1 wird in den Vektor kopiert und der Referenzzähler wird erhöht.
	  vecSharedPtr.push_back(sPtr1);

	  std::cout << "sPtr1 Referenzanzahl (nach dem Kopieren): "
	            << sPtr1.use_count() << std::endl; // Ausgabe: 4
    // Nun hat sPtr1 eine Referenzanzahl von 4 -----> sPtr1, sPtr2kopieren, sptr3_kopieren und der vecSharedPtr[0].

	// Jetzt TRANSPORTIEREN wir sPtr_move in den Vektor (mit move()).
	  std::cout << "sPtr_move Referenzanzahl (vor dem Transportieren): "
	            << sPtr_move.use_count() << std::endl; // Ausgabe: 1

	  //Transportieren mit move(), Referenzzähler wird NICHT erhöht.
	  vecSharedPtr.push_back(std::move(sPtr_move));

	  std::cout << "sPtr_move Referenzanzahl (nach dem Transportieren): "
	            << sPtr_move.use_count() << std::endl; // Ausgabe: 0
	      if (sPtr_move == nullptr) {
	          std::cout << "sPtr_move = nullptr (Besitz ist verschoben in den Vektor)" << std::endl;
	      }
	  //sPtr_move ist jetzt null, da der Besitz des Objekts durch den Vektor übernommen wurde.

	  std::cout << "Referenzanzahlen vor dem Ende von vAufgabe_1():" << std::endl;
	  std::cout << "sPtr1 Referenzanzahl : " << sPtr1.use_count() << std::endl;
	  std::cout << "sPtr_move Referenzanzahl : " << sPtr_move.use_count() << std::endl;

	  //Wenn wir schauen, welche sptr zuerst gelöscht werden, werden wir sehen, dass die Fahrzeuge "Shared-2-Move" zuerst gelöscht werden,
	  //weil sPtr_move der einzige Besitzer war und jetzt null ist.
	  std::cout << "vAufgabe_1() wird beendet..." << std::endl;
	  // Hier endet die Funktion vAufgabe_1.

	  /* Alle lokalen shared_ptr (sPtr1, sPtr_move, sPtr2_kopieren, sptr3_kopieren) werden zerstört.
	  Die Referenzanzahlen der Objekte im Heap werden entsprechend verringert.
	  Wenn die Referenzanzahl eines Objekts 0 erreicht, wird es automatisch gelöscht.*/





}

void vAufgabe_1a(){
	std::cout<<"-----vAufgabe_1a() gestartet-----"<<std::endl;

	std::vector<std::unique_ptr<Fahrzeug>> vektor_Fzg;

	double dSimulationsEnde = 5.0;
	double dZeitakt = 0.25;


	//Erstellen von 3 Fahrzeugen mit Benutzereingabe
	for(int i=0; i<3;i++){

		std::string sName;
		double dGeschwindigkeit;

		std::cout<<"Bitte geben Sie den Namen des Fahrzeugs "<<i+1<<": ";
		std::cin>>sName;

		std::cout<<"Bitte geben Sie die maximale Geschwindigkeit des Fahrzeugs "<<i+1<<": ";
		dGeschwindigkeit = eingabeKontrolle();



		auto pNeuesFzg = std::make_unique<Fahrzeug>(sName, dGeschwindigkeit);

		vektor_Fzg.push_back(std::move(pNeuesFzg));

	}

	while(dGlobaleZeit<dSimulationsEnde){
		//Die Schleife läuft, bis die gesamte Simulationszeit erreicht ist.


		//Erhöht die globale Zeit in jedem Simulationsschritt.
		dGlobaleZeit += dZeitakt;


		std::cout<<"\nAktuelle Globale Zeit: "<<dGlobaleZeit<<std::endl;


		//Ausgabe der Kopfzeile für die Fahrzeugdaten.(ID, Name, Geschwindigkeit, Gesamtstrecke, etc.)
		Fahrzeug::vKopf();

		std::cout<<std::endl;

		for(auto& w : vektor_Fzg){
			//Durchläuft alle Fahrzeuge im Vektor.

			//Simuliert die Bewegung des Fahrzeugs für das aktuelle Zeitintervall.
			w->vSimulieren();//(*pfzg).vSimulieren(); = pFzg->vSimulieren(); Fahrzeugzustand aktualisieren

			std::cout << *w; //Fahrzeuginformationen ausgeben

			std::cout<<std::endl;
		}


	}

}

void vAufgabe_2(){

	std::cout<<"-----vAufgabe_2() gestartet-----"<<std::endl;

	//Vektor zum Speichern von Fahrzeugen (PKW und Fahrrad)
	std::vector<std::unique_ptr<Fahrzeug>> vektor_Fzg;

	//Benutzereingabe für Anzahl der PKWs und Fahrräder
	int iAnzahlPKW, iAnzahlFahrrad; //Anzahl der PKWs und Fahrräder
	double dSimulationsEnde = 5.0; //Gesamtsimulationszeit in Stunden
	double dZeitakt = 0.25; //Zeitintervall für jeden Simulationsschritt in Stunden

	//Eingabe der Anzahl der PKWs und Fahrräder
	//Mit Eingabekontrolle werden nur positive Werte akzeptiert
	std::cout<<"Bitte geben Sie die Anzahl der PKWs ein: ";
	iAnzahlPKW = eingabeKontrolle(); //Eingabekontrolle für iAnzahlPKW
	std::cout<<"Bitte geben Sie die Anzahl der Fahrräder ein: ";
	iAnzahlFahrrad = eingabeKontrolle(); //Eingabekontrolle für iAnzahlFahrrad

	//PKW erzeugen und zum Vektor hinzufügen
	for(int i=0; i<iAnzahlPKW;i++){
		std::string sName;
		double dGeschwindigkeit;
		double dVerbrauch;
		double dTankvolumen;




		std::cout<<"Bitte geben Sie den Namen des PKWs "<<i+1<<": ";
		std::cin>>sName; //Eingabe des Namens des PKWs
		std::cout<<"Bitte geben Sie die maximale Geschwindigkeit des PKWs "<<i+1<<": ";
		dGeschwindigkeit = eingabeKontrolle(); //Eingabekontrolle für maximale Geschwindigkeit
		std::cout<<"Bitte geben Sie den Verbrauch des PKWs "<<i+1<<" (L/100km): ";
		dVerbrauch = eingabeKontrolle(); //Eingabekontrolle für Verbrauch
		std::cout<<"Bitte geben Sie das Tankvolumen des PKWs "<<i+1<<" (L): ";
		dTankvolumen = eingabeKontrolle(); //Eingabekontrolle für Tankvolumen

		//Erstellen eines neuen PKW-Objekts mit den eingegebenen Daten
		auto pNeuesFzg = std::make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch, dTankvolumen);

		//Hinzufügen des neuen PKW zum Vektor
		vektor_Fzg.push_back(std::move(pNeuesFzg));

	}

	//Fahrrad erzeugen und zum Vektor hinzufügen
	for(int i=0; i<iAnzahlFahrrad;i++){
		std::string sName;
		double dGeschwindigkeit;
		std::cout<<"Bitte geben Sie den Namen des Fahrrads "<<i+1<<": ";
		std::cin>>sName;
		std::cout<<"Bitte geben Sie die maximale Geschwindigkeit des Fahrrads "<<i+1<<": ";
		dGeschwindigkeit = eingabeKontrolle(); //Eingabekontrolle für maximale Geschwindigkeit

		//Erstellen eines neuen Fahrrad-Objekts mit den eingegebenen Daten
		auto pNeuesFzg = std::make_unique<Fahrrad>(sName, dGeschwindigkeit);
		//Hinzufügen des neuen Fahrrads zum Vektor
		vektor_Fzg.push_back(std::move(pNeuesFzg));

	}

	//Flag, um Tankvorgang nur einmal auszuführen
	bool bGetankt = false;

	//Hauptsimulationsschleife
	while(dGlobaleZeit<dSimulationsEnde){

		//Erhöht die globale Zeit in jedem Simulationsschritt.
		dGlobaleZeit += dZeitakt;

		//PKW tanken nach 3 Stunden (nur einmal)
		if(dGlobaleZeit >=3.0 && !bGetankt){
			bGetankt = true;//Setzt das Flag, um weiteren Tankvorgang zu verhindern
			std::cout<<"--- Tankvorgang bei 3 Stunden ---"<<std::endl;
			for(auto& w : vektor_Fzg){
				w->dTanken(); //Nur PKWs werden tanken, Fahrräder ignorieren diese Methode
			}
		}


		std::cout<<"\nAktuelle Globale Zeit: "<<dGlobaleZeit<<std::endl;

		//Ausgabe der Kopfzeile für die Fahrzeugdaten.(ID, Name, Geschwindigkeit, Gesamtstrecke, etc.)
		Fahrzeug::vKopf();

		std::cout<<std::endl;

		//Simulieren und Ausgabe jedes Fahrzeugs im Vektor mit Rangen-basiertem for-loop
		for(auto& w : vektor_Fzg){

			w->vSimulieren();//(*pfzg).vSimulieren(); = pFzg->vSimulieren(); Fahrzeugzustand aktualisieren

			std::cout << *w; //Fahrzeuginformationen ausgeben

			std::cout<<std::endl;
		}

	}
}

//Burada kaldık*********************************************************
void vAufgabe_3(){
	std::cout<<"-----vAufgabe_3() gestartet-----"<<std::endl;

	//Vektor zum Speichern von Fahrzeugen (PKW und Fahrrad)
	std::vector<std::unique_ptr<Fahrzeug>> vektor_Fzg;

	//Fügen wir ein Fahrrad und ein PKW zum Vektor mit festen Werten hinzu
	vektor_Fzg.push_back(std::make_unique<Fahrrad>("Fahrrad-1", 25.0));

	vektor_Fzg.push_back(std::make_unique<PKW>("PKW-1", 150.0, 6.5, 50.0));

	//Simulationsprozess für 3 Stunden mit Zeitintervall von 1.5 Stunden
	    double dSimulationsEnde = 3.0;
	    double dZeitakt = 1.5;

	    while(dGlobaleZeit < dSimulationsEnde) {
	        dGlobaleZeit += dZeitakt;

	        std::cout<<"-------------------------------------------------"<<std::endl;
	        std::cout<<"\nAktuelle Globale Zeit: "<<dGlobaleZeit<<std::endl;

	        Fahrzeug::vKopf();
	        std::cout << std::endl;
	        for(auto& pFzg : vektor_Fzg) {
	            pFzg->vSimulieren();
	            std::cout << *pFzg << std::endl;
	        }
	    }

	    // Nach 3 Stunden Simulation, führen wir die Tests durch
	    std::cout << "\n--- 3 Stunden ist vorbei ---\n" << std::endl;
	    std::cout << " Die Tests werden gestartet...\n" << std::endl;


	    std::cout << "Test 1: Ausgabeoperator Test" << std::endl;
	    std::cout<<std::endl;
	    Fahrzeug::vKopf();
	    std::cout << std::endl;
	    for(auto& pFzg : vektor_Fzg) {

	    	std::cout << *pFzg << std::endl;
	    }

	    std::cout << "\n Test 2: Vergleichsoperator '<' Test" << std::endl;

	    // Referenzen auf das Fahrrad und den PKW im Vektor
	    Fahrzeug& Fahrrad_1 = *vektor_Fzg[0];
	    Fahrzeug& PKW_1 = *vektor_Fzg[1];

	    std::cout<< "Gesamtstrecke von dem Fahrrad: " << Fahrrad_1.getGesamtStrecke() << " km" << std::endl;
	    std::cout<< "Gesamtstrecke von dem PKW: " << PKW_1.getGesamtStrecke() << " km" << std::endl;


	    if(Fahrrad_1 < PKW_1) {
	        std::cout << "Der Vergleichsoperator '<' funktioniert korrekt: Fahrrad hat weniger Gesamtstrecke als PKW." << std::endl;
	    } else {
	        std::cout << "FEHLER: Der Vergleichsoperator '<' funktioniert NICHT korrekt!" << std::endl;
	    }


	    	// Test 3: Kopierkonstruktor Test
	    	// Wir versuchen, ein Fahrzeugobjekt zu kopieren.
	    	// Dies sollte fehlschlagen, da der Kopierkonstruktor gelöscht wurde.
	        // Der folgende Code ist absichtlich auskommentiert, da er einen Kompilierungsfehler verursachen sollte.
	        // "use of deleted function 'Fahrzeug::Fahrzeug(const Fahrzeug&)'"
	        //Fahrzeug f2 = Fahrrad_1;

	        std::cout << "\n SCHLUSS DER TESTS\n" << std::endl;

	        std::cout << "\n--- AUFGABENBLOCK 1 TAMAMLANDI ---" << std::endl;
}



int main() {

	//vAufgabe_1();
	//vAufgabe_1a();
	//vAufgabe_2();
	vAufgabe_3();


	return 0;
}
