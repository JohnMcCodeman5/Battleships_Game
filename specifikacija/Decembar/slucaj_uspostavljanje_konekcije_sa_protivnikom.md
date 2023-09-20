# Uspostavljanje konekcije sa protivnikom

**Kratak opis**: Igrači šalju TCP zahtev za povezivanje na server nakon čega igrač klikom na dugme 'Započni igru' može pokrenuti partiju.


**Akteri**: Igrači


**Preduslovi**: Igrač je iz glavnog menija izabrao igranje multiplayer partije.


**Postuslovi**: Igrači su povezani na server i mogu da igraju partiju.


**Osnovni tok**:
1. Klijent šalje serveru TCP zahtev za povezivanje.
2. Server odobrava zahtev.
3. Uspostavlja se konekcija preko TCP protokola.

**Alternativni tokovi**:
-A1: Neuspela konekcija - otvara se prozor sa porukom o neuspeloj konekciji, i dugme koje omogućava ponovni pokušaj.

**Podtokovi**:

**Specijalni zahtevi**: Oba učesnika imaju pristup internetu, i imaju kod sebe klijent aplikaciju. Server aplikacija mora biti pokrenuta. 

**Dodatne infromacije**: /