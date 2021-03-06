#! /bin/bash

echo "--------------------CHARACTER_DRIVER------------------------"

for file in $(ls *.h) $(ls *.c)
do
    ci $file
done

for file in $(ls *.c,v) $(ls *h,v)
do
    co $file
done

checkout()
{  
        edit     
}

edit()
{
       read -p "Do you want to edit further y/n:"
       	   
             if [ "$REPLY" = "y" ]
         
         	then 
                
		for file in $(ls *.h,v)
	 	do
    	   	co -l $file
	 	done

		for file in $(ls *.c,v)
	 	do
    	   	co -l $file
	 	done
             fi
}

remove()
{
    read -p "Do you want to remove the driver y/n:"
     if [ "$REPLY" = "y" ]
      then 
           rmmod mylkm
           lsmod
           read
           dmesg
           read
           cat /proc/modules
           read
           cat /proc/devices
           
           rm myDev

          checkout

        else

          checkout
      fi
}
  
if ( make )
 then 
      read -p "Do you want to insert the driver y/n:"
      
      if [ "$REPLY" = "y" ]
        then 
             insmod ./modules/mylkm.ko
             lsmod
             read
             dmesg
             read
             cat /proc/modules
             read
             cat /proc/devices
             
             echo "Enter majorno"
             read majorno
           
              read -p "Do you want to test driver through application y/n:"
      
                 if [ "$REPLY" = "y" ]
                  then 
                      if ( make -C $(pwd)/application )
                        then       
                        
                           mknod ./myDev c $majorno 0
			   chmod 777 myDev
                           cd $(pwd)/application
                           ./app 
                           cd ..
                           remove
                        else
                          checkout
                      fi
                   
                  else
                    checkout 
                 fi    
         else
    
             checkout
        fi     
  else
           checkout  
fi
