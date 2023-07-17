(*Kattis - falsesecurity
  Relatively fine, alot of manipulation between string and char list in this question unforunately.
*)
open Printf
let charToMorse = function
  | 'A' -> ".-"
  | 'B' -> "-..."
  | 'C' -> "-.-."
  | 'D' -> "-.."
  | 'E' -> "."
  | 'F' -> "..-."
  | 'G' -> "--."
  | 'H' -> "...."
  | 'I' -> ".."
  | 'J' -> ".---"
  | 'K' -> "-.-"
  | 'L' -> ".-.."
  | 'M' -> "--"
  | 'N' -> "-."
  | 'O' -> "---"
  | 'P' -> ".--."
  | 'Q' -> "--.-"
  | 'R' -> ".-."
  | 'S' -> "..."
  | 'T' -> "-"
  | 'U' -> "..-"
  | 'V' -> "...-"
  | 'W' -> ".--"
  | 'X' -> "-..-"
  | 'Y' -> "-.--"
  | 'Z' -> "--.."
  | '_' -> "..--"
  | ',' -> ".-.-"
  | '.' -> "---."
  | '?' -> "----"
  | _ -> failwith "Invalid character"
let morseToChar = function
  |".-" -> 'A'
  |"-..." -> 'B'
  |"-.-." -> 'C'
  |"-.." -> 'D'
  |"." -> 'E'
  |"..-." -> 'F'
  |"--." -> 'G'
  |"...." -> 'H'
  |".." -> 'I'
  |".---" -> 'J'
  |"-.-" -> 'K'
  |".-.." -> 'L'
  |"--" -> 'M'
  |"-." -> 'N'
  |"---" -> 'O'
  |".--." -> 'P' 
  |"--.-" -> 'Q'
  |".-." -> 'R'
  |"..." -> 'S'
  |"-" -> 'T'
  |"..-" -> 'U'
  |"...-" -> 'V'
  |".--" -> 'W'
  |"-..-" -> 'X'
  |"-.--" -> 'Y'
  |"--.." -> 'Z'
  |"..--" -> '_'
  |".-.-" -> ','
  |"---." -> '.'
  |"----" -> '?'
  | _ -> failwith "Invalid morse code"

let rec take n xs = match (n, xs) with
| (0, _) -> []
| (_, []) -> []
| (n, x::xs) -> x :: take (n-1) xs

let rec drop n xs = match (n, xs) with
| (0, _) -> xs
| (_, []) -> []
| (n, x::xs) -> drop (n-1) xs

let rec splitBy xs ys =  match (xs, ys) with
| ([], _) -> []
| (x::xs, ys) -> take x ys :: splitBy xs (drop x ys)
let string_of_chars chars = 
  let buf = Buffer.create 16 in
  List.iter (Buffer.add_char buf) chars;
  Buffer.contents buf

let rec solve() =
  try
    let message = read_line () in
    let morseList = List.map charToMorse (List.of_seq (String.to_seq message)) in
    let lengthList = List.map String.length morseList in
    let revLengthList = List.rev lengthList in
    let outcome = splitBy revLengthList (List.of_seq (String.to_seq (List.fold_right (^) morseList "" ))) in
    let outcome2 = List.map (fun zs -> morseToChar (string_of_chars(zs))) outcome in
    let outcome3 = string_of_chars outcome2 in

    printf "%s\n" outcome3;
    solve()
    
  with
    End_of_file -> ()

let () = solve()
