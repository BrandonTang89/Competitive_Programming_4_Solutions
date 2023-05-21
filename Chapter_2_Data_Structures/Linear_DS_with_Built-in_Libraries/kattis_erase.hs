-- Kattis - erase
-- Easy
main :: IO()
main = interact(solve . lines)

solve :: [String] -> String
solve [n, a, b] = let n' = (read n :: Int) `mod` 2
                  in if all (\(x, y) -> if (n' == 0) then (x==y) else (x/=y)) (zip a b) then "Deletion succeeded" else "Deletion failed"
solve _ = error "error"