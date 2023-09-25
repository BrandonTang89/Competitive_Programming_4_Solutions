(*Kattis - backspace
  Relatively simple but boring tail recursive function.*)
open Scanf
open Printf
open List

let s = scanf "%s" (fun x -> x);;

let rec solve cur ys =
  match ys with
  | [] -> rev cur
  | (x :: xs) -> if x = '<' then solve (tl cur) xs else solve (x :: cur) xs;;
let explode s = List.init (String.length s) (String.get s);;

printf "%s\n" (String.of_seq (List.to_seq (solve [] (explode s))));;