-- Kattis - includesorting
-- The n^2 solution here works fine enough. It is a trap to use deriving Eq since we should not match on the last number.
-- Everything else is quite standard.
main :: IO()
main = interact (unlines . map show . solve . map (map read . words) . tail . lines)

data Con = Con Int Int Int Int

instance Eq Con where
    (Con sx tx lx _) == (Con sy ty ly _) = (sx, -tx, -lx) == (sy, -ty, -ly) -- x == y if x does as well as y
instance Ord Con where
    (Con sx tx lx _) <= (Con sy ty ly _) = (sx, -tx, -lx) <= (sy, -ty, -ly) -- x <= y if x does worse (at least as bad) than y

solve :: [[Int]] -> [Int]
solve xs = let cs = [Con s t l i | [s, t, l, i] <- xs]
               getScore (Con s t l i) = i + getPts (length (filter (> (Con s t l i)) cs)) (length (filter (== (Con s t l i)) cs))
               in map getScore cs

getPts :: Int -> Int -> Int
getPts r nr = ((sum [tab (r + 1 + i) | i <- [0..nr-1]] - 1) `div` nr) + 1

tab :: Int -> Int
tab 0 = error "tab 0"
tab 1 = 100
tab 2 = 75
tab 3 = 60
tab 4 = 50
tab 5 = 45
tab 6 = 40
tab 7 = 36
tab 8 = 32
tab 9 = 29
tab 10 = 26
tab 11 = 24
tab 12 = 22
tab 13 = 20
tab 14 = 18
tab 15 = 16
tab 16 = 15
tab 17 = 14
tab 18 = 13
tab 19 = 12
tab 20 = 11
tab 21 = 10
tab 22 = 9
tab 23 = 8
tab 24 = 7
tab 25 = 6
tab 26 = 5
tab 27 = 4
tab 28 = 3
tab 29 = 2
tab 30 = 1
tab _ = 0