-- Kattis - sequence
-- Constructive problem: Just taking the sequence of the powers of 2 starting from 2^0 = 1
main = interact (solve . read)

solve :: Int -> String
solve n = 
    let xs = scanl (*) 1 (repeat 2)
        xs' = takeWhile (<= n) xs
        xs'' = map show xs'
    in show (length xs'') ++ "\n" ++ unwords xs''