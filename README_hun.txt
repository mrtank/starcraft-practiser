A program célja segíteni az automatikus gyorsbillentyű szekvenciák rögzítését. Például a gyártósoron való végig "zongorázást".
A felhasználó maga adhatja meg, hogy milyen billentyű sorozatot szeretne gyakorolni.
Ezt egy .pra kiterjesztésű fájlba írja le.
A fájl szavakból áll, aminek az első betűje, hogy hányszor szeretnénk lenyomni a gombot, a második betűje maga a gomb, vagy a módosító karakter, és utána a gomb.
Példák:
    1a -> 1 darab a gomb
    1^a -> 1 darab control a gomb
    2ss -> 2 darab shift s gomb
    1^s1 -> 1 darab control shift 1-es gomb
    2putty -> 2 darab kattintás

A Load file gombal töltjük be a gyakorló fájlunkat (a terran.pra egy példa gyakorló fájl terrannak.), és az endlessly checkbox jelzi, hogy végtelenítve gyakorlunk-e.
Ha végtelenítve gyakorlunk nem ér véget a program futása ha egyszer végig "zongoráztunk" a billentyűkön, hanem addig fut a program, amíg nem nyomunk egy esc billentyűt.

Programozási nyelv : Qt.
Készítette : Garai Márton
