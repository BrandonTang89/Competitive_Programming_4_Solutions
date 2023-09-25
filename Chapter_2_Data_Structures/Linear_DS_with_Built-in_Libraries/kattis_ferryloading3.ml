(*Kattis - ferryloading3
  This is an example of the wrong type of question to use a functional lanugage for smh.
  It is just a dirty fat tail recursive function with extra things.
*)
open Printf
open Scanf
open List
let tc = scanf "%d\n" (fun x -> x);;

let rec parseInput xs k n = 
  if k = 0 then xs
  else let (time, side) = scanf "%d %s\n" (fun x y -> (x, y)) in
       if side = "left" then parseInput ((time, n-k, 0) :: xs) (k-1) n
       else parseInput ((time, n-k, 1) :: xs) (k-1) n;;

let rec printList xs =
match xs with
| [] -> printf "\n"
| (x::xs) -> let (t, i, p) = x in printf "%d %d %d\n" t i p; printList xs;;

let rec update t n arr xs =
  if n = 0 then (arr, xs)
  else
    match xs with
    | [] -> (arr, [])
    | (x::xs) -> arr.(x) <- t; 
    update t (n-1) arr xs;;

for t = 1 to tc do
  let (n, t, m) = scanf "%d %d %d\n" (fun x y z -> (x, y, z)) in
  let xs = parseInput [] m m in

  let rec solve arr xs time pos left right =
    if length xs = 1 && left = [] && right = [] then 
      for i = 0 to m - 1 do
        printf "%d\n" arr.(i)
      done
    else 
      let (curt, i, p) = hd xs in
      if curt <= time then
        if p = 0 then solve arr (tl xs) (time) pos (left@[i]) right
        else solve arr (tl xs) (time) pos left (right@[i])
      else
        if pos = 0 then
          if left != [] || right != [] then 
            let (narr, nleft) = update (time+t) n arr left in
            solve narr xs (time+t) 1 nleft right
          else solve arr xs curt 0 [] []
        else
          if left != [] || right != [] then 
            let (narr, nright) = update (time+t) n arr right in
            solve narr xs (time+t) 0 left nright
          else solve arr xs curt 1 [] []
        in 
  solve (Array.make m 0) (rev ((10000000,-1,-1) :: xs)) 0 0 [] [];
  printf "\n";

done;;

