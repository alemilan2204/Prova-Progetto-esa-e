#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
using namespace std;

enum OPZIONI // enum = set di costanti
{
    INVENTARIO,
    NEGOZIO,
    CERCA,
    BLACKJACK,
    OPZIONE,
    SALVATAGGIO
};


// -- -- -- -- -- -- --
void StampaMenu();
void StampaOpzioni();
void StampaInventario(bool inventario[], string nome);
bool HaSoldi(int soldiGiocatore, int costo);
void Negozio(int& soldi, bool inventario[]);
void Cerca(int& soldi);
void BlackJack(int& soldi);
void Salvataggio(int *soldi, bool oggettiPosseduti[]);
void Caricamento();

OPZIONI ScriviOpzioni(string input);
// -- -- -- -- -- -- --


int main()
{
    string nome = "";
    string input = "";

    int soldi = 11500;

    bool inventario[3] = {0}; //Pos 0: fucile da caccia, Pos 1: canna da pesca, Pos 2: PC

    // -- -- -- -- -- -- -- -- --     

    cout << "CIAO! Come ti chiami? IO sono Zenyatta!\n";
    cin >> nome;

    
    while (true)
    {
        StampaMenu();
        cin >> input;
        
        switch (ScriviOpzioni(input))
        {
            case INVENTARIO:
                StampaInventario(inventario, nome);
                break;

            case NEGOZIO:
                system("cls");                         // pulisce la console
                Negozio(soldi, inventario);
                break;

            case CERCA:
                system("cls");
                Cerca(soldi);
                break;

            case BLACKJACK:
                system("cls");
                BlackJack(soldi);
                break;

            case SALVATAGGIO:
                Salvataggio(&soldi, inventario);
                break;

            default:
                cout << "Scusa, non ho capito! :c \n";
                break;
        }
        
    }

    return 0;
}


void StampaMenu()
{
    system("cls");
    cout << "Seleziona l'operazione che vuoi eseguire :D \n\n";
    cout << "Scrivere 'Inventario' per visualizzare l'inventario.\n";
    cout << "Scrivere 'Negozio' per aprire il negozio.\n";
    cout << "Scrivere 'Cerca' per cercare soldi nei posti piu' disparati.\n";
    cout << "Scrivere 'BlackJack' per entrare nel casino' e iniziare a giocare a Back Jack.\n";
    cout << "Scrivere 'Opzioni' per vedere il menù delle opzioni\n";
    cout << "Scrivere 'Salvataggio' per salvare i progressi fatti fin'ora " 
            "(i.e. soldi, inventario)\n\n";
}

void StampaOpzioni()
{
    system("cls");
    textcolor(0);

} // TODO: Da fare

void StampaInventario(bool inventario[], string nome)    //Fa vedere l'inventario del giocatore, se è vuoto, lo scrive
{
    cout << "\nCiao, " << nome << ", questo e' il tuo inventario:\n";

    if (inventario[0]) { cout << "- Fucile da caccia\n"; }
    else if (inventario[1]) { cout << "- Canna da pesca\n"; }
    else if (inventario[2]) { cout << "- PC\n"; }
    else
    {
        cout << "\nOh no "<< nome <<"! Il tuo inventario e' vuoto :(\n"; 
    }
}

bool HaSoldi(int soldiGiocatore, int costo)     
{
    if (soldiGiocatore >= costo) { return true; }
}//controlla se ci sono soldi

void Negozio(int& soldi, bool inventario[])   
{
    int scelta = 0;
    // -- -- -- -- -- 
    cout << "\n-- -- -- NEGOZIO -- -- -- \n\n";
    cout << "1) Fucile da caccia......1000\n"
            "2) Canna da pesca........500 \n"
            "3) PC....................10000\n\n";

    cout << "Questo e' il negozio, vuoi comprare qualcosa? Scrivi il numero \n";
    cin >> scelta;

    switch (scelta)
    {
        case 1:
            if (HaSoldi(soldi, 1000))
            {
                soldi -= 1000;
                inventario[0] = true;
                cout << "Ottimo, ora possiedi il Fucile da caccia!\n ";
            }
            break;

        case 2:
            if (HaSoldi(soldi, 500))
            {
                soldi -= 500;
                inventario[1] = true;
                cout << "Che bello, ora puoi andare a pesca!! :)\n ";
            }
            break;

        case 3:
            if (HaSoldi(soldi, 10000))
            {
                soldi -= 10000;
                inventario[2] = true;
                cout << "Evidentemente sei così ricco da poterti permettere un PC!!  :o\n ";
            }
            break;

        default:
            break;
    }
}  //permette di acquistare alcuni oggetti, se il giocatore ha soldi

void Cerca(int& soldi)
{
    string posti[5] = { "scuola","orfanotrofio abbandonato","luna",
                       "villetta a schiera americana","museo" };

    srand(time(NULL));      //Inizializzazione del generatore di numeri casuali  

    int scelta = 0;
    int estratti[3];
    int soldiGuadagnati = 0;

    // -- -- -- -- -- -- -- -- -- -- -- -- --

    estratti[0] = rand() % 5;
    estratti[1] = rand() % 5;
    estratti[2] = rand() % 5;

    //verifica che il posto estratto non sia uguale a quello prima
    while (estratti[0] == estratti[1])
    {
        estratti[1] = rand() % 5;
    }

    while (estratti[1] == estratti[2] && estratti[0] == estratti[2])
    {
        estratti[2] = rand() % 5;
    }


    cout << "Scegli dove cercare i soldi: \n"
        << "1 - " << posti[estratti[0]] << "\n"
        << "2 - " << posti[estratti[1]] << "\n"
        << "3 - " << posti[estratti[2]] << "\n\n";

    cin >> scelta;

    if (scelta >= 4 || scelta < 1)
    {
        cout << "\nMah, hai perso quest' occasione >:(  \n";
        _getch();
        return;
    }

    soldiGuadagnati = rand() % 500;
    soldi += soldiGuadagnati;

    cout << "\nHai trovato " << soldiGuadagnati << " soldi! \n"
         << "Ora i tuoi soldi sono " << soldi << "\n"
         << "\nPremi un tasto per continuare... ";
    _getch();

}

void BlackJack(int& soldi)
{
    int scelta = 0;
    int somma = 0;
    int x = 0;              //add somma giocatore
    int sommaBanco = 0;
    int y = 0;              //add somma banco
    int puntata = 0;        //quanti soldi scommetti
    srand(time(NULL));      //Inizializzazione del generatore di numeri casuali  

    // -- -- -- -- -- -- -- -- 


    cout << "Quanti soldi scommetti? \nI tuoi soldi:" << soldi << "\n\n";
    cin >> puntata;

    if (puntata > soldi)
    {
        cout << "\nNon hai abbastanza soldi, Fuori di qui!!\n";
        _getch();
        return;
    }

    //stabilire le sommeiniziali di giocatore e banco

    somma += rand() % 9 + 1;     // si estrae un numero tra 1 e 10
    somma += rand() % 9 + 1;     // si estrae un altro numero tra 1 e 10

    sommaBanco += rand() % 9 + 1;     // si estrae un numero tra 1 e 10
    sommaBanco += rand() % 9 + 1;     // si estrae un altro numero tra 1 e 10

    //scelta se pescare o meno
    cout << "\nIl tuo punteggio attuale e': " << somma << " \n";
    cout << "Premi 0 se vuoi fermarti; \nPremi 1 se vuoi un'altra carta: \n\n" << endl;
    cin >> scelta;


    //se si pesca
    while (scelta == 1 && somma < 21)
    {
        x = rand() % 9 +1;
        y = rand() % 9 +1;
        cout << "\nCarta estratta: " << x << endl;

        somma += x; // Si somma il valore della carta estratta dal giocatore
        sommaBanco += y; // si somma il valore della carta estratta dal banco

        if (somma < 21)
        {
            cout << "\nIl tuo punteggio attuale e': " << somma << " \n";
            cout << "Premi 0 se vuoi fermarti; \nPremi 1 se vuoi un'altra carta: \n" << endl;
            cin >> scelta;
        }
    }


    //se non si pesca
    if (scelta == 0) // il giocatore decide di fermarsi prima del 21
    {
        cout << "\nIl tuo punteggio e': " << somma << endl;
        cout << "Il punteggio del banco e': " << sommaBanco << endl;

        if (somma > sommaBanco)
        {
            cout << "\nHai vinto: " << puntata << "s\n";
            soldi += puntata;
            cout << "I tuoi soldi sono ora: " << soldi << endl;
            cout << "Premi un tasto per continuare...";
            _getch();
        }
        else 
        {
            cout << "\nHai perso! \nIl banco si prende la tua puntata";
            soldi -= puntata;
            cout << "I tuoi soldi sono ora: " << soldi << endl;
            cout << "Premi un tasto per continuare...";
            _getch();
        }

    }


    //se la somma finale del giocatore è 21
    if (somma == 21)
    {
        cout << "\nBlack Jack!! \nHai vinto il doppio della puntata! ";
        soldi += 2 * puntata; 
        cout << "\nI tuoi soldi ora sono: " << soldi << endl;
        cout << "Premi un tasto per continuare...";
        _getch();
    }

    //se la somma del giocatore è maggiore di 21 o minore di quella del banco
    if (somma > 21 || somma < sommaBanco)
    {
        cout << "\nHai perso! \nIl banco si prende la tua puntata";
        soldi -= puntata;  
        cout << "\nI tuoi soldi sono ora: " << soldi << endl;
        cout << "Premi un tasto per continuare...";
        _getch();
    }

}

void Salvataggio(int* soldi, bool oggettiPosseduti[])
{

    // salva i progressi
} // TODO: Da fare

void Caricamento()
{
    //carica i dati
} // TODO: Da fare

OPZIONI ScriviOpzioni(string input)
{
    if (input == "Inventario") return INVENTARIO;
    if (input == "Negozio") return NEGOZIO;
    if (input == "Cerca") return CERCA;
    if (input == "BlackJack") return BLACKJACK;
    if (input == "Salvataggio") return SALVATAGGIO;
    return OPZIONI();
}
