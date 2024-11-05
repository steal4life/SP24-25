#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba {
    char ime[50];
    char prezime[50];
    int godina_rodjenja;
    struct osoba* next;
} Osoba;

Osoba* nova_osoba(const char* ime, const char* prezime, int godina_rodjenja) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
    if (!nova) {
        printf("Greska u alociranju memorije.\n");
        return NULL;
    }
    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina_rodjenja = godina_rodjenja;
    nova->next = NULL;
    return nova;
}

void dodaj_na_pocetak(Osoba** head, const char* ime, const char* prezime, int godina_rodjenja) {
    Osoba* nova = nova_osoba(ime, prezime, godina_rodjenja);
    nova->next = *head;
    *head = nova;
}

void ispisi_listu(Osoba* head) {
    Osoba* trenutna = head;
    while (trenutna != NULL) {
        printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n", trenutna->ime, trenutna->prezime, trenutna->godina_rodjenja);
        trenutna = trenutna->next;
    }
}

void dodaj_na_kraj(Osoba** head, const char* ime, const char* prezime, int godina_rodjenja) {
    Osoba* nova = nova_osoba(ime, prezime, godina_rodjenja);
    if (*head == NULL) {
        *head = nova;
        return;
    }
    Osoba* trenutna = *head;
    while (trenutna->next != NULL) {
        trenutna = trenutna->next;
    }
    trenutna->next = nova;
}

void dodaj_iza(Osoba* head, const char* prezime, const char* ime_nove, const char* prezime_nove, int godina_rodenja_nove) {
    Osoba* trenutna = head;

    while (trenutna != NULL && strcmp(trenutna->prezime, prezime) != 0) {
        trenutna = trenutna->next;
    }

    if (trenutna == NULL) {
        printf("Osoba sa prezimenom '%s' nije pronađena.\n", prezime);
        return;
    }

    Osoba* nova_osoba = nova_osoba2(ime_nove, prezime_nove, godina_rodenja_nove);
    if (nova_osoba == NULL) {
        return;
    }

    nova_osoba->next = trenutna->next;
    trenutna->next = nova_osoba;

    printf("Nova osoba dodana iza osobe s prezimenom '%s'.\n", prezime);
}

Osoba* pronadji_po_prezimenu(Osoba* head, const char* prezime) {
    Osoba* trenutna = head;
    while (trenutna != NULL) {
        if (strcmp(trenutna->prezime, prezime) == 0) {
            return trenutna;
        }
        trenutna = trenutna->next;
    }
    return NULL;
}

void obrisi_element(Osoba** head, const char* prezime) {
    Osoba* trenutna = *head;
    Osoba* prethodna = NULL;
    
    while (trenutna != NULL && strcmp(trenutna->prezime, prezime) != 0) {
        prethodna = trenutna;
        trenutna = trenutna->next;
    }
    
    if (trenutna == NULL) {
        printf("Osoba s prezimenom %s nije pronadena.\n", prezime);
        return;
    }
    
    if (prethodna == NULL) {
        *head = trenutna->next;
    } else {
        prethodna->next = trenutna->next;
    }
    
    free(trenutna);
    printf("Osoba s prezimenom %s je obrisana iz liste.\n", prezime);
}

int main() {
    Osoba* lista = NULL;
    
    dodaj_na_pocetak(&lista, "Ana", "Anic", 1990);
    dodaj_na_kraj(&lista, "Marko", "Maric", 1985);
    dodaj_na_pocetak(&lista, "Ivan", "Ivic", 1992);

    printf("Ispis liste:\n");
    ispisi_listu(lista);
    
    printf("\nTrazenje osobe s prezimenom 'Maric':\n");
    Osoba* pronadjena = pronadji_po_prezimenu(lista, "Maric");
    if (pronadjena) {
        printf("Pronadena osoba: %s %s, %d\n", pronadjena->ime, pronadjena->prezime, pronadjena->godina_rodjenja);
    } else {
        printf("Osoba nije pronadena.\n");
    }

    dodaj_iza(lista, "Anic", "Luka", "Lukic", 1993);
    
    printf("\nBrisanje osobe s prezimenom 'Anic':\n");
    obrisi_element(&lista, "Anic");
    
    printf("\nIspis liste nakon brisanja:\n");
    ispisi_listu(lista);
    
    return 0;
}
