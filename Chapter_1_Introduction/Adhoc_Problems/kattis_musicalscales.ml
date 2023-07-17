(*Kattis - musicalscales
  Easy but tedious. Note that using String.split_on_char also allows for non-empty strings
  so we should filter that out.
  I'm not sure if I'm dumb or something but I couldn't find typical things like drop and dropWhile
  for ocaml lists??
*)
open Printf

let n = read_line();;
let required = read_line();;
let requiredNotes = List.filter (fun x -> x <> "" ) 
(List.sort_uniq compare (String.split_on_char ' ' required));; 

let notes = ["A"; "A#"; "B"; "C"; "C#"; "D"; "D#"; "E"; "F"; "F#"; "G"; "G#"]
let infNotes = (notes @ notes @ notes @ notes);;

let rec dropWhile p = function
  | [] -> []
  | x :: xs -> if p x then dropWhile p xs else x :: xs

let rec drop n = function
  | [] -> []
  | x :: xs -> if n = 0 then x :: xs else drop (n - 1) xs

let rec zipDrop xs = function
  | [] -> []
  | y :: ys ->
    let nextxs = drop y xs in
    List.hd nextxs :: zipDrop nextxs ys

let rec sublist xs ys = (* is xs a sublist of ys? both sorted*)
  match xs, ys with
  | [], _ -> true
  | _, [] -> false
  | x :: xs, y :: ys -> (x = y && sublist xs ys) || (x > y && sublist (x :: xs) ys)
let scale = [0; 2; 2; 1; 2; 2; 2; 1]
let scales start =
  let no = dropWhile (fun x -> x <> start) infNotes in
  zipDrop no scale

let check note =
  let s = List.sort_uniq compare (scales note) in
  sublist requiredNotes s;;

let possibleScales = List.filter check notes;;

if possibleScales = [] then
  printf "none\n"
else
  List.iter (printf "%s ") possibleScales;