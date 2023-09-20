# Naziv: "Borba"

*Kratak opis:* Igrač bira polje na tabli koje želi da napadne.
 Ukoliko se brod nalazi iza te pozicije, igrač ima pravo da ponovo igra, sve dok ne promaši.
Nakon promašaja, protivnik je na potezu.
Protivnik može biti igrač ili računar.

*Akteri:*
Igrač

*Preduslovi:*
Igra je pokrenuta i igrač je odabrao pozicije za brodove.

*Osnovni tok:*
1. Igrač je na potezu za napad.
2. Aplikacija prikazuje tablu.
3. Igrač bira polje i aplikacija kreira novi potez.
4. Aplikacija kreira napad. 
5. Aplikacija izvršava napad. 
6. Aplikacija proverava status pozicije na koju je izvršen napad. <br />
	1. Ukoliko protivnički brod nije pogođen, protivnik je na potezu. <br />
	2. Ukoliko je protivnički brod pogođen, igrač je u mogućnosti da igra još jedan potez i uvećavaju se poeni <br />
        	1. Aplikacija računa poene. <br />
        	2. Aplikacija uvećava tekuće poene za izračunati broj dobitnih poena. <br />
        	3. Ukoliko protivnik ima još brodova na tabli prelazi se na 1. <br />
        	4. Ukoliko protivnik nema brodova na tabli, igrač je pobedio <br /> 
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. Prikazuje se konačan rezultat i prelazi se na slučaj upotrebe Čuvanje rezultata. <br />
			    
*Alternativni tokovi:*<br />
    Ime: Neočekivani prekid rada aplikacije <br />
        Opis: Ukoliko dođe do neočekivanog izlaza iz aplikacije, sva podešavanja i rezultat se poništavaju i aplikacija završava rad.
              Slučaj upotrebe se prekida.

*Dodatne informacije:*
