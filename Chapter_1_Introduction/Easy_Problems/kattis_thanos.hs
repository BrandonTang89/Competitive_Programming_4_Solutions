-- Kattis - thanos
-- Supposedly easy, the binary search was completely unnecessary
-- Time: O(1), Space: O(1)
import Control.Monad
solve :: Integer -> Integer -> Integer -> String
solve p r f = show $ binSearch 0 30 p r f

binSearch :: Integer -> Integer -> Integer -> Integer -> Integer -> Integer
binSearch le ri p r f
    | le == ri = le
    | otherwise = let m = (le + ri) `div` 2
                      t = p * (r ^ m)
                  in if t <= f then binSearch (m+1) ri p r f  -- go more years
                               else binSearch le m p r f -- at least as little as m years

main :: IO()
main = do
    l <- getLine
    let t = read l :: Int
    replicateM_ t (do
        l <- getLine
        let [p, r, f] = map read (words l) :: [Integer]
        putStrLn (solve p r f))
