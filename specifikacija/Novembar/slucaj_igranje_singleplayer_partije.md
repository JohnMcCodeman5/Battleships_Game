# **Igranje single player partije:**

**Akteri:** 
Igrač<br />

**Preduslovi:** Aplikacija je pokrenuta i otvoren je glavni meni<br />
**Postuslovi:** Aplikacija vraća igrača u glavni meni<br />

**Glavni tok**:
1. Igrač iz glavnog menija se bira dugme za pokretanje Single Player partije.
2. Igraču se omogućava da podesi težinu partije biranjem jedne od ponuđenih opcija nakon što se otvara
meni za podešavanje težine.<br />
	<ul>
    2.1 Biranjem težine "Easy", računar će igrati jednostavnije.<br />
    2.2 Biranjem težine "Hard", računar će igrati zahtevnije poteze protiv igrača.<br />
    	</ul>
3. Igrač pokreće partiju, prelazi se na slučaj upotrebe "Postavljanje brodova".
4. Igrač nakon postavljanja brodova, prelazi se na slučaj upotrebe "Borba".
5. Kada se partija završi, prelazi se na slučaj upotrebe "Čuvanje rezultata".
6. Aplikacija prikazuje glavni meni.

**Alternativni tokovi:**<br />
- A1: Neocekivan izlazak iz aplikacije. Pritiskom na taster escape, pauzira se trenutna faza aplikacije i dobijamo meni za rad koji nam
nudi dva dugmeta da jedno nam omogućava da nastavimo partiju, drugo dugme nam dozvoljava da izađemo na glavni meni.<br />

**Podtokovi:/**<br />

**Specijalni zahtevi:**<br />
 Igrač mora da poseduje klijent aplikacije.<br />
