#include <iostream>
#include "Fahrzeug.h"
#include <iomanip>

//Extern bedeutet, dass die Variable in einer anderen Datei definiert ist.
extern double dGlobaleZeit;





/* DIESE Zeile reserviert den Speicher für die 'static' Variable,
die in der .h-Datei nur "angekündigt" (deklariert) wurde.
Es darf nur EINE Definition im gesamten Programm geben.*/
int Fahrzeug::p_iMaxId = 0;
//Wir haben Fahrzeug:: genutzt, damit compiler die Definiton von p_iMaxId finden kann.



/* Konstruktoren und Destruktoren der Fahrzeug-Klasse
 Initialisierungsliste wird verwendet, um die Member direkt zu initialisieren
 (keine unnötigen Zuweisungen)*/
Fahrzeug::Fahrzeug():
		p_iId(++p_iMaxId),
		p_sName(""),
		p_dMaxGeschwindigkeit(0.0),
		p_dGesamtStrecke(0.0),
		p_dGesamtZeit(0.0),
		p_dZeit(0.0){

	std::cout<<"Fahrzeug erstellt -> ID : " << p_iId <<", Name : "<<p_sName<<std::endl;

}

//Konstruktor mit Name Parameter
Fahrzeug::Fahrzeug(std::string name):
		p_iId(++p_iMaxId),
		p_sName(name),
		p_dMaxGeschwindigkeit(0.0),
		p_dGesamtStrecke(0.0),
		p_dGesamtZeit(0.0),
		p_dZeit(0.0){

	std::cout<<"Fahrzeug erstellt -> ID : " << p_iId <<", Name : "<<p_sName<<std::endl;

}


//Konstruktor mit Name und maxGeschwindigkeit Parameter
Fahrzeug::Fahrzeug(std::string name, double maxGeschwindigkeit):
		p_iId(++p_iMaxId),
		p_sName(name),
		p_dMaxGeschwindigkeit((maxGeschwindigkeit < 0.0) ? 0.0 : maxGeschwindigkeit),
		p_dGesamtStrecke(0.0),
		p_dGesamtZeit(0.0),
		p_dZeit(0.0){

	std::cout<<"Fahrzeug erstellt -> ID : " << p_iId <<", Name : "<<p_sName<<std::endl;

}

//Destruktor
Fahrzeug::~Fahrzeug() {

	std::cout<<"Fahrzeug gelöscht -> ID : " << p_iId <<", Name : "<<p_sName<<std::endl;
}






void Fahrzeug::vKopf() {

	//Kopfzeile für die Fahrzeugdaten ausgeben
	std::cout << std::left;
	std::cout << std::setw(5) << "ID"; //Breit 5 für ID
	std::cout << std::setw(15) << "Name"; //Breit 15 für Name
	std::cout << std::setw(20) << "MaxGeschwindigkeit"; //Breit 20 für MaxGeschwindigkeit
	std::cout << std::setw(15) << "AktuelleGeschw"; //Breit 15 für AktuelleGeschw
	std::cout << std::setw(15) << "GesamtStrecke"; //Breit 15 für GesamtStrecke
	std::cout << std::setw(15) << "Verbrauch"; //Breit 15 für Verbrauch
	std::cout << std::setw(15) << "Tankinhalt"; //Breit 15 für Tankinhalt



}

// Ausgabe der Fahrzeugdaten auf einen Stream
void Fahrzeug::vAusgeben(std::ostream& o) const {

	// Textausgabe wird linkbündig ausgerichtet.
	o << std::left;

	o << std::fixed << std::setprecision(2); // Stellen wir feste Kommazahl mit 2 Nachkommastellen ein.


	o << std::setw(5) << p_iId;
	o << std::setw(15) << p_sName;

	o << std::right; // Ab hier rechtsbündig

	o << std::setw(18) << p_dMaxGeschwindigkeit;
	o << std::setw(16) << dGeschwindigkeit();
	o << std::setw(14) << p_dGesamtStrecke;

    // Formatierungzustände am Ende der Ausgabe zurücksetzen.
    // defaultfloat entfernt feste Kommazahl-Einstellung.
    // std::defaultfloat stellt die Standardausgabe wieder her.
	o << std::defaultfloat << std::right;

}



// Virtuelle Tankfunktion für alle Fahrzeuge.
double Fahrzeug::dTanken(double dMenge){
		return 0.0;
	}



void Fahrzeug::vSimulieren(){
	// Simuliert die Bewegung des Fahrzeugs für das vergangene Zeitintervall.
	// Aktualisiert die zurückgelegte Strecke, die Fahrzeit und synchronisiert die Fahrzeugzeit.

    	//Überprüfen wir, ob die Fahrzeugzeit hinter der globalen Zeit liegt
    	if(p_dZeit < dGlobaleZeit){//verhindert versehentlich doppelte Simulation

    		// 1. Zeitintervall berechnen
    		double dZeitIntervall = dGlobaleZeit - p_dZeit;

    		// 2. Zurückgelegte Strecke in diesem Zeitintervall berechnen
    		double dStrecke = dGeschwindigkeit() * dZeitIntervall;

    		// 3. Aktualisiere die Gesamtstrecke und Gesamtzeit
    		p_dGesamtStrecke += dStrecke;
    		p_dGesamtZeit += dZeitIntervall;

    		// 4. Aktualisiere die Fahrzeugzeit auf die globale Zeit
    		p_dZeit = dGlobaleZeit;
    	}



    }



	//Berechnung der aktuellen Geschwindigkeit des Fahrzeugs
    double Fahrzeug::dGeschwindigkeit() const{
    	return p_dMaxGeschwindigkeit;
    }


    // Überladen des Ausgabeoperators für Fahrzeug
    std::ostream& operator<<(std::ostream& o, const Fahrzeug& fzg){
		fzg.vAusgeben(o);
		return o;
	}

    // Überladen des Vergleichsoperators '<' für Fahrzeuge basierend auf der Gesamtstrecke
    bool Fahrzeug::operator<(const Fahrzeug& anderesFahrzeug) const{
    	return this->p_dGesamtStrecke < anderesFahrzeug.p_dGesamtStrecke;
    }

    // Getter für Gesamtstrecke
    double Fahrzeug::getGesamtStrecke() const{
		return p_dGesamtStrecke;
	}



