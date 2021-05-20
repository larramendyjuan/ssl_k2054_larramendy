#Ejercicio 2
#Punto A
sed 's/\. /\.\n/g' breve_historia.txt > punto_a.txt
#Punto B
sed '/^\s*$/d' breve_historia.txt
#Punto C
sed 's/\. /\.\n/g' breve_historia.txt | sed '/^\s*$/d' > breve_historia_2.txt
#Punto D
grep -i 'guerra' breve_historia.txt
#Punto E
grep -E '^A.*(s|s\.)$' breve_historia.txt
#Punto F
grep -c 'peronismo' breve_historia.txt
#Punto G
grep -c -E '(Sarmiento.*Rosas|Rosas.*Sarmiento)' breve_historia.txt
#Punto H
grep -E '1900|18[0-9][1-9]' breve_historia.txt
#Punto I
sed 's/^[^ ]* //g' breve_historia.txt
#Punto J
ls carpeta | grep -E '*\.txt'