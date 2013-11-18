 #!/bin/bash

#$1 es el nombre de tema
#$x numero 
#modificar directorio   `ls ../../../media/zev/Nuevo\ vol/TODO/` ../../../media/zev/Nuevo\ vol/TODO/$picture 
#poner en carpeta de open nlp  > ../../../media/zev/Nuevo\ vol/TODOtokenizer/$x
x=1
for picture in `ls TODO/`
do
   apache-opennlp-1.5.3/bin/opennlp SimpleTokenizer <  TODO/$picture  > TODOtokenizer/$x
   ((x=$x+1))
done
