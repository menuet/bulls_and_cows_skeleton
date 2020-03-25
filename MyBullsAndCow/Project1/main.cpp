
#include <iostream>
#include <ctime>

// pour les nombres aléatoires
#include <random>
#include <cstring> // strlen

using namespace std;

// Couleur au hasard
std::uniform_int_distribution<int> distribution;
std::default_random_engine generateur(time(NULL)); 




char tirer_couleur()
{
    static const char* const couleurs = "WRGBCYM";
    static const int nb = strlen(couleurs) - 1;

    return couleurs[distribution(generateur,
        std::uniform_int_distribution<int>::param_type{ 0, nb })];
}

char poser_question()
{
    char lu(' ');
    cout << "Entrez une couleur : ";
    cin >> lu;
    return lu;
}


void afficher_couleurs(char c1, char c2, char c3, char c4)
{
    cout << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4;
}

void afficher(int nb, char c)
{
    while (nb-- > 0) {
        cout << c;
    }
}


void message_gagne(int nb_coups)
{
    cout << "Bravo ! Vous avez trouvé en " << nb_coups << " coups." << endl;
}

void message_perdu(char c1, char c2, char c3, char c4)
{
    cout << "Perdu :-(" << endl;
    cout << "La bonne combinaison était : ";
    afficher_couleurs(c1, c2, c3, c4);
    cout << endl;
}

bool couleur_valide(char c)
{
    if (c == 'W' || c == 'R' || c == 'G' || c == 'B' || c == 'C' || c == 'Y' || c == 'M')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool verifier(char& c1, char& c2, int& score)
{
    if (c1 == c2)
    {
        score++;
        c2 = 'x';
        return true;

    }
    else
    {
        return false;
    }
}

void apparier(char c1_test, char& c1_reference, char& c2_reference,
    char& c3_reference, int& score)
{
    bool compar1(true);
    bool compar2(true);

    compar1 = verifier(c1_test, c1_reference, score);
    if (compar1 == false)
    {
        compar2 = verifier(c1_test, c2_reference, score);
        if (compar2 == false)
        {
            verifier(c1_test, c3_reference, score);
        }
    }
}

void afficher_reponses(char c1, char c2, char c3, char c4,
    char r1, char r2, char r3, char r4)
{
    int nb(0);
    int nb1(0);
    char c(' ');
    int score(0);

    /**Pour les couleurs bien placéés et identiques*/

    verifier(c1, r1, nb);
    verifier(c2, r2, nb);
    verifier(c3, r3, nb);
    verifier(c4, r4, nb);

    c = '#';
    afficher(nb, c);

    /**Pour les couleurs identiques mal placées*/

    if ('x' != r1)
        apparier(c1, r2, r3, r4, score);
    if ('x' != r2)
        apparier(c2, r1, r3, r4, score);
    if ('x' != r3)
        apparier(c3, r1, r2, r4, score);
    if ('x' != r4)
        apparier(c4, r1, r2, r3, score);

    c = '+';
    afficher(score, c);

    /**Pour les couleurs distinctes*/

    nb1 = 4 - (nb + score);
    c = '-';
    afficher(nb1, c);
}
void afficher_coup(char c1, char c2, char c3, char c4,
    char r1, char r2, char r3, char r4)
{
    afficher_couleurs(c1, c2, c3, c4);
    cout << " : ";
    afficher_reponses(c1, c2, c3, c4,
        r1, r2, r3, r4);
    cout << endl;
}

char lire_couleur()
{
    char lu(poser_question());
    while (not couleur_valide(lu)) {
        cout << "'" << lu << "' n'est pas une couleur valide." << endl;
        cout << "Les couleurs possibles sont : W, R, G, B, C, Y ou M." << endl;
        lu = poser_question();
    }
    return lu;
}

bool gagne(char c1, char c2, char c3, char c4,
    char r1, char r2, char r3, char r4)
{
    bool reponse(true);

    if (c1 == r1 && c2 == r2 && c3 == r3 && c4 == r4)
        reponse = true;
    else
        reponse = false;

    return reponse;
}

void jouer(int coup_max = 12)
{
    int nbre(0);

    /**Combinaison de réference à deviner*/

    char r1 = tirer_couleur();
    char r2 = tirer_couleur();
    char r3 = tirer_couleur();
    char r4 = tirer_couleur();
    char c1(' '), c2(' '), c3(' '), c4(' ');

    do
    {
        /**Demande des couleurs*/

        c1 = lire_couleur();
        c2 = lire_couleur();
        c3 = lire_couleur();
        c4 = lire_couleur();

        /**affichage du coup*/

        afficher_coup(c1, c2, c3, c4, r1, r2, r3, r4);
        nbre++;
    } while (!gagne(c1, c2, c3, c4, r1, r2, r3, r4) && (nbre < coup_max));

    if (gagne(c1, c2, c3, c4, r1, r2, r3, r4))
        message_gagne(nbre);
    else
        message_perdu(r1, r2, r3, r4);
}


int main()
{
    jouer();
    return 0;
}