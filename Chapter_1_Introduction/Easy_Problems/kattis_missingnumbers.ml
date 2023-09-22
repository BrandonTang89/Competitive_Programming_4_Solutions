(*Ka;ttis - missingnumbers
  Decided to just do this as imperatively as possible...
*)
open Scanf
open Printf
let n = scanf "%d\n" (fun x -> x);;
let perfect = ref true;;
let x = ref 1;;
for i = 1 to n do
  let c = scanf "%d\n" (fun x -> x) in
  while !x < c do
    printf "%d\n" !x;
    perfect := false;
    x := !x + 1;
  done;
  
  x := !x + 1
  done;

if !perfect then
  printf "good job\n";;