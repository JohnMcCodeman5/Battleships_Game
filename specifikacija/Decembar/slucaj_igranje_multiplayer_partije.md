# Igranje multiplayer partije

**Kratak opis**:
Nakon što je uspostavljena konekcija dva igrača, započinje se igra. Igra traje dok dok jedan od igrača ne potopi sve protivnikove brodove, nakon čega se vrši upis rezultata i igračima se prikazuje glavni meni.

**Akteri**:
Dva igrača

**Preduslovi**:
Uspostavljena je konekcija između dva igrača.

**Postuslovi**:
Jedan igrač je pobedio, i igračima je prikazan glavni meni.

**Osnovni tok**:
1. Prelazi se na slučaj upotrebe 'Uspostavljanje konekcije sa protivnikom'.
2. Igrač započinje partiju pritiskom na dugme 'Započni igru'
3. Prelazi se na slučaj upotrebe 'Postavljanje brodova'
4. Prelazi se na slučaj upotrebe 'Borba'
5. Prelazi se na slučaj upotrebe 'Čuvanje rezultata'
6. Aplikacija prikazuje glavni meni

**Alternativni tokovi**:
-A1: Neočekivan izlaz iz aplikacije - Ukoliko neko od igrača izađe iz aplikacije pre nego što je igra završena, pobeda pripada suprotnom igraču.

**Podtokovi**:

**Specijalni zahtevi**:
Neophodno je da imamo tačno dva igrača koja su povezana na isti server.

**Dodatne infromacije**: /
