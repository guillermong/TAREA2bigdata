 #!/bin/bash
 
 cont=0
 #for picture in `ls -S -r TODO/`

 for picture in `ls TODO/`
 do
 ((cont=$cont+1))
 mv TODO/$picture TODO/$cont
 done


sudo shutdown -h now
