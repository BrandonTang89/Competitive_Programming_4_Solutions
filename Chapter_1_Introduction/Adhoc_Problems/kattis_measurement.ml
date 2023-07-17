(*Kattis - measurement
   A much easier version of the kattis problem units. We just convert the source to the smallest
   unit then back to the desired unit. Note we need to print the float to roughly 10+ dp to AC.
*)
open Scanf
open Printf 

let ln = read_line()
let words = String.split_on_char ' ' ln

let (n::srcc::inn::destc::_) = words

let convert = function
  | "thou" -> "th"
  | "inch" -> "in"
  | "foot" -> "ft"
  | "yard" -> "yd"
  | "chain" -> "ch"
  | "furlong" -> "fur"
  | "mile" -> "mi"
  | "league" -> "lea"
  | shortForm -> shortForm
let src = convert srcc
let dest = convert destc
let n = float_of_int (int_of_string n)

let next = function
  | "th" -> (1, "th")
  | "in" -> (1000, "th")
  | "ft" -> (12, "in")
  | "yd" -> (3, "ft")
  | "ch" -> (22, "yd")
  | "fur" -> (10, "ch")
  | "mi" -> (8, "fur")
  | "lea" -> (3, "mi")
  | _ -> raise (Failure "Invalid unit on next")

let prev = function
  | "th" -> (1.0/.1000.0, "in")
  | "in" -> (1.0/.12.0, "ft")
  | "ft" -> (1.0/.3.0, "yd")
  | "yd" -> (1.0/.22.0, "ch")
  | "ch" -> (1.0/.10.0, "fur")
  | "fur" -> (1.0/.8.0, "mi")
  | "mi" -> (1.0/.3.0, "lea")
  | _ -> raise (Failure "Invalid unit on prev")

let rec convertToTh curUnit curVal = 
  let (factor, nextUnit) = next curUnit in
  let nextVal = curVal *. (float_of_int factor) in
  if nextUnit = "th" then nextVal else convertToTh nextUnit nextVal

let rec convertFromTh curUnit curVal targetUnit =
  if curUnit = targetUnit then curVal else
  let (factor, nextUnit) = prev curUnit in
  let nextVal = curVal *. factor in
  convertFromTh nextUnit nextVal targetUnit;;

printf "%.20f\n" (convertFromTh "th" (convertToTh src n) dest)