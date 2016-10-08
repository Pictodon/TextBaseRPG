#Back up done
>08-10-2016
>08-10-2016

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

\> String

String

Där andra "String" är vad som skrivs i konsollen av programmet


**Användbara saker**

>**pause();**

>**printString("");**

>**inputSign();**
