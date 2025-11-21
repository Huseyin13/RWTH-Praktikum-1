#pragma once
#include "Fahrzeug.h"
#include <limits>

 class PKW : public Fahrzeug {
//unterklasse      oberklasse

	private:

		//PKW spezifische Attribute
		double p_dVerbrauch; // Liter pro 100 km, Kraftstoffverbrauch des PKWs
		double p_dTankVolumen; // Maximales Tankvolumen in Litern
		double p_dTankInhalt; // Aktueller Tankinhalt in Litern



	public:

			// Konstruktor für PKW: Name, maximale Geschwindigkeit, Verbrauch und optional Tankvolumen (Standard=55 Liter)
			PKW(std::string name, double maxGeschwindigkeit,double verbrauch, double tankVolumen = 55.0);

			// Überschreiben der virtuellen Tankfunktion
			virtual double dTanken(double dMenge) override;

			// Überschreiben der virtuellen Ausgeben- und Simulieren-Funktionen
			virtual void vAusgeben(std::ostream& o) const override;
			virtual void vSimulieren() override;

			// Überschreiben der aktuellen Geschwindigkeitsberechnung
			//virtual double dGeschwindigkeit() const override;






};





