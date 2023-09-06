-- Kattis - happyprime
-- Not exactly the best problem for haskell. We ideally should use a hashmap to store the stuff
-- that we have seen before and cycle detect. Luckily just using a list happens to be fast enough
main :: IO()
main = interact(unlines . map (solve . words) . tail . lines)

primes :: [Int]
primes = filterPrime [2..] where
  filterPrime (p:xs) =
    p : filterPrime [x | x <- xs, x `mod` p /= 0]

solve :: [String] -> String
solve [t, n] = t ++ " " ++ n ++ " " ++ (if isPrime (read n) && isHappy (read n) [] then "YES" else "NO")

isPrime :: Int -> Bool
isPrime n = n `elem` takeWhile (<= n) primes

isHappy :: Int ->[Int] -> Bool
isHappy 1 _ = True
isHappy n xs  = (n `notElem` xs) && isHappy (sum (map (^ 2) (digits n))) (n : xs)

digits :: Int -> [Int]
digits 0 = []
digits n = digits (n `div` 10) ++ [n `mod` 10]