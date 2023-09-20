# Postavljanje brodova
**Kratak opis** : Igrac bira neki od pet brodova koji se nalaze pored table i postavlja ih na pozicije za koje on 
smatra da bi bilo dobro, a postoji i opcija da te pozicije izabere random algoritam.

**Akteri**:
Igrac - bira pozicije brodova

**Preduslovi**: Igra je pokrenuta i jedan igrac moze biti racunar ili moze biti dva igraca.

**Postuslovi**: Pozicije brodova su sacuvane 

**Osnovni tok**: 


1. Igrac postavlja ukupno 5 brodova
2. Prikazuje se dijalog sa dve opcije za automatsko biranje pozicija brodova ili rucno postavljanje brodova:<br />
	1. (2.1)Ukoliko je igrac izabrao automatsko biranje brodova: <br />
		1. (2.1.1)Aplikacija bira pozicije za brodove random algoritm <br />
		2. (2.1.2)Prelazi se na korak 3 <br />
	2. (2.2)Ukoliko je igrac izabrao rucno postavljanje brodova:<br />
		1. (2.2.1)Igrac bira brod koji ce postaviti<br />
		2. (2.2.2)Igrac bira poziciju koju ce postaviti<br />
		3. (2.2.3)Igrac bira rotaciju broda<br />
		4. (2.2.4)Prelazi se na korak 2.3 <br />
	3. (2.3)Aplikacija proverava da li je validna pozicija za postavljanje broda<br />
		1. (2.3.1)Ukoliko nije validna <br />
				1. (2.3.1.1)Aplikacija obavestava igrača o grešci<br />
				2. (2.3.1.2)Prelazi se na korak 2.2 sa istim brodom kao i ranije				<br />
		2. (2.3.2)Ukoliko jeste validna<br />
			1. (2.3.2.1)Smanjuje se broj preostalih brodova<br />
			2. (2.3.2.2)Potrebno je zapamtiti sva polja na kojima se sada nalazi brod na osnovu pocetne pozicije broda, njegove duzine i rotacije.<br />
		3. (2.3.3)Proverava se broj preostalih brodova<br />
			1. (2.3.3.1)Ukoliko je to nula, onda se prelazi na korak 3 <br />
			2. (2.3.3.2)Ukoliko je to broj veci od nule, prelazi se na korak 2.2.1<br />
3. Aplikacija prikazuje 'konacan rezultat' svih pozicija i pita korisnika da li bi zeleo da ponovi biranje<br />
	1. (3.1)Ukoliko korisnik zeli da ponovi biranje prelazi se na korak 2<br />
	2. (3.2)Ukoliko korisnik ne zeli da ponovi biranje prelazi se na korak 4<br />
4. Prelazi se na slucaj upotrebe 'Borba'<br />

**Alternativni tokovi**:
	A1: Neocekivani izlaz iz aplikacije.
	Igrac moze u bilo kom trenutku iskljuciti aplikaciju, tako da bi u ovom slucaju
	sve zapamcene podatke o pozicijama brodova, njihovim rotacijama i tipu trebalo izbrisati.

**Dodatne informacije**:
	Tokom biranja pozicija brodova, aplikacija pamti informacije o tipu broda, njegovoj poziciji i rotaciji koju
	je igrac postavio. 
		

