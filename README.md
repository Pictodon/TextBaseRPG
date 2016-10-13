#Backups done:
>07-10/2016

>08-10/2016 14:24

>09-10/2016 01:40

>09-10/2016 16:43

>09-13/2016 19:27

#VIKTIG INFORMATION!

Om ni vill göra en pause i spelet, använd INTE system("pause");

Skriv istället bara pause(); Det är en funktion som jag gjort för att snygga till det lite.

Samma sak gäller om ni ska printa text i konsollen. Använd printString("Texten ni ska skriva");

För console in(cin) bör även inputSign(); läggas precis ovanför cin som visas i exemplet nedan.

Exempel:

string input;

printString("Enter an input:");

inputSign();

cin >> input;

printString(input);

Detta ger resultatet:

     Enter an input:

       > String

        String

Där andra "String" är vad som skrivs i konsollen av programmet


**Användbara saker**

>**pause();**

>**printString("");**

>**instantPrint("");**

>**printStringColor(0-16, "", 0-16, "", 0-16, "", 0-16, "", false/true true is instant text);**

>**setTextColor(0-16'16=rainbow text');**

>**inputSign();**
