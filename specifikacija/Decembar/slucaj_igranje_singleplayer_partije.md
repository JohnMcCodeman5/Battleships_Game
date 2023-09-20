# **Igranje single player partije:**

**Kratak opis:**
Igrač iz glavnog menija bira igranje singleplayer partije. Nakon toga treba da izabere težinu bota. Igra traje dok igrač ili bot ne potopi sve protivnikove brodove, nakon čega se vrši upis rezultata, pa se igraču prikazuje glavni meni.

**Akteri:** 
Igrač<br />

**Preduslovi:** Aplikacija je pokrenuta i otvoren je glavni meni<br />
**Postuslovi:** Aplikacija vraća igrača u glavni meni<br />

**Glavni tok**:
1. Igrač iz glavnog menija bira dugme za pokretanje Single Player partije.
2. Igraču se omogućava da podesi težinu partije.<br />
	<ul>
    2.1 Biranjem težine "Easy", računar će igrati jednostavnije.<br />
    2.2 Biranjem težine "Hard", računar će igrati zahtevnije poteze protiv igrača.<br />
    	</ul>
3. Igrač pokreće partiju, prelazi se na slučaj upotrebe "Postavljanje brodova".
4. Prelazi se na slučaj upotrebe "Borba".
5. Kada se partija završi, prelazi se na slučaj upotrebe "Čuvanje rezultata".
6. Aplikacija prikazuje glavni meni.

**Alternativni tokovi:**<br />
- A1: Neocekivan izlazak iz aplikacije. Partija se prekida.<br />

**Podtokovi:/**<br />
/

**Specijalni zahtevi:**<br />
 /
