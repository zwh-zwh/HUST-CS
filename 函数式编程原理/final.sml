(*第一题*)
fun take( [ ], i) = [ ]
    | take(x::xs, i) = if i > 0 then x::take(xs, i-1)
 			   else [ ];
fun rtake ([ ], _, taken) = taken
    | rtake (x::xs,i,taken) =  if i>0 then rtake(xs, i-1, x::taken)
		  	   else taken;
(*功能：take函数是从表中取出i个元素，返回正序新表；
rtake是从表中取出i个元素放到taken中，taken中这i个元素顺序与原来相反
性能：两函数的Work均为O（n）*)


(*第二题*)
fun evens [] = []
 | evens (x::L) =
    case Int.compare(0,x mod 2) of
        EQUAL => x::evens(L)
        | _ => evens L;
val a = evens [1,2,3,4];
val b = evens [1,3,5,7];


(*第三题*)
fun toInt (base : int) (digits : int list) : int = 
    case digits of 
        [] => 0   
        | d::digits' => d + base * toInt base digits';
val a = toInt 10 [0,1,2]; 

fun toBase (base : int) (num : int) : int list = 
    case num of 
        0 => []
        | _ => (num mod base) :: toBase (base) (num div base);
val a = toBase 5 42;

fun convert (b1:int,b2:int) (L:int list) : int list =
    toBase (b2) (toInt b1 L);
val a = convert (10,5) [2,4];


    
