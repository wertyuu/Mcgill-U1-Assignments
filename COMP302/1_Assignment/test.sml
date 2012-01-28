datatype 'a bstree = Empty | Node of (int * 'a) * 'a bstree * 'a bstree

val t2 = Node ((7,"a"), Node ((3,"b"), Empty, Empty), Node ((9,"c"), Empty, Empty))
val t3 = Node ((2,"f"), Empty, t2)

fun height tree =
  let
    fun height' (z:int) Empty = z
      | height' z (Node (_,left, right)) = Int.max (height' (z+1) left,
      height' (z+1) right)
  in
    height' 0 tree
  end

fun test boo tree as (Node ( v as (hell, yea), L as Node ( s as (foo, bar), _, _), _)) = 
  case boo of
       true => height tree
     | false => height L


