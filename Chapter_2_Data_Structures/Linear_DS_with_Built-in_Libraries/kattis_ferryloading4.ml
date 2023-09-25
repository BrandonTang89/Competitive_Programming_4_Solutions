(*Kattis - ferryloading4
  We parse the input and get 2 lists. Then we do separate calculations to attain the number of
  ferry trips for left and right side then take max.
*)
open Printf
open Scanf

let rec parseInput l r k = 
  if k = 0 then (l, r)
  else let (len, side) = scanf "%d %s\n" (fun x y -> (x, y)) in
       if side = "left" then parseInput (len :: l) r (k-1)
       else parseInput l (len :: r) (k-1);;

let rec solve1 initLength len xs = 
  match xs with
  | [] -> 0
  | (x::xs) -> if x > len then 1 + solve1 initLength initLength (x::xs)
               else solve1 initLength (len-x) xs;;
let tc = scanf "%d\n" (fun x -> x);;

for t = 1 to tc do
  let (l, n) = scanf "%d %d\n" (fun x y -> (x, y)) in
  let l = l*100 in
  let (left, right) = parseInput [] [] n in
  let left = List.rev left in
  let right = List.rev right in

  let r = (solve1 l 0 right) in
  let r = if r = 0 then 0 else (r*2) in
  let le = (solve1 l 0 left) in
  let le = if le = 0 then 0 else (le*2)-1 in
  let ans = max le r in
  printf "%d\n" ans

done;;

