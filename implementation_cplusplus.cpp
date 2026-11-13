#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Passager {
private:
    int idPassager; string nom; string prenom; string numeroPasseport; string telephone;
public:
    Passager(int id, string n, string p, string passeport, string tel) {
        idPassager = id; nom = n; prenom = p; numeroPasseport = passeport; telephone = tel;
    }
    int getIdPassager() const { return idPassager; }
    string getNom() const { return nom; }
    void afficherDetails() const {
        cout << "[Passager] ID: " << idPassager << " | Nom: " << nom << " " << prenom
             << " | Passeport: " << numeroPasseport << " | Tel: " << telephone << endl;
    }
};

class Vol {
private:
    string numeroVol; string destination; string dateDepart; string heureDepart;
    int capacite; int placesDisponibles; double prixBillet;
public:
    Vol(string num, string dest, string date, string heure, int cap, double prix) {
        numeroVol = num; destination = dest; dateDepart = date; heureDepart = heure;
        capacite = cap; placesDisponibles = cap; prixBillet = prix;
    }
    string getNumeroVol() const { return numeroVol; }
    string getDestination() const { return destination; }
    string getDateDepart() const { return dateDepart; }
    int getPlacesDisponibles() const { return placesDisponibles; }
    double getPrixBillet() const { return prixBillet; }
    bool reserverPlace() { if (placesDisponibles > 0) { placesDisponibles--; return true; } return false; }
    void libererPlace() { if (placesDisponibles < capacite) placesDisponibles++; }
    void afficherDetails() const {
        cout << "[Vol] N: " << numeroVol << " | Destination: " << destination
             << " | Date: " << dateDepart << " " << heureDepart
             << " | Places: " << placesDisponibles << "/" << capacite << " | Prix: " << prixBillet << " XOF" << endl;
    }
};

class Reservation {
private:
    int idReservation; Passager* passager; Vol* vol; string statut;
public:
    Reservation(int id, Passager* p, Vol* v) { idReservation = id; passager = p; vol = v; statut = "En attente"; }
    int getIdReservation() const { return idReservation; }
    string getStatut() const { return statut; }
    Passager* getPassager() const { return passager; }
    Vol* getVol() const { return vol; }
    void setStatut(string s) { statut = s; }
    void afficherDetails() const {
        cout << "[Reservation] ID: " << idReservation << " | Client: " << passager->getNom()
             << " | Vol: " << vol->getNumeroVol() << " | Statut: " << statut << endl;
    }
};

class Paiement {
private:
    int idPaiement; Reservation* reservation; double montant; string modePaiement;
public:
    Paiement(int id, Reservation* res, double m, string mode) { idPaiement = id; reservation = res; montant = m; modePaiement = mode; }
    int getIdReservation() const { return reservation->getIdReservation(); }
    void effectuerPaiement() {
        cout << "[Succes] Paiement de " << montant << " XOF via " << modePaiement << " pour resa N " << reservation->getIdReservation() << endl;
        reservation->setStatut("Payee");
    }
    void afficherDetails() const {
        cout << "[Paiement] ID: " << idPaiement << " | Resa: " << reservation->getIdReservation() << " | Montant: " << montant << " | Mode: " << modePaiement << endl;
    }
};

class Annulation {
private:
    int idAnnulation; Reservation* reservation; string motif; string statutRemboursement;
public:
    Annulation(int id, Reservation* res, string m) {
        idAnnulation = id; reservation = res; motif = m;
        if (res->getStatut() == "Payee") statutRemboursement = "Rembourse"; else statutRemboursement = "Non applicable";
        res->getVol()->libererPlace(); res->setStatut("Annulee");
    }
    int getIdReservation() const { return reservation->getIdReservation(); }
    void afficherDetails() const {
        cout << "[Annulation] ID: " << idAnnulation << " | Resa: " << reservation->getIdReservation() << " | Motif: " << motif << " | Remboursement: " << statutRemboursement << endl;
    }
};

class AgenceVoyage {
private:
    vector<Passager> passagers; vector<Vol> vols; vector<Reservation> reservations;
    vector<Paiement> paiements; vector<Annulation> annulations;
    int compteurPassager; int compteurReservation; int compteurPaiement; int compteurAnnulation;
public:
    AgenceVoyage() {
        compteurPassager = 1; compteurReservation = 1; compteurPaiement = 1; compteurAnnulation = 1;
        passagers.reserve(100); vols.reserve(100); reservations.reserve(100);
        paiements.reserve(100); annulations.reserve(100);
    }
    void initialiserDonneesParDefaut() {
        vols.push_back(Vol("BJ-101", "Paris", "2026-12-15", "10:00", 5, 450000));
        vols.push_back(Vol("BJ-202", "Abidjan", "2026-11-20", "14:30", 3, 150000));
    }
    void enregistrerPassager() {
        string nom, prenom, passeport, tel;
        cout << "\n--- Enregistrement ---\nNom : "; cin >> nom;
        cout << "Prenom : "; cin >> prenom;
        cout << "Passeport : "; cin >> passeport;
        cout << "Telephone : "; cin >> tel;
        passagers.push_back(Passager(compteurPassager, nom, prenom, passeport, tel)); compteurPassager++;
        cout << "[OK] Passager enregistre !\n";
    }
    void ajouterVol() {
        string num, dest, date, heure; int cap; double prix;
        cout << "\n--- Ajout Vol ---\nNumero : "; cin >> num;
        cout << "Destination : "; cin >> dest;
        cout << "Date : "; cin >> date; cout << "Heure : "; cin >> heure;
        cout << "Capacite : "; cin >> cap; cout << "Prix : "; cin >> prix;
        vols.push_back(Vol(num, dest, date, heure, cap, prix));
        cout << "[OK] Vol ajoute !\n";
    }
    void afficherVolsDisponibles() {
        cout << "\n--- Vols ---\n";
        if (vols.empty()) { cout << "Aucun vol.\n"; return; }
        for (size_t i = 0; i < vols.size(); ++i) { cout << i + 1 << ". "; vols[i].afficherDetails(); }
    }
    void rechercherVol() {
        string rech; cout << "Destination ou Date : "; cin >> rech; bool t = false;
        for (size_t i = 0; i < vols.size(); ++i) {
            if (vols[i].getDestination() == rech || vols[i].getDateDepart() == rech) { vols[i].afficherDetails(); t = true; }
        }
        if (!t) cout << "Aucun vol trouve.\n";
    }
    void effectuerReservation() {
        if (passagers.empty() || vols.empty()) { cout << "[Erreur] Il faut un passager et un vol.\n"; return; }
        afficherVolsDisponibles();
        int cv; cout << "Choix vol : "; cin >> cv;
        if (cv < 1 || cv > (int)vols.size()) { cout << "[Erreur] Choix invalide.\n"; return; }
        if (vols[cv - 1].getPlacesDisponibles() <= 0) { cout << "[Erreur] Vol complet !\n"; return; }
        for (size_t i = 0; i < passagers.size(); ++i) { cout << i + 1 << ". "; passagers[i].afficherDetails(); }
        int cp; cout << "Choix passager : "; cin >> cp;
        if (cp < 1 || cp > (int)passagers.size()) { cout << "[Erreur] Choix invalide.\n"; return; }
        for (size_t i = 0; i < reservations.size(); ++i) {
            if (reservations[i].getPassager()->getIdPassager() == passagers[cp - 1].getIdPassager() && reservations[i].getVol()->getNumeroVol() == vols[cv - 1].getNumeroVol() && reservations[i].getStatut() != "Annulee") { cout << "[Erreur] Deja reserve ce vol !\n"; return; }
        }
        vols[cv - 1].reserverPlace();
        reservations.push_back(Reservation(compteurReservation, &passagers[cp - 1], &vols[cv - 1])); compteurReservation++;
        cout << "[OK] Reservation creee !\n";
    }
    void effectuerPaiement() {
        if (reservations.empty()) { cout << "[Erreur] Aucune reservation.\n"; return; }
        for (size_t i = 0; i < reservations.size(); ++i) { cout << i + 1 << ". "; reservations[i].afficherDetails(); }
        int cr; cout << "Reservation a payer : "; cin >> cr;
        if (cr < 1 || cr > (int)reservations.size()) { cout << "[Erreur] Choix invalide.\n"; return; }
        if (reservations[cr - 1].getStatut() == "Annulee") { cout << "[Erreur] Annulee, impossible de payer !\n"; return; }
        if (reservations[cr - 1].getStatut() == "Payee") { cout << "[Erreur] Interdit de payer 2 fois !\n"; return; }
        int cm; cout << "Mode (1: MTN MoMo, 2: Moov Money, 3: Especes) : "; cin >> cm;
        string mode = "Especes"; if (cm == 1) mode = "MTN MoMo"; else if (cm == 2) mode = "Moov Money";
        double montant = reservations[cr - 1].getVol()->getPrixBillet();
        paiements.push_back(Paiement(compteurPaiement, &reservations[cr - 1], montant, mode)); compteurPaiement++;
        paiements.back().effectuerPaiement();
    }
    void annulerReservation() {
        if (reservations.empty()) { cout << "[Erreur] Aucune reservation.\n"; return; }
        for (size_t i = 0; i < reservations.size(); ++i) { cout << i + 1 << ". "; reservations[i].afficherDetails(); }
        int cr; cout << "Reservation a annuler : "; cin >> cr;
        if (cr < 1 || cr > (int)reservations.size()) return;
        if (reservations[cr - 1].getStatut() == "Annulee") { cout << "[Erreur] Deja annulee !\n"; return; }
        string motif; cout << "Motif : "; cin.ignore(numeric_limits<streamsize>::max(), '\n'); getline(cin, motif);
        annulations.push_back(Annulation(compteurAnnulation, &reservations[cr - 1], motif)); compteurAnnulation++;
        cout << "[OK] Annulee, place liberee.\n";
    }
    void consulterReservations() {
        cout << "\n--- Reservations ---\n";
        if (reservations.empty()) { cout << "Aucune.\n"; return; }
        for (size_t i = 0; i < reservations.size(); ++i) reservations[i].afficherDetails();
        for (size_t i = 0; i < paiements.size(); ++i) paiements[i].afficherDetails();
        for (size_t i = 0; i < annulations.size(); ++i) annulations[i].afficherDetails();
    }
    void afficherInfosReservation() {
        int id; cout << "ID Reservation : "; cin >> id;
        for (size_t i = 0; i < reservations.size(); ++i) if (reservations[i].getIdReservation() == id) {
            reservations[i].afficherDetails(); reservations[i].getPassager()->afficherDetails(); reservations[i].getVol()->afficherDetails();
            for (size_t j = 0; j < paiements.size(); ++j) if (paiements[j].getIdReservation() == id) paiements[j].afficherDetails();
            return;
        }
        cout << "Introuvable.\n";
    }
    void lancerMenu() {
        initialiserDonneesParDefaut(); int choix;
        do {
            cout << "\n========================================\n";
            cout << " AGENCE DE VOYAGE DE COTONOU - MENU PRINCIPAL \n";
            cout << "========================================\n";
            cout << "1. Enregistrer un passager\n";
            cout << "2. Ajouter un vol\n";
            cout << "3. Afficher les vols disponibles\n";
            cout << "4. Rechercher un vol\n";
            cout << "5. Effectuer une reservation\n";
            cout << "6. Enregistrer un paiement\n";
            cout << "7. Annuler une reservation\n";
            cout << "8. Consulter les reservations\n";
            cout << "9. Afficher les informations d'une reservation\n";
            cout << "10. Quitter\n";
            cout << "Votre choix : ";
            if (!(cin >> choix)) { cout << "[Erreur] Saisie invalide.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
            switch (choix) {
                case 1: enregistrerPassager(); break;
                case 2: ajouterVol(); break;
                case 3: afficherVolsDisponibles(); break;
                case 4: rechercherVol(); break;
                case 5: effectuerReservation(); break;
                case 6: effectuerPaiement(); break;
                case 7: annulerReservation(); break;
                case 8: consulterReservations(); break;
                case 9: afficherInfosReservation(); break;
                case 10: cout << "Fermeture...\n"; break;
                default: cout << "[Erreur] Choix inconnu !\n";
            }
        } while (choix != 10);
    }
};

int main() { AgenceVoyage agence; agence.lancerMenu(); return 0; }
