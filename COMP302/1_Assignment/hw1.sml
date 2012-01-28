(* HOMEWORK 1 : COMP 302 Winter 2012
  
   PLEASE NOTE:  

   * All code files must be submitted electronically
     BEFORE class on 27 January, 2012

  *  The submitted file name must be hw2.sml 

  *  Your program must type-check and run usig 
     Standard ML of New Jersey v110.55.
*)

exception NotImplemented
exception Fail of string

(* ------------------------------------------------------------*)
(* QUESTION 1 : WARM-UP                                        *)
(* ------------------------------------------------------------*)
(* Q1 A: Average                                               *)

(* average: int list -> real 

 The function takes a list of integers and returns
 their average as a real number
*)
fun average list =  raise NotImplemented;

(*
Test cases:

average [1, 5, 2, 7];

average [13, 25, 22, 27]; 

average [1, 5, 2, 7];

average [13, 25, 22, 27]; 
*)
(* -------------------------------------------------------------*)
(* Q1 B:  Standard Deviation                                    *) 
(* -------------------------------------------------------------*)

(* stDev: int list -> real 

 The function takes a list of integers and returns their
 the standard deviation as a real number
*)


fun square (x:real) = x * x ;

fun stDev l =   raise notImplemented 
;

(*
Test cases:

stDev [1, 5, 2, 7];

stDev [13, 25, 22, 27];
*)


(* ------------------------------------------------------------*)
(* QUESTION 2  (10 points)                                     *)
(* ------------------------------------------------------------*)

(* Partial sums :

   Given a list of integers, compute the partial sums 
   i.e. the sums of all the prefixes

   psum: int list -> int list

*)

fun psum(l) = raise notImplemented


(* Some test cases 
- psum [1,1,1,1,1];
val it = [1,2,3,4,5] : int list

- psum [1,2,3,4];
val it = [1,3,6,10] : int list

- psum [];
val it = [] : int list

- psum [9];
val it = [9] : int list

*)


(* ------------------------------------------------------------*)
(* QUESTION 3 Balanced Binary Search Trees (70 points)         *)
(* ------------------------------------------------------------*)

datatype 'a bstree =
   Empty
 | Node of (int * 'a) * 'a bstree * 'a bstree;

(* Invariant: The integer keys are in inorder *)

(* ------------------------------------------------------------*)
(* QUESTION 3.1 : Check if tree is balanced  (10 points)          *)
(* ------------------------------------------------------------*)

fun balanced (t) = raise NotImplemented

(* ------------------------------------------------------------*)
(* QUESTION 3.2 : Rotations on sub-trees (20 points)            *)
(* ------------------------------------------------------------*)

(* Q 3.2 : Rotations (12 points) *)
fun rotLeft (Node(v, Node (vl, LL, LR), R)) = 
  raise NotImplemented

fun rotLeftRight (Node (v, Node (vl, LL, Node (vlr, LRL, LRR)), R)) = 
  raise NotImplemented

fun rotRight (Node(v, L, Node (vr, RL, RR))) = 
  raise NotImplemented

fun rotRightLeft (Node (v, L, Node (vr, Node (vrl, RLL, RLR), RR))) = 
raise NotImplemented


(* Q 3.2 : Rotations (8 points) *)
fun balance(n as Node(_, l, r)) = raise NotImplemented

(* ------------------------------------------------------------*)
(* QUESTION 1.3 : Insertion into an AVL tree (15 points)       *)
(* ------------------------------------------------------------*)


fun insert (d , t) = raise NotImplemented

(* ------------------------------------------------------------*)
(* QUESTION 1.3 : Deletion into an AVL tree (25 points)        *)
(* ------------------------------------------------------------*)

(* delMin (10 points) *)
fun delMin Empty = raise Fail "impossible"
  | delMin (t) = raise NotImplemented

(* delete (15 points) *)
fun delete (n, Empty) = raise Fail "value not in the tree"
  | delete (n, t) = raise NotImplemented
	  
(* ------------------------------------------------------------*)
(* Some test cases                                             *)
(* ------------------------------------------------------------*)
(*
- val t1 = insert ((3, "foo") , Empty );
val t1 = Node ((3,"foo"),Empty,Empty) : string bstree

- val t2 = insert ((2, "soo") , t1);
val t2 = Node ((3,"foo"),Node ((2,"soo"),Empty,Empty),Empty) : string bstree

- val t3 = insert ((1, "too") , t2);
val t3 =
  Node ((2,"soo"),Node ((1,"too"),Empty,Empty),Node ((3,"foo"),Empty,Empty))
  : string bstree

- val t4 = insert ((9, "sob"), t3);
val t4 =
  Node
    ((2,"soo"),Node ((1,"too"),Empty,Empty),
     Node ((3,"foo"),Empty,Node ((9,"sob"),Empty,Empty))) : string bstree

- val t5 = insert ((5, "bob"), t4); 
val t5 =
  Node
    ((2,"soo"),Node ((1,"too"),Empty,Empty),
     Node
       ((5,"bob"),Node ((3,"foo"),Empty,Empty),Node ((9,"sob"),Empty,Empty)))
  : string bstree

- val t6 = insert ((6, "top"), t5); 
val t6 =
  Node
    ((5,"bob"),
     Node
       ((2,"soo"),Node ((1,"too"),Empty,Empty),Node ((3,"foo"),Empty,Empty)),
     Node ((9,"sob"),Node ((6,"top"),Empty,Empty),Empty)) : string bstree

- val t7 = insert ((7,"beeb"), t6);
val t7 =
  Node
    ((5,"bob"),
     Node
       ((2,"soo"),Node ((1,"too"),Empty,Empty),Node ((3,"foo"),Empty,Empty)),
     Node
       ((7,"beeb"),Node ((6,"top"),Empty,Empty),Node ((9,"sob"),Empty,Empty)))
  : string bstree

val t6 = insert ((6, "top"), t5); 
val t6 =
  Node
    ((5,"bob"),
     Node
       ((2,"soo"),Node ((1,"too"),Empty,Empty),Node ((3,"foo"),Empty,Empty)),
     Node ((9,"sob"),Node ((6,"top"),Empty,Empty),Empty)) : string bstree
- val t7 = insert ((7,"beeb"), t6);
val t7 =
  Node
    ((5,"bob"),
     Node
       ((2,"soo"),Node ((1,"too"),Empty,Empty),Node ((3,"foo"),Empty,Empty)),
     Node
       ((7,"beeb"),Node ((6,"top"),Empty,Empty),Node ((9,"sob"),Empty,Empty)))
  : string bstree
- val t8 = insert ((11,"biib"), t7);
val t8 =
  Node
    ((5,"bob"),
     Node
       ((2,"soo"),Node ((1,"too"),Empty,Empty),Node ((3,"foo"),Empty,Empty)),
     Node
       ((7,"beeb"),Node ((6,"top"),Empty,Empty),
        Node ((9,"sob"),Empty,Node ((11,"biib"),Empty,Empty))))
  : string bstree
- 
- val t9 = delete (7, t8);
val t9 =
  Node
    ((5,"bob"),
     Node
       ((2,"soo"),Node ((1,"too"),Empty,Empty),Node ((3,"foo"),Empty,Empty)),
     Node
       ((9,"sob"),Node ((6,"top"),Empty,Empty),Node ((11,"biib"),Empty,Empty)))
  : string bstree
- val t10 = delete (5, t9);
val t10 =
  Node
    ((6,"top"),
     Node
       ((2,"soo"),Node ((1,"too"),Empty,Empty),Node ((3,"foo"),Empty,Empty)),
     Node ((9,"sob"),Empty,Node ((11,"biib"),Empty,Empty))) : string bstree
*)

