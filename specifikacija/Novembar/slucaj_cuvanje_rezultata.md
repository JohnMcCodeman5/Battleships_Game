# Čuvanje rezultata

**Kratak opis:** Nakon završetka partije, u zavisnosti od ostvarenog broja poena, aplikacija nudi mogućnost korisniku da ukuca svoje ime i sačuva rezultat u tabeli najboljih rezultata

**Akteri:** Igrač-upisuje svoje ime nakon završetka partije

**Preduslovi:** Aplikacija je pokrenuta i igrač je završio partiju

**Postuslovi:** Informacije o partiji su trajno sačuvane

**Osnovni tok:**

1. Igrač je završio partiju
2. Nakon završene partije aplikacija proverava da li je uslov ispunjen (broj osvojenih bodova je veći od najmanjeg broja bodova u tabeli rezultata) <br />
	1. Ako je uslov ispunjen prikazuje se prozor za unos imena <br />
    	1. Igrač unosi svoje ime <br />
    	2. Aplikacija čuva ime igrača i broj bodova  <br />
	2. Ako uslov nije ispunjen prelazi se na korak 3 <br />
3. Aplikacija prikazuje glavni meni

**Alternativni tokovi:** Neočekivani izlaz iz aplikacije. Ako u bilo kom korkau korisnik isključi aplikaciju, sve eventualno zapamćene informacije o trenutnoj partiji igre se poništavaju i aplikacija završava rad. Slučaj upotrebe se završava

**Podtokovi:** /

**Specijalni zahtevi:** /

**Dodatne informacije:** Tokom trajanja partije, aplikacija pamti broj osvojenih bodova igrača
