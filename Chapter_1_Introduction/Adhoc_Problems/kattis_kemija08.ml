(* Kattis - kemija08
   Relatively easy, just skip 2 letters on encountering a vowel
*)
open Printf
let line = read_line()
let xss = String.split_on_char ' ' line

let isVowel x = 
  if x = 'a' || x = 'e' || x = 'i' || x = 'o' || x = 'u' then true else false
let decodeWord xs =
  let ys = List.of_seq (String.to_seq xs) in
  let rec getWord zs =
    if zs = [] then [] else
      if isVowel (List.hd zs) then List.hd zs :: getWord (List.tl ( List.tl ( List.tl zs))) else
        List.hd zs :: getWord (List.tl zs);
  in
  printf "%s " (String.concat "" (List.map (String.make 1) (getWord ys)))

let () = 
  List.iter decodeWord xss