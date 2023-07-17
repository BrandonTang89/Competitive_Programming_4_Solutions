(*Kattis - drunkvigenere
  Easy stuff. Sometimes doing too much easy stuff makes one feel bad but doing the hard stuff is
  too hard...
*)
let shiftforward (src: char) (amt: char) = 
  Char.chr ((Char.code src - Char.code 'A' + (Char.code amt - Char.code 'A')) mod 26 + Char.code 'A')

let shiftbackward (src: char) (amt: char) = 
  Char.chr ((Char.code src - Char.code 'A' - (Char.code amt - Char.code 'A') + 26) mod 26 + Char.code 'A')

let plain = read_line()
let key = read_line()

let rec solve p k = match (p, k) with
| ([], []) -> print_newline()
| ([x], [y]) -> print_char (shiftbackward x y); print_newline()
| (x::x'::xs, y::y'::ys) -> print_char (shiftbackward x y); print_char (shiftforward x' y'); solve xs ys
| _ -> failwith "invalid input"

let () = solve (List.of_seq (String.to_seq plain)) (List.of_seq (String.to_seq key))