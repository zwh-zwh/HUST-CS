datatype tree = Empty | Node of tree * int * tree;

*(\*第一题\*)*

fun split [] = ([],0,[])

 |  split [*x*] = ([],x,[])

 |  split (*x*::L) = 

  let 

​    val (L1,*y*,L2) = split L

  in 

​    if (length(L1)>length(L2)) then

​      (L1,x,y::L2)

​    else

​      (y::L1,x,L2)

  end;

fun listToTree [] = Empty

 |  listToTree (L) =

  let 

​    val (L1,*x*,L2) = split(L)

  in 

​    Node(listToTree(L1),x,listToTree(L2))

  end;





*(\*第二题\*)*

fun revT Empty = Empty

 |  revT (Node(*t1*,*x*,*t2*)) = Node(revT(t2),x,revT(t1));

 *(\*假设树的总节点数为n，则work(n) = O(n)。而span和树的深度有关，span = O(d)\*)*



*(\*第三题\*)*

fun binarySearch (Empty,*i*) = false

 |  binarySearch (Node(*t1*,*x*,*t2*),*i*) = 

  case Int.compare(x, i) of

​    GREATER => binarySearch(t1,i)

​    | EQUAL => true

​    | LESS => binarySearch(t2,i);



*(\*第四题\*)*

fun treecompare (Empty,Empty) = EQUAL

 |  treecompare (Empty,*t*) = LESS

 |  treecompare (*t*,Empty) = GREATER

 |  treecompare (Node(*t0*,*x*,*t1*),Node(*t2*,*y*,*t3*)) = Int.compare(x,y);



fun SwapDown Empty = Empty

 | SwapDown (Node(Empty,*x*, Empty)) = Node(Empty,x, Empty)

 | SwapDown (Node(Empty, *x*, R)) =

  let

​    val Node(*t1*, *r*, *t2*) = R

  in

​    case treecompare (Node(Empty, x, R), R) of

​      GREATER => Node(Empty,r,SwapDown(Node(t1,x,t2)))

​      | *_* => Node(Empty, x, R)

  end

 | SwapDown (Node(L, *x*, Empty)) =

  let

​    val Node(*t1*, *l*, *t2*) = L

  in

​    case treecompare (Node(L, x, Empty), L) of

​      GREATER => Node(SwapDown(Node(t1,x,t2)), l, Empty)

​      | *_* => Node(L, x, Empty)     

  end

 | SwapDown (Node(Node(1l,*y1*,1r),*x*,Node(2l,*y2*,2r))) =

  case treecompare(Node(1l,y1,1r),Node(2l,y2,2r)) of

​    GREATER => 

​      if x>y2 then 

​        Node(Node(1l,y1,1r),y2,SwapDown(Node(2l,x,2r)))

​      else Node(Node(1l,y1,1r),x,Node(2l,y2,2r))

​    | *_* => 

​      if x>y1 then 

​        Node(SwapDown(Node(1l,x,1r)),y1,Node(2l,y2,2r)))

​      else Node(Node(1l,y1,1r),x,Node(2l,y2,2r));



fun heapify Empty = Empty

 | heapify (Node(L, *x*, R)) = SwapDown(Node(heapify(L), x , heapify(R)));