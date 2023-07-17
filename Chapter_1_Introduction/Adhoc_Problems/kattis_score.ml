(*Kattis - score
  Mostly straightforward with a fold_left. Note that there can be a difficult to spot bug when doing
  getScores where if we don't extract the first element as a "let x = ..." then the scanf will be
  evalulated after the recusive call so the order of elements in the list will be wrong... Ocaml
  is weird.
*)
open Scanf
open Printf

type time = Time of int * int
let toTime s = Time (s / 60, s mod 60)
let timeFormat (Time (h, m)) = sprintf "%d:%02d" h m

let rec getScores = function
  | 0 -> [('A', 0, 32*60)]
  | k -> let x = scanf "%c %d %d:%d\n" (fun a b c d -> (a, b, c*60 + d)) 
          in x :: getScores (k - 1)
let n = scanf "%d\n" (fun x -> x)
let xs = getScores n;;
let (endHomeLead, hTotalLead, aTotalLead, _) = List.fold_left (fun (homeLead, htime, atime, prevTime) (team, score, time) ->
  let additionalTime = time - prevTime in
  let newHomeLead = homeLead + (if team = 'A' then -score else score) in
  let newHtime = htime + (if homeLead > 0 then additionalTime else 0) in
  let newAtime = atime + (if homeLead < 0 then additionalTime else 0) in
  (newHomeLead, newHtime, newAtime, time)
) (0, 0, 0, 0) xs;;

let hformat = timeFormat (toTime hTotalLead) in
let aformat = timeFormat (toTime aTotalLead) in
printf "%c %s %s\n" (if endHomeLead > 0 then 'H' else 'A') hformat aformat;;