(**KAttis - calories
    Ran into a lot of issues with syntax and operator precedence. Overall this question is 
    just tedious
*)
open Scanf
open Printf

let rec solve() =
  let arr = Array.make 5 0.0 in
  let line = ref (read_line()) in
  while line.contents <> "-" do
    let l = line.contents in
    let (fat, fat_unit, protein, protein_unit, sugar, sugar_unit,
         starch, starch_unit, alcohol, alcohol_unit) = sscanf l "%d%c %d%c %d%c %d%c %d%c"
         (fun a b c d e f g h i j -> (float_of_int a, b, float_of_int c, d, float_of_int e, f,
                                      float_of_int g, h, float_of_int i, j)) in
    let percent = (if fat_unit == '%' then fat else 0.0) +.
                  (if protein_unit == '%' then protein else 0.0) +.
                  (if sugar_unit == '%' then sugar else 0.0) +.
                  (if starch_unit == '%' then starch else 0.0) +.
                  (if alcohol_unit == '%' then alcohol else 0.0) in
    
    let caloriesCounted =
      (if fat_unit == 'C' then fat else if fat_unit == 'g' then fat *. 9.0 else 0.0) +.
      (if protein_unit == 'C' then protein else if protein_unit == 'g' then protein *. 4.0 else 0.0) +.
      (if sugar_unit == 'C' then sugar else if sugar_unit == 'g' then sugar *. 4.0 else 0.0) +.
      (if starch_unit == 'C' then starch else if starch_unit == 'g' then starch *. 4.0 else 0.0) +.
      (if alcohol_unit == 'C' then alcohol else if alcohol_unit == 'g' then alcohol *. 7.0 else 0.0) in

    let totalCalories = caloriesCounted *. 100.0 /. (100.0 -. percent) in

    if fat_unit == 'g' then arr.(0) <- arr.(0) +. fat *. 9.0
    else if fat_unit == 'C' then arr.(0) <- arr.(0) +. fat
    else if fat_unit == '%' then arr.(0) <- arr.(0) +. fat *. totalCalories /. 100.0;

    if protein_unit == 'g' then arr.(1) <- arr.(1) +. protein *. 4.0
    else if protein_unit == 'C' then arr.(1) <- arr.(1) +. protein
    else if protein_unit == '%' then arr.(1) <- arr.(1) +. protein *. totalCalories /. 100.0;

    if sugar_unit == 'g' then arr.(2) <- arr.(2) +. sugar *. 4.0
    else if sugar_unit == 'C' then arr.(2) <- arr.(2) +. sugar
    else if sugar_unit == '%' then arr.(2) <- arr.(2) +. sugar *. totalCalories /. 100.0;

    if starch_unit == 'g' then arr.(3) <- arr.(3) +. starch *. 4.0
    else if starch_unit == 'C' then arr.(3) <- arr.(3) +. starch
    else if starch_unit == '%' then arr.(3) <- arr.(3) +. starch *. totalCalories /. 100.0;

    if alcohol_unit == 'g' then arr.(4) <- arr.(4) +. alcohol *. 7.0
    else if alcohol_unit == 'C' then arr.(4) <- arr.(4) +. alcohol
    else if alcohol_unit == '%' then arr.(4) <- arr.(4) +. alcohol *. totalCalories /. 100.0;

    line := read_line();
    (*printf "%f %f %f %f %f\n" arr.(0) arr.(1) arr.(2) arr.(3) arr.(4);*)
  done;

  let sum = arr.(0) +. arr.(1) +. arr.(2) +. arr.(3) +. arr.(4) in

  if sum > 0.0 then
    (printf "%d%%\n" (int_of_float (arr.(0) *. 100.0 /. sum +. 0.5));
    solve(););;

solve()