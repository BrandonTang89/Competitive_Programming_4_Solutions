-- Kattis - stararrangements
-- Finally some easy stuff for Haskell
-- Time: O(n), Space: O(n)
import Control.Monad
solve :: Int -> [(Int, Int)]
solve s = filter f [(i, j) | i <- [2..s-1], j <- [i-1, i]]
    where f (i, j) = (s `mod` (i+j)) == 0 || (s `mod` (i+j)) == i

main :: IO()
main = do
    l <- getLine
    putStrLn(l ++ ":")
    let s = read l :: Int
    let arr = solve s

    let arr' = map (\(i, j) -> show i ++ "," ++ show j ++ "\n") arr
    putStr $ concat arr'
