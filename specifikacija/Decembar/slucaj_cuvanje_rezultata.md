# Čuvanje rezultata

**Kratak opis:** Nakon završetka partije, aplikacija nudi mogućnost korisniku da ukuca svoje ime i sačuva rezultat u tabeli najboljih rezultata.

**Akteri:** Igrač-upisuje svoje ime nakon završetka partije.

**Preduslovi:** Aplikacija je pokrenuta i igrač je završio partiju.

**Postuslovi:** Informacije o partiji su trajno sačuvane.

**Osnovni tok:**

1. Igrač je završio partiju.
2. Nakon završene partije aplikacija prikazuje prozor za unos imena. <br />
    1. Igrač unosi svoje ime. <br />
    2. Aplikacija čuva ime igrača i broj bodova.  <br />
3. Aplikacija prikazuje glavni meni.

**Alternativni tokovi:** 
-A1: Neočekivani izlaz iz aplikacije. Ako u bilo kom koraku korisnik isključi aplikaciju, sve eventualno zapamćene informacije o trenutnoj partiji igre se poništavaju i aplikacija završava rad. Slučaj upotrebe se završava.

**Podtokovi:** /

**Specijalni zahtevi:** /

**Dodatne informacije:** Tokom trajanja partije, aplikacija pamti broj osvojenih bodova igrača.
