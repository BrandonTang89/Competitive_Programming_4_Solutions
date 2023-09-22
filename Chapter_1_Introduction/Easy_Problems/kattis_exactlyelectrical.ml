(*Kattis - Exactlyelectrical
  Straightforward O(1) math.
  *)
open Scanf
open Printf
let (x1, y1) = scanf "%d %d\n" (fun x y -> (x, y));;
let (x2, y2) = scanf "%d %d\n" (fun x y -> (x, y));;
let t = scanf "%d\n" (fun x -> x);;

let manDist x1 y1 x2 y2 = abs (x1 - x2) + abs (y1 - y2);;
if manDist x1 y1 x2 y2 <= t && (manDist x1 y1 x2 y2 - t) mod 2 == 0 then
    printf "Y\n"
else
    printf "N\n"
;;