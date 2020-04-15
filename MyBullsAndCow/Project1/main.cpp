#include <ctime>
#include <iostream>

// pour les nombres aléatoires
#include <cstring> // strlen
#include <random>

// Couleur au hasard
std::uniform_int_distribution<int> distribution;
std::default_random_engine generateur(time(NULL));

int selection = 0;

// Tirage ordinateur
char tirer_couleur()
{
    static const char* const couleurs = "WRGBCYM";
    static const int nb = strlen(couleurs) - 1;

    return couleurs[distribution(generateur, std::uniform_int_distribution<int>::param_type{0, nb})];
}

// Permet de récuperer l'entrée code joueur
char poser_question()
{
    char lu(' ');
    std::cout << "Enter colors one by one : ";
    std::cin >> lu;
    return lu;
}

// Verification de la couleur
bool couleur_valide(char c)
{
    return c == 'W' || c == 'R' || c == 'G' || c == 'B' || c == 'C' || c == 'Y' || c == 'M';
}

// Entrée code joueur
char lire_couleur()
{
    char lu(poser_question());
    while (not couleur_valide(lu))
    {
        std::cout << "'" << lu << "' is not a valid color." << std::endl;
        std::cout << "Colors available : W, R, G, B, C, Y ou M." << std::endl;
        lu = poser_question();
    }
    return lu;
}
// Affichage du code à trouver
void afficher_couleurs(char c1, char c2, char c3, char c4)
{
    std::cout << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4;
}

void afficher_bullsAndCows(int nb, char c)
{
    while (nb-- > 0)
    {
        std::cout << c;
    }
}

void message_gagne(int nb_coups)
{
    std::cout << "Well done ! You found in " << nb_coups << " tries." << std::endl;
}

void message_perdu(char c1, char c2, char c3, char c4)
{
    std::cout << "You lost." << std::endl;
    std::cout << "Good combination was : ";
    afficher_couleurs(c1, c2, c3, c4);
    std::cout << std::endl;
}

// Permet de savoir si une couleur est placée à la même place que l'autre
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

// Permet de savoir si une couleur est identique mais mal placée
void apparier(char c1_test, char& c1_reference, char& c2_reference, char& c3_reference, int& score)
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

void afficher_reponses(char c1, char c2, char c3, char c4, char r1, char r2, char r3, char r4)
{
    int nb(0);
    int nb1(0);
    char c(' ');
    int score(0);

    /**On s'occupe d'abord des couleurs identiques bien placées puis on les ignore dès qu'elles sont reconnues.
    On s'assure avec les if que si les couleurs sont identiques et bien placées, elles sont enlevées.
    On passe ensuite aux couleurs non identiques avec une simple soustraction avec les informations déja connues en
    amont.*/

    /**Pour les couleurs bien placéés et identiques*/

    verifier(c1, r1, nb);
    verifier(c2, r2, nb);
    verifier(c3, r3, nb);
    verifier(c4, r4, nb);

    c = '#';
    afficher_bullsAndCows(nb, c);

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
    afficher_bullsAndCows(score, c);

    /**Pour les couleurs distinctes*/

    /**Simple soustraction en connaissant déja les bien placées identiques et identiques mal placées*/

    nb1 = 4 - (nb + score);
    c = '-';
    afficher_bullsAndCows(nb1, c);
}
// Affichage de la tentative ainsi que des Bulls and Cows
void afficher_coup(char c1, char c2, char c3, char c4, char r1, char r2, char r3, char r4)
{
    afficher_couleurs(c1, c2, c3, c4);
    std::cout << " : ";
    afficher_reponses(c1, c2, c3, c4, r1, r2, r3, r4);
    std::cout << std::endl;
}

bool gagne(char c1, char c2, char c3, char c4, char r1, char r2, char r3, char r4)
{
    return c1 == r1 && c2 == r2 && c3 == r3 && c4 == r4;
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
        /**Demande des couleurs, c'est lourd je sais et peu pratique surtout pour l'option 3 mais j'ai du mal à
         * manipuler autrement*/

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

// Menu avec seulement l'option 1
void menu()
{
    std::cout << std::endl;
    std::cout << "-----------------WELCOME TO MY GAME BULLS AND COWS----------------- \n";
    std::cout << "What do you want to do ?\n";
    std::cout << "1. Humain Vs Computer\n";
    std::cout << "2.Computer Vs Computer\n";
    std::cout << "3.Game Option\n";
    std::cout << "4.Rules\n";

    std::cin >> selection;
    if (selection == 1)
    {
        std::cout << "You are playing against the computer\n";
        std::cout << "Good luck and have fun\n";
        std::cout << "Find now the code with WRGBCYM \n";
        jouer();
        menu();
    }

    if (selection == 2)
    {
        std::cout << "Not available";
        menu();
    }
    if (selection == 3)
    {
        std::cout << "Not available";
        menu();
    }
    if (selection == 4)
    {
        std::cout << "The object of the game is to try to find the computer generated 4 color combination.\n";
        std::cout << "You have 12 tries.\n";
        std::cout << "If a color is identical and well placed, a # will appear.\n";
        std::cout << "If it is identical and misplaced, then a + will appear.\n";
        std::cout << "And if it is the wrong color, you will see a - .\n";
        menu();
    }

    else
    {
        menu();
    }
};

int main()
{
    menu();
    return 0;
}