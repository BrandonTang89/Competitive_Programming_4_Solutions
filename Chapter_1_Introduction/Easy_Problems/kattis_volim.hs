-- Kattis - volim
-- Some slightly nontrivial parsing happening, the actual solving is quite standard
main :: IO()
main = interact (show . parse . lines)

parse :: [String] -> Int
parse (k:n:xs) = solve 0 (read k - 1) (map f xs) 
                where f x = (read t, o) 
                        where t:o:[] = words x
parse _ = error "error"

solve :: Int -> Int -> [(Int, String)] -> Int
solve cTime cPer ((t,o):xs) = if (cTime + t >= 210) then (cPer+1) else solve (cTime + t) (mod (cPer + (if o == "T" then 1 else 0)) 8) xs
solve _ _ _ = error "error"