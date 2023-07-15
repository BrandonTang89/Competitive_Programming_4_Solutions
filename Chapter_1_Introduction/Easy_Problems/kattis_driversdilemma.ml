(*Kattis - driversdilemma
  My first ocaml problem here. Feels like haskell with easier IO but sketchy error messages.*)
open Scanf
open Printf
let (c, x, m) = scanf "%f %f %f\n" (fun c x m -> (c/.2.0, x, m))

let xs = List.init (6) (fun _ -> scanf "%f %f\n" (fun a b -> (a, b)))

let check (d:float) ((speed : float), (eff : float))  = 
  let t = m /. speed in
  let fuel_used = t *. x +. m /. eff in
  if fuel_used > c then d else speed
  
let ans = List.fold_left (check : float -> float * float -> float ) (-1.0) xs 

let () = if ans < 0.0 then printf "NO\n" else printf "YES %d\n" (int_of_float ans)