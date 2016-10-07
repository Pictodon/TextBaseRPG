#VIKTIG INFORMATION!

Om ni vill göra en pause i spelet, använd INTE system("pause");

Skriv istället bara pause(); Det är en funktion som jag gjort för att snygga till det lite.

Samma sak gäller om ni ska printa text i konsollen. Använd printString("Texten ni ska skriva", false);

printString("", false/true);

Efter kommat kan det vara både false eller true, true om ni sätter en pause(); precis efter att den skrivit något
och false om ni inte gjort det.

Exempel:

1.

printString("This is some text with a pause directly afterwards", true);

pause();

2.

string name;

printString("Enter your name: ", false);

cin >> name;


**Användbara saker**

>**pause();**

>**printString("", false/true);**
