(*Kattis - prerequisites
  Make some use of sets (binary serach trees) to test for membership.
  A bunch of work to ensure that the IO is settled properly, especially regarding white space.
  *)
open Scanf 
open Printf
module SS = Set.Make(Int);;
let rec parseList n = 
  if n = 0 then (
    scanf "\n" (fun () -> ()) ();
    []
  )
  else if n = 1 then [scanf "%d\n" (fun x -> x)]
  else 
    let x = scanf "%d " (fun x -> x) in
    x :: parseList (n-1)
let k = ref (scanf "%d " (fun x -> x));;

let rec countmembers s courseList c =
  match courseList with
  | [] -> c
  | h::t -> 
    if SS.mem h s then countmembers s t (c+1)
    else (countmembers s t c)
  ;;

while !k != 0 do
  let possible = ref true in
  let m = scanf "%d\n" (fun x -> x) in
  let s = SS.empty in 
  let s = List.fold_right SS.add (parseList !k) s in

  for i = 1 to m do
    let total = scanf "%d " (fun x -> x) in
    let required = scanf "%d " (fun x -> x) in
    let courseList = parseList total in

    possible := (!possible) && ((countmembers s courseList 0) >= required);

  done;
  if !possible then printf "yes\n"
  else printf "no\n";
  k := (scanf "%d" (fun x -> x));

  if !k != 0 then let _ = scanf " " (fun () -> ()) () in ();
done;;