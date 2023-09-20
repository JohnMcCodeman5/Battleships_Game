# Postavljanje brodova
**Kratak opis** : Igrac bira neki od brodova (ili potencijalno mina) koji se nalaze pored table i postavlja ih na pozicije za koje on 
smatra da bi bilo dobro, a postoji i opcija da te pozicije izabere random algoritam.

**Akteri**:
Igrac - bira pozicije brodova i mina

**Preduslovi**: Igra je pokrenuta i jedan igrac moze biti racunar ili moze biti dva igraca

**Postuslovi**: Pozicije brodova i mina su sacuvane i iscrtane

**Osnovni tok**: 


1. Igrac postavlja ukupno 5 brodova i potencijalno 2 mine
2. Prikazuje se prozor sa tablom, iscrtanim brodovima i dugmetom za automatsko biranje pozicija brodova i opcijom za dodavanje mina:<br />
	1. (2.1)Ukoliko je igrac izabrao da doda mine: <br />
		1. (2.1.1)Aplikacija iscrtava mine ispod brodova<br />
		2. (2.1.2)Prelazi se na korak 2.2 <br />
	2. (2.2)Ukoliko je igrac izabrao automatsko biranje brodova: <br />
		1. (2.2.1)Aplikacija bira pozicije za brodove(i mine) random algoritmom <br />
		2. (2.2.2)Prelazi se na korak 2.3 <br />
	3. (2.3)Igrac rucno postavlja brodove:<br />
		1. (2.3.1)Igrac bira brod ili minu koji ce postaviti<br />
		2. (2.3.2)Igrac bira poziciju koju ce postaviti<br />
		3. (2.3.3)Igrac bira rotaciju broda<br />
		4. (2.3.4)Prelazi se na korak 2.4 <br />
	4. (2.4)Igrac klikom na dugme pokusava da zapocne partiju sa trenutnim pozicijama brodova i mina<br />	
		1. (2.4.1)Prelazi se na korak 2.5 <br />
	5. (2.5)Aplikacija proverava da li su svi brodovi i mine postavljeni i da li ima kolizija<br />
		1. (2.5.1)Ukoliko uslovi nisu ispunjeni <br />
				1. (2.5.1.1)Aplikacija obavestava igrača o grešci i ispisuje detalje <br />
				2. (2.5.1.2)Prelazi se na korak 2.3				<br />
		2. (2.5.2)Ukoliko uslovi jesu ispunjeni<br />
			1. (2.5.2.1)Potrebno je zapamtiti sva polja na kojima se sada nalazi brod ili mina na osnovu pocetne pozicije, duzine i rotacije <br />
			2. (2.5.2.2)Informacije o pozicijama se prenose tabli <br />
3. Prelazi se na slucaj upotrebe 'Borba'<br />

**Alternativni tokovi**:
	A1: Neocekivani izlaz iz aplikacije.
	Igrac moze u bilo kom trenutku iskljuciti aplikaciju, tako da bi u ovom slucaju
	svi zapamceni podaci o pozicijama brodova, njihovim rotacijama i pozicijama mina bivaju izbrisani.

	
**Podtokovi:/**<br />	


**Dodatne informacije**:
	Tokom biranja pozicija brodova, aplikacija pamti informacije o brodu, njegovoj poziciji i rotaciji koju
	je igrac postavio, kao i o pozicije mina. 
		


