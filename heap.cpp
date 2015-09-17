#include <iostream>
#include <string>
//#include <conio.h>
#include <fstream>
#include <math.h>
#include <time.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

using namespace std ;
#define MAXDEGREE 25  

/*************   DATA STRUCTURES AND METHODS DECLARATION FOR BINOMIAL HEAP********/
struct bnode {                   /*Binomial Node"*/ 
       struct bnode *child ;
       struct bnode *next ;      /* Points to sibling */
       int degree ;
       int key ;
};

struct qnode {                  /* Queue node used for level printing*/
       struct bnode *item ; 
       struct qnode  *next ; 
};

struct bnode * binsert (struct bnode * root , int k) ; 
struct bnode * bremovemin(struct bnode * root) ;
struct bnode * bmerge(struct bnode *p1 , struct bnode *p2) ;
struct bnode * bpaircombine(struct bnode *p) ;
/****  These functions are used for level printing ****/
void benqueue(struct qnode **first, struct bnode * item) ;
struct bnode * bdequeue(struct qnode **first ) ;
bool bqempty(struct qnode *first) ;
void bprintlevel(struct bnode * root ) ;  

/********************************************************************************/

/********* DATA STRUCTURES AND FUNCTIONS DECLARATION FOR  LEFTIST HEAP **********/
struct lnode {                    /*  Leftist Node stucture*/
       struct lnode *left ; 
       struct lnode *right ;
       int key ;
       int s ;
} ;
void linsert (struct lnode **root , int k ) ;
int lfinds(struct lnode *item) ;
struct lnode * lmeld(struct lnode *root , struct lnode *item);
struct lnode * lmerge(struct lnode *h1 , struct lnode *h2  ) ;
struct lnode * lremovemin (struct lnode * root ) ;
/****    These three are used for level order printing ****/
void levelp (struct lnode *root ) ;
int height (struct lnode *root ) ;
void level (struct lnode *root , int i , int j) ;
/************ ****************************************************************/


int main (int argc,char* argv[]) 
{
	string s; 
	char* name;
    if(!strcmp(argv[1],"-il")) 								// input mode for leftist tree
      {
        struct lnode * lroot= NULL ;                       // lroot points  min element
		name=argv[2];
		ifstream fp (name);									
		if (fp.is_open())
		{
   			while(!fp.eof()) 
    		{
                getline(fp,s) ;
    			if(s[0]=='I')                                    
    			{
    				string sub=s.substr(2);
		    		int i=atoi(sub.c_str());          	
    		        linsert(&lroot, i);                    // if I : Insert operation
	   		    } else if(s[0]=='D') {
	   			    lroot = lremovemin(lroot);            //  if D : delete operation
                } else {
                   cout<<"file format not supported"<<endl; 
                   return 0;
	   		    }
    	    }
    	    fp.close();	
    	    levelp (lroot) ;                         
	  } else
     	cout<<"invalid file name"<<endl; 
  } else if(!strcmp(argv[1],"-ib"))	{								// input mode for binomial tree
		struct bnode * broot= NULL ;
		name=argv[2];
		ifstream fp (name);
		if (fp.is_open())
		{
   			while(!fp.eof()) 
    		{
                getline(fp,s) ;
    			if(s[0]=='I')
    			{
    				string sub=s.substr(2);
		    		int i=atoi(sub.c_str());	
    		        broot = binsert(broot, i);                      //Insert Operation 
	   		    } else if(s[0]=='D') {
	   			    broot = bremovemin(broot);                      //Remove Min operation
                } else {
                   cout<<"file format not supported"<<endl;
                   return 0;
	   		    }
    	    }
    	    fp.close();
		   bprintlevel(broot) ;
       } else 
	       cout<<"invalid file name"<<endl;
  } else if(!strcmp(argv[1],"-r"))										// checks if input is for random mode
  	{
  		{
  			cout<<"\ntime taken in Leftist to perform 5000 operations after initializing\n ";
  			cout <<"\n 1000 2000 3000 4000 5000 elements\n" ;
  			clock_t start,time;
			int a=1;
			while(a!=6)
			{
				start=clock();                                          //clock is started 
				struct lnode *lroot = NULL ;
				for(int i=0;i<(a*1000);i++)								// initialize the leftist tree with 1000,2000,3000,4000,5000 elements
				{	
					int x=rand() % 5000;
					linsert(&lroot,x);
				}
				for(int i=0;i<5000;i++)									// give an operation sequence of 5000 operations randomly
				{
					int d=rand() % 2;
					if(d==1)
					{
						lroot=lremovemin(lroot);
					}
					else
					{
						int x=rand() % 5000;
						linsert(&lroot,x);
					}	
				}
				cout<<"  " <<clock()-start<< "  ";                       //calculates the time taken 
				a++;
			}
		}
		
		{
			cout<<"\n\ntime taken in Binomial tree to perform 5000 operations after initializing \n";
			cout <<"\n 1000 2000 3000 4000 5000 elements\n" ;
			clock_t start,time;
			int a=1;
			while(a!=6)
			{
                int count =0 ;
                start=clock(); 
				struct bnode *broot = NULL ;
				for(int i=0;i<(a*2000);i++)									// initialize a binomial heap with 1000, 2000,3000, 4000,5000 elements
				{
		
					int x=rand() % 2000;
					broot = binsert(broot, x);
				}
				for(int i=0;i<5000;i++)										// provide an operation sequence of 5000 operations randomly
				{
					int d=rand() % 2;
					if(d==1)
					{
                            count++ ;
						broot = bremovemin(broot);
					}
					else
					{                   
						int x=rand() % 5000;
						broot= binsert(broot,x);
					}	
				}
			cout<<"  " <<clock()-start<< "  ";
			a++;
			}
  		}
   	}else
	     cout<<"invalid input"<<endl;
//	getch();
}

/**************** FUNCTIONS FOR LEFTIST TREE********************/

/************************************************************
Function : linsert

Parameters : root and the element to insert 

Description : Insets elements into leftist tree.If root is null,
              insert the element and point root to it. if root 
              is not NULL, create a new element and meld it with 
              the root tree.
              
**************************************************************/


void linsert(struct lnode **root, int k ) 
{  
            if (*root == NULL ) {                                // Empty leftist tres
                      struct lnode *item = new lnode ; 
                      *root = item; 
                      item->key = k ;
                      item->left = NULL ;
                      item->right = NULL ;
                      item->s = lfinds(item ) ;                  //finds s value
                     // item->s = 1 ; 
            } else {
                      struct lnode *item = new lnode ; 
                      item->key = k ;
                      item->left = NULL ;
                      item->right = NULL ;
                      item->s = lfinds(item ) ;
                      struct lnode *temp =lmeld((*root) , item  ) ;   // meld root and new element
                      *root =  temp; 
            }
}

int lfinds(struct lnode *item)                             // returns s value by calling itself recursively
{ 
    if(item == NULL ) { return 0 ;}
    
    int l = lfinds(item->left ) ;
    int r = lfinds(item->right)  ;
    
    if (l >= r) return l+1 ; 
    else return r ;
}  

/***************************************************************
Function : lmeld (struct lnode *h1 , struct lnode *h2  )

Parameters : two leftist nodes h1, h2 . 

Output :  returns pointer to new tree after melding of h1 and h2.

Description : melding of two leftist trees into one.
**************************************************************/

struct lnode * lmeld (struct lnode *h1 , struct lnode *h2  )
{
       if (h1== NULL ) return h2 ;
       if (h2== NULL ) return h1 ;
       if (h1->key <h2->key)  return lmerge (h1,h2) ;     
       else return(lmerge (h2,h1)) ; 
}

struct lnode * lmerge(struct lnode *h1 , struct lnode *h2  )
{      
       if (h1->left ==NULL ) { h1->left = h2; } 
       else {
            h1->right = lmeld(h1->right,h2) ;                    //key of h1 always less than that of h2
            if ( h1->left->s < h1->right->s ) {                 // if s of left < s of right tree swap left and right subtrees
                                struct lnode *temp = h1->left ;
                                h1->left = h1->right ;
                                h1->right = temp ;
            }
            h1->s= h1->right->s+1 ;
                
       }
       return h1 ; 
}
/***************************************************************
Function : lremovemin 

Parameters : pointer to the root node  

Output :  removes the root node and forms a new tree and reutrns 
           pointer pointing  to the root .

Description : Removes the min element from the leftist tree. 
              Seperates the left and right sub tree of root and
              meld them together.  
**************************************************************/
struct lnode * lremovemin (struct lnode * root )  
{ 
       if (root==NULL) {
           return 0 ;
       }
       struct lnode *l =  root->left ;
       struct lnode *r =  root->right ;
       delete root ;
       return (lmeld(l ,r )) ;                              // melding right and left sub tree              
}

/***************************************************************
Functions : Levelp : used for printing nodes in every level. 
            Level  : recursively call it self and prints the nodes
                     in a level .
            Height : gets the height of the tree .

Description : First Levelp gets the height from height function 
              and then for each level calls Level Function to print
              the nodes in a level. 
**************************************************************/

void levelp (struct lnode *root ) 
{ 
     int h = height (root ) ;  
     for (int i=1; i<=h; i++ ) {
         cout << "\n Level "<< i <<":"<< "[" ;
         level(root, i, i) ;
         cout <<"]" ;
     }
}

void level (struct lnode *root , int i , int j) 
{ 
     if (root == NULL) return ;
     if ( i==1)  {
          cout  << root->key << " " ;               // prints the element in the level
     }
     else if (i>1) {
           level (root->left, i-1,j) ;
           level (root->right, i-1,j) ;
     }

} 
int height (struct lnode *root ) 
{ 
    int lh , rh ;
    if (root == NULL )  return 0 ; 
    else { 
     lh = height(root->left) ;
     rh = height (root->right) ;
    
    if (lh > rh ) 
    { return (lh+1) ;}
    else 
    { return rh+1 ; }
    
    }
}
/**************END OF FUNCTIONS FOR LEFTIST TREE********************/


/****************FUNCTIONS FOR BINOMIAL HEAP ***********************/
/*******************************************************************
Function : Binsert

Paramets : pointer to root of binomial heap  and element to insert

Description : Insets elements into Binomial Heap.If root is null,
              insert the element and points root to it. if root 
              is not NULL, create a new element and add it to the
              circular list cointaing root element.
*******************************************************************/

struct bnode * binsert (struct bnode * root , int k) 
{
       struct bnode *item = new bnode ; 
       
       if (item == NULL ) { 
                cout << "\n Not enough memory to create a new node for min binomial heap " ; 
                return 0;
       }
       item->key =  k ;
       if (root== NULL ) {                          // if heap is empty
                  root = item ; 
                  root->next=root ;
                  root->child=NULL ;
                  root->degree= 0; 
       } else { 
               item->degree= 0;
               item->child =NULL ;
               struct bnode * temp ;
               temp = root->next ; 
               root->next= item ;  
               item->next = temp ;
               if (root->key > k ) {
                             root = item ;
               }
       }
       return root ;
}
/*******************************************************************
Functio  : bremovemin

Paramets : pointer to root of binomial heap 

Description : Removes the min element from the Binoial Heap.  if root 
              is the only element in its circular list, point root to 
              its child and do pairwise combine, if not  seperate the 
              children of root and merge  it with remaining heap.
*******************************************************************/

struct bnode * bremovemin(struct bnode * root) 
{ 
       if( root == NULL ) { 
           return 0 ;
       } 
       
       struct bnode * temp = root->next ; 
       if (temp == root ) {                                 //  if only root is in top circular list
               struct bnode * item =  root->child ;
               root = item ; 
               if (root ==NULL ) {                           // i.e root is the only element in the heap
                        delete temp ;
                        return 0;
               } 
               item =  bpaircombine(root) ; 
               delete temp ;
               return item ; } 
       else {  
             struct bnode *item = root->child ;
             root->key = temp->key ; 
             root->child = temp->child ;
             root->degree = temp->degree;
             root->next = temp->next ;
             item = bmerge(root , item ) ;                 // merge heap remaining after removing min nide with child tree of min node
             item = bpaircombine(item) ;                     
             delete temp ;
             return item ;
       }
             
}
/*******************************************************************
Functio  : bpaircombine

Description : Go through the elements in the circular list and  if two 
              tree have same degree, make the node with higher element 
              as child to other tree.
*******************************************************************/

struct bnode * bpaircombine(struct bnode *p)
{ 
       if (p ==NULL ) { 
        //     cout << " " ; 
             return 0 ;
       }
       struct bnode * pt[MAXDEGREE]= {0} ;                 // initialize table with 0 
       struct bnode * temp = p ; 
       
       while (temp->next!= p ) { 
             temp = temp->next ;
       }
       temp->next = NULL ;
       
       temp = p; 
        
       
       while(temp != NULL ) { 
                      struct bnode * non = temp ;
                      
                      if (temp->next!= NULL) {                // find the next item in the circular list
                                       struct bnode * b = temp->next ;
                                       temp->next= NULL ;
                                       temp = b ;
                      } else { 
                             temp = NULL ;
                      }
                               
                      int degree  = non->degree ;
                      
                      if( pt[degree] == NULL)  {                //if there is no tree with same degree make that table entry point to the tree
                          pt[degree] = non  ; 
                      } else {
                             
                         while (true ) {
                                    
                             struct bnode * p1 = pt[non->degree] ; 
                             if (p1->key <= non->key ) {                           // make non as p1 child  
                                         if(p1->child == NULL ) {                  // if p1 has no child
                                                      p1->child = non; 
                                                      non->next= non ;
                                                      pt[non->degree] = NULL;
                                                      p1->degree++;
                                         } else {                                      // if p1 has already child insert non to its childs circular linked list
                                                struct bnode *t= p1->child->next ;
                                                p1->child->next= non ;
                                                non->next= t ;
                                                pt[non->degree] = NULL;
                                                p1->degree++ ;                         // after combining degree incremented
                                         }
                                         non = p1 ; 
                                         if ( pt[non->degree] == NULL ) {             //after incrementing degree if there is tree with same degree combine with it
                                              pt[non->degree] = non ;
                                              break ;
                                         }  else { 
                                                 continue ;
                                         }
                             } else { 
                                    if(non->child == NULL ) {                         //if non is smaller , make p1 as its child
                                                      non->child = p1; 
                                                      p1->next= p1 ;
                                                      pt[non->degree] = NULL;
                                                      non->degree++;
                                         } else {                                     // if child is not null, insert p1 into nons circular list
                                                struct bnode *t= non->child->next ;
                                                non->child->next= p1 ;
                                                p1->next = t ;
                                                pt[non->degree] = NULL;
                                                non->degree++ ;
                                         }
                                         if ( pt[non->degree] == NULL ) { 
                                              pt[non->degree] = non ;
                                              break ;
                                         }  else { 
                                                 continue ;
                                         }
                             }
                             
                         }           
                      }
       }
                           
       struct bnode *min =NULL ;
       struct bnode *temp1 = NULL ; 
       struct bnode *temp2 = NULL ; 
       for ( int i=0 ; i<MAXDEGREE ; i++ ){                          //forming the top level circular list and finding the min element
            if (pt[i]!=NULL ) { 
                            if (temp1 == NULL ) {
                                     temp1 = pt[i] ;
                                     min = pt[i] ;
                                     temp2= pt[i]; 
                            } else { 
                                   temp2->next= pt[i] ; 
                                   temp2 = pt[i]; 
                                   if (pt[i]->key < min->key) { 
                                                  min = pt[i] ;
                                   }
                            }
            }
       }
            temp2->next=temp1 ;
            return min ;
}
    
/*******************************************************************
Functio  : Bmerge 

Description : gets two bnodes pointers to two trees as paramets and 
              merges them and reutns pointer pointing to the smallest
              element of those two.
*******************************************************************/                                                                                                      
       
struct bnode * bmerge(struct bnode *p1 , struct bnode *p2) 
{ 
       if ( p1== NULL ) { 
            return p2 ;
       } else if ( p2== NULL)  {
              return p1; 
       } else { 
              struct bnode * temp = p1->next ;
              p1->next= p2->next ;
              p2->next = temp ; 
              return p1 ; 
       }
}
/*******************************************************************
Functio  : bprintlevel  

Description : a new stucture  qnode is used to build a queue. it goes
              through each element in the level and prints it, if it
              has a child then that is pushed into queue, which can
              used to print elements in the next level.                                   
*******************************************************************/ 
void bprintlevel(struct bnode * root ) 
{ 
     if (root == NULL ) { 
              cout << "\n Empty Min Binomial Heap " ; 
              return  ;
     }  else {
             struct qnode *first = NULL ;            // a new sturct for maintaining queue
             struct bnode * temp = root ;
             struct bnode * temp1 = NULL ;
             int  current =1  ; 
             int next =0 ;
             int l=1 ;                              // level number 
             benqueue(&first , root ) ;
             while(!bqempty(first) ) {
                   cout<<"level "<<l<<" : [";	    				
                   while(current!=0)
                   {
                         temp= bdequeue(&first);			//dequeue from the queue						
				         current--;
				         temp1=temp;
				         do													
				         {
                               cout<<" "<< temp->key;       //print the elements in that level 
                               if(temp->child!=NULL)        //if it has child put it into queue 
                               {
                                   next++;									
                                   benqueue(&first,temp->child);
                               }
				               temp=temp->next;
                         }while(temp!=temp1);
                    }		
			        current=next;								
			        next=0;
			        cout<<" ]"<<endl;
		         	l++;
	          }
	}
}
/*******************************************************************
Function  : benqueue  

Description :  if the queue is empty, a new item is created and first
               is pointed to that item. Else it is inserted at the 
               end of queue                           
*******************************************************************/            
void  benqueue(struct qnode **first, struct bnode * item) 
{ 
     if (*first == NULL ) {
                struct qnode *temp = new qnode ;  
                temp->item = item ;
                temp->next = NULL ; 
                *first= temp ;
     } else { 
            struct qnode * temp = *first ; 
            while (temp->next!=NULL ) { 
                  temp= temp->next ; 
            }
            struct qnode *temp1 = new qnode ; 
            temp1->item =item ;
            temp1->next = NULL;
            temp->next = temp1 ; 
     }
}
/*******************************************************************
Function  : bdequeue  

Description :  removes the element from the beginning of the queue 
               and returns it.                         
*******************************************************************/ 

struct bnode * bdequeue(struct qnode **first ) 
{ 
     
     struct qnode * temp  = *first ;
     struct bnode *item =  temp->item ; 
     *first = (*first)->next ;
     delete temp ;
     return item ;
}
/*******************************************************************
Function  : bqempty  

Description :  checks whether the queue is empty or not.                         
*******************************************************************/           
bool bqempty(struct qnode *first) 
{
      if (first == NULL )
          return true; 
      return false ; 
}
         
/*****************END OF FUNCTIONS OF BINOMIAL HEAP****************/

     
     

                          
                           
                       


                            

          
           
    
    

