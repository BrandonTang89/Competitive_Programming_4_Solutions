(*Kattis - sok
  Simple math. But again, doing floating point arithmetic in Ocaml requires specific operators
*)
open Scanf
open Printf
let (a, b, c) = scanf "%e %e %e\n" (fun a b c -> (a, b, c));;
let (i, j, k) = scanf "%e %e %e\n" (fun i j k -> (i, j, k));;

let process x y z xx yy zz = 
  let quant = min (x /. xx) (min (y /. yy) (z /. zz)) in
  (x -. xx *. quant, y -. yy *. quant, z -. zz *. quant, quant);;

let (a, b, c, quant) = process a b c i j k in
printf "%f %f %f\n" a b c;