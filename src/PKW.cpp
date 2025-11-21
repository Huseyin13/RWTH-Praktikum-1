#include <iostream>
#include "PKW.h"
#include <iomanip>

/* Konstruktor der PKW-Klasse
Initialisierungsliste wird verwendet, um:
Basisklassenmember direkt zu initialisieren (p_sName, p_iId usw.)
und effizient zu arbeiten (keine unnötigen Zuweisungen)
PKW-spezifische Variablen werden ebenfalls direkt initialisiert: Verbrauch, Tankvolumen, Tankinhalt*/
PKW::PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankVolumen):
		Fahrzeug(name,maxGeschwindigkeit),
		p_dVerbrauch(verbrauch),
		p_dTankVolumen(tankVolumen),
		p_dTankInhalt(tankVolumen / 2.0){


}

double PKW::dTanken(double dMenge) {
	double d_freierPlatz = p_dTankVolumen - p_dTankInhalt; // Verfügbarer Platz im Tank

	// Überprüfen, ob die zu tankende Menge gültig ist
	if(dMenge <= 0.0){
		return 0.0;
	}

	// Überprüfen, ob die zu tankende Menge den verfügbaren Platz überschreitet
	if(dMenge>= d_freierPlatz){

		p_dTankInhalt = p_dTankVolumen;

		return d_freierPlatz;

	}else // Normales Tanken
	{
		p_dTankInhalt += dMenge;
		return dMenge;
	}
}

void PKW::vAusgeben(std::ostream& o) const{

	// Rufen wir die Basisklassenmethode auf, um die gemeinsamen Fahrzeuginformationen auszugeben
	Fahrzeug::vAusgeben(o);

	// Fügen wir die PKW-spezifischen Informationen hinzu: Verbrauch und Tankinhalt
			o << std::fixed << std::setprecision(2)
			  << std::right
			  << std::setw(11) << p_dVerbrauch
			  << std::setw(16) << p_dTankInhalt;




}

void PKW::vSimulieren(){

	 // Wenn kein Kraftstoff im Tank ist, kann das Fahrzeug nicht fahren
     if(p_dTankInhalt <= 0.0){
    	 		 return;
     }

     // Speichern wir die vorherige Strecke, um die gefahrene Strecke zu berechnen
     double dStrecke_vorher = p_dGesamtStrecke;

     // Rufen wir die Basisklassenmethode auf, um die Bewegung zu simulieren
     Fahrzeug::vSimulieren();
     //Dank der Aufruf von Fahrzeug::vSimulieren() wird die Gesamtstrecke, die Gesamtzeit und die Fahrzeugzeit aktualisiert.

     // Berechnen wir die gefahrene Strecke
     double dGefahreneStrecke = p_dGesamtStrecke - dStrecke_vorher;

     // Berechnen wir den Kraftstoffverbrauch basierend auf der gefahrenen Strecke
     if(dGefahreneStrecke > 0.0){

    	 // Verbrauchter Kraftstoff in Litern
    	 double dVerbrauchterKraftstoff = (dGefahreneStrecke / 100.0) * p_dVerbrauch;

    	 // Reduzieren wir den Tankinhalt
    	 p_dTankInhalt -= dVerbrauchterKraftstoff;

    	 // Sicherstellen, dass der Tankinhalt nicht negativ wird
    	 if(p_dTankInhalt < 0.0){
			 p_dTankInhalt = 0.0;
		 }
     }

}

// Berechnen wir die aktuelle Geschwindigkeit des PKWs
/*double PKW::dGeschwindigkeit() const{

	// Geschwindigkeit ist immer die maximale Geschwindigkeit, solange Kraftstoff im Tank ist
	return p_dMaxGeschwindigkeit;
}*/






