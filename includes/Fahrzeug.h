#pragma once
#include <string>
#include <limits>

class Fahrzeug {


	private:

		/*const = Diese ID ist für das Objekt eindeutig und kann
		 nach der Erstellung (im Konstruktor) NIE geändert werden.*/
		const int p_iId; // Fahrzeug ID
		//Jede ID einzigartig für jedes Fahrzeugobjekt.
		//Deswegen const und haben wir unten kopierkonstruktor verboten.



		/*static = Gehört zur KLASSE, nicht zum Objekt.
		 Ein globaler Zähler für alle erstellten Fahrzeuge.*/
		static int p_iMaxId; //Maximale Fahrzeug ID (Anzahl der erstellten Fahrzeuge)

	protected:
		std::string p_sName; //Fahrzeug name

		double p_dMaxGeschwindigkeit; //Maximale Geschwindigkeit

		double p_dGesamtStrecke; //Gesamt zurückgelegte Strecke

		double p_dGesamtZeit; //Gesamt gefahrene Zeit

		double p_dZeit; //Letzte Simulationszeit



	public:

		Fahrzeug();//default constructor

		Fahrzeug(std::string name);//constructor mit name parameter

		Fahrzeug(std::string name, double maxGeschwindigkeit);//constructor mit name und maxGeschwindigkeit parameter

		virtual ~Fahrzeug(); //destructor



		static void vKopf(); //Kopfzeile ausgeben


		// Ausgabe der Fahrzeugdaten auf einen Stream
		virtual void vAusgeben(std::ostream& o) const;

		// Simulation des Fahrzeugs für das aktuelle Zeitintervall
		virtual void vSimulieren();


		/* Virtuelle Tankfunktion für alle Fahrzeuge.
		 Defaultparameter: unendlich -> bedeutet "so viel wie möglich tanken".
		 Basisklasse: macht nichts und gibt 0 zurück.
		 Abgeleitete Klassen wie PKW überschreiben diese Funktion.*/
		virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());


		// Berechnung der aktuellen Geschwindigkeit des Fahrzeugs
		virtual double dGeschwindigkeit() const;

		// Überladen des Vergleichsoperators '<' für Fahrzeuge basierend auf der Gesamtstrecke
		bool operator<(const Fahrzeug& anderesFahrzeug) const;



		  /* Wir verbieten den Kopierkonstruktor.
		     WARUM? Jedes Fahrzeug MUSS eine einzigartige 'p_iId' haben,
		     die es nur vom 'p_iMaxId'-Zähler bekommt.
		     Ein Kopiervorgang (z.B. Fahrzeug f2 = f1) würde die ID
		     duplizieren und unser System brechen.(compile time errror)*/
		Fahrzeug(const Fahrzeug&) = delete;

		// Getter für die Gesamtstrecke
		double getGesamtStrecke() const;









};

std::ostream& operator<<(std::ostream& o, const Fahrzeug& x);
