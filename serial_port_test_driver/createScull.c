#include"header.h"
#include"declaration.h"

Qset* createScull(int noi,int noq)
{
    Qset *lsqset=NULL;
    Qset *tempqset=NULL;
    int i=0,j,count=0;
    
    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
    
    for(i=0;i<noi;i++)
     {
                
              tempqset=(Qset*)kmalloc(sizeof(Qset),GFP_KERNEL);
              if(!tempqset)
               {
    		#ifdef DEBUG
    		printk(KERN_INFO "kmalloc:\n");
    		#endif
                goto ERR;
               }
                
               if(i==0)
                 lsqset=tempqset;
               if(i!=noi-1)
                 tempqset=tempqset->next;  
     }    
     
      tempqset=memset(tempqset,'\0',sizeof(Qset));    
      tempqset=lsqset;

      for(i=0;i<noi;i++)
       {
                
                tempqset->data=kmalloc(register_no*sizeof(char*),GFP_KERNEL); 
    		
              if(!(tempqset->data))
               {
    	        #ifdef DEBUG
    		printk(KERN_INFO "kmalloc:\n");
    		#endif
                goto ERR;
               }
               
                memset(tempqset->data,'\0',register_no*sizeof(char*));
                 
                 for(j=0;j<register_no;j++)
                  {                        
              		tempqset->data[j]=(char*)kmalloc(register_size*sizeof(char),GFP_KERNEL); 
              		if(!(tempqset->data[j]))
              		 {
    	        	  #ifdef DEBUG
    			  printk(KERN_INFO "kmalloc:\n");
    		          #endif
                          goto ERR;
                         }
                           memset(tempqset->data[j],'\0',register_size*sizeof(char));

                     count++;
                     if(count==noq)
                     break;
                   }
  
               tempqset=tempqset->next;
        }
        
         tempqset=lsqset;
                
               while(tempqset)
               {
                 #ifdef DEBUG
    		 printk(KERN_INFO "node address %p\n",tempqset);
    		 #endif
                 tempqset=tempqset->next;     
               } 
          
    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif
    return lsqset;

    ERR:  

    #ifdef DEBUG
    printk(KERN_INFO "%s :End with error\n",__func__);
    #endif
    return (Qset*)-1;
}

