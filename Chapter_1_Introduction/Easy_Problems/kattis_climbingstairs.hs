-- Kattis - climbingstairs
-- Simple to implement, abit tricky to ensure correctness.
-- Try both combinations of going to office first and going to desk first, taking the minimum of the two.
-- Time: O(1), Space: O(1)
main :: IO()
main = interact(show . solve . map read . words . head . lines)

solve :: [Int] -> Int
solve [n, r, k] = min (officefirst n r k) (deskfirst n r k)
solve _ = error "solve error"

officefirst :: Int -> Int -> Int -> Int
officefirst k d o = let a = o + abs (o - d)
                    in if k <= a then a + d else k + ((k-a) `mod` 2) + d
        
deskfirst :: Int -> Int -> Int -> Int
deskfirst k d o = if k <= d then (d + abs(d - o) + o) else (k + (k-d) `mod` 2 + abs(d - o) + o)