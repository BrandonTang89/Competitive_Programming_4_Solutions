(*Kattis - heartrate
  Basic stuff, getting used to the ocaml syntax...
*)
open Scanf
open Printf

let (tc: int) = scanf "%d\n" (fun x -> x);;

for i = 1 to tc do 
  let (b, p) = scanf "%d %f\n" (fun x y -> (x, y)) in
  let bpm = 60.0 *. (float_of_int b) /. p in
  let min_abpm = 60.0/. (p /. float_of_int (b-1)) in
  let max_abpm = 60.0/. (p /. float_of_int (b+1)) in

  printf "%f %f %f\n" (min_abpm) (bpm) (max_abpm)
  done