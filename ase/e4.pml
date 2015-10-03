/* Exercise 4	
  spin -a e4.pml
  gcc -DSAFETY pan.c -o pan
  ./pan
*/


chan print_possible = [0] of { bool };

byte printer = 0;



proctype user(byte id){
do
:: atomic {
   if 
   :: print_possible ? 1 -> printer ++;
		            printf("user %d is printing\n", id);
		            printer --;
			    print_possible ! 1					   								
   fi
   }
od								
}


init { 

          
     run user(0);
     run user(1);

     print_possible ! 1
}
     
    

active proctype verifier(){
       assert (printer <= 1)
}

