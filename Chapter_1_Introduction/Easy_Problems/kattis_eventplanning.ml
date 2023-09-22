(*Kattis - eventplanning
  Supposedly quite easy. It is just non-trivial to take input in ocaml. Remember that we need to exactly match the input format,
  including whitespace. Also, since IO has side effects, the order of execution matters. 
  So we need to do a weird thing with the let x = scanf ... before immediately using x.
*)
open Scanf
open Printf

let (n, b, h, w) = scanf "%d %d %d %d\n" (fun n b h w -> (n, b, h, w));;
let rec parseList k = 
  if k = 1 then [scanf "%d\n" (fun x -> x)]
  else 
    let x = (scanf "%d " (fun x -> x))
    in x :: parseList (k-1);;

let maximum l = List.fold_left max 0 l;;
let checkList l =
  if maximum l >= n then true
  else false;;

let curBest = ref 1000000000;; (*Best price so far*)

for t = 1 to h do

  let p = scanf "%d\n" (fun p -> p) in
  let l = parseList w in
  if checkList l && p*n <= b then
    curBest := min !curBest (p*n);
done;; 

if !curBest = 1000000000 then printf "stay home\n"
else printf "%d\n" !curBest;;