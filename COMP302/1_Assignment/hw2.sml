(* HOMEWORK 1 : COMP 302 Winter 2012
    
    Date: 14/01/2012
    Name: Jonathan Fokkan
    ID: 260447938

*)

(* Q1 *)
fun sum [] = 0
  | sum (x::xs) = x + sum xs

(* average : int list -> real *)
fun average [] = 0.0
  | average xs = real (sum xs) / real (length xs)

fun variance [] = 0.0
  | variance xs = 
    let
      val mean = average xs
      val difference : real list = map (fn x : int => (mean - real x) * (mean - real x)) xs
      (* A cool different way of writing sum :) *)
      fun sum ys =
          foldr (fn (x,y) => x+y) 0.0 ys
    in
      sum difference / real (length xs)
end

fun stDev xs = Math.sqrt (variance xs)


(* Q2 *)

fun psum xs = 
    let
      fun psum' z []      = []
        | psum' z (y::ys) = (z+y)::(psum' (z+y) ys)
    in
      psum' 0 xs
    end


(* Q3 *)

(* Q3.1 *)
datatype 'a bstree = Empty | Node of (int * 'a) * 'a bstree * 'a bstree

fun height tree =
  let
    fun height' (z:int) Empty = z
      | height' z (Node (_,left, right)) = Int.max (height' (z+1) left,
      height' (z+1) right)
  in
    height' 0 tree
  end

fun balanceFactor Empty                   = 0
  | balanceFactor (Node (_, left, right)) = height left - height right

val t2 = Node ((7,"a"), Node ((3,"b"), Empty, Empty), Node ((9,"c"), Empty, Empty))
val t3 = Node ((2,"f"), Empty, t2)

fun balanced tree = Int.abs (balanceFactor tree) <= 1

(* Q3.2 *)


fun rotLeft (Node (v, Node(vl, LL, LR), R))                         = Node (vl, LL, Node (v, LR, R))

fun rotLeftRight (Node (v, Node (vl, LL, Node (vlr, LRL, LRR)), R)) = Node (vlr,
  Node (vl, LL, LRL), Node (v, LRR, R))

fun rotRight (Node(v, L, Node (vr, RL, RR)))                        = Node (vr, Node (v, L, RL), RR)

fun rotRightLeft (Node (v, L, Node (vr, Node (vrl, RLL, RLR), RR))) = Node (vrl,
  Node (v, L, RLL), Node (vr, RLR, RR))


fun rebalance Empty  = Empty
  | rebalance tree   =
  let
    val L = (fn (Node(_, L, R)) => L) tree
    val R = (fn (Node(_, L, R)) => R) tree
  in
    if balanced tree then
      tree
    else
      if (balanceFactor tree = 2) then
        if (balanceFactor L) >= 0 then
          rotLeft tree
        else
          if (balanceFactor L) = ~1 then
            rotLeftRight tree
          else
            tree(*Impossible*)
      else
          if (balanceFactor R) <= 0 then
            rotRight tree
          else
            if (balanceFactor R) = 1 then
              rotRightLeft tree
            else
              tree (*Impossible*)
  end

(* Q3.3 *)

fun insert (v, Empty) = Node (v, Empty, Empty)
  | insert ((n : int, s), (Node ( (n2, s2), L, R )))= 
  if n < n2 then
    rebalance (Node ( (n2, s2), insert ( (n, s), L ), R ))
  else
    rebalance (Node ( (n2, s2), L, insert ( (n, s), R ) ))

(* Q3.4 *)

fun delMin Empty = raise Fail "impossible"
  | delMin (Node (v, Empty, Empty)) = (Empty, v)
  | delMin (Node (v, Empty, R))     = (rebalance R, v)
  | delMin (Node (v, L, R))         = 
    let
      val minTree = ((fn (x, y) => x) (delMin L))
      val min     = ((fn (x, y) => y) (delMin L))
    in
      (rebalance (Node (v, minTree, R)), min)
    end

fun delete (n, Empty)     = raise Fail "value not in the tree"
  | delete (key, tree)  = 
    let
      val minNode = ((fn (x, y) => y) (delMin tree))
      val minKey  = (fn (x, y) => x) minNode
      val minTree = (fn (x, y) => x) (delMin tree)
    in
      if minKey = key then
        rebalance minTree
      else
        insert (minNode, delete (key, minTree))
    end


val t1 = insert ((3, "foo") , Empty );
val t2 = insert ((2, "soo") , t1);
val t3 = insert ((1, "too") , t2);
val t4 = insert ((9, "sob"), t3);
val t5 = insert ((5, "bob"), t4); 
val t6 = insert ((6, "top"), t5); 
val t7 = insert ((7,"beeb"), t6);
val t8 = insert ((11,"biib"), t7);
val t9 = delete (7, t8);
val t10 = delete (5, t9);
val t11 = delete (11, t10);

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

