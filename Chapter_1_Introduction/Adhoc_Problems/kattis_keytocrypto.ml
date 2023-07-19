(*Kattis - keytocrypto
  Actually decently nice to do with functional lists. We recusively get the first len(key)
  characters of the message and use the new part of the message as the next key.
*)
open Scanf
open Printf

let moveBack amt src =
  let s = Char.code src - Char.code 'A' in
  let a = Char.code amt - Char.code 'A' in
 Char.chr (Char.code 'A' + (s - a + 26) mod 26)

 let rec drop n xs = match (n, xs) with
 | (0, _) -> xs
 | (_, []) -> []
 | (n, x::xs) -> drop (n-1) xs

 let rec take n xs = match (n, xs) with
| (0, _) -> []
| (_, []) -> []
| (n, x::xs) -> x :: take (n-1) xs

let rec decode key ciphertext =
  let n = List.length key in
  let truncatedCipherText = take n ciphertext in
  let truncatedKey = take (List.length truncatedCipherText) key in
  let newkey = List.map2 moveBack truncatedKey truncatedCipherText in
  let newCipherText = drop n ciphertext in
  if ciphertext == [] then [] else newkey @ decode newkey newCipherText

let () = 
  let cipher = scanf "%s\n" (fun x -> x) in
  let key = scanf "%s\n" (fun x -> x) in

  let cipherList = List.of_seq (String.to_seq cipher) in
  let keyList = List.of_seq (String.to_seq key) in

  let plainList = decode keyList cipherList in
  let plain = List.to_seq plainList |> String.of_seq in

  printf "%s\n" plain