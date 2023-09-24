(*Kattis - anotherbrick
  Feels abit dirty just making a finite automaton tail recursive function, but unfortunately
  this feels like the best way forward...
*)
open Scanf
open Printf

let (h, w, n) = scanf "%d %d %d\n" (fun h w n -> (h, w, n));;

let rec parseList k =
  if k = 1 then [scanf "%d\n" (fun x -> x)]
  else let x = scanf "%d " (fun x -> x)
       in x :: parseList (k - 1);;

let xs = parseList n;; 

let rec solve h w c xs =
  if c = 0 && h = 0 then true
  else if c = 0 then solve (h - 1) w w xs
  else if xs = [] then false
  else let x = List.hd xs in
       if x <= c then solve h w (c - x) (List.tl xs)
       else false;;

if solve h w 0 xs then printf "YES\n"
else printf "NO\n";;