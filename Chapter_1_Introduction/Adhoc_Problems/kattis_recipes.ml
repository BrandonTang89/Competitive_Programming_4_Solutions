(*Kattis - recipes
  Relatively straightforward. I realise parsing with a recursive function is relatively useful.
*)
open Scanf
open Printf
let tc = scanf "%d\n" (fun x -> x);;
for t = 1 to tc do
  let (n, p, d) = scanf "%d %d %d\n" (fun x y z -> (x, y, z)) in
  let scalefactor = (float_of_int d) /. (float_of_int p) in
  let rec parseList k =
    if k = 0 then []
    else
      let (name, a, b) = scanf "%s %f %f\n" (fun x y z -> (x, y, z)) in
      (name, a, b ):: parseList (k - 1)
  in

  let xs = parseList n in
  let mainIngredient = List.hd (List.filter (fun (name, a, b) -> b = 100.0) xs) in
  let (_, mainIngredientWeight, _) = mainIngredient in
  let scaledWeight = mainIngredientWeight *. scalefactor in

  printf "Recipe # %d\n" t;
  List.iter (fun (name, a, b) -> printf "%s %.1f\n" name (scaledWeight *. b /. 100.0)) xs;
  printf "----------------------------------------\n"

done;;