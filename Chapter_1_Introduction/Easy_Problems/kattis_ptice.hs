-- Kattis - ptice
-- Wows the infinite list is actually useful
aBest :: [Char]
aBest = ['A', 'B', 'C'] ++ aBest

bBest :: [Char]
bBest = ['B', 'A', 'B', 'C'] ++ bBest

gBest :: [Char]
gBest = ['C', 'C', 'A', 'A', 'B', 'B'] ++ gBest

solve :: [String] -> String
solve [n, s] = let bestNum = maximum [a, b, g]
                   a = sum (zipWith (\x y -> if x == y then 1 else 0) s aBest)
                   b = sum (zipWith (\x y -> if x == y then 1 else 0) s bBest)
                   g = sum (zipWith (\x y -> if x == y then 1 else 0) s gBest)
                in 
                (show bestNum) ++  (if (bestNum == a) then "\nAdrian\n" else "\n") ++ 
                (if (bestNum == b) then "Bruno\n" else "") ++
                (if (bestNum == g) then "Goran\n" else "")
solve _ = error "error"

main :: IO()
main = interact (solve . lines)